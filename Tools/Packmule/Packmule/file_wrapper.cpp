//
//  file_wrapper.cpp
//  Packmule
//
//  Created by krzysp on 24/12/2021.
//

#include "file_wrapper.hpp"
#include <stdio.h>

FileWrapper::FileWrapper(std::string filename, std::string folder)
    : m_filename(filename), m_folder(folder), buffer(NULL)
{
    FILE *fp = fopen(GetFullPath().c_str(), "rb");
    if (fp)
    {
        fseek(fp, 0, SEEK_END);
        m_size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        fclose(fp);
    }
};

FileWrapper::~FileWrapper()
{
    ClearMemory();
}

std::string FileWrapper::GetFullPath()
{
    std::string fullPath = std::string(m_folder);
    fullPath.append("/");
    fullPath.append(m_filename);
    return fullPath;
}

void *FileWrapper::LoadIntoMemory()
{
    FILE *fp = fopen(GetFullPath().c_str(), "rb");
    if (fp)
    {
        fseek(fp, 0, SEEK_END);
        long size = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        buffer = malloc(size);
        fread(buffer, size, 1, fp);

        fclose(fp);
    };

    return buffer;
}

void FileWrapper::ClearMemory()
{
    if (buffer)
    {
        free(buffer);
        buffer = NULL;
    }
}
