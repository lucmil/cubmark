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

#ifndef CUBMARK_URNG_H
#define CUBMARK_URNG_H

#include <cubmark/types.h>

namespace cb
{

/** \brief Random integer number generator
 *
 * Defaults to mt19937 if the platform does not supply a random device.
 */
extern
tr1::random_device urng;

/** \brief High-quality random double-precision number generator
 *
 * Generates random numbers from the [0,1) range.
 */
extern
tr1::ranlux48 urng01;

}

#endif//CUBMARK_URNG_H

