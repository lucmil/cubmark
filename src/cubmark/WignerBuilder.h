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

#ifndef CUBMARK_WIGNERBUILDER_H
#define CUBMARK_WIGNERBUILDER_H

#include <memory>

#include <cubmark/Wigner.h>

namespace cb
{

template<class F>
class WignerBuilder
{
public:
	WignerBuilder & a(double d_a);
	WignerBuilder & b(double d_b);
	WignerBuilder & epsabs(double d_epsabs);
	WignerBuilder & epsrel(double d_epsrel);
	WignerBuilder & psi(const F& d_psi);
	wigner<F> create() const;

	static WignerBuilder & getInstance();

private:
	WignerBuilder();
	WignerBuilder(const WignerBuilder &);
	WignerBuilder & operator=(const WignerBuilder &);

	double d_a;
	double d_b;
	double d_epsabs;
	double d_epsrel;
	F d_psi;

	static std::unique_ptr<WignerBuilder> instance;
};

}
#endif//CUBMARK_WIGNERBUILDER_H
