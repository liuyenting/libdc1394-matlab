MATLAB_ROOT=/Applications/MATLAB_R2016a.app

MATLAB_BIN=${MATLAB_ROOT}/bin
MEX=${MATLAB_BIN}/mex
# file extension of the MEX files on target system
MEXEXT=$(shell ${MATLAB_BIN}/mexext)

BIN_NAME=dc1394_mex

$(BIN_NAME).$(MEXEXT): dc1394_mex.cpp
	$(MEX) $< $(OBJS) `pkg-config --libs --cflags libdc1394-2` -output $(BIN_NAME).$(MEXEXT)

clean:
	@echo "Cleaning MEX files and object files"
	@rm *.mex* *.o 2> /dev/null; true
