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

#include <cubmark/W3WaveFunc.h>

#include <cmath>

namespace cb
{

W3WaveFunc::W3WaveFunc()
{
}

W3WaveFunc::W3WaveFunc(unsigned n, double a, double b) :
	n(n),
	a(a),
	b(b)
{
}

double W3WaveFunc::operator()(double x) const
{
	if(x > a && x < b)
	{
		return sqrt(2./(b-a)) * sin(n* M_PI * x/(b-a));
	}
	return 0.;
}

}

