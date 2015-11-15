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
#include <functional>

#include <cubmark/adapter/adapter.h>
#include <cubmark/Scanner.hpp>
#include <cubmark/StopTimer.h>

template<typename F>
class Wrapper {
public:
	typedef double (*C_FUNCTION)(double, double);
	Wrapper(const F& fctor) { fgAddress = &fctor; }
	C_FUNCTION adapt() { return &Glue; }
private:
	static const F* fgAddress;
	static double Glue(double x, double y) { return (*fgAddress)(x, y); }
};
template<typename F> const F* Wrapper<F>::fgAddress = 0;

class sumAdHoc
{
public:
	double operator()(double x, double y) const throw()
	{
		return x + y;
	}

	static sumAdHoc instance;
	static double Glue(double x, double y) throw()
	{
		return sumAdHoc::instance(x,y);
	}
};

sumAdHoc sumAdHoc::instance;

struct sum
:   std::binary_function<double, double, double>
{
	inline
	double operator()(double x, double y) const throw()
	{
		return x + y;
	}
};

/**
 * Results on a 1.47 GHz Pentium Dual-Core, 1E+09 repetitions, gcc 4.4 -O2:
 * (total time)
 * Ad-hoc	139
 * Wrapper	139
 * Adapter	487
 *
 * The ad-hoc and wrapper approaches were in-lined by the compiler.
 * Ad-hoc, wrapper and Adapter approaches have equal performance when
 * optimizations are turned off.
 *
 * \todo Check how this integrates with Boost::Lambda
 */
int main(int argc, char** argv)
{
	typedef double (*FuncPtr)(double, double);
	cb::Scanner<size_t> scanSize;
	const size_t repeats = (argc == 2) ? scanSize(argv[1]): 1;
	sumAdHoc::instance = sumAdHoc();
	cb::StopTimer t;
	cb::BinaryAdapter<sum>::Type* ad = cb::adapter(sum());
	FuncPtr adapted = ad->getPtr();
	FuncPtr adhoc = &sumAdHoc::Glue;
	sum f;
	Wrapper<sum> wrapperObj(f);
	FuncPtr wrapper = wrapperObj.adapt();
	volatile double a = 62;
   	volatile double b = 123;
	volatile double c = 0;

	t.start();
	for(size_t i = 0; i < repeats; ++i)
	{
		c = adapted(a,b);
	}
	t.stop();
	std::cout << "Adapter total time: " << t.getTime() << '\n';

	t.start();
	for(size_t i = 0; i < repeats; ++i)
	{
		c = adhoc(a,b);
	}
	t.stop();
	std::cout << "Ad-hoc total time: " << t.getTime() << '\n';

	t.start();
	for(size_t i = 0; i < repeats; ++i)
	{
		c = wrapper(a,b);
	}
	t.stop();
	std::cout << "Wrapper total time: " << t.getTime() << '\n';

	return 0;
}
