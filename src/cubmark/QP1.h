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

#ifndef CUBMARK_QP1_H
#define CUBMARK_QP1_H

#include <functional>

namespace cb
{

/** \brief QP1 test function
 *
 * \f[ f(x,y) = \frac{1} {(x^2 + y^2 + c^{-1})^2} \f]
 *
 * Proper integrals:
 * \f[ \int_0^\infty \int_0^\infty f(x,y) \, dy dx = \frac{1}{4} c \pi \f]
 * where \f$ c = [200 (C_x C_y + 1) ]^{-1} \f$
 */
class QP1
:   public std::binary_function<double, double, double>
{
public:
	/** \brief Constructor
	 *
	 * \param c   \f$ c \f$
	 */
	QP1(double c = 1.0);

	double operator()(double x, double y) const throw();

private:
	/** \brief \f$ c^{-1} \f$
	 */
	double cR;
};

}

#endif//CUBMARK_QP1_H
