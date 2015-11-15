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

#include <fstream>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <locale>
#include <sstream>
#include <memory>
#include <utility>
#include <map>
#include <string>
#include <boost/program_options.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include <cubmark/ViewFactory.h>
#include <cubmark/ViewBuilder.h>
#include <cubmark/Benchmark.h>
#include <cubmark/debug.h>
#include <cubmark/config.h>
#include <cubmark/exceptions.h>

#include <cubmark/SuiteResults.hpp>
#include <cubmark/SuiteSpecification.hpp>
#include <cubmark/CaseSpecification.hpp>
#include <cubmark/Definition.hpp>
#include <cubmark/Boundary.hpp>
#include <cubmark/Result.hpp>
#include <cubmark/CaseResults.hpp>

namespace po = boost::program_options;

namespace cbApp
{

class CLIInterface
{
	po::options_description cliOptions;
	po::variables_map variablesMap;
	char const* programName;
	po::options_description mandatory;
	po::options_description optional;
	po::options_description logging;
	po::options_description other;

	typedef std::map<std::string, std::string> DescMap;
	DescMap methodList;
	DescMap testFunctionList;
	DescMap viewList;

	void addMandatoryArguments()
	{
		mandatory.add_options()
				("function,f", po::value<std::string>(),
						"use FUNCTION as the integrand function.\n"
						"(e.g. `-f G1:h=100,e=2')")

				("method,m", po::value< std::vector<std::string> >(),
						"add and integration method to the benchmark suite.\n")

				("view,v", po::value< std::vector<std::string> >(),
						"select data output FORMAT:\n"
						"raw, full, histogram (default: raw)\n"
						"specify options after a colon.\n"
						"(e.g. `histogram:y=robustness')")

				("input,i", po::value< std::string >(),
						"run in sample processing mode.\n"
						"Read sample data from FILE (`-' for standard input).\n"
						"(default: standard input)")
		;
		cliOptions.add(mandatory);
	}

	void addOptions()
	{
		optional.add_options()
				("boundary,b", po::value<std::string>(),
						"integrate FUNCTION over a rectangular region of\n"
						"[A,B]x[C,D] (e.g. -1,1,-inf,inf)")

				("max-calls,c", po::value<unsigned long>()->default_value(100000),
						"limit the number of function evaluations\n"
						"`0'  will set the default of 100 000 calls")

				("output,o", po::value<std::string>()->default_value("-"),
						"write output to FILE (`-' for standard output)\n"
						"(default: standard output)")

				("samples,s", po::value<unsigned long>()->default_value(5),
						"number of parameter samples")
		;
		cliOptions.add(optional);
	}

	void addLoggingOptions()
	{
		logging.add_options()
				("log,l", po::value<std::string>()->default_value("trace.log"),
						"write log to FILE (default: trace.log)")

				("verbose,V", po::value<unsigned>()->default_value(1),
						"set verbosity:\n"
						"`0' report only fatal errors\n"
						"`1' include warning messages\n"
						"`2' include general information\n"
						"`3' include debugging messages\n"
						"(default: 1)")
		;
		cliOptions.add(logging);
	}

	void addHelp()
	{
		other.add_options()
				("help", "produce help message")
				("version", "print version string")
				("list-methods", "List available methods")
				("list-functions", "List available functions")
				("list-views", "List available data views")
				("list-all", "List methods, functions, and views")
		;
		cliOptions.add(other);
	}

	void initMethodList()
	{
		methodList["r2d2lri"] = "r2d2lri";
		methodList["adaptive-r2d2lri"] = "r2d2lri with adaptive subdivision";
		methodList["cubpack++"] = "Cubpack++";
		methodList["hintlib"] = "HIntLib";
		methodList["dcuhre"] = "DCUHRE";
		methodList["montecarlo"] = "GSL plain MC";
		methodList["qag2d"] = "Nested GSL QAG routines";
	}

	void initTestFunctionList()
	{
		testFunctionList["F1"] = "Oscillatory, exponential decay, radial symmetry";
		testFunctionList["W1"] = "Wigner dist. of a square wavefunction";
		testFunctionList["W2"] = "Wigner dist. of a triangle wavefunction";
		testFunctionList["W3"] = "Wigner dist. of a infinite potential well";
		testFunctionList["G1"] = "Genz Oscillatory";
		testFunctionList["G2"] = "Genz Product Peak";
		testFunctionList["G3"] = "Genz Corner Peak";
		testFunctionList["G4"] = "Genz Gaussian";
		testFunctionList["G5"] = "Genz C0";
		testFunctionList["G6"] = "Genz Discontinuous";
		testFunctionList["QP1"] = "Rational decay, Sector integral";
		testFunctionList["P1"] = "Rational decay, Plane integral";
		testFunctionList["RD28"] = "RD28";
		testFunctionList["RD29"] = "RD29";
		testFunctionList["RD31"] = "RD31";
		testFunctionList["RD35"] = "RD35";
	}

