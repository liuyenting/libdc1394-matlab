/*
 * Copyright (c) 2016 Liu Yen-Ting
 *
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef DC1394_SYSTEM_H
#define DC1394_SYSTEM_H

#include <mex.h>

void system_init_library(int nlhs, mxArray *plhs[],
                         int nrhs, const mxArray *prhs[]) {
    const int dc1394_obj_fields_cnt = 2;
    static const char *dc1394_obj_fields[dc1394_obj_fields_cnt] = {
        "lib_obj",
        "cam_obj"
    };
    
    // create MATLAB strucutre to store the handles
    plhs[0] = mxCreateStructMatrix(1, 1, 
                                   dc1394_obj_fields_cnt,
                                   dc1394_obj_fields);
    
    // create the library object
    dc1394_t *lib_obj = dc1394_new();
    
    // save the handle into the structure
    mxArray *data = mxCreateNumericMatrix(1, 1, mxUINT32_CLASS, mxREAL);
    uint32_t *d32 = (uint32_t *)mxGetPr(data);
    *d32 = (uint32_t)lib_obj;
    mxSetField(plhs[0], 0, "lib_obj", data);
}

void system_free_library(int nlhs, mxArray *plhs[],
                         int nrhs, const mxArray *prhs[]) {
}

void system_enumerate_devices(int nlhs, mxArray *plhs[], 
                              int nrhs, const mxArray *prhs[]) {
}

#endif