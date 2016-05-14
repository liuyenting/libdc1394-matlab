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

#include <mex.h>
#include <cstddef>
#include <cstring>
#include <vector>

// matlab handle
#include "class_handle.hpp"

// wrapper for libdc1394
#include "dc1394.hpp"

/*
 * Prototypes
 */
void mexFunction(int, mxArray *, int, const mxArray *);
int func_lut(char *, int, mxArray *, int, const mxArray *);

void lib_init(int, mxArray *, int, const mxArray *);
void lib_delete(int, mxArray *, int, const mxArray *);
void lib_enumerate(int, mxArray *, int, const mxArray *);

void cam_connect(int, mxArray *, int, const mxArray *);
void cam_disconnect(int, mxArray *, int, const mxArray *);

/*
 * The gateway function
 */
void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[]) {
	if(nrhs < 1)
		mexErrMsgTxt("Not enough input arguments");

	char *command = (char *)mxArrayToString(prhs[0]);

	if(func_lut(command, nlhs, plhs, (nrhs-1), &(prhs[1])) < 0)
		mexErrMsgTxt("No such command");
}

/*
 * Using wrapper function to avoid illegal access
 */
int func_lut(char *command,
             int nlhs, mxArray *plhs[],
             int nrhs, const mxArray *prhs[]) {
	// valid commands
	static const char *func_name_lut[] = {
		"init",
		"delete",
		"enumerate",
		"connect",
		"disconnect",
		NULL
	};

	// function entries
	static void (*func_ptr_lut[])(int nlhs, mxArray *plhs[],
	                              int nrhs, const mxArray *prhs[]) = {
		lib_init,
		lib_delete,
		lib_enumerate,
		cam_connect,
		cam_disconnect
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

/* handle = dc1394('init'); */
void lib_init(int nlhs, mxArray *plhs[],
              int nrhs, const mxArray *prhs[]) {
	if(nlhs != 1)
		mexErrMsgTxt("init: One output expected.");

	// create new object and convert to mat format for storage
	plhs[0] = ptr2mat<dc1394>(new dc1394);
}

/* dc1394('delete', handle); */
void lib_delete(int nlhs, mxArray *plhs[],
                int nrhs, const mxArray *prhs[]) {
	if(nrhs != 1)
		mexWarnMsgTxt("delete: Unexpected arguments ignored.");

	destroy_object<dc1394>(prhs[0]);
}

/* list = dc1394('enumerate', handle); */
void lib_enumerate(int nlhs, mxArray *plhs[],
                   int nrhs, const mxArray *prhs[]) {
	if(nlhs != 1)
		mexErrMsgTxt("init: One output expected.");
	if(nrhs != 1)
		mexWarnMsgTxt("delete: Unexpected arguments ignored.");

	// acquire the library object
	dc1394 *lib_obj = mat2ptr<dc1394>(prhs[0]);

	cam_list = lib_obj->enumerate_cameras();

	// create the array to store GUIDs
	int total_cams = cam_list.size();
	const mwSize dims[] = { cam_list.size() };
	plhs[0] = mxCreateNumericArray(1, dims, mxUINT64_CLASS, mxREAL);
	uint64_t *output_mat = (uint64_t *)mxGetData(plhs[0]);

	// store the GUIDs into array
	for(int i = 0; i < total_cams; i++)
		output_mat[i] = cam_list[i];
}

void cam_connect(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[]) {

}
void cam_disconnect(int nlhs, mxArray *plhs[],
                    int nrhs, const mxArray *prhs[]) {

}
