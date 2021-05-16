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
#include <algorithm>

#include <cubmark/W1.h>
#include <cubmark/constants.h>

namespace cb
{

W1::W1(double x0[])
{
	if(x0)
	{
		this->x0[0] = x0[0];
		this->N = PI * sqrt(x0[0]);
	}
	else
	{
		this->x0[0] = 1.0;
		this->N = PI;
	}
}

double W1::operator()(double x, double k) const
{
	if(x < -eps || (x - x0[0]) > eps)
	{
		return 0.;
	}
	const double z = std::min(2.0*x, 2.0*(x0[0]-x));

	if(fabs(k) > eps)
	{
		return sin(k*z)/N/k;
	}
	else
	{
		return z/N;
	}
}

}

