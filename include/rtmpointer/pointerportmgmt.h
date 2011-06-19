/* rtmpointer
 *
 * Header file for port management functions.
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

#if !defined(POINTERPORTMGMT_H_)
#define POINTERPORTMGMT_H_

#include <rtmpointer/pointerport.h>
#include <rtm/RTObject.h>

namespace RTC
{
    bool addPointerPort(char const* name, PointerPortBase& port,
            RTObject_impl& rtc);
}; // namespace RTC

#endif // !defined(POINTERPORTMGMT_H_)

