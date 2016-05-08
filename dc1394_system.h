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

/*
 * handle = dc1394( 'init_library' );
 */
void system_init_library(int nlhs, mxArray *plhs[],
                         int nrhs, const mxArray *prhs[]) {
    const int dc1394_obj_fields_cnt = 2;
    static const char *dc1394_obj_fields[dc1394_obj_fields_cnt] = {
        "lib_obj",
        "cam_obj"
    };
    
    // create MATLAB strucutre to store the handles
    plhs[0] = mxCreateStructMatrix(1, 1, dc1394_obj_fields_cnt, dc1394_obj_fields);
    
    // create the library handle
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

/*
 * cam_list = dc1394( 'enumerate_cameras', handle );
 */
void system_enumerate_cameras(int nlhs, mxArray *plhs[], 
                              int nrhs, const mxArray *prhs[]) {
    if(nrhs != 1)
        mexErrMsgTxt("Requires library handle");
    
    // parse the library handle
    dc1394_t *lib_obj = *(dc1394_t **)mxGetPr(mxGetField(prhs[0], 0, "lib_obj"));
    dc1394error_t err;
    
    // enumerate the devices
    dc1394camera_list_t *cam_list;
    err = dc1394_camera_enumerate(lib_obj, &cam_list);
    if(err != DC1394_SUCCESS) {
        dc1394_free(lib_obj);
        mexErrMsgTxt("Unable to enumerate cameras");
    } else if(cam_list->num == 0) {
        dc1394_free(lib_obj);
        mexErrMsgTxt("No camera found");
    } else {
        // create the array to store GUIDs
        const mwSize dims[] = { cam_list->num };
        plhs[0] = mxCreateNumericArray(1, dims, mxUINT64_CLASS, mxREAL);
        uint64_t *output_mat = (uint64_t *)mxGetData(plhs[0]);
        
        // store the GUIDs into array
        for(int nrow = 0; nrow < cam_list->num; nrow++)
            output_mat[nrow] = cam_list->ids[nrow].guid;
        
        // release the list
        dc1394_camera_free_list(cam_list);
    }
}

void system_init_camera(int nlhs, mxArray *plhs[],
                        int nrhs, const mxArray *prhs[]) {
};

void system_free_camera(int nlhs, mxArray *plhs[],
                        int nrhs, const mxArray *prhs[]) {
};

#endif