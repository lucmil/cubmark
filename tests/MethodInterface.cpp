#define BOOST_TEST_MODULE Method test
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/push_front.hpp>
#include <limits>
#include <cstdlib>

#include <cubmark/config.h>
#include <cubmark/constants.h>
#include <cubmark/Method.h>

typedef boost::mpl::list<> empty;

#define LIST empty

#if defined(CUBMARK_HAS_R2D2LRI)
#include <cubmark/R2d2lri.h>
typedef boost::mpl::push_front<LIST, cb::R2d2lri>::type push_r2d2lri;
#include <cubmark/Adaptive.h>
typedef boost::mpl::push_front<push_r2d2lri, cb::Adaptive>::type push_adaptive;
#undef LIST
#define LIST push_adaptive
#endif

#if defined(CUBMARK_HAS_CUBPACKPP)
#include <cubmark/Cubpack.h>
typedef boost::mpl::push_front<LIST, cb::Cubpack>::type push_cubpackpp;
#undef LIST
#define LIST push_cubpackpp
#endif

#if defined(CUBMARK_HAS_HINTLIB)
#include <cubmark/HIntLib.h>
typedef boost::mpl::push_front<LIST, cb::HIntLib>::type push_hintlib;
#undef LIST
#define LIST push_hintlib
#endif

#if defined(CUBMARK_HAS_DCUHRE)
#include <cubmark/Dcuhre.h>
typedef boost::mpl::push_front<LIST, cb::Dcuhre>::type push_dcuhre;
#undef LIST
#define LIST push_dcuhre
#endif

#if defined(CUBMARK_HAS_GSL)
#include <cubmark/Qag2D.h>
typedef boost::mpl::push_front<LIST, cb::Qag2D>::type push_gsl;
#undef LIST
#define LIST push_gsl
#endif

typedef LIST test_types;

const cb::Boundary unitSquare(	0.0,		1.0,		0.0,		1.0		);

const cb::Boundary rightPlane(	-cb::inf,	cb::inf,	-cb::inf,	cb::inf	);

const cb::Boundary planeSector1st(		0.,	cb::inf, 	0.0,		cb::inf	);
const cb::Boundary planeSector2nd(-cb::inf,	0.0,		0.0,		cb::inf	);
const cb::Boundary planeSector3rd(		0.,	cb::inf,	-cb::inf,	0.0		);
const cb::Boundary planeSector4th(-cb::inf,	0.0,		-cb::inf,	0.0		);

const cb::Boundary xStrip	(0.0,		1.0,		-cb::inf,	cb::inf	);
const cb::Boundary yStrip	(-cb::inf,	cb::inf,	0.0,		1.0		);
const cb::Boundary xPosStrip(0.0,		1.0,		0.0,		cb::inf	);
const cb::Boundary xNegStrip(0.0,		1.0,		-cb::inf,	0.0		);
const cb::Boundary yPosStrip(0.0,		cb::inf,	0.0,		1.0		);
const cb::Boundary yNegStrip(-cb::inf,	0.0,		0.0,		1.0		);

double integrand(double, double)
{
	return 1.;
}

/**
 * A function with undefined values within a unit circle at the point of origin.
 */
double singular(double x, double y)
{
	return log(sqrt(x*x + y*y) -1.);
}

template<class M>
struct MethodFixture
{
	cb::Method* method;

	MethodFixture()
	{
		method = new M();
	}

	~MethodFixture()
	{
		delete method;
	}

};

#if defined(CUBMARK_HAS_R2D2LRI)
template<>
struct MethodFixture<cb::Adaptive>
{
	cb::Method* method;

	MethodFixture()
	{
		method = new cb::Adaptive(new cb::R2d2lri);
	}

	~MethodFixture()
	{
		delete method;
	}

	static double integrand(double, double)
	{
		return 1.;
	}
};
#endif//defined(CUBMARK_HAS_R2D2LRI)

BOOST_AUTO_TEST_SUITE(MethodInterface)

