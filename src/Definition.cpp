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

#include <sstream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/trim.hpp>

#include <cubmark/Definition.h>

#include <cubmark/Scanner.hpp>
#include <cubmark/debug.h>

namespace cb
{

Definition::Definition()
{
}

Definition::Definition(const std::string& definitionStr)
{
	parseDefinition(definitionStr);
}

const std::string& Definition::getName() const
{
	return name;
}

const Definition::ParametersType& Definition::getParameters() const
{
	return parameters;
}

std::string Definition::getString() const
{
	std::ostringstream definitionStr;
	definitionStr << name <<':';

	ParametersType::const_iterator i = parameters.begin();
	const ParametersType::const_iterator end = parameters.end();

	if(i!=end)
	{
		definitionStr << i->first <<'='<< i->second;
		++i;
	}

	for(; i != end; ++i)
	{
		definitionStr <<','<< i->first <<'='<< i->second;
	}

	return definitionStr.str();
}

void Definition::parseDefinition(const std::string& definition)
{
	const size_t colonPos = definition.find(':');
	name = definition.substr(0, colonPos);
	boost::trim(name);

	if(colonPos != std::string::npos)
	{
		const std::string parametersStr(definition.substr(colonPos + 1));
		parseParameters(parametersStr);
	}
}

void Definition::parseParameters(const std::string& parametersStr)
{
	// Split string into separate parameter definitions
	typedef boost::tokenizer<boost::char_separator<char> > TokenizerType;
	boost::char_separator<char> commaSep(",");
	TokenizerType tokenizer(parametersStr, commaSep);

	TokenizerType::iterator i;
	const TokenizerType::iterator end = tokenizer.end();
	for(i = tokenizer.begin(); i != end; ++i)
	{
		const size_t eqPos = i->find('=');
		std::string name(i->substr(0, eqPos));
		boost::trim(name);

		std::string value;
		if(eqPos != std::string::npos)
		{
			value = i->substr(eqPos + 1);
		}
		parameters.push_back(make_pair(name, value));
	}
}

}
