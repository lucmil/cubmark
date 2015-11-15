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

#include <algorithm>

#include <cubmark/QP1Builder.h>

#include <cubmark/adapter/adapter.h>
#include <cubmark/constants.h>
#include <cubmark/algorithm.h>
#include <cubmark/debug.h>
#include <cubmark/InvalidValueError.h>

namespace cb
{

QP1Builder::QP1Builder() :
	RandomFunctorBuilder(Boundary(0, inf, 0, inf))
{
}

double QP1Builder::c() const
{
	return 1.0/(200.0 * (dC[0] + dC[1] + 1.0));
}

void QP1Builder::setupAdapter()
{
	QP1 ftor(c());
	if(!ftorAdapter)
	{
		adapter<QP1>(ftorAdapter);
	}
	adapterSetFunctor(ftorAdapter, ftor);
}

double QP1Builder::integral(const Boundary& boundary)
{
	CHECK(feq0(boundary.l(0)) && feq0(boundary.l(1)) ,
			InvalidValueError("Lower boundary has to be 0"));

	CHECK(boundary.u(0) == inf && boundary.u(1) == inf,
			InvalidValueError("Upper boundary has to be infinite"));

	return 0.25 * PI * c();
}

}