BOOST_AUTO_TEST_CASE_TEMPLATE(InitialState, T, test_types )
{
	typedef MethodFixture<T> FixtureType;
	FixtureType f;

    BOOST_CHECK_EQUAL(f.method->getIntegrand(), static_cast<cb::Method::IntegrandType>(0));
    BOOST_CHECK_EQUAL(f.method->hasIntegrand(), false);
    BOOST_CHECK_EQUAL(f.method->hasBoundary(), false);
	BOOST_CHECK_EQUAL(f.method->getRelativeTolerance(), 0.0);
	BOOST_CHECK_EQUAL(f.method->getAbsoluteTolerance(), 0.0);
	BOOST_CHECK_NE(f.method->getCallLimit(), 0);
	BOOST_WARN_EQUAL(f.method->getCallCnt(), 0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(IntegrandSetup, T, test_types )
{
	typedef MethodFixture<T> FixtureType;
	FixtureType f;

	f.method->setIntegrand(&integrand);

    BOOST_CHECK_EQUAL( f.method->getIntegrand(), &integrand);
    BOOST_CHECK_EQUAL( f.method->hasIntegrand(), true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ParametersAreIndependent, T, test_types )
{
	typedef MethodFixture<T> FixtureType;
	FixtureType f;

	const size_t callLimit = f.method->getCallLimit();

	f.method->setIntegrand(&integrand);
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), false);
    BOOST_CHECK_EQUAL( f.method->getAbsoluteTolerance(), 0.0);
    BOOST_CHECK_EQUAL( f.method->getRelativeTolerance(), 0.0);
    BOOST_CHECK_EQUAL( f.method->getCallLimit(), callLimit);

	f.method->setBoundary(unitSquare);
    BOOST_CHECK_EQUAL( f.method->getIntegrand(), &integrand);
    BOOST_CHECK_EQUAL( f.method->getAbsoluteTolerance(), 0.0);
    BOOST_CHECK_EQUAL( f.method->getRelativeTolerance(), 0.0);
    BOOST_CHECK_EQUAL( f.method->getCallLimit(), callLimit);

	f.method->setRelativeTolerance(0.01);
    BOOST_CHECK_EQUAL( f.method->getIntegrand(), &integrand);
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), true);
    BOOST_CHECK_EQUAL( f.method->getAbsoluteTolerance(), 0.0);
    BOOST_CHECK_EQUAL( f.method->getCallLimit(), callLimit);

	f.method->setAbsoluteTolerance(0.01);
    BOOST_CHECK_EQUAL( f.method->getIntegrand(), &integrand);
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), true);
    BOOST_CHECK_EQUAL( f.method->getRelativeTolerance(), 0.01);
    BOOST_CHECK_EQUAL( f.method->getCallLimit(), callLimit);

	f.method->setCallLimit(1000000);
    BOOST_CHECK_EQUAL( f.method->getIntegrand(), &integrand);
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), true);
    BOOST_CHECK_EQUAL( f.method->getAbsoluteTolerance(), 0.01);
    BOOST_CHECK_EQUAL( f.method->getRelativeTolerance(), 0.01);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(RectangleBoundarySetup, T, test_types )
{
	typedef MethodFixture<T> FixtureType;
	FixtureType f;
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), false);

	f.method->setBoundary(unitSquare);
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), true);

	f.method->setBoundary(cb::Boundary());
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), false);

}

