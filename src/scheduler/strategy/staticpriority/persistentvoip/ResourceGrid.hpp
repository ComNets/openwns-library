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

#ifndef WNS_SCHEDULER_STRATEGY_STATICPRIORITY_PERSISTENTVOIP_RESOURCEGRID_HPP
#define WNS_SCHEDULER_STRATEGY_STATICPRIORITY_PERSISTENTVOIP_RESOURCEGRID_HPP

#include <WNS/scheduler/SchedulerTypes.hpp>
#include <WNS/SmartPtr.hpp>
#include <WNS/RefCountable.hpp>

#include <map>
#include <set>
#include <sstream>

namespace wns { namespace scheduler { namespace strategy { namespace staticpriority { namespace persistentvoip {

class Frame;

class ResourceBlock
{
    public:        
        ResourceBlock(Frame* parent, unsigned int index);
        ~ResourceBlock();

        bool
        operator<(const ResourceBlock& other) const;

        bool
        isFree() const;

        void
        setOccupied();

        void
        setFree();

        unsigned int
        getSubChannelIndex();

        unsigned int
        getFrameIndex();

    private:
        bool free_;
        bool neverUsed_;
        unsigned int subChannel_;
        Frame* parent_;

        wns::logger::Logger* logger_;
}; 

typedef std::vector<ResourceBlock> ResourceBlockVector;
typedef ResourceBlockVector::iterator ResourceBlockVectorIt;

typedef std::set<ResourceBlock*> ResourceBlockPointerSet;
typedef ResourceBlockPointerSet::iterator ResourceBlockPointerSetIt;

class TransmissionBlock :
    public wns::RefCountable
{
    public:
        TransmissionBlock(ResourceBlockVectorIt& start, 
            ResourceBlockVectorIt& end,
            ConnectionID cid);

        ~TransmissionBlock();

        bool
        operator==(const TransmissionBlock& other) const;

        bool
        operator<(const TransmissionBlock& other) const;

        unsigned int
        getCID();

    private:
        ResourceBlockPointerSet rbs_;
        ConnectionID cid_;
        unsigned int start_;
        unsigned int length_;
        unsigned int frame_;            
};

typedef wns::SmartPtr<TransmissionBlock> TransmissionBlockPtr; 

class ResourceGrid;

class Frame :
    public wns::IOutputStreamable
{
    public:
        struct SearchResult
        {
            SearchResult() :
                success(false),
                start(0),
                length(0),
                needed(0),
                frame(0)
            {};

            bool
            operator<(const SearchResult& other) const
            {
                return this->start < other.start;
            };

            bool success;
            unsigned int start;
            unsigned int length;
            unsigned int needed;
            unsigned int frame;
        };

        typedef std::set<SearchResult> SearchResultSet;

        Frame(ResourceGrid* parent, unsigned int index);
        
        ~Frame();

        SearchResult
        findTransmissionBlock(unsigned int start, unsigned int minLength);

        SearchResultSet
        findTransmissionBlocks(unsigned int minLength);

        void
        reserve(ConnectionID cid, unsigned int st, 
            unsigned int l, bool persistent);

        unsigned int
        getFrameIndex();
    
        void
        clearUnpersistentSchedule();

        wns::logger::Logger*
        getLogger();

    private:
        virtual std::string
        doToString() const;

        ResourceBlockVector rbs_;
        std::map<ConnectionID, TransmissionBlockPtr> persistentSchedule_;
        std::map<ConnectionID, TransmissionBlockPtr> unpersistentSchedule_;

        unsigned int numberOfSubChannels_;
        unsigned int frame_;
        ResourceGrid* parent_;

        wns::logger::Logger* logger_;
};

typedef wns::SmartPtr<Frame> FramePtr;
typedef std::vector<Frame> FrameVector;
typedef FrameVector::iterator FrameVectorIt;

class ITBChoser;

class ResourceGrid
{
    public:
        ResourceGrid(const wns::pyconfig::View& config,
            wns::logger::Logger& logger, 
            unsigned int numberOfFrames, 
            unsigned int subChannels);

        ~ResourceGrid();

        bool
        scheduleCID(unsigned int frame, ConnectionID cid, 
            unsigned int length, bool persistent);

        unsigned int
        getSubChannelsPerFrame();

        unsigned int
        getNumberOfFrames();

        void
        onNewFrame(unsigned int index);

        wns::logger::Logger*
        getLogger();

        /* only for testing */
        Frame*
        getFrame(unsigned int index);

    private:
        unsigned int numberOfFrames_;
        unsigned int subChannelsPerFrame_;
        FrameVector frames_;

        ITBChoser* tbChoser_;

        wns::logger::Logger* logger_;
};

}}}}}

#endif
