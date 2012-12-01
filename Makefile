exe := et
sources := main.cc
include_dirs := include

# Override the default compiler
#    Understands clang++, g++, and icpc.
CXX := clang++

# Other things that I could need:
#    need_blas := true includes BLAS and LAPACK
#    need_boost := true includes Boost and libraries defined in settings.mk/boost.mk
#need_blas := false
need_boost := true

include common.mk

