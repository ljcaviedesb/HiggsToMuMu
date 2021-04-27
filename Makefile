# Makefile is a part of the PYTHIA event generator.
# Copyright (C) 2020 Torbjorn Sjostrand.
# PYTHIA is licenced under the GNU GPL v2 or later, see COPYING for details.
# Please respect the MCnet Guidelines, see GUIDELINES for details.
# Author: Philip Ilten, September 2014.
#
# This is is the Makefile used to build PYTHIA Higgs to mumu taken from Makefile
# Pythia examples
################################################################################
# VARIABLES: Definition of the relevant variables from the configuration script.
################################################################################

# Set the shell.
SHELL=/usr/bin/env bash

# Include the configuration.
-include Makefile.inc

# Check distribution (use local version first, then installed version).
ifneq ("$(wildcard ../lib/libpythia8.*)","")
  PREFIX_LIB=../lib
  PREFIX_INCLUDE=../include
endif
CXX_COMMON:=-I$(PREFIX_INCLUDE) $(CXX_COMMON) $(GZIP_LIB)
CXX_COMMON+= -L$(PREFIX_LIB) -Wl,-rpath,$(PREFIX_LIB) -lpythia8 -ldl
PYTHIA=$(PREFIX_LIB)/libpythia8$(LIB_SUFFIX)

################################################################################
# RULES: Definition of the rules used to build the PYTHIA examples.
################################################################################

# Rules without physical targets (secondary expansion for specific rules).
.SECONDEXPANSION:
.PHONY: all clean

# All targets (no default behavior).
all:
	$(info Usage: make mainXX)

# PYTHIA library.
$(PYTHIA):
	$(error Error: PYTHIA must be built, please run "make"\
                in the top PYTHIA directory)

# Examples without external dependencies.
main%: $(PYTHIA) main%.cc
	$(CXX) $@.cc -o $@ $(CXX_COMMON)


# ROOT libraries generated via CINT.
main%.so: main%Dct.cc
	$(CXX) $< -o $@ -w $(CXX_SHARED) $(CXX_COMMON)\
	 $(ROOT_LIB) `$(ROOT_CONFIG) --cflags`
main%Dct.cc: main%.h main%LinkDef.h
ifeq ($(ROOT_USE),true)
	$(ROOT_BIN)rootcint -f $@ -I$(PREFIX_INCLUDE) $^
else
	$(error Error: $@ requires ROOT)
endif

# ROOT (turn off all warnings for readability).
mymain01: $(PYTHIA) $$@.cc
ifeq ($(ROOT_USE),true)
	$(CXX) $@.cc -o $@ -w $(CXX_COMMON) $(ROOT_LIB)\
	 `$(ROOT_CONFIG) --cflags --glibs`
else
	$(error Error: $@ requires ROOT)
endif
main92: $(PYTHIA) $$@.cc main92.so
	$(CXX) $@.cc main92.so -o $@ -w $(CXX_COMMON) -Wl,-rpath,./\
	 `$(ROOT_CONFIG) --cflags --glibs`

# RIVET with optional ROOT (if RIVET, use C++14).
main93: $(PYTHIA) $$@.cc $(if $(filter true,$(ROOT_USE)),main93.so)
ifeq ($(RIVET_USE),true)
	$(CXX) $@.cc -o $@ -w $(CXX_COMMON:c++11=c++14) -Wl,-rpath,./\
	 $(if $(filter true,$(ROOT_USE)),main93.so -DPY8ROOT\
         $(ROOT_LIB) `$(ROOT_CONFIG) --cflags --glibs`)\
	 $(RIVET_INCLUDE) $(RIVET_LIB)
else
	$(error Error: $@ requires RIVET)
endif


# User-written examples for tutorials, without external dependencies.
mymain%: $(PYTHIA) mymain%.cc
	$(CXX) $@.cc -o $@ $(CXX_COMMON)

# Internally used tests, without external dependencies.
test%: $(PYTHIA) test%.cc
	$(CXX) $@.cc -o $@ $(CXX_COMMON)

# Clean.
clean:
	@rm -f main[0-9][0-9]; rm -f out[0-9][0-9];\
	rm -f main[0-9][0-9][0-9]; rm -f out[0-9][0-9][0-9];\
	rm -f mymain[0-9][0-9]; rm -f myout[0-9][0-9];\
	rm -f test[0-9][0-9][0-9]; rm -f *.dat;\
	rm -f weakbosons.lhe; rm -f hist.root;\
	rm -f *~; rm -f \#*; rm -f core*; rm -f *Dct.*; rm -f *.so;\
	rm -f *.log; rm -f *plot.py; rm -f *.pcm;
