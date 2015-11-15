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

#ifndef CUBMARK_G5_H
#define CUBMARK_G5_H

#include <functional>

namespace cb
{

/** \brief Genz "C0" test function
 *
 * \f[
 * f(x,y) = \exp(-C_x |x - x_0| -C_y |y - y_0|)
 * \f]
 *
 * The X vector contains the coordinates of the saddle point.
 *
 * Proper integral:
 * \f[
 * \int_0^1 \int_0^1 f(x,y) \, dy dx =
 * 		\frac{1}{C_x}
 * 		\frac{1}{C_y}
 *		\left[ 2
 * 			- \exp(-C_x x_0)
 * 			- \exp(C_x x_0 - C_x)
 * 		\right]
 *
 * 		\left[ 2
 * 			- \exp(-C_y y_0)
 * 			- \exp(C_y y_0 - C_y)
 * 		\right]
 * \f]
 */
class G5
:   public std::binary_function<double, double, double>
{
public:
	/** \brief Constructor
	 *
	 * \param C		Two element array with C_x,C_y scaling parameters
	 * \param x0	Two element array with x_0,y_0 peak displacement parameters
	 */
	G5(double C[] = 0, double x0[] = 0);

	double operator()(double x, double y) const throw();

private:
	double C[2];
	double x0[2];
};

}

#endif//CUBMARK_G5_H
