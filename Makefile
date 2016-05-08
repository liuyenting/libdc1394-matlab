MATLAB_ROOT=/Applications/MATLAB_R2016a.app

MATLAB_BIN=${MATLAB_ROOT}/bin
MEX=${MATLAB_BIN}/mex
# file extension of the MEX files on target system
MEXEXT=$(shell ${MATLAB_BIN}/mexext)

dc1394.$(MEXEXT): dc1394.c
    $(MEX) $< $(OBJS) `pkg-config --libs --cflags libdc1394-2` -output dc1394.$(MEXEXT)

clean:
    rm *.mex* *.o