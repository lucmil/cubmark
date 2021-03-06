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

#ifndef CUBMARK_W1WAVEFUNC_H
#define CUBMARK_W1WAVEFUNC_H

#include <functional>

namespace cb
{

/** \brief Wavefunction for testing with cb::wigner
 *
 * Normalized wavefunction, constant for \f$ x \in [a,b] \f$.
 * \f[
 * \psi_n(x) = \frac{1}{\sqrt{b-a}}
 * \f]
 *
 * Also \f$ \psi_n(x) = 0 \f$ for \f$ x \in (-\infty,a) \cup (b,\infty) \f$.
 */
struct W1WaveFunc
:   public std::unary_function<double, double>
{
	/** \brief Default constructor
	 */
	W1WaveFunc();

	/** \brief Constructor
	 *
	 * \param a \f$ a \f$
	 * \param b \f$ b \f$
	 */
	W1WaveFunc(double a, double b);

	/** \brief Overloaded function operator
	 *
	 * \param x
	 * \returns \f$ psi_n(x) \f$
	 */
	double operator()(double x) const;

	/** \brief \f$ a \f$
	 */
	double a;

	/** \brief \f$ b \f$
	 */
	double b;

	/** \brief \f$ c \f$
	 */
	double c;
};

}
#endif//CUBMARK_PSI_CONSTANT_H
