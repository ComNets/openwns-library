/*******************************************************************************
 * This file is part of openWNS (open Wireless Network Simulator)
 * _____________________________________________________________________________
 *
 * Copyright (C) 2004-2007
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

#ifndef WNS_SCHEDULER_METASCHEDULER_IMETASCHEDULER_HPP
#define WNS_SCHEDULER_METASCHEDULER_IMETASCHEDULER_HPP

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>

#include <boost/algorithm/string.hpp>

#include <WNS/container/Registry.hpp>
#include <WNS/scheduler/strategy/StrategyInterface.hpp>
#include <WNS/scheduler/SchedulerTypes.hpp>


#include <WNS/StaticFactory.hpp>
#include <WNS/PyConfigViewCreator.hpp>
#include <WNS/Singleton.hpp>
#include <WNS/pyconfig/View.hpp>
#include <WNS/probe/bus/ContextCollector.hpp>



namespace wns {namespace scheduler{ namespace metascheduler {
  
  
	class BSInfo{
	  public:
		  wns::scheduler::UserID getUserInFrequency (int frequency, const std::vector<int>& userMapping);
		  int getPhyModeIndexInFrequency (int frequency, const std::vector<int>& phyModeMapping);
	  public:
		  wns::scheduler::UserID BSID; 
		  wns::scheduler::UserSet connectedUTs;
		  int availableFreqChannels;
		  
		  //DL
		  wns::scheduler::RegistryProxyInterface* regProxyDL;
		  const wns::pyconfig::View *PyConfigDL;
		  wns::scheduler::strategy::StrategyInput *inputDL;
		  
		  //UL
		  wns::scheduler::RegistryProxyInterface* regProxyUL;
		  const wns::pyconfig::View *PyConfigUL;
		  wns::scheduler::strategy::StrategyInput *inputUL;
		  
		  std::vector<int> resourceBlockSizes;
		  std::vector<wns::scheduler::UserID> vActiveUsers;
		  
		  wns::scheduler::UserSet activeUsers;
		  wns::scheduler::UserSet activeUsersOld;
		  wns::scheduler::UserSet::const_iterator itaActiveUser;
		  
		  std::map<int, wns::scheduler::ChannelQualityOnOneSubChannel> interferenceMap;
		  std::vector<int> bestCombination;
		  std::vector<int> bestCombinationBlockPhyMode;
		  
		  friend class IMetaScheduler;
		};
	
	class UTInfo{
	
	  public:
		  wns::scheduler::UserID UTID;
		  wns::scheduler::RegistryProxyInterface* regProxy;
		  const wns::pyconfig::View *PyConfig;
		  wns::scheduler::strategy::StrategyInput *inputUL;
		  
		  wns::scheduler::UserID connectedToBS;
		  
		  friend class IMetaScheduler;

		};	
	
	struct PeerResource
	{
		PeerResource() {subChannel=0; timeSlot=0; spatialLayer=0;};
		~PeerResource() {};
		int subChannel;
		int timeSlot;
		int spatialLayer;
		
		bool operator<(const PeerResource& b) const;
	};
	
	//bool operator<(const PeerResource &a, const PeerResource& b);
	
	struct peerGroup
		     {
		      peerGroup() {};
		      ~peerGroup() {};
		      
		      /** @brief resources allocated to this peerGroup */
		      std::vector<PeerResource> resources;
		      
		      /** @brief peers (that use the same PRB but are connected to a different BS) */		      
		      wns::scheduler::UserSet peers;
		      
	};
	
	class IMetaScheduler {
	  public:
		
		IMetaScheduler();
		virtual ~IMetaScheduler() = 0;
		
  		/**
		 * @brief Attach a Scheduler to the MetaScheduler
		 *
		 * Called by the constructor of the Scheduler, hence there is no
		 * need to call this method explictly.
		 */
			
		virtual void attachBS(const wns::pyconfig::View *pyConfig, wns::scheduler::RegistryProxyInterface* registryProxy, bool IamUplinkMaster)=0;
		
		virtual void attachUT(const wns::pyconfig::View *pyConfig, wns::scheduler::RegistryProxyInterface* registryProxy)=0;
		
		/**
		 * @brief Remove Scheduler from the MetaScheduler (not in use)
		 */
		virtual void detach(const std::string &oldScheduler)=0;

		
		/**
		 * @brief Returns a pointer to a MetaScheduler according to PyConfig and ensures it to be a Singleton
		 */		
		static IMetaScheduler* getMetaScheduler(const wns::pyconfig::View& config);
		
		
		/**
		 * @brief Creates a StrategyInput Object, registers it to the according UT/SS and returns a pointer
		 */
		virtual wns::scheduler::strategy::StrategyInput 
		*returnStrategyInputBS(wns::scheduler::RegistryProxyInterface* registryProxy,bool IamUplinkMaster)=0;
		
		
		virtual wns::scheduler::strategy::StrategyInput 
		*returnStrategyInputUT(wns::scheduler::RegistryProxyInterface* registryProxy)=0;
		
		virtual void optimize(void)=0;
		 /**
		 * @brief Provides the changes to an existing schedulingMap according to the applied MetaScheduler strategy
		 */
		virtual void provideMetaConfiguration(const wns::scheduler::strategy::StrategyInput* strategyInput, wns::scheduler::SchedulingMapPtr schedulingMap)=0;
		
		/*
		//virtual void setActiveUserSet(BSInfo* p_BSInfo, int frameNr) = 0;
		//virtual void computeRessourceBlockSizes (BSInfo* p_BSInfo) = 0;
		//virtual void applyPeerMapping (peerGroup* PeerGroup) = 0;
		//virtual void applyPeerMapping (void) = 0;
		//virtual void applyFrequencyMap (void) = 0;
		//virtual void applyBestPermutation (void) = 0;
		//virtual void updateUserSubchannels (void) = 0;
		//virtual bool computeInterferenceMap (void) = 0;
		//virtual void GetInterfererOnFrequency (BSInfo* pBS, int iFrequency,
				      std::vector<std::vector<int> >& currentCombination,
				      std::set<wns::scheduler::UserID>& interferer) = 0;
		//virtual void GetInterfererOnFrequency (wns::scheduler::UserID user, int iFrequency,
				      std::set<wns::scheduler::UserID>& interferer) = 0;

		//virtual double GetUserScore (BSInfo* pBS,
					   wns::scheduler::UserID user,
					   std::set<wns::scheduler::UserID>& interferer) = 0;
		//virtual wns::Ratio estimateSINR (BSInfo* pBS,
					   wns::scheduler::UserID user,
					   std::set<wns::scheduler::UserID>& interferer) = 0;
		//virtual wns::scheduler::ChannelQualityOnOneSubChannel getMeasurementsForUser (wns::scheduler::UserID) = 0;
//	  private:
	    
		*/
	  protected:
		static IMetaScheduler* metaScheduler;
		
		wns::probe::bus::ContextCollector metaSchedulerCPUCycles_;
		wns::probe::bus::ContextCollector metaSchedulerTime_;
		/**
		* @brief Container for the set frequencies
		*/
	
		//Base Station and UserTerminal Information
		
		typedef wns::container::Registry<long int,BSInfo*> baseStationContainer;
		typedef baseStationContainer::const_iterator baseStationContainerIterator;
		
		
		std::map< wns::scheduler::UserID, BSInfo*> BSMap;
		std::vector<wns::scheduler::metascheduler::BSInfo*> baseStations;
		
		std::map< wns::scheduler::UserID, UTInfo*> UTMap;
		//baseStationContainer allBaseStation;
		
		baseStationContainerIterator itaAllBaseStation;
		
		
		typedef wns::container::Registry<std::string,UTInfo*> userTerminalContainer;
		typedef userTerminalContainer::const_iterator userTerminalContainerIterator;		
		userTerminalContainer allUserTerminal;
		userTerminalContainerIterator itaAllUserTerminal;
		
		//contains the available subchannel and may be used for subchannel blocking 		
		typedef wns::container::Registry<int,std::string> frequencyContainer;
		typedef frequencyContainer::const_iterator frequencyContainerIterator;		
		frequencyContainer allSetFrequencies;
		frequencyContainerIterator itaAllSetFrequencies;
		
		wns::scheduler::SchedulingMapPtr mp_schedulingMap;
		const wns::scheduler::strategy::StrategyInput* mp_StrategyInput;
		BSInfo* mp_CurrentBSInfo;
		
		std::vector<wns::scheduler::UserID> frequencyMap;
		std::vector<peerGroup> resourceGroups;
		
	  };//end IMetaScheduler
	      
	
	
	typedef wns::PyConfigViewCreator<IMetaScheduler> MetaSchedulerCreator;
		
	} //END METASCHEDULER

     } //END SCHEDULER
     
} //END NAMESPACE
#endif // WNS_SCHEDULER_METASCHEDULER_IMETASCHEDULER_HPP

