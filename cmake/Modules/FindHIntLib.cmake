# CMakeLists.txt for Cubature Benchmark
# Copyright (C) 2009 Łukasz Lis
#
# This file is free software. You have unlimited permission to copy, modify
# and distribute it.

# - Try to find HIntLib
include(CubmarkMacros)

cubmark_find_method_library(HIntLib HIntLib/ hintlib)
