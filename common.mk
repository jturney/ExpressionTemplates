assembly := $(subst .cc,.s,$(sources))
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

# Default make target
all: $(exe)

# Rule to create executable
$(exe): $(objects)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBRARIES)

# Rule to create assembly code only
asm: $(assembly)

.PHONY: clean
clean:
	$(RM) $(exe) $(objects) $(dependencies) $(assembly)

ifneq "$(MAKECMDGOALS)" "clean"
ifneq "$(MAKECMDGOALS)" "asm"
-include $(dependencies)
endif
endif

%.o: %.cc
	$(CXX) -c $< $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -o $@ -MT $@ -MMD -MP -MF $*.d

%.s: %.cc
	$(CXX) -S $< $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -o $@

