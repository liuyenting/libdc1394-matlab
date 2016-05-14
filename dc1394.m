%
% MIT License
%
% Copyright (c) 2016 Liu, Yen-Ting
%
% Permission is hereby granted, free of charge, to any person obtaining a copy
% of this software and associated documentation files (the "Software"), to deal
% in the Software without restriction, including without limitation the rights
% to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
% copies of the Software, and to permit persons to whom the Software is
% furnished to do so, subject to the following conditions:
%
% The above copyright notice and this permission notice shall be included in all
% copies or substantial portions of the Software.
%
% THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
% IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
% FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
% AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
% LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
% OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
% SOFTWARE.
%

%DC1394 MATLAB class wrapper to the underlying dc1394 C++ class
classdef dc1394 < handle
    properties (SetAccess = private, Hidden = true)
        % Handle to the underyling dc1394 class instance
        objectHandle;
    end
    
    methods
        %% Constructor - Create a new dc1394 class instance
        function this = dc1394(varargin)
            this.objectHandle = dc1394_mex('init');
        end
        
        %% Destructor - Destroy the dc1394 class instance
        function delete(this)
            dc1394_mex('delete', this.objectHandle);
        end
        
        %% Enumerate - Enumerate all valid cameras
        function list = enumerate(this)
            list = dc1394_mex('enumerate', this.objectHandle);
        end
    end
end
