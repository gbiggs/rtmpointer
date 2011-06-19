/* rtmpointer
 *
 * Component source file.
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


#include "pub_rtc.h"

#include <rtmpointer/pointerportmgmt.h>
#include <sstream>


PublisherRTC::PublisherRTC(RTC::Manager* manager)
    : RTC::DataFlowComponentBase(manager),
    port_("PublisherPort"), count_(0)
{
}


PublisherRTC::~PublisherRTC()
{
}


RTC::ReturnCode_t PublisherRTC::onInitialize()
{
    // Register the port with the component
    addPointerPort("PublisherPort", port_, *this);
    return RTC::RTC_OK;
}


RTC::ReturnCode_t PublisherRTC::onExecute(RTC::UniqueId ec_id)
{
    port_->int_value = count_++;
    std::stringstream tmp;
    tmp << "String value #" << port_->int_value;
    port_->str_value = tmp.str();
    port_.mark_new();
    return RTC::RTC_OK;
}


static const char* spec[] =
{
    "implementation_id", "PubComp",
    "type_name",         "pubcomp",
    "description",       "RTMPointer data creator component",
    "version",           "1.0",
    "vendor",            "Geoffrey Biggs, AIST",
    "category",          "Example",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
};

extern "C"
{
    void rtc_init(RTC::Manager* manager)
    {
        coil::Properties profile(spec);
        manager->registerFactory(profile, RTC::Create<PublisherRTC>,
                RTC::Delete<PublisherRTC>);
    }
};

