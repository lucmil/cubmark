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

#ifndef CUBMARK_CONSTANT_H
#define CUBMARK_CONSTANT_H

#include <functional>

namespace cb
{

/**
 * \brief Boundary function functor
 */
class Constant
:   public std::unary_function<double, double>
{
public:
	/**
	 * \brief Default constructor
	 */
	Constant();

	/** \brief Constructor
	 *
	 * \param c Value of the function
	 */
	Constant(double c);

	/** \brief Overloaded function operator
	 *
	 * \param x Discarded
	 */
	double operator()(double x) const throw();
private:
	/**
	 * \brief Value of the function
	 */
	double c;
};

}
#endif//CUBMARK_CONSTANT_H
