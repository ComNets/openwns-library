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

#include <WNS/scheduler/tests/RegistryProxyStub.hpp>
#include <WNS/pyconfig/Parser.hpp>
#include <WNS/node/tests/Stub.hpp>

#include <WNS/scheduler/SchedulerTypes.hpp>

//#include <RISE/PhyModeMapper.hpp>
#include "PhyModeMapperStub.hpp"

using namespace wns::scheduler;
using namespace wns::scheduler::tests;
/*
RegistryProxyStub::RegistryProxyStub()
	: classifier(NULL),
	  phyModeMapper(NULL),
	  myUserID(new wns::node::tests::Stub()),
	  queueSizeLimit(100000),
	channelQualities(),
	phymode2SINR()
{
}
*/

RegistryProxyStub::RegistryProxyStub()
	: classifier(NULL),
	  //ofdmaProvider(NULL),
	  phyMode(),
	  phyModeMapper(NULL),
	  myUserID(new wns::node::tests::Stub()),
	  queueSizeLimit(100000)
{
	wns::pyconfig::Parser parser;
	parser.loadString("import openwns.PhyMode\n" 
			  "from openwns.interval import Interval\n"
			  "phyMode = openwns.PhyMode.PhyModeDropin3()\n"
			  "phyModeMap = openwns.PhyMode.PhyModeMapperDropin()\n"
			  "phyModeMap.setMinimumSINR(3.0)\n"
			  "phyModeMap.addPhyMode(Interval(-200.0,   3.0, \"(]\"), openwns.PhyMode.PhyModeDropin1())\n"
			  "phyModeMap.addPhyMode(Interval(   3.0,  10.0, \"(]\"), openwns.PhyMode.PhyModeDropin2())\n"
			  "phyModeMap.addPhyMode(Interval(  10.0, 200.0, \"(]\"), openwns.PhyMode.PhyModeDropin3())\n"
			  "\n"
		);
	phyMode = wns::SmartPtr<const wns::service::phy::phymode::PhyModeInterface>
		( new wns::scheduler::tests::PhyMode(parser.get("phyMode")) );
	phyModeMapper = new wns::scheduler::tests::PhyModeMapper(parser.get("phyModeMap"));
}

RegistryProxyStub::~RegistryProxyStub()
{
}


UserID
RegistryProxyStub::getUserForCID(ConnectionID cid)
{
	return CID2User[cid];
}

ConnectionVector
RegistryProxyStub::getConnectionsForUser(const UserID  user )
{
	return User2CID[user];
}

ConnectionID
RegistryProxyStub::getCIDforPDU(const wns::ldk::CompoundPtr& compound)
{
	if (classifier) // if classifier is set, use it
	{
		wns::ldk::ClassifierCommand* command = dynamic_cast<wns::ldk::ClassifierCommand*>(classifier->getCommand(compound->getCommandPool()));
        return command->peer.id;
	}
	assure(compound2CIDmap.find(compound) != compound2CIDmap.end(), "setCIDforPDU has to be called first");

	return compound2CIDmap[compound];
}

void
RegistryProxyStub::setCIDforPDU(const wns::ldk::CompoundPtr& compound, ConnectionID cid)
{
	compound2CIDmap[compound] = cid;
}

void
RegistryProxyStub::setFriends(const wns::ldk::CommandTypeSpecifierInterface* _classifier )
{
	classifier = const_cast<wns::ldk::CommandTypeSpecifierInterface*>(_classifier);
}

/*
void
RegistryProxyStub::setFriends(const wns::ldk::CommandTypeSpecifierInterface* _classifier,
			      wns::service::phy::ofdma::BFInterface* _ofdmaProvider)
{
	classifier = const_cast<wns::ldk::CommandTypeSpecifierInterface*>(_classifier);
	ofdmaProvider = _ofdmaProvider;
}
*/

void
RegistryProxyStub::setFUN(const wns::ldk::fun::FUN* /* fun */)
{
}

std::string
RegistryProxyStub::getNameForUser(const UserID /* user */)
{
	return std::string("n/a");
}

wns::service::phy::phymode::PhyModeMapperInterface*
RegistryProxyStub::getPhyModeMapper() const
{
//	assure (phyModeMapper != NULL, "phyModeMapper==NULL");
         return phyModeMapper;
}

wns::SmartPtr<const wns::service::phy::phymode::PhyModeInterface>
RegistryProxyStub::getBestPhyMode(const wns::Ratio& /*sinr*/)
{
	return this->phyMode;
}

UserID
RegistryProxyStub::getMyUserID()
{
	return myUserID;
}

