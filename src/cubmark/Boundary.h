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

#ifndef CUBMARK_BOUNDARY_H
#define CUBMARK_BOUNDARY_H

#include <utility>
#include <vector>
#include <string>

namespace boost
{
	namespace serialization
	{
		class access;
	}
}

namespace cb
{

/** \brief Rectangular integral region class
 */
class Boundary
{
	friend class boost::serialization::access;
public:
	/** \brief Default constructor.
	 */
	Boundary();

	/** \brief Parse a boundary string
	 */
	Boundary(const std::string& boundaryStr);

	/** \brief Base constructor.
	 *
	 * Initiates an object which represents a region
	 * \f[ D = [a,b] \times [c,d] \f]
	 * where \f$ a,b,c,d \in R \f$
	 *
	 * \pre a,b,c and d are not NaN
	 * \param a
	 * \param b
	 * \param c
	 * \param d
	 * \throws std::runtime_exception When isnan() returns true for one of a, b, c, d.
	 */
	Boundary(double a, double b, double c, double d);

	/** \brief Is the boundary valid?
	 *
	 * \return True if none of the boundary parameters contain a NaN.
	 */
	bool isValid() const;

	/** \brief Is the boundary infinite in any axis?
	 *
	 * \returns True if either a, b, c or d equals inf or -inf.
	 */
	bool isInfinite() const;

	/** \brief Does the boundary define an infinite (right) plane?
	 *
	 * \returns True if (a, b) = (-inf, inf) and (c, d) = (-inf, inf)
	 */
	bool isPlane() const;

	/** \brief Does the boundary define a square region?
	 *
	 * \returns True if (b - a) == (c - d)
	 */
	bool isRegular() const;

	/** \brief Fill in missing boundaries with values from another object
	 *
	 * \param boundary Replace missing values from this object
	 * \return number of values taken from boundary
	 */
	void fillIn(const Boundary& boundary);

	const std::pair<double, double>& getLimits(size_t dim) const;
	double u(size_t dim) const;
	double l(size_t dim) const;

	void setLimits(size_t dim, const std::pair<double, double>& limits) ;
	void setU(size_t dim, double u);
	void setL(size_t dim, double l);

	template<class Archive>
	void serialize(Archive& archive, const unsigned int version);
private:
	void parseBoundaryStr(const std::string &boundaryStr);

	typedef std::vector< std::pair<double, double> > LimitsType;
	typedef std::vector< std::pair<bool, bool> > PlaceholdersType;

	LimitsType limits;
	PlaceholdersType placeholders;
};

}
#endif//CUBMARK_BOUNDARY_H
