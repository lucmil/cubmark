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

#include <functional>
#include <stdexcept>

#include <cubmark/RuleChain.h>

#include <cubmark/adapter/adapter.h>
#include <cubmark/debug.h>

namespace cb
{

template<int DIM>
class ActionDispatch :
	public std::binary_function<double, void*, double>
{
	friend class RuleChain<DIM>;

	RuleChain<DIM>* ruleChain;

	ActionDispatch(RuleChain<DIM>& ruleChain) :
		ruleChain(&ruleChain)
	{
	}

public:
	ActionDispatch() :
		ruleChain(0)
	{
	}

	double operator()(double a, void *)
	{
		return ruleChain->ruleActionDispatch(a);
	}
};

template<int DIM>
RuleChain<DIM>::RuleChain() :
	rulePos(0),
	callCnt(0)
{
	initRuleActions();
}

template<int DIM>
void RuleChain<DIM>::initRuleActions()
{
	for(size_t i = 0; i < DIM-1; ++i)
	{
		ruleActions[i] = &RuleChain<DIM>::storeAndCallNext;
	}
	ruleActions[DIM-1] = &RuleChain<DIM>::evaluateIntegrand;
}

template<int DIM>
void RuleChain<DIM>::setIntegrand(Method::IntegrandType integrand)
{
	this->integrand = integrand;
}

template<int DIM>
QagRule& RuleChain<DIM>::getRule(size_t dimension)
{
	return rules[dimension];
}

template<int DIM>
const QagRule& RuleChain<DIM>::getRule(size_t dimension) const
{
	return rules[dimension];
}

template<int DIM>
unsigned long RuleChain<DIM>::getCallCnt() const
{
	return callCnt;
}

template<int DIM>
double RuleChain<DIM>::compute()
{
	ActionDispatch<DIM> dispatch(*this);
	typename BinaryAdapter<ActionDispatch<2> >::Type* dispatchAdapter(adapter(dispatch));
	AdapterLock lock(dispatchAdapter);

	for(size_t i = 0; i < DIM; ++i)
	{
		rules[i].setIntegrand(dispatchAdapter->getPtr());
	}

	rulePos = 0u;
	callCnt = 0u;
	const double result = rules[0].compute();

	CHECK(rulePos == 0, std::logic_error(
					"Chain returned before all rules were evaluated."));

	return result;
}

template<int DIM>
double RuleChain<DIM>::evaluateIntegrand(double y)
{
	++callCnt;
	return (*integrand)(x[0], y);
}

template<int DIM>
double RuleChain<DIM>::storeAndCallNext(double a)
{
	/* Store point coordinate */
	this->x[rulePos] = a;

	/* Forward the evaluation to the next rule */
	++rulePos;
	const double result = rules[rulePos].compute();
	--rulePos;

	return result;
}

template<int DIM>
double RuleChain<DIM>::ruleActionDispatch(double a)
{
	return (this->*(ruleActions[rulePos]))(a);
}

}
