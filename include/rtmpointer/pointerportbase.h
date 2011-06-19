/* rtmpointer
 *
 * Header file for the pointer-sharing port base class.
 *
 * Copyright 2011 Geoffrey Biggs geoffrey.biggs@aist.go.jp
 *     RT-Synthesis Research Group
 *     Intelligent Systems Research Institute,
 *     National Institute of Advanced Industrial Science and Technology (AIST),
 *     Japan
 *     All rights reserved.
 *
 * This file is part of rtmpointer.
 *
 * rtmpointer is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License,
 * or (at your option) any later version.
 *
 * rtmpointer is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with rtmpointer. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#if !defined(POINTERPORTBASE_H_)
#define POINTERPORTBASE_H_

#include <coil/Properties.h>
#include <rtm/PortBase.h>
#include <string>

namespace RTC
{
    class PointerPortBase
        : public PortBase
    {
        public:
            PointerPortBase(std::string name)
                : PortBase(name.c_str())
            {
                addProperty("port.port_type", "PointerPort");
            }
            virtual ~PointerPortBase()
            {
            }

            virtual void init(coil::Properties const& props)
            {
                props_ << props;
            }

            coil::Properties const& properties() const { return props_; }

            void activateInterfaces() { /* Nothing to do */ };
            void deactivateInterfaces() { /* Nothing to do */ };

        protected:
            ReturnCode_t publishInterfaces(ConnectorProfile& cp) = 0;
            ReturnCode_t subscribeInterfaces(ConnectorProfile const& cp) = 0;
            void unsubscribeInterfaces(ConnectorProfile const& cp) = 0;

            coil::Properties props_;
    };
}; // namespace RTC

#endif // !defined(POINTERPORTBASE_H_)

