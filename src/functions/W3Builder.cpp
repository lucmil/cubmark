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

#include <cubmark/W3Builder.h>

#include <cubmark/adapter/adapter.h>
#include <cubmark/constants.h>

namespace cb
{

W3Builder::W3Builder() :
	RandomFunctorBuilder(Boundary(0.0, 1.0, -inf, inf))
{
}

void W3Builder::setupAdapter()
{
	const int N = (int)trunc(dR + 1);
	W3 ftor(N, dx0);
	if(!ftorAdapter)
	{
		adapter<W3>(ftorAdapter);
	}
	adapterSetFunctor(ftorAdapter, ftor);
}

double W3Builder::integral(const Boundary&)
{
	// True only for [-inf,inf]x[-inf,inf]
	return 1.;
}

RandomFunctorBuilder& W3Builder::x0(double dx0, unsigned long dim)
{
	RandomFunctorBuilder::x0(dx0, dim);
	updateDefaultBoundary();
	return *this;
}

void W3Builder::updateDefaultBoundary()
{
	this->defaultBoundary.setU(0, (dC[0] + dx0[0]) / difficultyFactor());
}

}
