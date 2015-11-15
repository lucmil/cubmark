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

#ifndef CUBMARK_HINTLIB
#define CUBMARK_HINTLIB

#include <cubmark/config.h>
#include <cubmark/Method.h>
#include <cubmark/HIntLibIntegrand.h>

#include <HIntLib/defaults.h>
#include <HIntLib/esterr.h>
#include <HIntLib/hypercube.h>
#include <HIntLib/integrator.h>
#include <HIntLib/adaptintegrator.h>

namespace HIntLib
{
class EmbeddedRuleFactory;
}


namespace cb
{

using HIntLib::EmbeddedRuleFactory;
using HIntLib::Index;
using HIntLib::Integrator;
using HIntLib::real;
using HIntLib::Hypercube;
using HIntLib::AdaptIntegrator;
using HIntLib::EstErr;

/** \brief HIntLib library Adapter
 *
 * \tparam R HIntLib integration rule class
 */
class HIntLib
:   public Method
{
public:
	/** \brief Constructor
	 *
	 * \param rf Integration rule factory (default Rule75GenzMalik)
	 */
	HIntLib(EmbeddedRuleFactory *ruleFactory = 0);

	~HIntLib();

	void setRelativeTolerance(double relativeTolerance);
	double getRelativeTolerance() const;

	void setAbsoluteTolerance(double absoluteTolerance);
	double getAbsoluteTolerance() const;

	void setBoundary(const Boundary& boundary);
	bool hasBoundary() const;

	void setIntegrand(IntegrandType integrand);
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
	Boundary boundary;
	HIntLibIntegrand integrand;
	bool evaluationSuccess;

	Index callLimit;
	real relErrTol;
	real absErrTol;
	Hypercube region;
	AdaptIntegrator integrator;
	EstErr result;

};

}
#endif//CUBMARK_HINTLIB
