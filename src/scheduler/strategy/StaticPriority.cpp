/*******************************************************************************
 * This file is part of openWNS (open Wireless Network Simulator)
 * _____________________________________________________________________________
 *
 * Copyright (C) 2004-2009
 * Chair of Communication Networks (ComNets)
 * Kopernikusstr. 5, D-52074 Aachen, Germany
 * phone: ++49-241-80-27910,
 * fax: ++49-241-80-22242
 * email: info@openwns.org
 * www: http://www.openwns.org
 * _____________________________________________________________________________
 *
 * openWNS is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License version 2 as published by the
 * Free Software Foundation;
 *
 * openWNS is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/

#include <WNS/scheduler/strategy/staticpriority/SubStrategyInterface.hpp>
#include <WNS/scheduler/strategy/StaticPriority.hpp>
#include <WNS/scheduler/strategy/Strategy.hpp>
#include <WNS/scheduler/strategy/SchedulerState.hpp>
#include <WNS/scheduler/SchedulingMap.hpp>
#include <WNS/scheduler/SchedulerTypes.hpp>
#include <WNS/pyconfig/View.hpp>

#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <set>

using namespace wns::scheduler;
using namespace wns::scheduler::strategy;
using namespace wns::scheduler::strategy::staticpriority;

STATIC_FACTORY_REGISTER_WITH_CREATOR(StaticPriority,
				     StrategyInterface,
				     "StaticPriority",
				     wns::PyConfigViewCreator);

StaticPriority::StaticPriority(const wns::pyconfig::View& config):
	Strategy(config),
	numberOfPriorities(config.get<int>("numberOfPriorities")),
	subStrategies(),
	resourceUsage(0.0)
{
	MESSAGE_SINGLE(NORMAL, logger, "StaticPriority() instance created. numberOfPriorities="<<numberOfPriorities);
	// TODO: loop over all priorities and initialize subStrategies
	assure(numberOfPriorities == config.len("subStrategies"),"numberOfPriorities="<<numberOfPriorities<<" != "<<config.len("subStrategies"));
	for (int priority=0; priority<numberOfPriorities; ++priority) {
	  wns::pyconfig::View substrategyView = config.getView("subStrategies",priority);
	  std::string substrategyName = substrategyView.get<std::string>("__plugin__");
	  MESSAGE_SINGLE(NORMAL, logger, "subStrategy["<<priority<<"]="<<substrategyName);
	  wns::scheduler::strategy::staticpriority::SubStrategyInterface* substrategy = NULL;
	  if (substrategyName.compare("NONE")!=0) {
	    // create the subscheduling strategy for this priority:
	    wns::scheduler::strategy::staticpriority::SubStrategyCreator* subStrategyCreator = wns::scheduler::strategy::staticpriority::SubStrategyFactory::creator(substrategyName);
	    substrategy = subStrategyCreator->create(substrategyView);
	  } else {
	    substrategy = NULL;
	  }
	  subStrategies.push_back(substrategy);
	  //subStrategies[priority] = substrategy;
	} // for all priorities
}

StaticPriority::~StaticPriority()
{
  for (int priority=0; priority<numberOfPriorities; ++priority) {
    if (subStrategies[priority]!=NULL) { delete subStrategies[priority]; }
  }
}

float
StaticPriority::getResourceUsage() const
{
	return resourceUsage;
}

// inherited by base class Strategy to do first-time initialization:
void
StaticPriority::onColleaguesKnown()
{
	Strategy::onColleaguesKnown(); // must be done in every derived method
	MESSAGE_SINGLE(NORMAL, logger,"StaticPriority::onColleaguesKnown():");
	assure(numberOfPriorities==colleagues.registry->getNumberOfPriorities(),"numberOfPriorities="<<numberOfPriorities<<" but registry->getNumberOfPriorities()="<<colleagues.registry->getNumberOfPriorities());
	SchedulerStatePtr schedulerState = getSchedulerState();
	// priority is out of [0..MaxPriority-1]:
	for (int priority=0; priority<numberOfPriorities; ++priority) {
	  MESSAGE_SINGLE(NORMAL, logger, "initializing subStrategy["<<priority<<"]");
	  wns::scheduler::strategy::staticpriority::SubStrategyInterface* substrategy = subStrategies[priority];
	  assure(substrategy!=NULL, "The substrategy["<<priority<<"] is not accessible");
	  substrategy->setColleagues(this, colleagues.queue, colleagues.registry);
	  //schedulerState->currentSubStrategyState = ...;
	}
}

//void
//StaticPriority::doStartScheduling(int fChannels, int maxBeams, simTimeType slotLength)
StrategyResult
StaticPriority::doStartScheduling(SchedulerStatePtr schedulerState,
				  SchedulingMapPtr schedulingMap)
{
	assure(numberOfPriorities>0,"illegal numberOfPriorities="<<numberOfPriorities);

	MESSAGE_SINGLE(NORMAL, logger, "StaticPriority::doStartScheduling():"
		       << " numberOfPriorities="<<numberOfPriorities);

	// prepare result datastructure:
	MapInfoCollectionPtr mapInfoCollection = MapInfoCollectionPtr(new wns::scheduler::MapInfoCollection);
	StrategyResult strategyResult(schedulingMap,mapInfoCollection);
	this->resourceUsage=0.0;

	MESSAGE_SINGLE(NORMAL, logger, "doStartScheduling(): userSelection. getDL=" << schedulerState->isDL << ", isTX=" << schedulerState->isTx << ", schedulerSpot="<<wns::scheduler::SchedulerSpot::toString(schedulerState->schedulerSpot));

	// user selection
	UserSet	allUsers;
	//if ( !(schedulerState->isDL) && !schedulerState->isTx )
	if ( schedulerState->schedulerSpot == wns::scheduler::SchedulerSpot::ULMaster() )
	{       // I am master scheduler for uplink (RS-RX)
		allUsers = colleagues.registry->getActiveULUsers();
		//allUsers = colleagues.queue->getQueuedUsers(); // soon possible with new queueInterface [rs]
		MESSAGE_SINGLE(NORMAL, logger, "doStartScheduling(): Master Rx-Scheduling...");
	} else {
		// get all users which have PDUs in their queues
		allUsers = colleagues.queue->getQueuedUsers();
		MESSAGE_SINGLE(NORMAL, logger, "doStartScheduling(): Slave UL-Scheduling or Master DL-Scheduling...");
	}

	MESSAGE_SINGLE(NORMAL, logger, "doStartScheduling(): allUsers.size()="<<allUsers.size()<<": Users="<<printUserSet(allUsers));
	// filter reachable users
	UserSet activeUsers = colleagues.registry->filterReachable(allUsers);
	MESSAGE_SINGLE(NORMAL, logger, "doStartScheduling(): activeUsers.size()="<<activeUsers.size()<<": Users="<<printUserSet(activeUsers));

	if ( !activeUsers.empty() && groupingRequired() ) // only if (maxBeams>1)
	{	// grouping needed for beamforming & its antenna pattern
		GroupingPtr grouping = schedulerState->currentState->getNewGrouping(); // also stored in schedulerState
		int maxBeams = schedulerState->currentState->strategyInput->maxBeams;
		if ( schedulerState->isTx ) // transmitter grouping
		    grouping = colleagues.grouper->getTxGroupingPtr(activeUsers, maxBeams);
		else // receiver grouping
		    grouping = colleagues.grouper->getRxGroupingPtr(activeUsers, maxBeams);
		assure(schedulerState->currentState->getGrouping() == grouping,"invalid grouping");
		// ^ otherwise we have to set it here.
		MESSAGE_SINGLE(NORMAL, logger, "doStartScheduling(): Number of Groups = " << grouping->groups.size());
		MESSAGE_SINGLE(NORMAL, logger, "doStartScheduling(): grouping.getDebugOutput = " << grouping->getDebugOutput());
	} else {
		MESSAGE_SINGLE(VERBOSE, logger, "doStartScheduling(): no grouping required.");
	}
	//if ( !activeUsers.empty() ) { // NO! go into all subStrategies anytime
	//ConnectionAttributes connectionAttributes; // NEW: std::map< ConnectionID, ConnectionsCharacteristics >

	// start scheduling with highest priority
	// a connection with p=0 (undefined) must not exist
	//assure(colleagues.registry->getConnectionsForPriority(0).size()==0,"getConnectionsForPriority(0)>0 ???");
	// priority is out of [0..MaxPriority-1]:
	for ( int priority = 0; priority < numberOfPriorities; ++priority )
	{
		if (subStrategies[priority] == NULL) continue;
		schedulerState->currentState->setCurrentPriority(priority);
		MESSAGE_SINGLE(NORMAL, logger, "doStartScheduling(): now scheduling priority=" << priority);
		// get all registered connections for the current priority
		ConnectionSet allConnections = colleagues.registry->getConnectionsForPriority(priority); // all
		MESSAGE_SINGLE(NORMAL, logger, "allConnections      = "<<printConnectionSet(allConnections));
		ConnectionSet reachableConnections = colleagues.registry->filterReachable(allConnections);
		MESSAGE_SINGLE(NORMAL, logger, "reachableConnections= "<<printConnectionSet(reachableConnections));
		// don't filter out unqueued cids since the subStrategy may want to update the state for every cid
		//ConnectionSet activeConnections = colleagues.queue->filterQueuedCids(reachableConnections);
		//MESSAGE_SINGLE(NORMAL, logger, "activeConnections   ="<<printConnectionSet(activeConnections));
		schedulerState->currentState->activeConnections = reachableConnections;
		// start SubScheduling in any case (even with empty user or cid list)
		// because the substrategies may need to keep and track their own state over time
		MapInfoCollectionPtr resultBursts = subStrategies[priority]->doStartSubScheduling(schedulerState, schedulingMap);
		// copy ^ of std::list<MapInfoEntryPtr>
		if (resultBursts->size()>0) {
		  MESSAGE_SINGLE(NORMAL, logger, "merged "<<resultBursts->size()<<" entries of resultBursts="<<resultBursts.getPtr()<<" into mapInfoCollection="<<mapInfoCollection.getPtr()<<" (now size="<<mapInfoCollection->size()<<")");
		  mapInfoCollection->join(*resultBursts); // collects result bursts. Do not use merge! (sorts bySmartPtr)
		}
	} // end for (over all priorities)
	// READY!
	MESSAGE_SINGLE(NORMAL, logger, "StaticPriority: "<<schedulingMap->getNumberOfCompounds()<<" compounds scheduled");
	MESSAGE_SINGLE(NORMAL, logger, schedulingMap->toString());
	this->resourceUsage = schedulingMap->getResourceUsage();
/*
#ifndef WNS_NDEBUG
	MESSAGE_SINGLE(NORMAL, logger, "mapInfoCollection(method1)="<<wns::scheduler::printMapInfoCollection(mapInfoCollection));
	MapInfoCollectionPtr mapInfoCollection_method2 = MapInfoCollectionPtr(new wns::scheduler::MapInfoCollection);
	// translate result into currentBurst to allow bursts.push_back(currentBurst)
	schedulingMap->convertToMapInfoCollection(mapInfoCollection_method2);
	MESSAGE_SINGLE(NORMAL, logger, "mapInfoCollection(method2)="<<wns::scheduler::printMapInfoCollection(mapInfoCollection));
#endif
*/
	return strategyResult;
} // doStartScheduling()