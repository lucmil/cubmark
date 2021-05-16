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

#ifndef CUBMARK_DEBUG_CHECK_HPP
#define CUBMARK_DEBUG_CHECK_HPP

#include <cubmark/CHECK.h>
#include <cubmark/LogManager.h>

#ifndef CUBMARK_NDEBUG
#ifdef  CUBMARK_USE_EXCEPTIONS

#include <stdexcept>

namespace cb
{

/** \brief Runtime assertion check
 *
 * \param expression expression to check
 * \param error_message Error message to pass with the exception
 * \throws std::runtime_error when expression is false
 */
void CHECK_(bool expression, const char *error_message, const char *prefix = "");

/** \brief Assertion check
 *
 * \param expression expression to check
 * \param exception exception to throw when expression is false
 * \throws \c exception when \c expression is false
 * \tparam E exception class
 */
template<class E>
void CHECK_(bool expression, const E& exception, const char* prefix = "")
{
	if(!expression)
	{
		LOG_RAW(FATAL, "Assertion failed at " << prefix << "\nException thrown: "
				<< exception.what());
		throw exception;
	}
}

}

#else //CUBMARK_USE_EXCEPTIONS

namespace cb
{

template<class E>
void CHECK_(bool expression, const E &exception, const char *prefix);

/** \brief Assertion check w/o exceptions
 *
 * This function prints \c exception.what() and calls exit() instead
 * of actually throwing the exception.
 *
 * \param expression expression to check
 * \param exception pseudo-exception to throw when expression is false
 * \param prefix Prefix inserted before the error message. See
 *               CUBMARK_LOG_PREFIX
 * \tparam E pseudo-exception class
 */
void CHECK_(bool expression, const char *error_message, const char *prefix = "");

template<class E>
void CHECK_(bool expression, const E &exception, const char *prefix = "");
{
	CHECK_(expression, exception.what(), prefix);
}

}

#endif//CUBMARK_USE_EXCEPTIONS
#endif//CUBMARK_NDEBUG

namespace cb
{

/** \brief Static assertion checker
 *
 * \tparam E compile-time expression result
 */
template<bool E>
struct compile_time_checker
{
	compile_time_checker(...) {};
	operator int() const {return 0;};
};

/** \brief Static assertion checker
 */
template<>
struct compile_time_checker<false>
{
};

}

#endif//CUBMARK_DEBUG_CHECK_HPP

