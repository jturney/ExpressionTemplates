# Compilation flags specific for icpc
icpc.optimization := -O3
icpc.debug := -O0 -g
icpc.cxxflags := -std=c++11
icpc.ldflags := 
icpc.target_arch := -march=corei7-avx
icpc.blas_cxxflags := -mkl
icpc.blas_libraries := -mkl
