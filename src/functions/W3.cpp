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

#include <cubmark/W3.h>

#include <cmath>
#include <algorithm>

#include <cubmark/constants.h>

namespace cb
{

W3::W3(int n, double x0[]) :
	n(n)
{
	if(x0)
	{
		this->x0[0] = x0[0];
	}
	else
	{
		this->x0[0] = 1.0;
	}
}

double W3::operator()(double x, double k) const
{
	if(x < -eps || (x - x0[0]) > eps)
	{
		return 0.;
	}
	const double L = x0[0];
	const double z = std::min(2.0 * x, 2.0 * (L-x));

	// k != 0.0
	if(fabs(k) > eps * 1e3)
	{
		return .5 / (PI * L) *(
				sin((PI*n/L-k)*z)/(PI*n/L-k)
				+sin((PI*n/L+k)*z)/(PI*n/L+k)
				+(sin(2.*PI*n*x/L - k*z) - sin(2.*PI*n*x/L + k*z))/k);
	}
	else
	{
		// k == 0.0
		return sin(n*PI/L*z)/(n*PI*PI) - z/(PI*L) * cos(n*PI/L*z);
	}
}

}

