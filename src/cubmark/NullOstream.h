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

// Copyright (C) 1997, 1998, 1999, 2000, 2001, 2002, 2003, 2004, 2005,
// 2006, 2007, 2008, 2009
// Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** \file
 * \brief Stream pointing to /dev/null
 *
 * This file contains the class definition and utilities for a complete
 * std::ostream interface of a stream that does absolutely nothing.
 */
#ifndef CUBMARK_NULLOSTREAM_H
#define CUBMARK_NULLOSTREAM_H

#include <iostream>
#include <ios>
#include <streambuf>

namespace cb
{

/** \brief Output stream to /dev/null
 *
 * Use as any other standard output stream.
 */
template<typename CharT, typename Traits>
class NullOstream :
	public std::basic_ostream<CharT, Traits>
{
public:

	typedef CharT char_type;
	typedef typename Traits::int_type int_type;
	typedef typename Traits::pos_type pos_type;
	typedef typename Traits::off_type off_type;
	typedef Traits traits_type;

	virtual ~NullOstream()
	{
	}

	class sentry;
	friend class sentry;

	NullOstream& operator<<(NullOstream& (*__pf)(NullOstream&))
	{
		return *this;
	}

	NullOstream&
	operator<<(std::basic_ios<CharT, Traits>& (*__pf)(std::basic_ios<CharT, Traits>&))
	{
		return *this;
	}

	NullOstream& operator<<(std::ios_base& (*__pf) (std::ios_base&))
	{
		return *this;
	}

	NullOstream& operator<<(long)
	{
		return *this;
	}

	NullOstream& operator<<(unsigned long)
	{
		return *this;
	}

	NullOstream& operator<<(bool)
	{
		return *this;
	}

	NullOstream& operator<<(short)
	{
		return *this;
	}

	NullOstream& operator<<(unsigned short)
	{
		return *this;
	}

	NullOstream& operator<<(int)
	{
		return *this;
	}

	NullOstream& operator<<(unsigned int)
	{
		return *this;
	}

#ifndef __STRICT_ANSI__
	NullOstream& operator<<(long long)
	{
		return *this;
	}

	NullOstream& operator<<(unsigned long long)
	{
		return *this;
	}
#endif//__STRICT_ANSI__

	NullOstream& operator<<(double)
	{
		return *this;
	}

	NullOstream& operator<<(float)
	{
		return *this;
	}

	NullOstream& operator<<(long double)
	{
		return *this;
	}

	NullOstream& operator<<(const void*)
	{
		return *this;
	}

	NullOstream& operator<<(std::basic_streambuf<CharT, Traits>*)
	{
		return *this;
	}


	NullOstream& put(char_type __c);
	NullOstream& write(const char_type* __s, std::streamsize __n);

	NullOstream& flush();
	pos_type tellp();
	NullOstream& seekp(pos_type);
	NullOstream& seekp(off_type, std::ios_base::seekdir);

	NullOstream()
	{
	}
};

template <typename CharT, typename Traits>
class NullOstream<CharT, Traits>::sentry
{
	public:
	explicit sentry(NullOstream<CharT, Traits>&);
	~sentry()
	{
	}

	operator bool() const
	{
		return true;
	}
};

template<typename CharT, typename Traits>
NullOstream<CharT, Traits>&
operator<<(NullOstream<CharT, Traits>& out, CharT)
{
	return out;
}

template<typename CharT, typename Traits>
NullOstream<CharT, Traits>&
operator<<(NullOstream<CharT, Traits>& out, char)
{
	return out;
}

template<typename CharT, typename Traits>
NullOstream<CharT, Traits>&
operator<<(NullOstream<CharT, Traits>& out, const CharT*)
{
	return out;
}

template<typename CharT, typename Traits>
NullOstream<CharT, Traits> &
operator<<(NullOstream<CharT, Traits>& out, const char*)
{
	return out;
}

template<typename CharT, typename Traits>
NullOstream<CharT, Traits>& endl(NullOstream<CharT, Traits>& os)
{
	return os;
}

template<typename CharT, typename Traits>
NullOstream<CharT, Traits>& ends(NullOstream<CharT, Traits>& os)
{
	return os;
}

template<typename CharT, typename Traits>
NullOstream<CharT, Traits>& flush(NullOstream<CharT, Traits>& os)
{
	return os;
}

}

#endif//CUBMARK_NULLOSTREAM_H
