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

#ifndef WNS_SCHEDULER_METASCHEDULER_NOMETASCHEDULER_HPP
#define WNS_SCHEDULER_METASCHEDULER_NOMETASCHEDULER_HPP

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>

#include <WNS/container/Registry.hpp>
#include <WNS/scheduler/strategy/StrategyInterface.hpp>
#include <WNS/StaticFactory.hpp>
#include <WNS/scheduler/metascheduler/IMetaScheduler.hpp>
#include <WNS/scheduler/metascheduler/MetaScheduler.hpp>
#include <WNS/Singleton.hpp>
#include <WNS/scheduler/strategy/Strategy.hpp>



namespace wns { namespace scheduler{ namespace metascheduler{
	
	class NoMetaScheduler:public MetaScheduler
	//, public wns::scheduler::strategy::Strategy 
	      {
	  
	  public:
	    
		NoMetaScheduler(const wns::pyconfig::View& _config);//: availableFrequencyChannels(0), numberBS(0),numberCount(1) {}						
		
		~NoMetaScheduler(){};
				
		
		void optimize(void);
		
		void doOptimize(void);
		
		/**
		 * @brief Modifys a SchedulingMap.
		 *
		 */			
		//void provideMetaConfiguration(const wns::scheduler::strategy::StrategyInput* strategyInput, wns::scheduler::SchedulingMapPtr schedulingMap);
		
	
	   protected:

		std::vector<std::string> frequencyMap;
		std::vector<peerGroup> resourceGroups;
			
			
	 };		  
      }
   }
}




#endif // WNS_SCHEDULER_METASCHEDULER_METASCHEDULER_HPP

