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

#ifndef CUBMARK_RD28BUILDER_H
#define CUBMARK_RD28BUILDER_H

#include <cubmark/TestFunctorBuilder.h>

namespace cb
{

class RD28Builder :
	public TestFunctorBuilder
{
public:
	RD28Builder();
	Method::IntegrandType create();

	/** \brief Calculate the analytic value of the function's integral
	 *
	 * \param region Region for which to calculate the integral
	 * \returns Analytic value of integral
	 * \throws InvalidValueError No analytic solution available
	 *                           for the given region
	 */
	double integral(const Boundary& region = Boundary());

	void parseParameter(const std::string& name, const std::string& value);
	const Boundary& getDefaultBoundary();

	/** \brief RD28 test function
	 *
	 * \f[ f(x,y) = y^{-2} \f]
	 *
	 * The test integral is of the form:
	 * \f[ \int_2^1 \int_{-\infty}^{-1} f(x, y) dy dx = -1 \f]
	 */
	static double compute(double x, double y) throw();
private:
	const Boundary defaultBoundary;
};

}
#endif//CUBMARK_RD28BUILDER_H
