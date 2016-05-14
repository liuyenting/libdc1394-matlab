/*
 * MIT License
 *
 * Copyright (c) 2016 Liu, Yen-Ting
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <mex.h>
#include <cstddef>
#include <string>
#include <vector>
#include <dc1394/dc1394.h>

#include "dc1394.hpp"

dc1394::dc1394() {
	lib_obj = dc1394_new();
}

dc1394::~dc1394() {
	dc1394_free(lib_obj);
}

std::vector<uint64_t> dc1394::enumerate_cameras() {
	dc1394camera_list_t *cam_list;

	err = dc1394_camera_enumerate(lib_obj, &cam_list);
	if(err != DC1394_SUCCESS) {
		dc1394_camera_free_list(cam_list);
		dc1394_free(lib_obj);
		throw std::runtime_error("dc1394: Unable to enumerate cameras.");
	}

	std::vector<uint64_t> guid_list;
	if(cam_list->num == 0)
		fprint(stderr, "dc1394: No camera found.");
	else {
		// store GUIDs into the vector
		for(int i = 0; i < cam_list->num; i++)
			guid_list.push_back(cam_list->ids[i].guid);
	}

	dc1394_camera_free_list(cam_list);
	return guid_list;
}
