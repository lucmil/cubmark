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

#ifndef CUBMARK_W3_H
#define CUBMARK_W3_H

#include <functional>

namespace cb
{

/** \brief Analytic form of W_n(x,k) for an infinite potential well
 *
 * \f[
 * W_n(x,k) = \frac{1}{\pi}
 * \int_0^{min\{2(x-a);2(b-a)\}}
 *      \psi^\ast_n \left(x-\frac{\zeta}{2} \right)
 *      \psi_n      \left(x+\frac{\zeta}{2} \right) \cos(k \zeta) dz
 * \f]
 * See cb::W3WaveFunc.
 */
struct W3 :
	std::binary_function<double, double, double>
{
	/** \brief Constructor
	 *
	 * \param n \f$ n \f$
	 * \param b \f$ b \f$
	 */
	W3(int n = 1, double x0[] = 0);

	/** \brief Overloaded call operator
	 *
	 * \f[
	 * W_n(x,k) = \frac{1}{2 \pi L} \, \left[
	 * \frac{1}{\frac{\pi n}{L} - k} \sin\left({(\frac{\pi n}{L} - k)} \zeta\right)
	 * + \frac{1}{\frac{\pi n}{L} + k} \sin\left((\frac{\pi n}{L} + k) \zeta\right)
	 * + \frac{1}{k} \sin\left(2 \, \frac{\pi n x}{L} - k \zeta\right)
	 * - \frac{1}{k} \sin\left(2 \, \frac{\pi n x}{L} + k \zeta\right)
	 * \right]
	 * \f]
	 * for \f$ k \ne 0 \f$ and
	 * \f[
	 * W_n(x,k = 0) = -\frac{1}{\pi L} \left[
	 *       \zeta \cos\left(2 \, \frac{\pi n x}{L}\right)
	 *      -\frac{L}{\pi n} \sin\left(\frac{\pi n \zeta}{L}\right)
	 * \right]
	 * \f]
	 * where
	 * \f[
	 * \zeta = \min\left\{ 2(x-a); 2(b-x) \right\}
	 * \f]
	 *
	 * \param x \f$ x \f$
	 * \param k \f$ k \f$
	 * \returns \f$ W_n(x,k) \f$
	 */
	double operator()(double x, double k) const throw();

private:
	int n;
    double x0[1];
};

}

#endif//CUBMARK_W3_H
