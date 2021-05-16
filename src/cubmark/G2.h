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

#ifndef CUBMARK_G2_H
#define CUBMARK_G2_H

#include <functional>
#include <functional>

namespace cb
{

/** \brief Genz "Product peak" test function
 *
 * \f[
 * f(x,y) =
 * \frac{1}
 * {
 * 		\left[C_x^2 + (x - x_0)^2\right]
 * 		\left[C_y^2 + (y - y_0)^2\right]
 * }
 * \f]
 *
 * Proper integral:
 * \f[
 * \int_0^1 \int_0^1 f(x,y) \, dy dx =
 * \frac{-1}{C_x C_y}
 * \left[
 * 		 \arctan\left(-\frac{y_0 - 1}{C_y} \right)
 * 		-\arctan\left(-\frac{y_0}{C_y} \right)
 * \right]
 * \left[
 * 		 \arctan\left(\frac{x_0 - 1}{C_x} \right)
 * 		-\arctan\left(\frac{x_0}{C_x} \right)
 * \right]
 * \f]
 */
class G2
:   public std::binary_function<double, double, double>
{
public:
	/** \brief Constructor
	 *
	 * \param C   Two element array with C_x,C_y scaling parameters
	 * \param x_0 Two element array with x_0,y_0 peak displacement parameters
	 */
	G2(double C[] = 0, double x_0[] = 0);

	double operator()(double x, double y) const;

private:
	double C[2];
	double x_0[2];
};

}

#endif//CUBMARK_G2_H
