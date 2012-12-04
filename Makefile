exe := et
sources := main.cc
include_dirs := include

# Override the default compiler
#    Understands clang++, g++, and icpc.
CXX := icpc

# Other things that I could need:
#    need_debug := adds debug flags to the compilation
#    need_blas  := true includes BLAS and LAPACK
#    need_boost := true includes Boost and libraries defined in settings.mk/boost.mk
#    need_gmp   := true includes The GNU Multiple Precision Arithmetic Library
#need_blas := false
need_debug := true
need_gmp := true
need_boost := true

include common.mk

