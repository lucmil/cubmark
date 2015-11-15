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

#ifndef CUBMARK_W2_H
#define CUBMARK_W2_H

#include <functional>

namespace cb
{

/** \brief Analitic form of the wigner function for a triangular wavefunction
 *
 * \f[
 * W_n(x,k) = \frac{1}{\pi}
 * \int_0^{min\{2(x);(x_0 - x)\}}
 *      \psi^\ast_n \left(x-\frac{\zeta}{2} \right)
 *      \psi_n      \left(x+\frac{\zeta}{2} \right) \cos(k \zeta) dz
 * \f]
 *
 * The function is defined by the tipping point \f$ T = (C_x, y) \f$
 * of the wavefunction, where y is such that the wavefunction is normalized.
 * The wavefunction is defined to be linear over [0,x_0] and zero otherwise
 *
 * See cb::W2WaveFunc.
 */
class W2 :
	public std::binary_function<double, double, double>
{
public:
	/** \brief Constructor
	 *
	 * \precond \f$ 0 < x_0 \f$
	 * \precond \f$ 0 < C_x \f$
	 * \param C C_x parameter
	 * \param x0 Upper limit of the wavefunction
	 */
	W2(double C[] = 0, double x0[] = 0);

	/** \brief Overloaded function operator
	 *
	 * \param x \f$ x \f$
	 * \param k \f$ k \f$
	 * \returns \f$ W_n(x, k) \f$
	 */
	double operator()(double x, double k) const throw();

private:
	double b;

	/** \brief \f$ C_x \f$
	 */
	double C[1];

	/** \brief \f$ x_0 \f$
	 */
	double x0[1];

	/** \brief \f$ A_l \f$
	 *
	 * Left slope
	 */
	double A_l;

	/** \brief \f$ B_l \f$
	 *
	 * Left slope
	 */
	double B_l;

	/** \brief \f$ A_r \f$
	 *
	 * Right slope
	 */
	double A_r;

	/** \brief \f$ B_r \f$
	 *
	 * Right slope
	 */
	double B_r;

	/** \brief Squared normalization constant
	 */
	double N_sqr;

	/** \brief Indefinite integral when the boundary fits on one slope.
	 *
	 * \f[
	 * W_n(x,k) =
	 *   \frac{1}{\pi k} {A^2 x^2 \sin(k \zeta)}
	 * - \frac{1}{4 \pi k} \, {A^2 \zeta^2 \sin(k \zeta)}
	 * + \frac{2}{\pi k} \, {A B x \sin(k \zeta)}
	 * - \frac{1}{2 \pi k^2} \, {A^2 \zeta \cos(k \zeta)}
	 * + \frac{1}{\pi k}{B^2 \sin(k \zeta)}
	 * + \frac{1}{2 \pi k^3} \, {A^2 \sin(k \zeta)}
	 * \f]
	 */
	double I(double A, double B, double z, double x, double k) const throw();

	/** \brief Indefinite integral when the boundary fits on one slope and k = 0.
	 *
	 * \f[
	 * W_n(x,k = 0) =
	 *   \frac{1}{\pi} {A^2 x^2 \zeta}
	 * - \frac{1}{12\pi} \, {A^2 \zeta^3}
	 * + \frac{2}{\pi} \, {A B x \zeta}
	 * + \frac{1}{\pi} {B^2 \zeta}
	 * \f]
	 *
	 */
	double I_0(double A, double B, double z, double x) const throw();

	/** \brief Indefinite integral when the boundary is on both slopes
	 *
	 * \f[
	 * W_n(x,k) =
	 *   \frac{1}{\pi k} {A_l A_r x^2 \sin(k \zeta)}
	 * - \frac{1}{4 \pi k} \, {A_l A_r \zeta^2 \sin(k \zeta)}
	 * + \frac{1}{\pi k} {A_l B_r x \sin(k \zeta)}
	 * - \frac{1}{2 \pi k} \, {A_l B_r \zeta \sin(k \zeta)}
	 * + \frac{1}{\pi k} {A_r B_l x \sin(k \zeta)}
	 * + \frac{1}{2 \pi k} \, {A_r B_l \zeta \sin(k \zeta)}
	 * - \frac{1}{2 \pi k^2} \, {A_l A_r \zeta \cos(k \zeta)}
	 * + \frac{1}{\pi k} {B_l B_r \sin(k \zeta)}
	 * - \frac{1}{2 \pi k^2} \, {A_l B_r \cos(k \zeta)}
	 * + \frac{1}{2 \pi k^2} \, {A_r B_l \cos(k \zeta)}
	 * + \frac{1}{2 \pi k^3} \, {A_l A_r \sin(k \zeta)}
	 * \f]
	 *
	 */
	double I_lr(double z, double x, double k) const throw();


	/** \brief Indefinite integral when the boundary is on both slopes, k = 0
	 *
	 * \f[
	 * W_n(x,k = 0) =
	 *   \frac{1}{\pi} {A_l A_r x^2 \zeta}
	 * - \frac{1}{12 \pi} \, {A_l A_r \zeta^3}
	 * + \frac{1}{\pi} {A_l B_r x \zeta}
	 * - \frac{1}{4 \pi} \, {A_l B_r \zeta^2}
	 * + \frac{1}{\pi} {A_r B_l x \zeta}
	 * + \frac{1}{4 \pi} \, {A_r B_l \zeta^2}
	 * + \frac{1}{\pi} {B_l B_r \zeta}
	 * \f]
	 */
	double I_lr_0(double z, double x) const throw();
};

}

#endif//CUBMARK_W2_H
