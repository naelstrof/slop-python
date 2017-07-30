from distutils.core import setup, Extension

extension_mod = Extension("slop", sources = ["slop_module.c"], libraries = ['slopy'])

setup(name = "slop", ext_modules=[extension_mod])
