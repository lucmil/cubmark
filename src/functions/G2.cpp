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

#include <cubmark/G2.h>

#include <cmath>

namespace cb
{

G2::G2(double C[], double x_0[])
{
	if(C)
	{
		this->C[0] = C[0];
		this->C[1] = C[1];
	}
	else
	{
		this->C[0] = 1.0;
		this->C[1] = 1.0;
	}

	if(x_0)
	{
		this->x_0[0] = x_0[0];
		this->x_0[1] = x_0[1];
	}
	else
	{
		this->x_0[0] = 0.0;
		this->x_0[1] = 0.0;
	}
}


double G2::operator()(double x, double y) const throw()
{
	x -= x_0[0];
	y -= x_0[1];
	return 1.0/(C[0]*C[0] + x*x)/(C[1]*C[1] + y*y);
}


}

