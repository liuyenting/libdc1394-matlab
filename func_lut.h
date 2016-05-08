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

#ifndef FUNC_LUT_H
#define FUNC_LUT_H

#include <mex.h>
#include <stddef.h>
#include <string.h>

// using wrapper function to avoid illegal access
int func_lut(char *command,
             int nlhs, mxArray *plhs[],
             int nrhs, const mxArray *prhs[]) {
    // function table
    static void (*func_ptr_lut[])(int nlhs, mxArray *plhs[], 
                                  int nrhs, const mxArray *prhs[]) = {
        system_init_library,
        system_free_library,
        system_enumerate_cameras,
        system_init_camera,
        system_free_camera
    };
    
    // function name
    static const char *func_name_lut[] = {
        "init_library",
        "free_library",
        "enumerate_cameras",
        "init_camera",
        "free_camera",
        NULL
    };
    
    for(int i = 0; func_name_lut[i] != NULL; i++) {
        if(!strcmp(command, func_name_lut[i])) {
            func_ptr_lut[i](nlhs, plhs, nrhs, prhs);
            return 0;
        }
    }
    
    // no match in the function name lookup table
    return -1;
}             

#endif