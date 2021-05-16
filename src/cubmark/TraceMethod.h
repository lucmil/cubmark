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

#ifndef CUBMARK_TRACEMETHOD
#define CUBMARK_TRACEMETHOD

#include <memory>

#include <cubmark/Method.h>

namespace cb
{

/** \brief Tracing shim for concrete Method classes
 *
 * Class for debugging concrete Method classes.
 * Each function:
 * a) logs arguments passed to it
 * b) checks preconditions
 * c) calls the concrete method.
 * d) checks postconditions
 *
 * If any checks fail, an exception will be thrown.
 * Preconditions and postconditions for each function are mentioned in the
 * Method class documentation.
 */
class TraceMethod
:   public Method
{
public:
	/** \brief Constructor
	 *
	 * \param method Object to trace
	 */
	TraceMethod(Method* method);
	~TraceMethod();

	void setRelativeTolerance(double relativeTolerance);
	double getRelativeTolerance() const;

	void setAbsoluteTolerance(double absoluteTolerance);
	double getAbsoluteTolerance() const;

	void setBoundary(const Boundary& b);
	bool hasBoundary() const;

	void setIntegrand(IntegrandType f);
	IntegrandType getIntegrand() const;
	bool hasIntegrand() const;

	double compute();

	bool failed() const;
	unsigned long getCallCnt() const;
	double getAbsoluteErrorEstimate() const;
	double getRelativeErrorEstimate() const;
	void setCallLimit(unsigned long callLimit);
	unsigned long getCallLimit() const;
private:
	std::unique_ptr<Method> methodInstance;
};

}
#endif//CUBMARK_TRACEMETHOD
