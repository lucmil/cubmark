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

#ifndef CUBMARK_F1_H
#define CUBMARK_F1_H

#include <functional>

namespace cb
{

/** \brief Test function 1
 *
 * \f[ f(x,y) =
 * 		\sin( r )
 * 		\exp \left( -t r^2 \right)
 * \f]
 * where
 * \f[ r = \sqrt{(x - \alpha)^2 + (y - \beta)^2} \f]
 * \f[ \alpha = 4 x_0 - 2 \f]
 * \f[ \beta = 4 y_0 - 2 \f]
 * \f[ t = \frac{8}{C_x + C_y + 1} \f]
 *
 * The test integral is of the form:
 * \f[ \int_\infty^\infty \int_\infty^\infty f(x,y) dy dx =
 * 		\frac{\pi}{t} \exp(-\frac{1}{4t}) \sqrt{ \frac{\pi}{4t} } \f]
 */
class F1
:   public std::binary_function<double, double, double>
{
public:
	/** \brief Constructor
	 *
	 * \param C
	 * \param x
	 */
	F1(double C[] = 0, double x0[] = 0);
	double operator()(double x, double y) const;
private:
	double t;
	double alpha;
	double beta;
};

}

#endif//CUBMARK_F1_H
