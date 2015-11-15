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

#ifndef CUBMARK_W3WAVEFUNC_H
#define CUBMARK_W3WAVEFUNC_H

#include <functional>

namespace cb
{

/** \brief Wavefunction for testing with cb::wigner
 *
 * \f[
 * \psi_n(x) = \sqrt{\frac{2}{L}} \sin \left(\frac{n \pi x}{L} \right)
 * \f]
 * for \f$ x \in [a,b] \f$ where \f$ L = b - a \f$.
 * Also \f$ \psi_n(x) = 0 \f$ for \f$ x \in (-\infty,a) \cup (b,\infty) \f$.
 *
 * An analitic form of the Wigner function is in cb::W3
 */
struct W3WaveFunc
:   public std::unary_function<double, double>
{
	/** \brief Default constructor
	 */
	W3WaveFunc();

	/** \brief Constructor
	 *
	 * \param n \f$ n \f$
	 * \param a \f$ a \f$
	 * \param b \f$ b \f$
	 */
	W3WaveFunc(unsigned n, double a, double b);

	/** \brief Overloaded function operator
	 *
	 * \param x \f$ x \f$
	 * \returns \f$ psi_n(x) \f$
	 */
	double operator()(double x) const throw();

	unsigned n;
	double a;
	double b;
	double L;
};

}
#endif//CUBMARK_W3WAVEFUNC_H
