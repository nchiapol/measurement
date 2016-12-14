# distutils: language = c++
# distutils: sources  = measurement.cpp
""" The MSS module allows to represent and manipulate measurements
with statistical and systematic uncertainties """
from libcpp.string cimport string
from cython.operator cimport dereference as deref

cdef extern from "measurement.h":
    cdef cppclass MSS:
        MSS()
        MSS(double, double, double)
        double val()
        double stat()
        double syst()
        void setVal(double)
        void setStat(double)
        void setSyst(double)
        MSS add(const MSS&, const MSS&, double, double)
        MSS mul(const MSS&, const MSS&, double, double)
        MSS sub(const MSS&, const MSS&, double, double)
        MSS div(const MSS&, const MSS&, double, double)
        double getTotalUncertainty()
        string getString(const string&, int)
        string getStringSqSum(const string&, int)

cdef wrapMSS(MSS src):
    ret = Mss()
    ret.ptr = src
    return ret

cdef ensureMss(thing):
    if type(thing) == Mss:
        tmp = <Mss> thing
    else:
        tmp = Mss(thing)
    return tmp

cdef class Mss:
    """Measurement with statistical and systematic uncertainties

    The MSS class represents a measurement with statistical and systematic uncertainties
    and provides the basic mathematical operations (+, -, *, /) to combine several numbers.

    Example
    -------
    >>> R = MSS(1400, 30, 0)
    >>> I = MSS(1.12, 0.01, 0)
    >>> U = R*I
    >>> print U
    1568.00000 +/- 36.40000 +/- 0.00000"
    """
    cdef MSS ptr
    def __cinit__(self, double val=1, double stat=0, double syst=0):
        self.ptr = MSS(val, stat, syst)
    def __str__(self):
        return self.getString()
    def __repr__(self):
        return self.getString()

    @property
    def val(self):
        return self.ptr.val()
    @property
    def stat(self):
        return self.ptr.stat()
    @property
    def syst(self):
        return self.ptr.syst()

    def setVal(self, val):
        """ set the value """
        self.ptr.setVal(val)
    def setStat(self, stat):
        """ set the statistical uncertainty """
        self.ptr.setStat(stat)
    def setSyst(self, syst):
        """ set the systematic uncertainty """
        self.ptr.setSyst(syst)

    def add(Mss self, b, cStat=0., cSyst=0.):
        """ add two measurements (or a measurement and a number)

        cStat and cSyst are the correlation coefficient
        for the statistical and systematic uncertainties respectively
        """
        tmp_b = <Mss> ensureMss(b)
        return wrapMSS(self.ptr.add(self.ptr, tmp_b.ptr, cStat, cSyst))
    def __add__(self, b):
        tmp_self = <Mss> ensureMss(self)
        return tmp_self.add(b)
    def mul(Mss self, b, cStat=0., cSyst=0.):
        """ multiply two measurements (or a measurement and a number)

        cStat and cSyst are the correlation coefficient
        for the statistical and systematic uncertainties respectively
        """
        tmp_b = <Mss> ensureMss(b)
        return wrapMSS(self.ptr.mul(self.ptr, tmp_b.ptr, cStat, cSyst))
    def __mul__(self, b):
        tmp_self = <Mss> ensureMss(self)
        return tmp_self.mul(b)
    def sub(Mss self, b, cStat=0., cSyst=0.):
        """ subtract two measurements (or a measurement and a number)

        cStat and cSyst are the correlation coefficient
        for the statistical and systematic uncertainties respectively
        """
        tmp_b = <Mss> ensureMss(b)
        return wrapMSS(self.ptr.sub(self.ptr, tmp_b.ptr, cStat, cSyst))
    def __sub__(self, b):
        tmp_self = <Mss> ensureMss(self)
        return tmp_self.sub(b)
    def div(Mss self, b, cStat=0., cSyst=0.):
        """ divide two measurements (or a measurement and a number)

        cStat and cSyst are the correlation coefficient
        for the statistical and systematic uncertainties respectively
        """
        tmp_b = <Mss> ensureMss(b)
        return wrapMSS(self.ptr.div(self.ptr, tmp_b.ptr, cStat, cSyst))
    def __div__(self, b):
        tmp_self = <Mss> ensureMss(self)
        return tmp_self.div(b)

    def getTotalUncertainty(self):
        """ calculate the total uncertainty (by adding in quadrature) """
        return self.ptr.getTotalUncertainty()
    def getString(self, delimiter = "+/-", digits=5):
        """ create a string representation of the measurement

        The statistical and the systematic uncertainties are
        given separated by the delimiter and all values are
        rounded to the given number of digits.
        """
        return self.ptr.getString(delimiter, digits)
    def getStringSqSum(self, delimiter, digits):
        """ create a string representation of the measurement

        The statistical and the systematic uncertainties are
        combined (added in quadrature) and given as one value
        separated by the delimiter. All values are rounded to
        the given number of digits.
        """
        return self.ptr.getStringSqSum(delimiter, digits)

cpdef add(Mss a, b, cStat=0., cSyst=0.):
    """ helper calling a.add(b, cStat, cSyst) """
    return a.add(b, cStat, cSyst)

cpdef mul(Mss a, b, cStat=0., cSyst=0.):
    """ helper calling a.mul(b, cStat, cSyst) """
    return a.mul(b, cStat, cSyst)

cpdef sub(Mss a, b, cStat=0., cSyst=0.):
    """ helper calling a.sub(b, cStat, cSyst) """
    return a.sub(b, cStat, cSyst)

cpdef div(Mss a, b, cStat=0., cSyst=0.):
    """ helper calling a.div(b, cStat, cSyst) """
    return a.div(b, cStat, cSyst)

