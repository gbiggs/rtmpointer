/* rtmpointer
 *
 * Header file for the pointer-sharing port.
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

#if !defined(POINTERPORT_H_)
#define POINTERPORT_H_

#include <rtmpointer/pointerportbase.h>

#include <boost/type_traits/is_array.hpp>
#include <sstream>
#include <string>

namespace RTC
{
    template<typename DataType>
    struct PortValue
    {
        public:
            PortValue()
                : value_(0), is_new_(false)
            {}

            DataType* value_;
            bool is_new_;
    };

    template<typename DataType>
    class PointerPort
        : public PointerPortBase
    {
        public:
            PointerPort(std::string const name)
                : PointerPortBase(name), data_is_mine_(false)
            {
                RTC_TRACE(("PointerPort()"));
            }

            ~PointerPort()
            {
                RTC_TRACE(("~PointerPort()"));
                if (data_is_mine_ && port_value_)
                {
                    if (boost::is_array<DataType>::value)
                    {
                        delete[] port_value_->value_;
                    }
                    else
                    {
                        delete port_value_->value_;
                    }
                    delete port_value_;
                }
            }

            void init(coil::Properties const& props)
            {
                RTC_TRACE(("init()"));
                PointerPortBase::init(props);
            }

            DataType* value() const { return port_value_->value_; }

            DataType* operator->() const { return port_value_->value_; }

            bool is_new() const { return port_value_->is_new_; }
            void mark_new() { port_value_->is_new_ = true; }
            void mark_old() { port_value_->is_new_ = false; }

        private:
            PortValue<DataType>* port_value_;
            bool data_is_mine_;

            ReturnCode_t publishInterfaces(ConnectorProfile& cp)
            {
                RTC_TRACE(("publishInterfaces()"));
                if (port_value_)
                {
                    // Check the connector profile for an address
                    CORBA::Long ii = NVUtil::find_index(cp.properties,
                            "pointerport.address");
                    if (ii >= 0)
                    {
                        // Cannot connect an already-connected port
                        RTC_ERROR(("Port %s is already connected.", getName()));
                        return RTC_ERROR;
                    }
                    RTC_INFO(("pointerport.address key not found"));
                    // Place the current address in the connector profile
                    std::stringstream ss;
                    ss << port_value_;
                    NVUtil::appendStringValue(cp.properties,
                            "pointerport.address", ss.str().c_str());
                }
                else
                {
                    // Check the connector profile for an address
                    CORBA::Long ii = NVUtil::find_index(cp.properties,
                            "pointerport.address");
                    if (ii >= 0)
                    {
                        // Another port in the chain has allocated
                        // memory. This port will get the address in
                        // subscribeInterfaces().
                        return RTC_OK;
                    }
                    RTC_INFO(("pointerport.address key not found"));
                    // Allocate the memory space
                    port_value_ = new PortValue<DataType>;
                    port_value_->value_ = new DataType;
                    data_is_mine_ = true;
                    // Place the current address in the connector profile
                    std::stringstream ss;
                    ss << port_value_;
                    NVUtil::appendStringValue(cp.properties,
                            "pointerport.address", ss.str().c_str());
                }
                return RTC_OK;
            }

            ReturnCode_t subscribeInterfaces(ConnectorProfile const& cp)
            {
                // Get the address from the connector profile
                CORBA::Long ii = NVUtil::find_index(cp.properties,
                        "pointerport.address");
                if (ii < 0)
                {
                    RTC_ERROR(("No address found for pointer sharing"));
                    return RTC_ERROR;
                }
                char const* address(0);
                if (!(cp.properties[ii].value >>= address))
                {
                    RTC_ERROR(("pointerport.address is empty"));
                    return RTC_ERROR;
                }
                // Put the address into the pointer
                std::istringstream is(address);
                void* temp;
                if (!(is >> temp))
                {
                    RTC_ERROR(("Failed to read pointer address"));
                    return RTC_ERROR;
                }
                RTC_DEBUG(("Read pointer address %p from %s", temp,
                            address));
                port_value_ = reinterpret_cast<PortValue<DataType>*>(temp);
                data_is_mine_ = false;
                return RTC_OK;
            }

            void unsubscribeInterfaces(ConnectorProfile const& cp)
            {
                RTC_TRACE(("unsubscribeInterfaces()"));
                if (data_is_mine_ && port_value_)
                {
                    if (boost::is_array<DataType>::value)
                    {
                        delete[] port_value_->value_;
                    }
                    else
                    {
                        delete port_value_->value_;
                    }
                    delete port_value_;
                }
                port_value_ = 0;
                data_is_mine_ = false;
            }
    };
}; // namespace RTC

#endif // !defined(POINTERPORT_H_)

