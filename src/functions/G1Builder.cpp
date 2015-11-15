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

#include <cubmark/G1Builder.h>

#include <cubmark/adapter/adapter.h>
#include <cubmark/constants.h>
#include <cubmark/algorithm.h>
#include <cubmark/debug.h>
#include <cubmark/InvalidValueError.h>

namespace cb
{

G1Builder::G1Builder()
{
}

void G1Builder::setupAdapter()
{
	G1 ftor(dR);
	if(!ftorAdapter)
	{
		adapter<G1>(ftorAdapter);
	}
	adapterSetFunctor(ftorAdapter, ftor);
}

RandomFunctorBuilder& G1Builder::C(double C_dim, unsigned long dim)
{
	const double Cp = C_dim / difficultyFactor();
	defaultBoundary.setU(dim, Cp);
	return RandomFunctorBuilder::C(C_dim, dim);
}

double G1Builder::integral(const Boundary& boundary)
{
	CHECK(feq0(boundary.l(0)) && feq0(boundary.l(1)) ,
			InvalidValueError("Lower boundary has to be 0"));

	CHECK(!boundary.isInfinite(), InvalidValueError("Solution for infinite"
			" integration boundary is divergent."));

	const double C_x = boundary.u(0);
	const double C_y = boundary.u(1);

	return (  cos(2*PI*dR + C_x)
			+ cos(2*PI*dR + C_y)
			- cos(2*PI*dR + C_x + C_y)
			- cos(2*PI*dR)) ;
}

}
