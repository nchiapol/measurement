from distutils.core import setup
from Cython.Build import cythonize

setup(
        name = "mssapp",
        ext_modules = cythonize("msscy.pyx")
    )

