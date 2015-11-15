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

#ifndef CUBMARK_DCUHRE_PROTOTYPES
#define CUBMARK_DCUHRE_PROTOTYPES

#ifdef  __cplusplus
extern "C"
{
#endif//__cplusplus

typedef void (*DcuhreFuncType)(int* NDIM, double* X, int* NFUN, double* F);

void dcuhre_(int* NDIM, int* NUMFUN, double* A, double* B, int* MINPTS, int* MAXPTS,
		DcuhreFuncType FUNSUB,
		double* EPSABS, double* EPSREL, int* KEY, int* NW, int* RESTAR,
		double* RESULT, double* ABSERR, int* NEVAL, int* IFAIL, double* WORK);

#ifdef  __cplusplus
}
#endif//__cplusplus
#endif//CUBMARK_DCUHRE_PROTOTYPES
