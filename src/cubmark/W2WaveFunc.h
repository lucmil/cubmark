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

#ifndef CUBMARK_W2WAVEFUNC_H
#define CUBMARK_W2WAVEFUNC_H

#include <functional>

namespace cb
{

/** \brief Wavefunction for testing with cb::wigner
 *
 * Triangular function:
 * \f[
 * \psi_n(x) = N (A_l x + B_l)
 * \f]
 * for \f$ x \in (a,x_t) \f$
 * \f[
 * \psi_n(x) = N (A_r x + B_r)
 * \f]
 * for \f$ x \in [x_t,b) \f$
 * \f[ \psi_n(x_t) = N y_t \f]
 * and \f$ \psi_n(x) = 0 \f$ for \f$ x \in (-\infty,a] \cup [b,\infty) \f$.
 */
struct W2WaveFunc
:   public std::unary_function<double, double>
{
	W2WaveFunc();

	/** \brief Constructor
	 *
	 *  The function is defined by the tipping point \f$ T = (x_t, y_t) \f$.
	 *
	 *  \pre \f$ x_t \in [a,b] \f$
	 *
	 * \param x \f$ x_t \f$
	 * \param y \f$ y_t \f$
	 * \param a \f$ a \f$
	 * \param b \f$ b \f$
	 */
	W2WaveFunc(double x, double y, double a, double b);

	/** \brief Overloaded function operator
	 *
	 * \param x \f$ x \f$
	 * \returns \f$ psi_n(x) \f$
	 */
	double operator()(double x) const;

	/** \brief \f$ a \f$
	 */
	double a;

	/** \brief \f$ b \f$
	 */
	double b;

	/** \brief \f$ x_t \f$
	 */
	double x_t;

	/** \brief \f$ A_l \f$
	 */
	double A_l;

	/** \brief \f$ B_l \f$
	 */
	double B_l;

	/** \brief \f$ A_r \f$
	 */
	double A_r;

	/** \brief \f$ B_r \f$
	 */
	double B_r;

	/** \brief \f$ N \f$
	 *
	 * Normalization constant
	 */
	double N;
};

}
#endif//CUBMARK_W2WAVEFUNC_H
