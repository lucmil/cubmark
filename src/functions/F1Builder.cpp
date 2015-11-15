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

#include <stdexcept>

#include <cubmark/F1Builder.h>

#include <cubmark/adapter/adapter.h>
#include <cubmark/constants.h>
#include <cubmark/InvalidValueError.h>

namespace cb
{

F1Builder::F1Builder() :
	RandomFunctorBuilder(Boundary(-inf, inf, -inf, inf))
{
}

void F1Builder::setupAdapter()
{
	F1 ftor(dC, dx0);
	if(!ftorAdapter)
	{
		adapter<F1>(ftorAdapter);
	}
	adapterSetFunctor(ftorAdapter, ftor);
}

double F1Builder::integral(const Boundary& region)
{
	if(region.isPlane() || region.isRegular())
	{
		const double t = 8.0 / (dC[0] + dC[1] + 1.0);
		return PI / t * exp(-0.25/t) * sqrt(0.25 * PI / t);
	}
	throw InvalidValueError("Unsupported or invalid integration boundary.");
	return sNaN;
}

}
