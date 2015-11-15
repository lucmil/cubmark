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

#include <cubmark/TestFunctorFactory.h>

#include <cubmark/G1Builder.h>
#include <cubmark/G2Builder.h>
#include <cubmark/G3Builder.h>
#include <cubmark/G4Builder.h>
#include <cubmark/G5Builder.h>
#include <cubmark/G6Builder.h>
#include <cubmark/F1Builder.h>
#include <cubmark/W1Builder.h>
#include <cubmark/W2Builder.h>
#include <cubmark/W3Builder.h>
#include <cubmark/QP1Builder.h>
#include <cubmark/P1Builder.h>
#include <cubmark/RD28Builder.h>
#include <cubmark/RD29Builder.h>
#include <cubmark/RD31Builder.h>
#include <cubmark/RD35Builder.h>
#include <cubmark/InvalidNameError.h>
#include <cubmark/debug.h>

namespace cb
{

TestFunctorFactory::TestFunctorFactory()
{
	initIdMap();
}

TestFunctorBuilder*
TestFunctorFactory::getByDefinition(const Definition& definition) const
{
	typedef Factory<TestFunctorFactory, TestFunctorBuilder, TestFunctorIdType>
			SuperType;

	TestFunctorBuilder* testFunctorBuilder = SuperType::getByDefinition(definition);
	CHECK(testFunctorBuilder, InvalidNameError("Invalid function name."));
	testFunctorBuilder->parseDefinition(definition);
	return testFunctorBuilder;
}

TestFunctorBuilder* TestFunctorFactory::getById(TestFunctorIdType id) const
{
	TestFunctorBuilder* testFunctorBuilder = 0;
	switch(id)
	{
		case F_G1:	testFunctorBuilder = new G1Builder;		break;
		case F_G2:	testFunctorBuilder = new G2Builder;		break;
		case F_G3:	testFunctorBuilder = new G3Builder;		break;
		case F_G4:	testFunctorBuilder = new G4Builder;		break;
		case F_G5:	testFunctorBuilder = new G5Builder;		break;
		case F_G6:	testFunctorBuilder = new G6Builder;		break;
		case F_W1:	testFunctorBuilder = new W1Builder;		break;
		case F_W2:	testFunctorBuilder = new W2Builder;		break;
		case F_W3:	testFunctorBuilder = new W3Builder;		break;
		case F_F1:	testFunctorBuilder = new F1Builder;		break;
		case F_QP1:	testFunctorBuilder = new QP1Builder;	break;
		case F_P1:	testFunctorBuilder = new P1Builder;		break;
		case F_RD28:	testFunctorBuilder = new RD28Builder;	break;
		case F_RD29:	testFunctorBuilder = new RD29Builder;	break;
		case F_RD31:	testFunctorBuilder = new RD31Builder;	break;
		case F_RD35:	testFunctorBuilder = new RD35Builder;	break;
	}
	CHECK(testFunctorBuilder, "No method registered with that ID");
	return testFunctorBuilder;
}

void TestFunctorFactory::initIdMap()
{
	idMap["F1"] = F_F1;
	idMap["W1"] = F_W1;
	idMap["W2"] = F_W2;
	idMap["W3"] = F_W3;
	idMap["G1"] = F_G1;
	idMap["G2"] = F_G2;
	idMap["G3"] = F_G3;
	idMap["G4"] = F_G4;
	idMap["G5"] = F_G5;
	idMap["G6"] = F_G6;
	idMap["QP1"] = F_QP1;
	idMap["P1"] = F_P1;
	idMap["RD28"] = F_RD28;
	idMap["RD29"] = F_RD29;
	idMap["RD31"] = F_RD31;
	idMap["RD35"] = F_RD35;
}

}
