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

#ifndef CUBMARK_G3_H
#define CUBMARK_G3_H

#include <functional>

namespace cb
{

/** \brief Genz "Corner peak" test function
 *
 * \f[
 * f(x,y) = \frac{1}{(1 + w_x + w_y)^3}
 * \f]
 * where
 * \f[
 * w_x = \left\{ \begin{array} {ll}
 * x & {\rm for} \, x \le \frac{1}{2} \\
 * C_x - x & {\rm otherwise}
 * \end{array} \right.
 * \f]
 * Likewise for \f$ w_y \f$
 *
 * This means that the \f$ x_0 \f$ vector decides
 * the placement of the corner peak instead of displacement.
 *
 * Proper integral:
 * \f[
 * \int_0^{C_x} \int_0^{C_y} f(x,y) \, dy dx =
 * 		\frac{1}{2} C_y \left(
 * 				\frac{1}{C_y + 1}
 * 			-	\frac{1}{C_x^2 + C_x C_y + 2 C_x + C_y + 1}
 * 		\right)
 * \f]
 */
class G3
:   public std::binary_function<double, double, double>
{
public:
	/** \brief Constructor
	 *
	 * \param C	Two element array
	 * \param x Upper boundaries of the integration region
	 */
	G3(double C[] = 0, double x[] = 0);
	double operator()(double x, double y) const;
private:
	double C[2];
	double x0[2];
};

}

#endif//CUBMARK_G3_H
