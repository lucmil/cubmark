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

#ifndef CUBMARK_CASE_H
#define CUBMARK_CASE_H

#include <cubmark/Boundary.h>

namespace cb
{

/** \brief Benchmark case class
 *
 * Defines all parameters needed for a single benchmark run.
 * This class provides a binding between a function and it's integral.
 */
struct Sample
{
	/**
	 * \brief Type of a pointer to a benchmark function
	 */
	typedef double (*IntegrandType)(double, double);

	/**
	 * \brief Constructor
	 */
	Sample(size_t caseIdx, IntegrandType f, const Boundary& boundary, double I);

	/**
	 * \brief Two dimensional real function
	 */
	IntegrandType integrandPtr;

	/**
	 * \brief Integral region
	 */
	Boundary boundary;

	/**
	 * \brief Exact integral value
	 *
	 * Use NaN equivalent for "unknown"
	 */
	double I;

	size_t caseIdx;
};

}

#endif//CUBMARK_CASE_H
