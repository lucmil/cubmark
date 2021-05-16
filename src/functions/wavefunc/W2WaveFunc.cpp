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

#include <cubmark/W2WaveFunc.h>

#include <cmath>
#include <stdexcept>

#include <cubmark/debug.h>

namespace cb
{

W2WaveFunc::W2WaveFunc()
{
}

W2WaveFunc::W2WaveFunc(double x, double y, double a, double b)
:	a(a),
	b(b),
	x_t(x),
	A_l(y/(x-a)),
	B_l(-A_l*a),
	A_r(y/(x-b)),
	B_r(-A_r*b)
{
	CHECK(a < x && x < b, "Invalid tipping point");

	// Normalize
	const double I_a = A_l*A_l/3. * pow(a, 3.) + A_l * B_l * a*a + B_l*B_l *a;
	const double I_lx = A_l*A_l/3. * pow(x, 3.) + A_l * B_l * x*x + B_l*B_l *x;
	const double I_rx = A_r*A_r/3. * pow(x, 3.) + A_r * B_r * x*x + B_r*B_r *x;
	const double I_b = A_r*A_r/3. * pow(b, 3.) + A_r * B_r * b*b + B_r*B_r *b;

	N = 1./(sqrt(fabs(I_lx - I_a + I_b - I_rx)));
}

double W2WaveFunc::operator()(double x) const
{
	double result = 0.;
	if(x < x_t)
	{
		if(x > a)
		{
			result = A_l*x + B_l;
		}
	}
	else if(x < b)
	{
		result = A_r*x + B_r;
	}
	return N * result;
}

}
