objects := $(subst .cc,.o,$(sources))
dependencies := $(subst .cc,.d,$(sources))

include settings.mk/$(CXX).mk
include settings.mk/boost.mk

CXXFLAGS += $($(CXX).cxxflags)
LDFLAGS  += $($(CXX).ldflags)
TARGET_ARCH += $($(CXX).target_arch)

ifeq "$(need_debug)" "true"
	CXXFLAGS += $($(CXX).debug)
else
	CXXFLAGS += $($(CXX).optimization)
endif

ifeq "$(need_blas)" "true"
	CXXFLAGS += $($(CXX).blas_cxxflags)
	LIBRARIES += $($(CXX).blas_libraries)
endif

ifeq "$(need_boost)" "true"
	include_dirs += $(boost.include_dirs)
	LIBRARIES += $(boost.libraries)
endif

CPPFLAGS += $(addprefix -I ,$(include_dirs))
vpath %.h $(include_dirs)

all: $(exe)

$(exe): $(objects)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBRARIES)

.PHONY: clean
clean:
	$(RM) $(exe) $(objects) $(dependencies)

ifneq "$(MAKECMDGOALS)" "clean"
-include $(dependencies)
endif

%.o: %.cc
	$(CXX) -c $< $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -o $@ -MT $@ -MMD -MP -MF $*.d



