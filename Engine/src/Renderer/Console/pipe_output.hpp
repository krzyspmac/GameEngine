// Copyright (c) 2022 Krzysztof Pawłowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef pipe_output_hpp
#define pipe_output_hpp

#include <iostream>
#include <vector>

#define MAX_STDOUT_LEN 4096

namespace engine
{
    class PipeOutputI
    {
    public:
        virtual ~PipeOutputI() { };

        virtual void ConnectStdOut() = 0;
        virtual void ReleaseStdOut() = 0;
        virtual std::vector<std::string> ReadPipeLines() = 0;
    };

    class PipeOutputUnix: public PipeOutputI
    {
        bool m_possible;
        int m_savedStdOut;
        int m_outPipes[2];
        char buffer[MAX_STDOUT_LEN+1];
    public:
        PipeOutputUnix();
        virtual ~PipeOutputUnix() { };

        void ConnectStdOut();
        void ReleaseStdOut();
        std::vector<std::string> ReadPipeLines();
    };
};

#endif /* pipe_output_hpp */
