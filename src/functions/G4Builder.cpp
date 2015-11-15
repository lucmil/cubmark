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

#include <cubmark/G4Builder.h>

#include <cubmark/adapter/adapter.h>
#include <cubmark/constants.h>
#include <cubmark/debug.h>

namespace cb
{

G4Builder::G4Builder()
{
	this->dC[0] = 1.0;
	this->dC[1] = 1.0;
	this->dx0[0] = 0.0;
	this->dx0[1] = 0.0;
}

void G4Builder::setupAdapter()
{
	G4 ftor(dC, dx0);
	if(!ftorAdapter)
	{
		adapter<G4>(ftorAdapter);
	}
	adapterSetFunctor(ftorAdapter, ftor);
}

double G4Builder::integral(const Boundary& boundary)
{
	if(boundary.isPlane())
	{
		return 4.0/dC[0]/dC[1];
	}

	CHECK(!boundary.isInfinite(), "Unsupported integration region.");
	return	PI * (
			( erf( -dC[0] * boundary.u(0) + dC[0] * dx0[0])
			- erf( -dC[0] * boundary.l(0) + dC[0] * dx0[0])
			)
			*
		 	( erf(-dC[1] * boundary.u(1) + dC[1] * dx0[1]) 
			- erf(-dC[1] * boundary.l(1) + dC[1] * dx0[1])
			)
		   ) / (dC[0] * dC[1])/4.0;
}

}