	void initViewList()
	{
		viewList["raw"] = "Raw data for delayed processing with `-i'";
		viewList["full"] = "Table view. One table per method";
		viewList["histogram"] = "XY field mapping suitable for gnuplot";
		viewList["testpack"] = "TESTPACK statistics";
	}

	void showList(const DescMap& list) const
	{
		DescMap::const_iterator i = list.begin();
		for(; i != list.end(); ++i)
		{
			std::cout << std::setw(18) << i->first
					<< " - " << i->second << '\n';
		}
	}

	void showVersion()
	{
		std::cout << "Cubmark " CUBMARK_VERSION "\n";
	}

	void showHelp()
	{
		showUsage();
		std::cout << '\n' << mandatory << '\n' << optional << '\n'
				<< logging << '\n' << other << '\n';
	}

	void showUsage()
	{
		std::cout <<"Usage: "<< programName << " "
				"-f FUNCTION "
				"[-b BOUNDARY] "
				"-m METHODS "
				"-v VIEWS "
				"[OPTIONS]\n"
				"Test cubature METHODS by approximating an integral of FUNCTION "
				"over the specified BOUNDARY.\n";
	}

	void parseArguments(int argc, char *argv[])
	{
		po::store(po::parse_command_line(argc, argv, cliOptions), variablesMap);
		po::notify(variablesMap);
	}

	void setLogLevel(unsigned logLevel)
	{
		using cb::LogManager;
		if(logLevel > LogManager::LVL_TRACE)
		{
			throw std::domain_error("Invalid logging level.");
		}

		LOG_LEVEL(static_cast<LogManager::LogLevelType>(logLevel));
	}

	template<class F, class S>
	S& setupStreamByArgument(const std::string& argument, S& std, F& fileStream)
	{
		if(variablesMap.count(argument))
		{
			const std::string& fileName =
					variablesMap[argument].as<std::string>();

			if(fileName != "-")
			{
				fileStream.open(fileName.c_str());
				return fileStream;
			}
		}
		return std;
	}

	void setupLogging(std::ofstream& logFile)
	{
		if(variablesMap.count("verbose"))
		{
			unsigned logLevel = variablesMap["verbose"].as<unsigned>();
			setLogLevel(logLevel);
		}

		std::ostream& logStream(setupStreamByArgument("log", std::cerr, logFile));
		LOG_STREAM(logStream);
	}

	std::ostream& setupOutput(std::ofstream& outputFile)
	{
		return setupStreamByArgument("output", std::cout, outputFile);
	}

	std::istream& setupInput(std::ifstream& inputFile)
	{
		return setupStreamByArgument("input", std::cin, inputFile);
	}

	void buildSuiteSpecification(cb::SuiteSpecification& suiteSpec)
	{
		if(variablesMap.count("boundary"))
		{
			cb::Boundary boundary(variablesMap["boundary"].as<std::string>());
			suiteSpec.setBoundary(boundary);
		}

		if(variablesMap.count("function"))
		{
			cb::Definition definition(variablesMap["function"].as<std::string>());
			suiteSpec.setTestFunctor(definition);
		}

		if(variablesMap.count("max-calls"))
		{
			unsigned long callLimit = variablesMap["max-calls"].as<unsigned long>();
			suiteSpec.setCallLimit(callLimit);
		}

		if(variablesMap.count("samples"))
		{
			unsigned long sampleLimit = variablesMap["samples"].as<unsigned long>();
			suiteSpec.setSampleLimit(sampleLimit);
		}

		if(variablesMap.count("method"))
		{
			const std::vector<std::string>& methodDefinitionStrs =
					variablesMap["method"].as< std::vector<std::string> >();

			std::vector<std::string>::const_iterator i;
			const std::vector<std::string>::const_iterator end =
					methodDefinitionStrs.end();

			for(i = methodDefinitionStrs.begin(); i != end; ++i)
			{
				cb::Definition methodDefinition(*i);
				suiteSpec.addMethod(methodDefinition.getName());
			}
		}

		/* Create test cases for tolerances from 1 to 13 significant digits */
		for(int d = 2; d < 15; ++d)
		{
			cb::CaseSpecification caseSpec;
			caseSpec.setRelativeTolerance(5.0 * exp10(-d));
			suiteSpec.addCase(caseSpec);
		}
	}

	void readSamples(cb::SuiteResults& suiteResults)
	{
		std::ifstream inputFile;
		std::istream& inputStream(setupInput(inputFile));
		boost::archive::binary_iarchive ia(inputStream);
		ia & suiteResults;
	}

