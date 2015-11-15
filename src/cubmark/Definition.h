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

#ifndef CUBMARK_DEFINITION_H
#define CUBMARK_DEFINITION_H

#include <deque>
#include <utility>
#include <string>

#include <cubmark/config.h>
#include <cubmark/types.h>

namespace boost
{
	namespace serialization
	{
		class access;
	}
}

namespace cb
{

/** \brief Definition class
 *
 * Class for tokenizing parameter strings.
 * See the constructor documentation for input syntax.
 *
 */
class Definition
{
	friend class boost::serialization::access;
public:
	typedef std::deque< std::pair<std::string, std::string> > ParametersType;

	/** \brief Default constructor
	 */
	Definition();

	/** \brief Parse a definition string
	 *
	 * A definition string is of the form:
	 * \code
	 * name:parameter_list
	 * \endcode
	 * An example of a test function definition could be: W3:n=3,C_x=2
	 *
	 * A parameter list is of the form:
	 * \code
	 * parameter_1,parameter_2,...,parameter_n
	 * \endcode
	 * where each parameter is a pair of name and value
	 * \code
	 * name[=value]
	 * \endcode
	 *
	 * \param definitionStr Definition string
	 */
	Definition(const std::string& definitionStr);

	/** \brief Get the name of the definition
	 *
	 * \returns Name of the definition
	 */
	const std::string& getName() const;

	/** \brief Get the parameter list of the definition
	 *
	 * \returns Parameter list
	 */
	const ParametersType& getParameters() const;

	std::string getString() const;

	template<class Archive>
	void serialize(Archive& archive, const unsigned int version);
private:
	std::string name;
	ParametersType parameters;

	/** \brief Parse a definition string
	 *
	 * \param definition Definition string
	 */
	void parseDefinition(const std::string& definition);

	/** \brief Parse a parameter list string
	 *
	 * \param parametersStr parameter list
	 */
	void parseParameters(const std::string& parametersStr);
};

}
#endif//CUBMARK_DEFINITION_H
