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

#ifndef CUBMARK_TESTFUNCTORFACTORY_H
#define CUBMARK_TESTFUNCTORFACTORY_H

#include <map>
#include <string>

#include <cubmark/config.h>
#include <cubmark/Definition.h>
#include <cubmark/Factory.hpp>

namespace cb
{

enum TestFunctorIdType
{
	F_G1,
	F_G2,
	F_G3,
	F_G4,
	F_G5,
	F_G6,
	F_W1,
	F_W2,
	F_W3,
	F_F1,
	F_QP1,
	F_P1,
	F_RD28,
	F_RD29,
	F_RD31,
	F_RD35
};

class TestFunctorBuilder;

class TestFunctorFactory :
	public Factory<TestFunctorFactory, TestFunctorBuilder, TestFunctorIdType>
{
public:
	TestFunctorFactory();
	TestFunctorBuilder* getByDefinition(const Definition& definition) const;
	TestFunctorBuilder* getById(TestFunctorIdType id) const;
private:
	void initIdMap();
};

}
#endif//CUBMARK_TESTFUNCTORFACTORY_H
