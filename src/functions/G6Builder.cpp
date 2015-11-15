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

#include <cubmark/G6Builder.h>

#include <cubmark/adapter/adapter.h>
#include <cubmark/constants.h>
#include <cubmark/algorithm.h>
#include <cubmark/debug.h>
#include <cubmark/InvalidValueError.h>

namespace cb
{

G6Builder::G6Builder()
{
}

void G6Builder::setupAdapter()
{
	G6 ftor(dC, dx0);
	if(!ftorAdapter)
	{
		adapter<G6>(ftorAdapter);
	}
	adapterSetFunctor(ftorAdapter, ftor);
}

double G6Builder::integral(const Boundary& boundary)
{
	CHECK(		feq0(boundary.l(0)) && feq(boundary.u(0), 1.0)
			&&	feq0(boundary.l(1)) && feq(boundary.u(1), 1.0),
			InvalidValueError("Only unit square solution available."));

	return		( exp(dC[0] * dx0[0]) - 1 ) / dC[0]
			*	( exp(dC[1] * dx0[1]) - 1 ) / dC[1];
}

}
