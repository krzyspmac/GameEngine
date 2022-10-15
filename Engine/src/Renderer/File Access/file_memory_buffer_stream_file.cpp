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

#include "file_access_provider.h"
#include "easy.h"
#include <stdio.h>

using namespace engine;

FileMemoryBufferStreamFromFile::FileMemoryBufferStreamFromFile(std::string filename)
    : FileStreamI(filename)
{
    m_fp = fopen(filename.c_str(), "rb");
    if (m_fp)
    {
        fseek(m_fp, 0, SEEK_END);
        #if __APPLE__
        m_size = ftell(m_fp);
        #else
        m_size = _ftelli64(fp);
        #endif
        fseek(m_fp, 0, SEEK_SET);
    }
    else
    {
        LOGGER().Log("Could not open file for reading: %s", filename.c_str());
        m_size = -1;
    }
}

FileMemoryBufferStreamFromFile::~FileMemoryBufferStreamFromFile()
{
    if (m_fp)
    {
        fclose(m_fp);
    }
}

int64_t FileMemoryBufferStreamFromFile::Seek(int64_t offset, int whence)
{
    if (m_fp != nullptr)
    {
        return fseek(m_fp, offset, whence);
    }
    else
    {
        return -1;
    }
}

size_t FileMemoryBufferStreamFromFile::Read(void *ptr, size_t size, size_t maxnum)
{
    if (m_fp != nullptr)
    {
        return fread(ptr, size, maxnum, m_fp);
    }
    else
    {
        return 0;
    }
}

std::string FileMemoryBufferStreamFromFile::ReadBufferString()
{
    if (m_fp == nullptr)
    {   return "";
    }
    
    char *memory = (char*)malloc((m_size + 1) * sizeof(char));
    if (memory)
    {
        memset(memory, '\0', m_size + 1);
        fread(memory, m_size, 1, m_fp);

        std::string result(memory);

        free(memory);
        return result;
    }
    else
    {
        return "";
    }
}

static FileMemoryBufferStreamFromFile *currentStream = nullptr;

static Sint64 sizeF(struct SDL_RWops * context)
{
    return currentStream->GetSize();
}

static Sint64 seekF(struct SDL_RWops * context, Sint64 offset, int whence)
{
    return currentStream->Seek(offset, whence);
}

static size_t readF(struct SDL_RWops * context, void *ptr, size_t size, size_t maxnum)
{
    return currentStream->Read(ptr, size, maxnum);
}

static int closeF(struct SDL_RWops * context)
{
    return 0;
}
