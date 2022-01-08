//
//  pipe_output.hpp
//  Engine
//
//  Created by krzysp on 08/01/2022.
//

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

        void ConnectStdOut();
        void ReleaseStdOut();
        std::vector<std::string> ReadPipeLines();
    };
};

#endif /* pipe_output_hpp */
