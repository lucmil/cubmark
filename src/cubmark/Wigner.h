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

/** \example wigner_grid.cpp
 * Example usage of the cb::wigner class template
 */
#ifndef CUBMARK_WIGNER_H
#define CUBMARK_WIGNER_H

#include <functional>
#include <cmath>

#include <cubmark/debug.h>
#include <cubmark/adapter.h>

extern "C"
{
#include <gsl/gsl_integration.h>
}

namespace cb
{

template<class F>
class WignerBuilder;

/** \brief Wigner functor class
 *
 * This functor approximates a value of a Wigner function for a given
 * wavefunction.
 *
 * \f[
 * W_n(x,k) = \frac{1}{\pi}
 * \int_0^{min\{2(x-a);2(x-b)\}}
 *      \psi^\ast_n \left(x-\frac{\zeta}{2} \right)
 *      \psi_n      \left(x+\frac{\zeta}{2} \right) \cos(k \zeta) dz
 * \f]
 * where \f$ \psi_n(x) = 0 \f$ for \f$ x \in (-\infty,a) \cup (b,\infty) \f$.
 *
 * \pre The \c F class has a default constructor defined
 * \pre The \c F class has an overloaded assignment operator defined
 * \pre The \c F class has a \c const overloaded unary function operator defined
 * \tparam F Wavefunction functor class
 *
 * \todo Use QagRule for integration
 */
template<class F>
class Wigner
:   public std::binary_function<double, double, double>
{
public:
	/** \brief Default constructor
	 */
	Wigner();

	/** \brief Constructor
	 *
	 * Initializes a \c GSL integration workspace.
	 *
	 * \param a \f$ a \f$
	 * \param b \f$ b \f$
	 * \param psi Instance of the wavefunction functor
	 * \param epsrel Relative error tolerance
	 * \param epsabs Absolute error tolerance
	 */
	Wigner(double a, double b, const F& psi, double epsrel, double epsabs = 0.);

	/** \brief Destructor
	 */
	~Wigner();

	double operator()(double x, double k) const;

private:
	void workspace_realloc(size_t n);
	double a;
	double b;
	double epsabs;
	double epsrel;
	size_t calls;
	gsl_integration_workspace *ws;
	F psi;
};

}

#include <cubmark/WignerBuilder.h>

#endif//CUBMARK_WIGNER_H

