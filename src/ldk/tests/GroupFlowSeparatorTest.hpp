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

#ifndef WNS_LDK_GROUPFLOWSEPARATOR_TEST_HPP
#define WNS_LDK_GROUPFLOWSEPARATOR_TEST_HPP

#include <WNS/ldk/FlowSeparator.hpp>

#include <WNS/ldk/Group.hpp>
#include <WNS/ldk/tools/Stub.hpp>
#include <WNS/ldk/multiplexer/OpcodeProvider.hpp>
#include <WNS/ldk/multiplexer/OpcodeKey.hpp>

#include <WNS/pyconfig/Parser.hpp>

#include <cppunit/extensions/HelperMacros.h>

#include <stdexcept>

namespace wns { namespace ldk { namespace tests {

	class GroupFlowSeparatorTest : public CppUnit::TestFixture  {
		CPPUNIT_TEST_SUITE( GroupFlowSeparatorTest );
		CPPUNIT_TEST( testIncoming );
		CPPUNIT_TEST( testOutgoing );
		CPPUNIT_TEST_SUITE_END();
	public:
		void setUp();
		void tearDown();

		void testIncoming();
		void testOutgoing();
	private:
		Layer* layer;
		fun::FUN* fuNet;

		multiplexer::OpcodeProvider* opcode;
		tools::Stub* upper;
		tools::Stub* lower;

		Group* prototype;

		FlowSeparator* flowSeparator;
	};

} // tests
} // ldk
} // wns



#endif // NOT defined WNS_LDK_GROUPFLOWSEPARATOR_TEST_HPP


