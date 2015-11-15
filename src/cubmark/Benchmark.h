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

#ifndef CUBMARK_BENCHMARK_H
#define CUBMARK_BENCHMARK_H

#include <boost/scoped_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

/**
 * \brief Main namespace of the Benchmark suite
 */
namespace cb
{

class Sample;
class Boundary;
class Method;
class SuiteResults;
class TestFunctorBuilder;

/** \brief Class for evaluating benchmarks
 */
class Benchmark
{
public:
	/** \brief Constructor
	 */
	Benchmark(SuiteResults& suiteResults);

	/** \brief Destructor
	 */
	~Benchmark();

	/** \brief Start the benchmark
	 *
	 * \post suiteResults will contain the results of the benchmark
	 */
	void computeResults();

private:
	void initMethods();
	void initTestFunctorBuilder();
	Sample createSample(size_t caseIdx);
	Boundary getSampleBoundary() const;
	void runMethod(const size_t methodIdx, const Sample& testSample);

	/** \brief Contains method results for each computed sample
	 */
	SuiteResults& suiteResults;
	boost::scoped_ptr<TestFunctorBuilder> testFunctorBuilder;
	boost::ptr_vector<Method> methods;
};

}

#endif//CUBMARK_BENCHMARK_H
