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

#ifndef CUBMARK_F1BUILDER_H
#define CUBMARK_F1BUILDER_H

#include <cubmark/types.h>
#include <cubmark/F1.h>
#include <cubmark/RandomFunctorBuilder.h>

namespace cb
{

class F1Builder :
	public RandomFunctorBuilder
{
public:
	F1Builder();

	/** \brief Calculate the analytic value of the function's integral
	 *
	 * The region argument is ignored to allow use with cubature methods without
	 * support for improper integrals.
	 *
	 * \todo This should not be the default behaviour. Add a parameter switch
	 *       which will allow to control this behaviour through the CLI.
	 *
	 * \param region Ignored
	 * \returns Value of integral for
	 *          \f$ D = [-inf, inf] \times [-inf, inf] \f$
	 * \throws InvalidValueError No analytic solution available
	 *                           for the given region
	 */
	double integral(const Boundary& region = Boundary());
protected:
	void setupAdapter();
};

}
#endif//CUBMARK_F1BUILDER_H
