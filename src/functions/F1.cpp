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

#include <cmath>

#include <cubmark/F1.h>

namespace cb
{

F1::F1(double C[], double x0[])
{
	double C_x = 0.0;
	double C_y = 0.0;

	if(C)
	{
		C_x = C[0];
		C_y = C[1];
	}
	t = 8.0 / (C_x + C_y + 1.0);

	if(x0)
	{
		this->alpha = 4.0 * x0[0] - 2.0;
		this->beta = 4.0 * x0[1] - 2.0;
	}
	else
	{
		this->alpha = 0.0;
		this->beta = 0.0;
	}
}


double F1::operator()(double x, double y) const
{
	x -= alpha;
	y -= beta;
	const double r = hypot(x,y);
	return sin(r) * exp(-t * r*r);
}

}

