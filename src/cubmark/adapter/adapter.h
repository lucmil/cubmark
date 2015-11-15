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

/** \file
 * \brief Main header for functor Adapters
 *
 * This library provides a method for interfacing C code with C++ code.
 *
 * \par Quick start:
 * Skip the rationale and
 * see cb::UnaryAdapter and cb::BinaryAdapter documentation in the
 * adapter/types.h header for example usage.
 *
 * \par Rationale:
 * A common usage pattern for interfacing with legacy C code is to define a
 * functor, use a function as an entry point for the C code, like
 * so:
 * \code
 * struct power
 * {
 *    f() : k(0) {}
 *    f(int k) : k(k) {}
 *    int k;
 *    int operator()(int x) const
 *    {
 *      return / * x^k * /;
 *    }
 * };
 *
 * power functor;
 * int Adapter(int x)
 * {
 *     return functor(x);
 * }
 *
 * int main()
 * {
 *     functor = power(10);
 *     std::cout << legacy_c_function(&Adapter) << '\n';
 * }
 * \endcode
 * But this becomes tedious as every functor requires it's own hand-written
 * function. This approach also limits the number of simultaneous
 * instances of the functor to one (or one's mastery of the copy-paste buffer).
 *
 * This library provides a straightforward method of functor->function pointer
 * "conversion" via an Adapter. The number of simultaneous instances of a
 * functor is limited at compile-time, with the upper limit being specific to
 * the compiler's template depth recursion.
 *
 * See cb::AdapterTraits.
 *
 * \todo Rewrite the library to enable in-lining of functors.
 * \todo Better documentation of the concepts a functor must fullfil to
 *       be usable with Adapters.
 */
/** \example adapter_function_template.cpp
 * A full example on how to acquire an Adapter for the simplest functor.
 */
/** \example adapter_function_template_stl.cpp
 * A full example on how to acquire an Adapter for STL-style functors.
 */
/** \example adapter_benchmark.cpp
 * Performance comparison of this approach and static functions.
 */
#ifndef CUBMARK_ADAPTER_LIB
#define CUBMARK_ADAPTER_LIB

#include <cubmark/adapter/types.h>
#include <cubmark/adapter/AdapterLock.h>

#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include <cubmark/adapter/constants.h>
#include <cubmark/adapter/cxx0x/adapter_stl.hpp>
#else
#error Adapters require variadic templates from c++0x
#endif

#endif//CUBMARK_ADAPTER_LIB
