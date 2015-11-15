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

#include <cubmark/Wigner.h>
#ifndef CUBMARK_WIGNER_HPP
#define CUBMARK_WIGNER_HPP

#include <functional>
#include <cmath>

#include <cubmark/debug.h>
#include <cubmark/adapter.h>

extern "C"
{
#include <gsl/gsl_errno.h>
}

namespace cb
{

template<class F>
struct WavefuncIntegrand
:   public std::binary_function<double, void*, double>
{
	double operator()(double zeta, void*) const throw()
	{
		return f(x + zeta *.5) * f(x - zeta *.5);
	}
	F f;
	double x, k;
};

template<class F>
Wigner<F>::Wigner() :
	a(0.), b(0.),
	epsabs(0.), epsrel(0.),
	calls(0),
	ws(0)
{
}

template<class F>
Wigner<F>::wigner(double _a, double _b, const F& _psi, double _epsrel,
		double _epsabs) :
	a(_a),
	b(_b),
	epsabs(_epsabs),
	epsrel(_epsrel),
	calls(100u),
	ws(0),
	psi(_psi)
{
	workspace_realloc(1000);
}

template<class F>
Wigner<F>::~Wigner()
{
	gsl_integration_workspace_free(ws);
}

template<class F>
double Wigner<F>::operator()(double x, double k) const
{
	// Upper integration boundary
	double zu;
	{
		const double z_a = (x-a), z_b = (b-x);
		zu = 2.*((z_a < z_b) ? z_a : z_b); // min(z_a, z_b)
	}

	WignerWrapper<F> w_n;
	w_n.f = psi;
	w_n.x = x;
	w_n.k = k;
	typename BinaryAdapter<WavefuncWrapper<F> Type f_a(Adapter(w_n));

	gsl_function f;
	f.function = f_a.getPtr();
	f.params = 0;

	gsl_integration_qawo_table *qawo_tbl =
		gsl_integration_qawo_table_alloc(k, zu, GSL_INTEG_COSINE, 16);

	double r = 0., est = 0.;
	int status = 0;
	status = gsl_integration_qawo(&f, a, epsrel, epsabs, calls, ws, qawo_tbl,
			&r, &est);

	gsl_integration_qawo_table_free(qawo_tbl);
	if(status)
	{
		throw std::logic_error(gsl_strerror(status));
	}
	return r/M_PI;
}

template<class F>
void Wigner<F>::workspace_realloc(size_t n)
{
	if(ws != 0)
	{
		gsl_integration_workspace_free(ws);
	}
	ws = gsl_integration_workspace_alloc(n);
}

}
#endif//CUBMARK_WIGNER_HPP

