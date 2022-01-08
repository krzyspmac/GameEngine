//
//  pipe_output.cpp
//  Engine
//
//  Created by krzysp on 08/01/2022.
//

#include "pipe_output.hpp"
#include "fcntl.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sstream>

using namespace engine;

/**
 Windows will need its own pipe processing
 https://stackoverflow.com/questions/26561604/create-named-pipe-c-windows
 */

PipeOutputUnix::PipeOutputUnix()
{
    m_savedStdOut = dup(STDOUT_FILENO); // save file for later
    buffer[MAX_STDOUT_LEN] = {0};

    if (pipe(m_outPipes) != 0)
    {
        printf("Could not create a pipe! Std redidrection will not work.");
        m_possible = false;
        return;
    }

    long flags = fcntl(m_outPipes[0], F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(m_outPipes[0], F_SETFL, flags);

    m_possible = true;
}

void PipeOutputUnix::ConnectStdOut()
{
    if (!m_possible) { return; };

    dup2(m_outPipes[1], STDOUT_FILENO); // redirect stdout to the pipe
    //close(m_outPipes[1]);
}

void PipeOutputUnix::ReleaseStdOut()
{
    if (!m_possible) { return; };

    fflush(stdout);
    dup2(m_savedStdOut, STDOUT_FILENO);
}

std::vector<std::string> PipeOutputUnix::ReadPipeLines()
{
    std::vector<std::string> result;

    if (!m_possible) { return result; };

    fflush(stdout);
    read(m_outPipes[0], buffer, MAX_STDOUT_LEN);

    std::stringstream data_stream(buffer);
    std::string line;

    while(std::getline(data_stream, line))
    {
        result.push_back(line);
    }

    bzero(buffer, MAX_STDOUT_LEN);

    return result;
}
