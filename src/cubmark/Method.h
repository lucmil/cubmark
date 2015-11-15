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

#ifndef CUBMARK_METHOD_H
#define CUBMARK_METHOD_H

#include <cstdlib>

#include <cubmark/Boundary.h>

namespace cb
{

/**
 * \brief Common interface for all cubature methods
 */
class Method
{
public:
	/**
	 * \brief Integrand function type
	 */
	typedef double (*IntegrandType)(double,double);

	/**
	 * \brief Destructor
	 */
	virtual ~Method();

	/**
	 * \brief Set requested relative cubature error tolerance
	 *
	 * \param relativeTolerance Relative error tolerance or 0.0 (set method default)
	 */
	virtual void setRelativeTolerance(double relativeError) = 0;

	/**
	 * \brief Get the currently set relative cubature error tolerance
	 *
	 * \returns Current relative cubature error tolerance or 0.0 (unset)
	 */
	virtual double getRelativeTolerance() const = 0;

	/**
	 * \brief Set requested absolute cubature error tolerance
	 *
	 * \param absoluteTolerance Absolute error tolerance or 0.0 (set method default)
	 */
	virtual void setAbsoluteTolerance(double absoluteError) = 0;

	/**
	 * \brief Get the currently set absolute cubature error tolerance
	 *
	 * \returns Current cubature error tolerance or 0.0 (unset)
	 */
	virtual double getAbsoluteTolerance() const = 0;

	/**
	 * \brief Set a rectangular boundary
	 *
	 * Call with no arguments to clear the boundary.
	 * \param c Rectangular boundary object
	 */
	virtual void setBoundary(const Boundary& boundary = Boundary()) = 0;

	/**
	 * \brief Check if this instance had a valid boundary set
	 *
	 * \returns True if setBoundary() had been called with a valid Boundary
	 *          object
	 */
	virtual bool hasBoundary() const = 0;

	/**
	 * \brief Set the integrand to function F
	 *
	 * \param f pointer to integrand function
	 */
	virtual void setIntegrand(IntegrandType f) = 0;

	/**
	 * \brief Get the current integrand
	 *
	 * \returns Pointer to integrand function
	 */
	virtual IntegrandType getIntegrand() const = 0;

	/**
	 * \brief Check if this instance had an integrand set
	 *
	 * \returns True if setIntegrand() had been called
	 */
	virtual bool hasIntegrand() const = 0;

	/**
	 * \brief Evaluate the cubature
	 *
	 * \pre A boundary had been set with setBoundary()
	 * \pre Integrand had been set with setIntegrand()
	 * \pre Absolute or/and relative error tolerance had been set with
	 *      setAbsoluteTolerance(), setRelativeTolerance()
	 *
	 * \returns Cubature value
	 */
	virtual double compute() = 0;

	/**
	 * \brief Did the last evaluation fail?
	 */
	virtual bool failed() const = 0;

	/**
	 * \brief Get the number of integrand calls used by the last evaluation
	 *
	 * \returns Number of integrand calls or 0 (no evaluation took place)
	 */
	virtual unsigned long getCallCnt() const = 0;

	/**
	 * \brief Get the absolute error estimate of the last cubature
	 *
	 * \returns Absolute error estimate
	 */
	virtual double getAbsoluteErrorEstimate() const = 0;

	/**
	 * \brief Get the absolute error estimate of the last cubature
	 *
	 * \returns Absolute error estimate
	 */
	virtual double getRelativeErrorEstimate() const = 0;

	/**
	 * \brief Set the integrand call limit
	 *
	 * The default is method-specific.
	 *
	 * \param max_calls Maximum number of allowed integrand function calls or
	 *                  (0 for default)
	 */
	virtual void setCallLimit(unsigned long callLimit) = 0;

	/**
	 * \brief Get the integrand call limit
	 *
	 * \returns Maximum number of allowed integrand function calls
	 */
	virtual unsigned long getCallLimit() const = 0;
};

}
#endif//CUBMARK_METHOD_H
