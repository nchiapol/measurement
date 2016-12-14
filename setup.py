from distutils.core import setup, Extension

extension_mod = Extension("_mss", ["measurement_wrap.cxx","measurement.cpp"],
                          language="c++")

setup(name = "_mss", ext_modules=[extension_mod])