wns::CandI
RegistryProxyStub::estimateTxSINRAt(const UserID user)
{
	//throw Exception("estimateTxSINRAt: Not implemented");
	return wns::CandI(wns::Power::from_dBm(-80.0),
			  wns::Power::from_dBm(-95.0));
}

wns::CandI
RegistryProxyStub::estimateRxSINROf(const UserID user)
{
	//throw Exception("estimateRxSINROf: Not implemented");
	return wns::CandI(wns::Power::from_dBm(-80.0),
			  wns::Power::from_dBm(-95.0));
}


wns::Power
RegistryProxyStub::estimateInterferenceAt(const UserID /* user */)
{
	return wns::Power::from_dBm(-100);
}

wns::Power
RegistryProxyStub::estimateInterferenceStdDeviation(const UserID /* user */)
{
	return wns::Power::from_dBm(0.1);
}

Bits
RegistryProxyStub::getQueueSizeLimitPerConnection()
{
	return queueSizeLimit;
}

wns::service::dll::StationType
RegistryProxyStub::getStationType(const UserID /* user */)
{
	return 0;
}

UserSet
RegistryProxyStub::filterReachable(UserSet users)
{
	return users;
}

ConnectionSet
RegistryProxyStub::filterReachable(ConnectionSet connections)
{
	return connections;
}

wns::scheduler::PowerMap
RegistryProxyStub::calcULResources(const wns::scheduler::UserSet&, uint32_t) const
{
	return wns::scheduler::PowerMap();
}

wns::scheduler::UserSet
RegistryProxyStub::getActiveULUsers() const
{
	return wns::scheduler::UserSet();
}

int
RegistryProxyStub::getTotalNumberOfUsers(wns::scheduler::UserID /*user*/) const
{
	return 1;
}

void
RegistryProxyStub::associateCIDandUser(ConnectionID cid, UserID user) {
	assure(user, "You have to specify a valid user id");
	assure(cid, "You have to specify a valid connection id");

	User2CID[user].push_back(cid);
	CID2User[cid] = user;
}

void
RegistryProxyStub::setQueueSizeLimitPerConnection(Bits bits)
{
	queueSizeLimit = bits;
}


wns::scheduler::ChannelQualitiesOnAllSubBandsPtr
RegistryProxyStub::getChannelQualities4UserOnUplink(UserID /*user*/, int /*frameNr*/)
{
	return wns::scheduler::ChannelQualitiesOnAllSubBandsPtr();

}

wns::scheduler::ChannelQualitiesOnAllSubBandsPtr
RegistryProxyStub::getChannelQualities4UserOnDownlink(UserID /*user*/, int /*frameNr*/)
{
	return wns::scheduler::ChannelQualitiesOnAllSubBandsPtr();
}

wns::scheduler::PowerCapabilities
RegistryProxyStub::getPowerCapabilities(const UserID) const
{
	wns::scheduler::PowerCapabilities result;
	result.maxOverall = wns::Power::from_dBm(46.0);
	result.maxPerSubband = wns::Power::from_dBm(36.0);
	result.nominalPerSubband = wns::Power::from_dBm(26.0);
	return result;
}

wns::scheduler::PowerCapabilities
RegistryProxyStub::getPowerCapabilities() const
{
	wns::scheduler::PowerCapabilities result;
	result.maxOverall = wns::Power::from_dBm(46.0);
	result.maxPerSubband = wns::Power::from_dBm(36.0);
	result.nominalPerSubband = wns::Power::from_dBm(26.0);
	return result;
}

int
RegistryProxyStub::getNumberOfPriorities()
{
	return 0;
}

wns::scheduler::ConnectionList&
RegistryProxyStub::getCIDListForPriority(int /*priority*/)
{
	wns::scheduler::ConnectionList connList;
	wns::scheduler::ConnectionID cid = 0;
	connList.push_front(cid);
	wns::scheduler::ConnectionList& c = connList;
	return c;
}


const wns::service::phy::phymode::PhyModeInterfacePtr
RegistryProxyStub::getPhyMode(ConnectionID /*cid*/)
{
	return this->phyMode;
}

int
RegistryProxyStub::getPriorityForConnection(wns::scheduler::ConnectionID /*cid*/)
{
	return 0;
}

std::string
RegistryProxyStub::compoundInfo(const wns::ldk::CompoundPtr& /*compound*/)
{
}

bool
RegistryProxyStub::getDL() const
{
	return false;
}

bool
RegistryProxyStub::getCQIAvailable() const
{
	return false;
}

/*
  Local Variables:
  mode: c++
  fill-column: 80
  c-basic-offset: 8
  c-comment-only-line-offset: 0
  c-tab-always-indent: t
  indent-tabs-mode: t
  tab-width: 8
  End:
*/