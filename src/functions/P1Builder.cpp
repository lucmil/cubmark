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

#include <cubmark/P1Builder.h>

#include <cubmark/adapter/adapter.h>
#include <cubmark/constants.h>
#include <cubmark/debug.h>
#include <cubmark/InvalidValueError.h>

namespace cb
{

P1Builder::P1Builder() :
	RandomFunctorBuilder(Boundary(-inf, inf, -inf, inf))
{
}

double P1Builder::c() const
{
	return (dC[0] + dC[1] + 1.0)/30.0;
}

void P1Builder::setupAdapter()
{
	P1 ftor(c());
	if(!ftorAdapter)
	{
		adapter<P1>(ftorAdapter);
	}
	adapterSetFunctor(ftorAdapter, ftor);
}

double P1Builder::integral(const Boundary& boundary)
{
	CHECK(boundary.l(0) == -inf && boundary.l(1) == -inf,
			InvalidValueError("Lower boundary has to be infinite"));

	CHECK(boundary.u(0) == inf && boundary.u(1) == inf,
			InvalidValueError("Upper boundary has to be infinite"));

	return PI * c();
}

}
