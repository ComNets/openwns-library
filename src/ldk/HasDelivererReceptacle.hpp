/******************************************************************************
 * WNS (Wireless Network Simulator)                                           *
 * __________________________________________________________________________ *
 *                                                                            *
 * Copyright (C) 2004-2008                                                    *
 * Chair of Communication Networks (ComNets)                                  *
 * Kopernikusstr. 1, D-52074 Aachen, Germany                                  *
 * phone: ++49-241-80-27910 (phone), fax: ++49-241-80-22242                   *
 * email: wns@comnets.rwth-aachen.de                                          *
 * www: http://wns.comnets.rwth-aachen.de                                     *
 ******************************************************************************/

#ifndef WNS_LDK_HASDELIVERERRECEPTACLE_HPP
#define WNS_LDK_HASDELIVERERRECEPTACLE_HPP

#include <WNS/ldk/IDelivererReceptacle.hpp>
#include <WNS/ldk/DelivererReceptacleRegistry.hpp>
#include <WNS/ldk/LinkHandlerInterface.hpp>
#include <WNS/ldk/SinglePort.hpp>
#include <WNS/ldk/Port.hpp>
#include <WNS/ldk/fun/FUN.hpp>

#include <WNS/Assure.hpp>

#include <string>

namespace wns { namespace ldk {

        template <typename CLASS, typename PORTID = SinglePort>
        class HasDelivererReceptacle
            : public virtual DelivererReceptacleRegistry
        {
        public:
            HasDelivererReceptacle(CLASS* fu)
                : DelivererReceptacleRegistry(),
                  delivererReceptacle_(fu)
            {
                addToDelivererReceptacleRegistry(PORTID().name, &delivererReceptacle_);
            }

            virtual
            ~HasDelivererReceptacle()
            {}

            class DelivererReceptacle
                : public virtual IDelivererReceptacle
            {
            public:
                DelivererReceptacle(CLASS* fu)
                    : fu_(fu)
                {}

                virtual
                ~DelivererReceptacle()
                {}

                virtual void
                onData(const CompoundPtr& compound)
                {
                    fu_->getFUN()->getLinkHandler()->onData(this, compound);
                }

                virtual void
                doOnData(const CompoundPtr& compound)
                {
                    fu_->doOnData(compound, Port<PORTID>());
                }

                virtual FunctionalUnit*
                getFU()
                {
                    return fu_;
                }

            private:
                CLASS* fu_;
            };

        private:
            HasDelivererReceptacle()
            {}

            DelivererReceptacle delivererReceptacle_;
        };


        template <typename CLASS>
        class HasDelivererReceptacle<CLASS, SinglePort>
            : public virtual IDelivererReceptacle,
              public virtual DelivererReceptacleRegistry
        {
        public:
            HasDelivererReceptacle()
                : DelivererReceptacleRegistry()
            {
                //                assureNotNull(dynamic_cast<CLASS*>(this));
                //                fu_ = dynamic_cast<CLASS*>(this);
                addToDelivererReceptacleRegistry(SinglePort().name, this);
            }

            HasDelivererReceptacle(FunctionalUnit* fu)
                : DelivererReceptacleRegistry(),
                  fu_(fu)
            {
                addToDelivererReceptacleRegistry(SinglePort().name, this);
            }

            virtual
            ~HasDelivererReceptacle()
            {}

            virtual void
            onData(const CompoundPtr& compound)
            {
                dynamic_cast<CLASS*>(this)->getFUN()->getLinkHandler()->onData(this, compound);
            }

            virtual FunctionalUnit*
            getFU()
            {
                return dynamic_cast<CLASS*>(this);
            }

        private:
            CLASS* fu_;
        };


    } // ldk
} // wns

#endif // NOT defined WNS_LDK_HASDELIVERERRECEPTACLE_HPP
