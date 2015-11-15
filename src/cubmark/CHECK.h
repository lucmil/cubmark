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

#ifndef CUBMARK_CHECK_H
#define CUBMARK_CHECK_H

#include <cubmark/config.h>

#ifndef CUBMARK_NDEBUG

#define CHECK(expression, error) \
		CHECK_(expression, error, CUBMARK_LOG_PREFIX # expression)

#else //CUBMARK_NDEBUG

#define CHECK(expression, exception)

#endif//CUBMARK_NDEBUG

/** \brief Compile-time assertion
 *
 * If the assertion fails the compiler will abort with an "undefined
 * constructor" error with the error message passed as the type in the argument
 * list of the undefined constructor.
 *
 * Example:
 * \code
 * STATIC_CHECK(sizeof(unsigned char) == 1, Wrong_size_of_unsigned_char)
 * \endcode
 * If the expression fails GCC will abort compilation with the error message.
 * <pre>
 * error: no matching function for call to
 * ‘cb::compile_time_checker<false>::compile_time_checker(main()::Wrong_size_of_unsigned_char)
 * </pre>
 *
 * \param cond Compile-time expression to chcek
 * \param error_msg Error message to show when the assertion fails.
 *                  This is used as a type so the message should be in a
 *                  form of a legal type identifier.
 */
#define STATIC_CHECK(cond, msg) \
		{\
			class error_msg {}; \
			(void)sizeof(cb::compile_time_checker<cond>(error_msg()) != 0); \
		}

#endif//CUBMARK_CHECK_H

