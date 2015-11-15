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

#ifndef CUBMARK_P1_H
#define CUBMARK_P1_H

#include <cubmark/QP1.h>

namespace cb
{

/** \brief P1 test function
 *
 * \f[ f(x,y) = \frac{1} {(x^2 + y^2 + c^{-1})^2} \f]
 *
 * The only difference between P1 and QP1 are their test integrals and the c
 * parameter.
 *
 * Proper integral:
 * \f[ \int_{-\infty}^\infty \int_{-\infty}^\infty f(x,y) \, dy dx = c \pi \f]
 * where \f$ c = (C_x C_y + 1)/30 \f$
 */
typedef cb::QP1 P1;

}

#endif//CUBMARK_P1_H
