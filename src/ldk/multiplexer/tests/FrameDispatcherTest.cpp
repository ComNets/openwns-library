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

#include "FrameDispatcherTest.hpp"

#include <WNS/ldk/tests/LayerStub.hpp>
#include <WNS/ldk/utils.hpp>

#include <WNS/pyconfig/Parser.hpp>

#include <iostream>

using namespace wns::ldk::tools;
using namespace wns::ldk::multiplexer;

CPPUNIT_TEST_SUITE_REGISTRATION( FrameDispatcherTest );

void
FrameDispatcherTest::setUp()
{
	layer = new tests::LayerStub();
	fuNet = new fun::Main(layer);

	pyconfig::Parser emptyConfig;
	upper1 = new Stub(fuNet, emptyConfig);
	upper2 = new Stub(fuNet, emptyConfig);

	pyconfig::Parser dispatcherConfig;
	dispatcherConfig.loadString(
		"import openwns.ldk\n"
		"dispatcher = openwns.ldk.Multiplexer.FrameDispatcher(42)\n"
		);
	pyconfig::View dispatcherView(dispatcherConfig, "dispatcher");
	dispatcher = new FrameDispatcher(fuNet, dispatcherView);
	lower1 = new Stub(fuNet, emptyConfig);
	lower2 = new Stub(fuNet, emptyConfig);

	fuNet->addFunctionalUnit("ernie", dispatcher);

	upper1
		->connect(dispatcher)
		->connect(lower1);

	upper2
		->connect(dispatcher)
		->connect(lower2);
} // setUp


void
FrameDispatcherTest::tearDown()
{
	delete upper1;
	delete upper2;
	delete dispatcher;
	delete lower1;
	delete lower2;

	delete layer;
} // tearDown


void
FrameDispatcherTest::testOutgoing()
{
	{
		CompoundPtr compound(fuNet->createCompound());
		upper1->sendData(compound);
	}
	CPPUNIT_ASSERT(lower1->sent.size() == 1);
	CPPUNIT_ASSERT(lower2->sent.size() == 0);

	{
		CompoundPtr compound(fuNet->createCompound());
		upper2->sendData(compound);
	}
	CPPUNIT_ASSERT(lower1->sent.size() == 1);
	CPPUNIT_ASSERT(lower2->sent.size() == 1);

	OpcodeCommand* command1 = dispatcher->getCommand(lower1->sent[0]->getCommandPool());
	OpcodeCommand* command2 = dispatcher->getCommand(lower2->sent[0]->getCommandPool());
	CPPUNIT_ASSERT(command1->peer.opcode != command2->peer.opcode);
} // testOutgoing


void
FrameDispatcherTest::testIncoming()
{
	{
		CompoundPtr compound(fuNet->createCompound());
		upper1->sendData(compound);
	}
	{
		CompoundPtr compound(fuNet->createCompound());
		upper2->sendData(compound);
	}


	CPPUNIT_ASSERT(upper2->received.size() == 0);
	lower2->onData(lower2->sent.at(0));
	CPPUNIT_ASSERT(upper2->received.size() == 1);

	CPPUNIT_ASSERT(upper1->received.size() == 0);
	lower1->onData(lower1->sent.at(0));
	CPPUNIT_ASSERT(upper1->received.size() == 1);
} // testIncoming


void
FrameDispatcherTest::testDispatching()
{
	{
		CompoundPtr compound(fuNet->createCompound());
		upper1->sendData(compound);
	}
	{
		CompoundPtr compound(fuNet->createCompound());
		upper2->sendData(compound);
	}


	CPPUNIT_ASSERT(upper2->received.size() == 0);
	dispatcher->onData(lower2->sent.at(0));
	CPPUNIT_ASSERT(upper2->received.size() == 1);

	CPPUNIT_ASSERT(upper1->received.size() == 0);
	dispatcher->onData(lower1->sent.at(0));
	CPPUNIT_ASSERT(upper1->received.size() == 1);
} // testDispatching


void
FrameDispatcherTest::testSizes()
{
	CompoundPtr compound(fuNet->createCompound());

	CPPUNIT_ASSERT_EQUAL(0, compound->getLengthInBits());
	upper1->sendData(compound);
	CPPUNIT_ASSERT_EQUAL(42, compound->getLengthInBits());
} // testIncoming


void
FrameDispatcherTest::testPyConfig()
{
	pyconfig::Parser config;
	config.loadString(
		"from openwns.FUN import FUN, Node\n"
		"from openwns.Tools import Stub\n"
		"from openwns.Multiplexer import FrameDispatcher\n"
		"fuNet = FUN()\n"
		"u1 = Node('mon', Stub())\n"
		"u2 = Node('dieu', Stub())\n"
		"d = Node('dispatcher', FrameDispatcher(23))\n"
		"l1 = Node('oh', Stub())\n"
		"l2 = Node('lala', Stub())\n"
		"fuNet.setFunctionalUnits(u1, u2, d, l1, l2)\n"
		"u1.connect(d)\n"
		"d.connect(l1)\n"
		"u2.connect(d)\n"
		"d.connect(l2)\n"
		);

	pyconfig::View funConfig(config, "fuNet");
	Layer* l = new tests::LayerStub();
	fun::Main* fuNet = new fun::Main(l);

	configureFUN(fuNet, funConfig);

	wns::ldk::tools::Stub* u1 = fuNet->findFriend<wns::ldk::tools::Stub*>("mon");
	wns::ldk::tools::Stub* u2 = fuNet->findFriend<wns::ldk::tools::Stub*>("dieu");
	wns::ldk::tools::Stub* l1 = fuNet->findFriend<wns::ldk::tools::Stub*>("oh");
	wns::ldk::tools::Stub* l2 = fuNet->findFriend<wns::ldk::tools::Stub*>("lala");

	{
		CompoundPtr compound(fuNet->createCompound());
		u1->sendData(compound);
	}
	CPPUNIT_ASSERT(l1->sent.size() == 1);
	CPPUNIT_ASSERT(l2->sent.size() == 0);

	{
		CompoundPtr compound(fuNet->createCompound());
		u2->sendData(compound);
	}
	CPPUNIT_ASSERT(l1->sent.size() == 1);
	CPPUNIT_ASSERT(l2->sent.size() == 1);

	CPPUNIT_ASSERT(u2->received.size() == 0);
	l2->onData(l2->sent.at(0));
	CPPUNIT_ASSERT(u2->received.size() == 1);

	CPPUNIT_ASSERT(u1->received.size() == 0);
	l1->onData(l1->sent.at(0));
	CPPUNIT_ASSERT(u1->received.size() == 1);

	CPPUNIT_ASSERT(u2->received.size() == 1);
	dispatcher->onData(l2->sent.at(0));
	CPPUNIT_ASSERT(u2->received.size() == 2);

	CPPUNIT_ASSERT(u1->received.size() == 1);
	dispatcher->onData(l1->sent.at(0));
	CPPUNIT_ASSERT(u1->received.size() == 2);

	delete fuNet;
	delete l;
} // testIncoming