BOOST_AUTO_TEST_CASE_TEMPLATE(InfiniteStripBoundarySetup, T, test_types )
{
	typedef MethodFixture<T> FixtureType;
	FixtureType f;
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), false);

	f.method->setBoundary(xStrip);
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), true);

	f.method->setBoundary(yStrip);
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), true);

	f.method->setBoundary(cb::Boundary());
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), false);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(SemiInfiniteStripBoundarySetup, T, test_types )
{
	typedef MethodFixture<T> FixtureType;
	FixtureType f;
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), false);

	f.method->setBoundary(xPosStrip);
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), true);

	f.method->setBoundary(xNegStrip);
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), true);

	f.method->setBoundary(yPosStrip);
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), true);

	f.method->setBoundary(yNegStrip);
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), true);

	f.method->setBoundary(cb::Boundary());
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), false);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(PlaneSectorBoundarySetup, T, test_types )
{
	typedef MethodFixture<T> FixtureType;
	FixtureType f;
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), false);

	f.method->setBoundary(planeSector1st);
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), true);

	f.method->setBoundary(planeSector2nd);
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), true);

	f.method->setBoundary(planeSector3rd);
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), true);

	f.method->setBoundary(planeSector4th);
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), true);

	f.method->setBoundary(cb::Boundary());
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), false);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(PlaneBoundarySetup, T, test_types )
{
	typedef MethodFixture<T> FixtureType;
	FixtureType f;
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), false);

	f.method->setBoundary(rightPlane);
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), true);

	f.method->setBoundary(cb::Boundary());
    BOOST_CHECK_EQUAL( f.method->hasBoundary(), false);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(RelativeToleranceSetup, T, test_types )
{
	typedef MethodFixture<T> FixtureType;
	FixtureType f;

	f.method->setRelativeTolerance(0.01);
	BOOST_CHECK_EQUAL(f.method->getRelativeTolerance(), 0.01);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(AbsoluteToleranceSetup, T, test_types )
{
	typedef MethodFixture<T> FixtureType;
	FixtureType f;

	f.method->setAbsoluteTolerance(0.01);
	BOOST_CHECK_EQUAL(f.method->getAbsoluteTolerance(), 0.01);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(CallLimitSetup, T, test_types )
{
	typedef MethodFixture<T> FixtureType;
	FixtureType f;

	f.method->setCallLimit(1000000);
	BOOST_REQUIRE_LE(f.method->getCallLimit(), 1000000);
	BOOST_WARN_EQUAL(f.method->getCallLimit(), 1000000);
}

void setupUnitSquareIntegrand(cb::Method& method)
{
	method.setIntegrand(&integrand);
	method.setBoundary(unitSquare);
	method.setCallLimit(100000);
}

void checkUnitSquareIntegrand(cb::Method& method)
{
	double result = cb::NaN;

	BOOST_REQUIRE_NO_THROW(result = method.compute());
	BOOST_REQUIRE_EQUAL(std::isnan(result), false);
	BOOST_REQUIRE_CLOSE(result, 1.0, 0.01);
	BOOST_REQUIRE_EQUAL(method.failed(), false);
	BOOST_WARN_LE(method.getCallCnt(), 100000);
	BOOST_CHECK_LE(method.getCallCnt(), 150000);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(RelativeToleranceTestRun, T, test_types )
{
	typedef MethodFixture<T> FixtureType;
	FixtureType f;

	setupUnitSquareIntegrand(*f.method);
	f.method->setRelativeTolerance(0.01);
	checkUnitSquareIntegrand(*f.method);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(AbsoluteToleranceTestRun, T, test_types )
{
	typedef MethodFixture<T> FixtureType;
	FixtureType f;

	setupUnitSquareIntegrand(*f.method);
	f.method->setAbsoluteTolerance(0.01);
	checkUnitSquareIntegrand(*f.method);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(FailureTestRun, T, test_types )
{
	typedef MethodFixture<T> FixtureType;
	FixtureType f;
	double result = cb::NaN;

	f.method->setIntegrand(&singular);
	f.method->setBoundary(unitSquare);
	f.method->setAbsoluteTolerance(0.01);
	f.method->setCallLimit(100000);

	BOOST_REQUIRE_NO_THROW(result = f.method->compute());
	BOOST_REQUIRE_EQUAL(std::isnan(result), true);
	BOOST_REQUIRE_EQUAL(f.method->failed(), true);
	BOOST_WARN_LE(f.method->getCallCnt(), 100000);
}

BOOST_AUTO_TEST_SUITE_END()
