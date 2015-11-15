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
#include <cubmark/adapter/adapter.h>

struct x_times_y
{
	int y;
	int operator()(int x)
	{
		return x;
	}
};

extern "C"
{

int legacy_c_function(int (*callback)(int))
{
	return callback(42); // This will call x_times::operator()
}

}

int main()
{
	x_times_y four;
	four.y = 4;
	cb::AdapterFtorBase<x_times_y, int, int>* Glue = 0;
	cb::adapter(Glue);
	Glue->setFunctor(four);
	std::cout << legacy_c_function(Glue->getPtr()) << '\n';
	return 0;
}
