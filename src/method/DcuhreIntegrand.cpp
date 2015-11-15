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

#include <stdexcept>
#include <cubmark/debug.h>

#include <cubmark/DcuhreIntegrand.h>

namespace cb
{

DcuhreIntegrand::DcuhreIntegrand() :
	integrand(0)
{
}

DcuhreIntegrand::DcuhreIntegrand(Method::IntegrandType integrand) :
	integrand(integrand)
{
	CHECK(integrand != 0, std::logic_error("Integrand pointer is NULL"));
}

void
DcuhreIntegrand::operator()(int* /*NDIM*/, double* X, int* /*NFUN*/, double* F)
const
{
	F[0] = (*integrand)(X[0], X[1]);
}

}
