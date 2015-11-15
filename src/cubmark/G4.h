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

#ifndef CUBMARK_G4_H
#define CUBMARK_G4_H

#include <functional>

namespace cb
{

/** \brief Genz "Gaussian" test function
 *
 * \f[
 * f(x,y) = \exp(-(C_x^2 (x - x_0^2) + C_y^2 (y - y_0)^2))
 * \f]
 *
 * Proper integral:
 * \f[
 * \int_a^b dx \int_c^d dy f(x,y) =
 * \frac{1}{4 \, C_x C_y}
 * 	{\left[
 * 		\pi \mathop{\rm Erf}(-C_x b + C_x x_0)
 * 		- \pi \mathop{\rm Erf}(-C_x a + C_x x_0)
 * 	\right]} \mathop{\rm Erf}(-C_y d + C_y y_0)
 * 	- {\left[
 * 		\pi \mathop{\rm Erf}(-C_x b + C_x x_0)
 * 		- \pi \mathop{\rm Erf}(-C_x a + C_x x_0)
 * 	\right]} \mathop{\rm Erf}(-C_y c + C_y y_0)
 * \f]
 *
 * Plane integral:
 * \f[
 * \int_{-\infty}^{\infty} \int_{-\infty}^{\infty} f(x,y) \, dy dx =
 * \frac{4}{C_x C_y}
 * \f]
 */
class G4
:   public std::binary_function<double, double, double>
{
public:
	/** \brief Constructor
	 *
	 * \param C   Two element array with C_x,C_y scaling parameters
	 * \param x_0 Two element array with x_0,y_0 peak displacement parameters
	 */
	G4(double C[] = 0, double x_0[] = 0);

	double operator()(double x, double y) const throw();

private:
	double C[2];
	double x_0[2];
};

}

#endif//CUBMARK_G4_H
