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

#ifndef CUBMARK_G1_H
#define CUBMARK_G1_H

#include <functional>

namespace cb
{

/** \brief Genz "Oscillatory" test function
 *
 * \f[
 * f(x,y) = \cos ( 2 \pi R + x + y)
 * \f]
 *
 * The C vector is used for upper integration boundary instead of scaling.
 *
 * The test integral is of the form:
 * \f[
 * \int_0^{C_x} \int_0^{C_y} f(x,y) \, dy dx =
 *   \cos( 2 \pi R + C_x )
 * + \cos( 2 \pi R + C_y )
 * - \cos( 2 \pi R + C_x + C_y )
 * - \cos( 2 \pi R )
 * \f]
 */
class G1
:   public std::binary_function<double, double, double>
{
public:
	/** \brief Constructor
	 *
	 * \param R phase
	 */
	G1(double R = 1);
	double operator()(double x, double y) const throw();
private:
	double R;
};

}

#endif//CUBMARK_G1_H
