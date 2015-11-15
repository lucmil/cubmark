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

#ifndef CUBMARK_W1_H
#define CUBMARK_W1_H

#include <functional>

namespace cb
{

/** \brief Analitic form of the wigner function for a constant wavefunction
 *
 * \f[
 * W_n(x,k) = \frac{1}{\pi}
 * \int_0^{min\{2 x; 2(x_0 - x)\}}
 *      \psi^\ast_n \left(x-\frac{\zeta}{2} \right)
 *      \psi_n      \left(x+\frac{\zeta}{2} \right) \cos(k \zeta) d \zeta
 * \f]
 * See cb::W1WaveFunc.
 */
class W1 :
	public std::binary_function<double, double, double>
{
public:
	/** \brief Constructor
	 *
	 * \param x0 Upper boundary
	 */
	W1(double x0[] = 0);

	/** \brief Overloaded function operator
	 *
	 * \param x \f$ x \f$
	 * \param k \f$ k \f$
	 * \returns \f$ W_n(x, k) \f$
	 */
	double operator()(double x, double k) const throw();

private:
	/** \brief \f$ x_0 \f$
	 */
	double x0[1];

	/** \brief Normalization constant divided by PI
	 */
	double N;
};

}

#endif//CUBMARK_W1_H
