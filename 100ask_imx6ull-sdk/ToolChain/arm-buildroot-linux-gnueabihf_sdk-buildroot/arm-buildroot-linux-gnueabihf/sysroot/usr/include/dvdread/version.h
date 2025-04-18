/*
 * This file is part of libdvdread
 * Copyright (C) 2015 VideoLAN
 *
 * This file is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef DVDREAD_VERSION_H_
#define DVDREAD_VERSION_H_

#define DVDREAD_VERSION_CODE(major, minor, micro) \
    (((major) * 10000) +                         \
     ((minor) *   100) +                         \
     ((micro) *     1))

#define DVDREAD_VERSION_MAJOR 6
#define DVDREAD_VERSION_MINOR 0
#define DVDREAD_VERSION_MICRO 2

#define DVDREAD_VERSION_STRING "6.0.2"

#define DVDREAD_VERSION \
    DVDREAD_VERSION_CODE(DVDREAD_VERSION_MAJOR, DVDREAD_VERSION_MINOR, DVDREAD_VERSION_MICRO)

#endif /* DVDREAD_VERSION_H_ */
