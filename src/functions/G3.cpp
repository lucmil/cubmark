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

#include <cubmark/G3.h>

#include <cmath>

namespace cb
{

G3::G3(double C[], double x0[])
{
	if(C)
	{
		this->C[0] = C[0];
		this->C[1] = C[1];
		this->x0[0] = x0[0];
		this->x0[1] = x0[1];
	}
	else
	{
		this->C[0] = 1.0;
		this->C[1] = 1.0;
		this->x0[0] = 0.0;
		this->x0[1] = 0.0;
	}
}


double G3::operator()(double x, double y) const
{
	if(x0[0] > 0.5)
	{
		x = C[0] - x;
	}
	if(x0[1] > 0.5)
	{
		y = C[1] - y;
	}
	return 1.0/pow(1 + x + y, 3.0);
}


}

