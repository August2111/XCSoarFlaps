/*
  Copyright_License {

  XCSoar Glide Computer - http://www.xcsoar.org/
  Copyright (C) 2000 - 2009

  M Roberts (original release)
  Robin Birch <robinb@ruffnready.co.uk>
  Samuel Gisiger <samuel.gisiger@triadis.ch>
  Jeff Goodenough <jeff@enborne.f2s.com>
  Alastair Harrison <aharrison@magic.force9.co.uk>
  Scott Penrose <scottp@dd.com.au>
  John Wharington <jwharington@gmail.com>
  Lars H <lars_hn@hotmail.com>
  Rob Dunning <rob@raspberryridgesheepfarm.com>
  Russell King <rmk@arm.linux.org.uk>
  Paolo Ventafridda <coolwind@email.it>
  Tobias Lohner <tobias@lohner-net.de>
  Mirek Jezek <mjezek@ipplc.cz>
  Max Kellermann <max@duempel.org>

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
  }
*/


#ifndef TASKPOINT_HPP
#define TASKPOINT_HPP

#include "Util/Serialisable.hpp"
#include "Navigation/ReferencePoint.hpp"
#include "Navigation/Waypoint.hpp"
#include "Navigation/Aircraft.hpp"

struct GLIDE_RESULT;
class MacCready;


class TaskPoint : 
  public ReferencePoint, public Serialisable {
public:
  TaskPoint(const WAYPOINT & wp) : Elevation(wp.Altitude), 
                                            ReferencePoint(wp.Location)
    { }

  // not const because may need to perform lookup and save
  virtual double getElevation() const;

  virtual GEOPOINT get_reference_remaining() const;
  
  double get_bearing(const AIRCRAFT_STATE &) const;

  double get_distance(const AIRCRAFT_STATE &) const;

  virtual double get_distance_remaining(const AIRCRAFT_STATE &) const;
  virtual double get_bearing_remaining(const AIRCRAFT_STATE &) const;

  GLIDE_RESULT glide_solution_remaining(const AIRCRAFT_STATE &, 
                                        const MacCready &mac,
                                        const double minH=0) const;
  GLIDE_RESULT glide_solution_sink(const AIRCRAFT_STATE &, 
                                   const MacCready &mac,
                                   const double S) const;
  virtual void print(std::ostream& f) const;

protected:
  const double Elevation;
};

#endif
