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

#include <cubmark/G2Builder.h>

#include <cubmark/adapter/adapter.h>
#include <cubmark/constants.h>

namespace cb
{

G2Builder::G2Builder()
{
}

void G2Builder::setupAdapter()
{
	G2 ftor(dC, dx0);
	if(!ftorAdapter)
	{
		adapter<G2>(ftorAdapter);
	}
	adapterSetFunctor(ftorAdapter, ftor);
}

/*
 * Calculate the component of an integral of G2
 * The integral is of the form:
 * I = product_i(-1/C(1:m) * K(1:m) )
 * where K is a vector of components.
 *
 * The i-th element of the K vector depends only on the C,x_0 parameters for the
 * i-th dimension and it's integration boundaries a,b.
 *
 * This function can calculate K for every proper and improper combination
 * of boundary values a,b.
 */
inline
double K(double a, double b, double C, double x_0)
{
	const bool aIsInf = isinf(a);
	const bool bIsInf = isinf(b);

	if(!aIsInf && !bIsInf)
	{
		return atan((a - x_0)/C) - atan((b - x_0)/C);
	}
	else if(aIsInf && bIsInf)
	{
		return copysign(PI, a);
	}
	else if(aIsInf)
	{
		return - atan((b - x_0)/C) - PI/C/2.0;
	}
	else
	{
		return atan((a - x_0)/C) - PI/C/2.0;
	}
}

double G2Builder::integral(const Boundary& boundary)
{
	return K(boundary.l(1), boundary.u(1), dC[1], dx0[1])
			* K(boundary.l(0), boundary.u(0), dC[0], dx0[0])/dC[0]/dC[1];
}

}
