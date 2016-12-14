.PHONY: all_tests run_pytest run_cpptest all_examples run_cppexample run_swigexample run_cppexample clean

all: build_cpp build_swig build_cython all_tests

all_tests: run_cpptest run_pytests

all_examples: run_cppexample run_swigexample run_cythonexample


build_cpp:
	g++ -fPIC -shared -o libmeasurement.so measurement.cpp
	g++ -std=c++11 -I/usr/include/unittest++ -I. -L. test/measurement_test.cpp measurement.cpp -o test/test_suite -lUnitTest++
	g++ -I. -L. -o examples/example examples/example.cpp -lmeasurement

build_swig:
	swig -Wall -python -keyword -c++ measurement.i
	python setup.py build_ext --swig-opts=-c++ --inplace

build_cython:
	python setup_cython.py build_ext --inplace

run_cpptest:
	@echo "\n** running c++ test suite **"
	LD_LIBRARY_PATH=. test/test_suite

run_pytests:
	@echo "\n** running python test suite **"
	python -m unittest discover


run_cppexample:
	LD_LIBRARY_PATH=. examples/example

run_swigexample:
	PYTHONPATH=. python examples/example.py

run_cythonexample:
	PYTHONPATH=. python examples/example_cy.py


clean:
	rm -f _mss.so
	rm -f msscy.so
	rm -f msscy.cpp
	rm -f examples/example
	rm -f libmeasurement.so
	rm -f measurement.so
	rm -f measurement_wrap.cxx
	rm -f mss.py
	rm -f mss.pyc
	rm -f test/__init__.pyc
	rm -f test/test_mss.pyc
	rm -f test/test_suite
	rm -rf build


