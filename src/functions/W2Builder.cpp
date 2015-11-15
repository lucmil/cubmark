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

#include <cubmark/W2Builder.h>

#include <cubmark/adapter/adapter.h>
#include <cubmark/constants.h>

#include <algorithm>

namespace cb
{

W2Builder::W2Builder() :
	RandomFunctorBuilder(Boundary(0.0, 1.0, -inf, inf))
{
	this->dC[0] = 0.5;
	this->dx0[0] = 1.0;
}

void W2Builder::setupAdapter()
{
	W2 ftor(dC, dx0);
	if(!ftorAdapter)
	{
		adapter<W2>(ftorAdapter);
	}
	adapterSetFunctor(ftorAdapter, ftor);
}

double W2Builder::integral(const Boundary&)
{
	// True only for [-inf,inf]x[-inf,inf]
	return 1.;
}

RandomFunctorBuilder& W2Builder::C(double dC, unsigned long dim)
{
	RandomFunctorBuilder::C(dC, dim);
	updateDefaultBoundary();
	return *this;
}

RandomFunctorBuilder& W2Builder::x0(double dx0, unsigned long dim)
{
	RandomFunctorBuilder::x0(dx0, dim);
	updateDefaultBoundary();
	return *this;
}

void W2Builder::updateDefaultBoundary()
{
	this->defaultBoundary.setU(0, (dC[0] + dx0[0]) / difficultyFactor());
}

}
