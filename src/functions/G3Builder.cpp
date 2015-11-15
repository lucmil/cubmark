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

#include <cubmark/G3Builder.h>

#include <cubmark/adapter/adapter.h>
#include <cubmark/constants.h>
#include <cubmark/debug.h>
#include <cubmark/InvalidValueError.h>

namespace cb
{

G3Builder::G3Builder()
{
}

RandomFunctorBuilder& G3Builder::C(double C_dim, unsigned long dim)
{
	const double Cp = C_dim / difficultyFactor();
	defaultBoundary.setU(dim, Cp);
	return RandomFunctorBuilder::C(C_dim, dim);
}

void G3Builder::setupAdapter()
{
	G3 ftor(dC, dx0);
	if(!ftorAdapter)
	{
		adapter<G3>(ftorAdapter);
	}
	adapterSetFunctor(ftorAdapter, ftor);
}

double G3Builder::integral(const Boundary& boundary)
{
	const double C_x = boundary.u(0);
	const double C_y = boundary.u(1);
	const char* domainErrorMsg =
			"No analytic solution available for chosen parameters";

	CHECK(!boundary.isInfinite(), InvalidValueError(domainErrorMsg));
	CHECK(C_x > 0.0, InvalidValueError(domainErrorMsg));
	CHECK(C_y > 0.0, InvalidValueError(domainErrorMsg));

	return 0.5*C_y/(C_y + 1.0)
			- 0.5*C_y/(C_x * C_x + C_x*C_y + 2*C_x + C_y + 1.0);
}

}
