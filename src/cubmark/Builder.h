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

#ifndef CUBMARK_BUILDER_H
#define CUBMARK_BUILDER_H

#include <string>

namespace cb
{

class Definition;

/** \brief Common class for all builders
 */
class Builder
{
public:
	virtual ~Builder();

	/** \brief Set a parameter
	 *
	 * An implementing function should parse the provided value and name string.
	 *
	 * \param name Parameter name string
	 * \param value Parameter value string
	 *
	 * \throws InvalidNameError	 No parameter exists with the given name
	 * \throws InvalidValueError Parsed value is invalid (i.e. out of range)
	 */
	virtual void parseParameter(const std::string& name,
			const std::string& value) = 0;

	/** \brief Setup builder using a definition
	 *
	 * Parse multiple definitions in one go. This function will call
	 * parseParameter for each parameter found in the passed definition.
	 * Overload this in your subclass if you need more complex definition handling.
	 *
	 * \param definition Definition object
	 */
	virtual void parseDefinition(const Definition& definition);
};

}
#endif//CUBMARK_BUILDER_H
