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

#include <cubmark/WignerBuilder.h>

namespace cb
{

WignerBuilder::WignerBuilder() :
	d_a(0),
	d_b(0),
	d_epsrel(0.),
	d_epsabs(0.)
{
}


template<class F>
WignerBuilder & WignerBuilder::a(double _a)
{
	d_a = _a;
	return *this;
}


template<class F>
WignerBuilder & WignerBuilder::b(double _b)
{
	d_b = _b;
	return *this;
}


template<class F>
WignerBuilder & WignerBuilder::epsabs(double _epsabs)
{
	d_epsabs = _epsabs;
	return *this;
}


template<class F>
WignerBuilder & WignerBuilder::epsrel(double _epsrel)
{
	d_epsrel = _epsrel;
	return *this;
}


template<class F>
WignerBuilder & WignerBuilder::psi(const F& d_psi)
{
	d_psi = _psi;
	return *this;
}


template<class F>
wigner<F> WignerBuilder::create() const
{
	return wigner<F>(d_a, d_b, d_psi, d_epsabs, d_epsrel);
}


template<class F>
static WignerBuilder & WignerBuilder::getInstance()
{
	if(!instance.get())
	{
		instance.reset(new WignerBuilder<F>());
	}
	return *instance;
}


template<class F>
std::auto_ptr<WignerBuilder<F> > WignerBuilder::instance;

}
