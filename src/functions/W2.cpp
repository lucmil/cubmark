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

#include <cubmark/W2.h>

#include <cmath>
#include <algorithm>

#include <cubmark/constants.h>
#include <cubmark/W2WaveFunc.h>

namespace cb
{

W2::W2(double C[], double x0[])
{
	if(C)
	{
		this->C[0] = C[0];
	}
	else
	{
		this->C[0] = 0.5;
	}

	if(x0)
	{
		this->x0[0] = x0[0];
	}
	else
	{
		this->x0[0] = 0.5;
	}
	b = this->x0[0] + this->C[0];

	W2WaveFunc p(this->C[0], 1.0, 0, b);
	A_l = p.A_l;
	A_r = p.A_r;
	B_l = p.B_l;
	B_r = p.B_r;
	N_sqr = p.N * p.N;
}

double W2::I(double A, double B, double z, double x, double k)
		const
{
	return pow(A, 2) * pow(x, 2) * sin(k * z)/(PI * k)
			+ 2. * A * B * x * sin(k * z)/(PI * k)
			+ pow(B, 2) * sin(k * z)/(PI * k)
			- .25 * pow(A, 2)/(PI * pow(k, 3)) * (
					2. * k * z * cos(k * z)
					+ (pow(k, 2) * pow(z, 2) - 2.) * sin(k*z));
}

double W2::I_0(double A, double B, double z, double x)
		const
{
	return pow(A, 2) * pow(x, 2) * z/PI
			- 1./12. * pow(A, 2) * pow(z, 3)/PI
			+ 2. * A * B * x * z/PI
			+ pow(B, 2) * z/PI;
}

double W2::I_lr(double z, double x, double k) const
{
	return A_l * A_r * pow(x, 2) * sin(k * z)/(PI * k)
			+ A_l * B_r * x * sin(k * z)/(PI * k)
			+ A_r * B_l * x * sin(k * z)/(PI * k)
			+ B_l * B_r * sin(k * z)/(PI * k)
			- .5 * (k * z * sin(k * z) + cos(k * z))
					* A_l * B_r/(PI * pow(k, 2))
			+ .5 * (k * z * sin(k * z) + cos(k * z))
					* A_r * B_l/(PI * pow(k, 2))
			- .25 * A_l * A_r/(PI * pow(k, 3)) * (
					2. * k * z * cos(k * z)
					+ (pow(k, 2) * pow(z, 2) - 2.) * sin(k * z));
}

double W2::I_lr_0(double z, double x) const
{
	return A_l * A_r * pow(x, 2) * z/PI
			- 1./12. * A_l * A_r * pow(z, 3)/PI
			+ A_l * B_r * x * z/PI
			- .25 * A_l * B_r * pow(z, 2)/PI + A_r * B_l * x * z/PI
			+ .25 * A_r * B_l * pow(z, 2)/PI + B_l * B_r * z/PI;
}

double W2::operator()(double x, double k) const
{
	if(x < 0.0 || x - b > eps)
	{
		return 0.0;
	}
	const double z = std::min(2.0 * x, 2.0*(b - x));
	double result = 0.;

	// k != 0.0
	/*
	 * The cube root of epsilon of my machine is approximately 6e-06
	 * The equation gets unstable approximately when k < 1e-06 probably due to
	 * the k^3 in the divisor. Can't say for sure. Just an educated guess.
	 */
	if(fabs(k) > cbrt(eps))
	{
		if(x-.5*z < C[0])
		{
			if(x+.5*z < C[0])
			{
				// Left slope
				result = I(A_l, B_l, z, x, k);
			}
			else if(x < C[0])
			{
				// Both slopes, X on left slope
				result = (I(A_l, B_l, 2.*(C[0] - x), x, k)
						+ I_lr(z, x, k) - I_lr(2.*(C[0] - x), x, k));
			}
			else
			{
				// Both slopes, X on right slope
				result = (I(A_r, B_r, 2.*(x - C[0]), x, k)
						+ I_lr(z, x, k) - I_lr(2.*(x - C[0]), x, k));
			}
		}
		else
		{
			// Right slope
			result = I(A_r, B_r, z, x, k);
		}
	}
	else
	{
		// k == 0
		if((x - 0.5 * z) < C[0])
		{
			if((x + 0.5 * z) < C[0])
			{
				// Left slope
				result = I_0(A_l, B_l, z, x);
			}
			else if(x < C[0])
			{
				// Both slopes, X on left slope
				result = (I_0(A_l, B_l, 2.*(C[0] - x), x)
						+ I_lr_0(z, x) - I_lr_0(2.*(C[0] - x), x));
			}
			else
			{
				// Both slopes, X on right slope
				result = (I_0(A_r, B_r, 2.*(x - C[0]), x)
						+ I_lr_0(z, x) - I_lr_0(2.*(x - C[0]), x));
			}
		}
		else
		{
			// Right slope
			result = I_0(A_r, B_r, z, x);
		}
	}
	return result * N_sqr;
}

}

