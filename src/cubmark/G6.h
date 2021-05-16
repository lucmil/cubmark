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

#ifndef CUBMARK_G6_H
#define CUBMARK_G6_H

#include <functional>

namespace cb
{

/** \brief Genz "Discontinuous" test function
 *
 * \f[
 * f(x,y) = \left\{ \begin{array}{ll}
 * \exp(C_x x + C_y y) & {\rm for} \, x \le x_0 \, {\rm and} \, y_0 \le y_0\\
 * 0	& {\rm otherwise}
 * \end{array} \right.
 * \f]
 *
 * Proper integral:
 * \f[
 * \int_0^1 \int_0^1 f(x,y) \, dy dx =
 * 		\frac{1}{C_x C_y} [\exp(C_x x_0) - 1] [\exp(C_y y_0) - 1]
 * \f]
 */
class G6
:   public std::binary_function<double, double, double>
{
public:
	/** \brief Constructor
	 *
	 * \param C   Two element array with C_x,C_y scaling parameters
	 * \param x_0 Two element array with x_0,y_0 peak displacement parameters
	 */
	G6(double C[] = 0, double x_0[] = 0);

	double operator()(double x, double y) const;

private:
	double C[2];
	double x_0[2];
};

}

#endif//CUBMARK_G6_H
