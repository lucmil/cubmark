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

#ifndef CUBMARK_G3BUILDER_H
#define CUBMARK_G3BUILDER_H

#include <cubmark/G3.h>
#include <cubmark/RandomFunctorBuilder.h>

namespace cb
{

class G3Builder :
	public RandomFunctorBuilder
{
public:
	G3Builder();

	/** \brief Calculate the analytic value of the function's integral
	 *
	 * \pre region.isInfinite() == false
	 * \param region Region for which to calculate the integral
	 * \returns Analytic value of integral
	 * \throws InvalidValueError No analytic solution available
	 *                           for the given region
	 */
	double integral(const Boundary& region = Boundary());
protected:
	void setupAdapter();
private:
	RandomFunctorBuilder& C(double C_dim, unsigned long dim);
};

}
#endif//CUBMARK_G3BUILDER_H
