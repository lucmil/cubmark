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
#include <cmath>

// For functor templates
#include <functional>

#include <cubmark/adapter/adapter.h>

// Unary STL functor
struct x_times_y
:   std::unary_function<int, int>
{
	int y;
	int operator()(int x)
	{
		return x*y;
	}
};

// Binary STL functor
struct norm
:   std::binary_function<double, double, double>
{
	int k;
	double operator()(double x, double y)
	{
		return pow(fabs(x-y), k);
	}
};

// This works too
struct x_plus_y
{
	typedef double result_type;
	typedef double first_argument_type;
	typedef double second_argument_type;

	double operator()(double x, double y)
	{
		return x+y;
	}
};

int legacy_c_function(int (*callback)(int))
{
	return callback(42);
}

double legacy_c_function2(double (*binary_callback)(double, double))
{
	return binary_callback(4, 2);
}

int main()
{
	using namespace cb;
	x_times_y four;
	four.y = 4;

	norm square_norm;
	square_norm.k = 2;

	UnaryAdapter<x_times_y>::Type* Glue = cb::adapter(four);
	std::cout << legacy_c_function(Glue->getPtr()) << '\n'; // 168

	// First lock stil held
	{
		// The Adapter keeps a copy of the passed functor so only the lock
		// object has be to held in scope
		BinaryAdapter<x_plus_y>::Type* Glue2 = cb::adapter(x_plus_y());
		std::cout << legacy_c_function2(Glue2->getPtr()) << '\n'; // 6
	} // Second lock freed

	BinaryAdapter<norm>::Type* Glue3 = cb::adapter(square_norm);
	std::cout << legacy_c_function2(Glue3->getPtr()) << '\n'; // 4

	return 0;
}
