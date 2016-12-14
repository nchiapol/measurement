// create constant for module level docstring

%define DOCSTR
"Measurement with statistical and systematic uncertainties

The MSS class represents a measurement with statistical and systematic uncertainties
and provides the basic mathematical operations (+, -, *, /) to combine several numbers.

Example
-------
>>> R = MSS(1400, 30, 0)
>>> I = MSS(1.12, 0.01, 0)
>>> U = R*I
>>> print U
1568.00000 +/- 36.40000 +/- 0.00000"
%enddef

// initialise module
%module(docstring=DOCSTR) mss

// define headers for wrapper file
%{
#include "measurement.h"
%}

// activate docstring features
%define CORRDOC
"cStat and cSyst are the correlation coefficient
for the statistical and systematic uncertainties respectively"
%enddef

%feature("autodoc", "2");
%feature("docstring") MSS::add CORRDOC;
%feature("docstring") MSS::sub CORRDOC;
%feature("docstring") MSS::mul CORRDOC;
%feature("docstring") MSS::div CORRDOC;

// include headers needed by swig
%include "std_string.i"
%include "measurement.h"

// add useful functions to python proxy class
%extend MSS {
  std::string __str__() {
       return $self->getString();
  }
  std::string __repr__() {
       return $self->getString();
  }
};

// add python code to the end of the module
%pythoncode %{
  MSS.val = property(_mss.MSS_val)
  MSS.stat = property(_mss.MSS_stat)
  MSS.syst = property(_mss.MSS_syst)
  add = MSS_add
  sub = MSS_sub
  mul = MSS_mul
  div = MSS_div
%}

