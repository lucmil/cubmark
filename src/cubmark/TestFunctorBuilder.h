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

#ifndef CUBMARK_TEST_FUNCTOR_BUILDER_H
#define CUBMARK_TEST_FUNCTOR_BUILDER_H

#include <string>

#include <cubmark/Builder.h>
#include <cubmark/Boundary.h>
#include <cubmark/Method.h>

namespace cb
{

#ifdef __GXX_EXPERIMENTAL_CXX0X__
template<class, class ...>
class AdapterBase;
#else
template<class, class, class>
class AdapterBase;
#endif

/** \brief Interface for functor builders with command-line parameters
 *
 * This interface provides a common method of passing parameters from the
 * command-line to functor builders.
 */
class TestFunctorBuilder :
	public Builder
{
public:
	virtual ~TestFunctorBuilder();

	/** \brief Create an Adapter with the functor.
	 *
	 * \returns Pointer to Adapter (and it's ownership)
	 * \throws IncompleteError At least one required parameter is missing.
	 */
	virtual Method::IntegrandType create() = 0;

	/** \brief Returns the default integration boundary for it's test function
	 *
	 * \returns Default boundary used with this function for test purposes
	 */
	virtual const Boundary& getDefaultBoundary() = 0;

	/** \brief Calculate the analytic value of the function's integral
	 *
	 * \param region Region for which to calculate the integral
	 * \returns Analytic value of integral
	 * \throws InvalidValueError No analytic solution available
	 *                           for the given region
	 */
	virtual double integral(const Boundary& region = Boundary()) = 0;
};

}
#endif//CUBMARK_TEST_FUNCTOR_BUILDER_H

