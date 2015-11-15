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
#include <iomanip>
#include <deque>
#include <numeric>

#include <cubmark/debug.h>
#include <cubmark/Scanner.hpp>
#include <cubmark/W1.h>
#include <cubmark/W2.h>
#include <cubmark/W3.h>

void usage(const char* argv0)
{
	std::cerr << "Usage: " << argv0 << " [c|t|w<n>] [k_n] [nk] [nx]\n";
}

template<class F>
void computeGrid(size_t N, size_t M, double x_n, double k_n, F f)
{
	const double dx = x_n/(double)(N-1);
	const double dk = (2.0 * k_n)/(double)(M-1);
	double I = 0.0;
	std::cout << "# [x_0, x_n]x[k_0, k_n]"
			" = [ 0, "<< x_n <<"] x ["<< -k_n <<", "<< k_n <<" ]\n"
			"# n_x = "<< N <<","
			" n_k = "<< M <<","
			" dx = "<< dx <<","
			" dk = "<< dk <<'\n'
			<< std::setprecision(20)
			<< "# x\tk\tW_n(x,k)\n"
			"# Analytic data\n";

	for(size_t i = 0; i < N; ++i)
	{
		const double x = dx * (double)i;
		for(size_t j = 0; j < M; ++j)
		{
			const double k = dk * (double)j - k_n;
			const double w = f(x, k);
			std::cout << x <<'\t'<< k <<'\t'<< w << '\n';
			I += w;
		}
		std::cout << '\n';
	}
	I *= dx;
	I *= dk;
	std::cout << "# I = " << I << '\n';
}

int main(int argc, char* argv[])
{
	using namespace cb;
	size_t N = 512, M = 512;
	int n = 1;
	double x_n = 1.;
	double k_n = 50.;
	char type = 'c';

	Scanner<double> scanDbl;
	Scanner<size_t> scanSize;
	try
	{
		switch(argc)
		{
			case 5:
			N = scanSize(argv[4]);
			case 4:
			M = scanSize(argv[3]);
			case 3:
			k_n = scanDbl(argv[2]);
			CHECK(k_n > 0, "Error: k_n has to be positive.");

			case 2:
			type = argv[1][0];
			n = (argv[1][1] == '\0') ? 1 : scanSize(&argv[1][1]);

			case 1:
			break;

			default:
			usage(argv[0]);
			return -1;
		}
	}
	catch(std::runtime_error& e)
	{
		std::cerr << e.what() << '\n';
		usage(argv[0]);
		return -1;
	}

	std::cout << "# t = " << type << ", n = "<< n <<'\n';
	double C[] = { 1.0, 1.0 };
	double x0[] = { 1.0, 1.0 };
	switch(type)
	{
		case 'c':
		{
			x0[0] = x_n;
			computeGrid(N, M, x_n, k_n, W1(x0));
		}
		break;

		case 't':
		{
			C[0] = 0.5 * x_n;
			x0[0] = 0.5 * x_n;
			computeGrid(N, M, x_n, k_n, W2(C, x0));
		}
		break;

		case 'w':
		{
			x0[0] = x_n;
			computeGrid(N, M, x_n, k_n, W3(n, x0));
		}
		break;

		default:
		std::cerr << "Invalid wavefunction type. Allowed are: c,t and w\n";
		usage(argv[0]);
		return -1;
	}

}
