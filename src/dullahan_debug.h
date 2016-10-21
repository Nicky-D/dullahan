/*
    @brief Dullahan - a headless browser rendering engine
           based around the Chromium Embedded Framework

    @author Callum Prentice - September 2016

    Copyright (c) 2016, Linden Research, Inc.
    
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    
    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#ifndef _DULLAHAN_DEBUG
#define _DULLAHAN_DEBUG

#define ENABLE_DEBUG_OUTPUT 0

#if (ENABLE_DEBUG_OUTPUT)
#include <iostream>
#include <sstream>

#define DLNOUT( x ) \
    std::ostringstream s; \
    s << "DLNOUT> " << x << std::endl; \
    std::cout  << s.str(); \
    OutputDebugStringA(s.str().c_str());
#else
#define DLNOUT( x )
#endif

#endif // _DULLAHAN_DEBUG
