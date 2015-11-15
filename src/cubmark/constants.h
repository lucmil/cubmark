/*
 * This file is part of Cubature Benchmark.
 * Copyright (C) 2009 Łukasz Lis
 *
 * Cubature Benchmark is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cubature Benchmark is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cubature Benchmark.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CUBMARK_CONSTANTS_H
#define CUBMARK_CONSTANTS_H

#include <limits>
#include <cmath>

namespace cb
{

static const double NaN = std::numeric_limits<double>::quiet_NaN();
static const double sNaN = std::numeric_limits<double>::signaling_NaN();
static const double inf = std::numeric_limits<double>::infinity();
static const double eps = std::numeric_limits<double>::epsilon();
static const double PI = static_cast<double>(4.0l * atanl(1.0l));

}

#endif//CUBMARK_CONSTANTS_H
