#include <UnitTest++.h>
#include "../measurement.h"

struct myFix
{
  myFix() {};
  ~myFix() {};

  MSS a = MSS(2, 0.3, 0.1);
  MSS b = MSS(3, 0.4, 0.1);
};

TEST_FIXTURE(myFix, getstring)
{
    CHECK_EQUAL("2.00000 +/- 0.30000 +/- 0.10000", a.getString() );
    CHECK_EQUAL("2.00000 & 0.30000 & 0.10000", a.getString("&") );
}

TEST_FIXTURE(myFix, addition)
{
    MSS c = a+b;
    CHECK_EQUAL( 5, c.val() );
    CHECK_EQUAL(.5, c.stat());
    CHECK_CLOSE(0.141, c.syst(), 0.001);
}

TEST_FIXTURE(myFix, multiplication)
{
    MSS c = a*b;
    CHECK_EQUAL(6, c.val());
    CHECK_CLOSE(1.204, c.stat(), 0.001);
    CHECK_CLOSE(0.360, c.syst(), 0.001);
}

TEST_FIXTURE(myFix, division)
{
    MSS c = b/a;
    CHECK_EQUAL(1.5, c.val());
    CHECK_CLOSE(0.301, c.stat(), 0.001);
    CHECK_CLOSE(0.090, c.syst(), 0.001);
}

TEST_FIXTURE(myFix, subtraction)
{
    MSS c = a-b;
    CHECK_EQUAL(-1, c.val());
    CHECK_EQUAL(.5, c.stat());
    CHECK_CLOSE(0.141, c.syst(), 0.001);
}

TEST_FIXTURE(myFix, addition_s)
{
    a+=b;
    CHECK_EQUAL( 5, a.val() );
    CHECK_EQUAL(.5, a.stat());
    CHECK_CLOSE(0.141, a.syst(), 0.001);
}


TEST_FIXTURE(myFix, multiplication_s)
{
    a*=b;
    CHECK_EQUAL(6, a.val());
    CHECK_CLOSE(1.204, a.stat(), 0.001);
    CHECK_CLOSE(0.360, a.syst(), 0.001);
}

TEST_FIXTURE(myFix, division_s)
{
    b/=a;
    CHECK_EQUAL(1.5, b.val());
    CHECK_CLOSE(0.301, b.stat(), 0.001);
    CHECK_CLOSE(0.090, b.syst(), 0.001);
}

TEST_FIXTURE(myFix, subtraction_s)
{
    a-=b;
    CHECK_EQUAL(-1, a.val());
    CHECK_EQUAL(.5, a.stat());
    CHECK_CLOSE(0.141, a.syst(), 0.001);
}


/** full usage tests based on exercise sheet from Data-Analysis lecture */
TEST(da_A1)
{
    MSS R(1400, 30, 0);
    MSS I(1.120, 0.010, 0);
    MSS U = R*I;
    CHECK_CLOSE(1568., U.val(), 0.01);
    CHECK_CLOSE(36., U.stat(), 0.5);
}

TEST(da_A2)
{
    MSS R = MSS( 900, 10, 0);
    MSS U = MSS(  45,  1, 0);
    MSS I = U/R;
    CHECK_EQUAL(0.05, I.val());
    CHECK_CLOSE(0.00124, I.stat(), 0.00001);
}

TEST(da_A3)
{
    MSS I_1 = MSS( 11e-3, 0.2e-3, 0.5e-3);
    MSS I_2 = MSS( 32e-3, 0.2e-3, 0.5e-3);
    MSS U_1 = MSS(  10, 20e-3, 50e-3);
    MSS U_2 = MSS(  30, 20e-3, 50e-3);
    MSS R = MSS::div(MSS::sub(U_2, U_1, 0, 1), MSS::sub(I_2, I_1, 0, 1));
    CHECK_CLOSE(952., R.val(), 0.5);
    CHECK_CLOSE(13., R.getTotalUncertainty(), 0.5);
    MSS R_m = MSS::mul(MSS(0.5, 0, 0), MSS::add(MSS::div(U_1, I_1), MSS::div(U_2, I_2), 0, 1));
    CHECK_CLOSE(923., R_m.val(), 0.5);
    CHECK_CLOSE(30., R_m.getTotalUncertainty(), 0.5);
}

TEST(da_A4)
{
    MSS L  = MSS(1, 0, 0.01);
    MSS r  = MSS(0.1, 0, 0.001);
    double pi = 3.1415926;
    MSS R = MSS::div(L, MSS::mul(r, r, 0, 1)*pi, 0, 1);
    CHECK_CLOSE(0.01, R.syst()/R.val(), 0.005);
    MSS m = MSS::mul(L, MSS::mul(r, r, 0, 1)*pi, 0, 1);
    CHECK_CLOSE(0.03, m.syst()/m.val(), 0.005);
}

int main()
{
    return UnitTest::RunAllTests();
}

