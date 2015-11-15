/*
 * This file is part of Cubature SuiteResults.
 * Copyright (C) 2009 Łukasz Lis
 *
 * Cubature SuiteResults is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cubature SuiteResults is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cubature SuiteResults.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cubmark/Result.h>
#include <cubmark/SuiteResults.h>
#include <cubmark/CaseResults.h>
#include <cubmark/CaseSpecification.h>
#include <iostream>

namespace cb
{

SuiteResults::SuiteResults()
{
}

SuiteResults::~SuiteResults()
{
}

void SuiteResults::setSpecification(const SuiteSpecification& suiteSpecification)
{
	this->suiteSpecification = suiteSpecification;

	for(size_t i = 0; i < suiteSpecification.getCaseCnt(); ++i)
	{
		CaseResults caseResults(suiteSpecification);
		suiteResults.push_back(caseResults);
	}
}

void SuiteResults::addSample(const Result& sampleResult)
{
	CaseResults& caseSpec =
			this->getCaseResults(sampleResult.getCase());

	caseSpec.addSample(sampleResult);
}

CaseResults& SuiteResults::getCaseResults(size_t caseIdx)
{
	return this->suiteResults[caseIdx];
}

const SuiteSpecification& SuiteResults::getSpecification() const
{
	return this->suiteSpecification;
}

}

