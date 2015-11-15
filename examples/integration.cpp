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

#include <iostream>
#include <limits>
#include <cmath>

#include <cubmark/Qag2D.h>

double f(double x, double y)
{
	return sin(sqrt(x*x + y*y))*exp(-(x*x + y*y));
	//return 1.;
}

int main()
{
	using namespace std;
	using namespace cb;

	const double F = 0.5 * sqrt(pow(3.141592, 3.0)) * exp(-0.25);

	Boundary D(0,1,0,1);

	Qag2D I;
	I.setRelativeTolerance(1e-3);
	I.setIntegrand(&f);
	I.setBoundary(D);
	const double C = I.compute();

	cout << C << "\n"
		   "Abs.EE: " << I.getAbsoluteErrorEstimate() << "\n"
		   "Error: " << (F- C) << "\n"
		   "Calls: " << I.getCallCnt() << "\n";

	return 0;
}
