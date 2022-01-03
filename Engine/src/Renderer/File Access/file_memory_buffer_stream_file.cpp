//
//  file_memory_buffer_stream_file.cpp
//  Engine
//
//  Created by krzysp on 23/12/2021.
//

#include "file_access_provider.h"
#include <stdio.h>

using namespace engine;

FileMemoryBufferStreamFromFile::FileMemoryBufferStreamFromFile(std::string filename)
    : FileMemoryBufferStreamI(filename)
{
    FILE *fp = fopen(filename.c_str(), "r");
    if (fp)
    {
        fseek(fp, 0, SEEK_END);
        //size = ftell(fp);
        size = _ftelli64(fp);
        fseek(fp, 0, SEEK_SET);

        memory = malloc(size + 1);
        memset(memory, '\0', size + 1);
        
        fread(memory, size, 1, fp);

        fclose(fp);
    };
}

FileMemoryBufferStreamFromFile::~FileMemoryBufferStreamFromFile()
{
    if (memory)
    {
        free(memory);
        memory = NULL;

        size = 0;
    }
}
