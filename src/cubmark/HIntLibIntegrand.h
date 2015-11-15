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

#ifndef CUBMARK_HINTLIB_ADAPTER
#define CUBMARK_HINTLIB_ADAPTER

#include <cubmark/Method.h>
#include <HIntLib/integrand.h>

namespace cb
{

/** \brief Adapter of function pointers to HIntLib::Integrand class
 */
class HIntLibIntegrand :
	public HIntLib::Integrand
{
public:
	/** \brief Constructor
	 *
	 * Required by the interface.
	 *
	 * \param dimension integrand dimension (ignored, always 2)
	 */
	explicit HIntLibIntegrand(int dimension);

	/** \brief Destructor
	 */
	~HIntLibIntegrand();

	/** \brief Returns the number of calls off operator()
	 *
	 * \returns Number of calls to operator() since last call to reset_counter()
	 */
	unsigned long getCallCnt() const;

	/** \brief Returns the currently set integrand.
	 *
	 * \returns Pointer to currently set integrand or 0 if not set.
	 */
	Method::IntegrandType getIntegrand() const;

	/** \brief Zero the call counter
	 */
	void resetCallCnt();

	/** \brief Change the integrand function
	 *
	 * \param integrand pointer to integrand function
	 */
	void setIntegrand(Method::IntegrandType integrand);

	HIntLib::real operator()(const HIntLib::real x[]);
private:
	Method::IntegrandType integrand;
	unsigned long callCnt;
	static double noop(double, double);
};

}
#endif//CUBMARK_HINTLIB_ADAPTER
