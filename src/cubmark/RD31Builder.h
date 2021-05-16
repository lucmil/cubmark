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

#ifndef CUBMARK_RD31BUILDER_H
#define CUBMARK_RD31BUILDER_H

#include <cubmark/TestFunctorBuilder.h>

namespace cb
{

class RD31Builder :
	public TestFunctorBuilder
{
public:
	RD31Builder();
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

	/** \brief RD31 test function
	 *
	 * \f[ f(x,y) = \frac{1}{(x^2 + y^2 + 20x - 10y + 126)^2} \f]
	 *
	 * The test integral is of the form:
	 * \f[ \int_0^\infty \int_0^\infty f(x, y) dy dx = \frac{1}{4} \pi \f]
	 */
	static double compute(double x, double y);
private:
	const Boundary defaultBoundary;
};

}
#endif//CUBMARK_RD31BUILDER_H
