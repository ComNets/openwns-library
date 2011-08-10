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

#ifndef WNS_SCHEDULER_STRATEGY_STATICPRIORITY_PERSISTENTVOIP_TBCHOSER_HPP
#define WNS_SCHEDULER_STRATEGY_STATICPRIORITY_PERSISTENTVOIP_TBCHOSER_HPP

#include <WNS/scheduler/strategy/staticpriority/persistentvoip/ResourceGrid.hpp>
#include <WNS/distribution/Uniform.hpp>
#include <WNS/StaticFactory.hpp>

namespace wns { namespace scheduler { namespace strategy { namespace staticpriority { namespace persistentvoip {

class ITBChoser
{
    public:         
        typedef wns::Creator<ITBChoser> Creator;
        typedef wns::StaticFactory<Creator> Factory;

        virtual Frame::SearchResult
        choseTB(const Frame::SearchResultSet& tbs) = 0;

    private:
        virtual Frame::SearchResult
        doChoseTB(const Frame::SearchResultSet& tbs) = 0;
};

class TBChoser :
    public ITBChoser
{
    public:         
        typedef wns::Creator<ITBChoser> Creator;
        typedef wns::StaticFactory<Creator> Factory;

        virtual Frame::SearchResult
        choseTB(const Frame::SearchResultSet& tbs);

    private:
        virtual Frame::SearchResult
        doChoseTB(const Frame::SearchResultSet& tbs) = 0;
};

class First :
    public TBChoser
{
        virtual Frame::SearchResult
        doChoseTB(const Frame::SearchResultSet& tbs);
};

class BestFit :
    public TBChoser
{        
        virtual Frame::SearchResult
        doChoseTB(const Frame::SearchResultSet& tbs);
};

class WorstFit :
    public TBChoser
{         
        virtual Frame::SearchResult
        doChoseTB(const Frame::SearchResultSet& tbs);
};

class Random :
    public TBChoser
{       
        virtual Frame::SearchResult
        doChoseTB(const Frame::SearchResultSet& tbs);

        wns::distribution::StandardUniform rnd_;
};


}}}}}

#endif
