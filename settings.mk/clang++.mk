# Clang is the only one that seems to work on Mac OS X
clang++.optimization := -O3
clang++.debug := -O0 -g
clang++.cxxflags := -std=c++11 -stdlib=libc++
clang++.ldflags := -std=c++11 -stdlib=libc++
clang++.target_arch := -mavx
clang++.blas_cxxflags := 
clang++.blas_libraries := -llapack -lblas
