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

#ifndef CUBMARK_R2D2LRI
#define CUBMARK_R2D2LRI

#include <memory>
#include <functional>

#include <cubmark/types.h>
#include <cubmark/Constant.h>
#include <cubmark/Method.h>
#include <cubmark/adapter/types.h>

#include <r2d2lri.h>

namespace cb
{

/** \brief r2d2lri algorithm Adapter
 */
class R2d2lri
:   public Method
{
public:
	R2d2lri();
	~R2d2lri();

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
	void setCallLimit(unsigned long max_calls);
	unsigned long getCallLimit() const;

private:
	DoubleIntegral di;
	IntegrandType integrand;

	double a;
	double b;
	UnaryAdapter<Constant>::Type* g;
	UnaryAdapter<Constant>::Type* h;
};

}
#endif//CUBMARK_R2D2LRI