	void runBenchmark(cb::SuiteResults& suiteResults)
	{
		cb::SuiteSpecification suiteSpec;
		buildSuiteSpecification(suiteSpec);
		suiteResults.setSpecification(suiteSpec);
		cb::Benchmark benchmark(suiteResults);
		benchmark.computeResults();
	}

	template<class C>
	void setupViews(C& viewBuilders)
	{
		cb::ViewFactory viewFactory;
		if(variablesMap.count("view"))
		{
			const std::vector<std::string>& viewDefinitionStrs =
					variablesMap["view"].as< std::vector<std::string> >();

			std::vector<std::string>::const_iterator i;
			const std::vector<std::string>::const_iterator end =
					viewDefinitionStrs.end();

			for(i = viewDefinitionStrs.begin(); i != end; ++i)
			{
				cb::Definition viewDefinition(*i);
				LOG(INFO, "Adding data view: " << viewDefinition.getName());
				cb::ViewBuilder* viewBuilder =
						viewFactory.getByDefinition(viewDefinition);

				viewBuilders.push_back(viewBuilder);
			}
		}
	}

	CLIInterface()
	{
	}

public:
	CLIInterface(int argc, char *argv[]) :
		programName(argv[0]),
		mandatory("Mandatory options"),
		optional("Allowed options"),
		logging("Logging options"),
		other("Other")
	{
		addMandatoryArguments();
		addOptions();
		addLoggingOptions();
		addHelp();
		initMethodList();
		initTestFunctionList();
		initViewList();
		parseArguments(argc, argv);
	}

	int run()
	{
		int exitStatus = 0;

		if(variablesMap.count("version"))
		{
			showVersion();
		}
		else if(variablesMap.count("help"))
		{
			showHelp();
		}
		else if(variablesMap.count("list-methods"))
		{
			showList(methodList);
		}
		else if(variablesMap.count("list-functions"))
		{
			showList(testFunctionList);
		}
		else if(variablesMap.count("list-views"))
		{
			showList(viewList);
		}
		else if(variablesMap.count("list-all"))
		{
			std::cout << "Methods:\n";
			showList(methodList);
			std::cout << "\nTest functions:\n";
			showList(testFunctionList);
			std::cout << "\nViews:\n";
			showList(viewList);
		}
		else
		{
			const bool read = variablesMap.count("input");
			const bool benchmark = variablesMap.count("function");

			if(read == benchmark)
			{
				std::cout << "Either -f or -i has to be specified\n";
				showUsage();
				exitStatus = -1;
			}
			else
			{
				std::ofstream logFile;
				setupLogging(logFile);

				std::vector<std::string> methodNames;
				boost::ptr_vector<cb::ViewBuilder> viewBuilders;
				setupViews(viewBuilders);

				cb::SuiteResults suiteResults;
				if(read)
				{
					readSamples(suiteResults);
				}
				else
				{
					runBenchmark(suiteResults);
				}

				std::stringstream outputBuf;
				for(size_t i = 0; i < viewBuilders.size(); ++i)
				{
					viewBuilders[i].create(suiteResults, outputBuf);
					outputBuf << "\n\n";
				}
				std::ofstream outputFile;
				std::ostream& outputStream(setupOutput(outputFile));
				outputStream << outputBuf.str();
			}
		}

		return exitStatus;
	}
};

int exitStatus = 0;


} // end namespace

int main(int argc, char *argv[])
{
	try
	{
		std::locale def;
		std::cout.imbue(def);
		std::cerr.imbue(def);
		std::cin.imbue(def);

		cbApp::CLIInterface cubmark(argc, argv);
		cbApp::exitStatus = cubmark.run();
	}
	catch(cb::InvalidNameError& e)
	{
		std::cerr <<"Invalid name exception: "<< e.what() <<"\n"
				"See error log for details.\n";

		cbApp::exitStatus = -1;
	}
	catch(cb::InvalidValueError& e)
	{
		std::cerr <<"Invalid value exception: "<< e.what() <<"\n"
				"See error log for details.\n";

		cbApp::exitStatus = -1;
	}
	catch(cb::IncompleteError& e)
	{
		std::cerr <<"Incomplete definition exception: "<< e.what() <<"\n"
				"See error log for details.\n";

		cbApp::exitStatus = -1;
	}
	catch(std::runtime_error& e)
	{
		std::cerr <<"Runtime exception: "<< e.what() <<"\n"
				"See error log for details.\n";

		cbApp::exitStatus = -1;
	}
	catch(std::exception& e)
	{
		std::cerr <<"Unhandled exception: "<< e.what() <<"\n"
				"See error log for details.\n";

		cbApp::exitStatus = -1;
	}
	catch(...)
	{
		cbApp::exitStatus = -1;
	}

	return cbApp::exitStatus;
}
