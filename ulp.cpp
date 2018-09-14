// ulp.cpp - units in the last place
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "xllfloat.h"
#include "ulp.h"

#ifndef CATEGORY
#define CATEGORY "Float"
#endif

using namespace xll;

static AddInX xai_ulp(
	FunctionX(XLL_DOUBLE, _T("?xll_ulp"), _T("ULP"))
	.Arg(XLL_DOUBLE, _T("x"), _T("is a floating point number."))
	.Arg(XLL_DOUBLE, _T("y"), _T("is a floating point number. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("The number of floating point values that can be exactly represented between x and y"))
	.Documentation(
		_T("Note <codeInline>ULP(y, x) = n</codeInline> if and only ")
		_T("if <codeInline>y = NEXTAFTER(x, n)</codeInline>.")
/*		,
		xml::xlink(_T("NEXTAFTER"))
*/	)
);
double WINAPI
xll_ulp(double x, double y)
{    
#pragma XLLEXPORT

	return static_cast<double>(ulp(x, y));
}

#ifdef _DEBUG

template<class T>
void
xll_test_nextafter(void)
{
    T x = T(1.23), y;
		
	y = nextafter(x, x + 1);
	ensure (1 == ulp(y, x));
	y = nextafter(x, x - 1);
	ensure (-1 == ulp(y, x));
}

int
xll_test_ulp(void)
{
	try {
		xll_test_nextafter<float>();
		xll_test_nextafter<double>();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return 1;
}

static Auto<OpenAfter> xao_test_ulp(xll_test_ulp);

#endif // _DEBUG