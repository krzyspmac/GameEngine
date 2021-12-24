//
//  file_wrapper.hpp
//  Packmule
//
//  Created by krzysp on 24/12/2021.
//

#ifndef file_wrapper_hpp
#define file_wrapper_hpp

#include <iostream>

class FileWrapper
{
public:
    FileWrapper(std::string filename, std::string folder);
    ~FileWrapper();

    std::string GetFullPath();
    std::string &GetFilename() { return m_filename; };
    std::string &GetFolder() { return m_folder; };
    long GetSize() { return m_size; };
    void *LoadIntoMemory();
    void ClearMemory();

private:
    std::string m_filename;
    std::string m_folder;
    long m_size;

    void *buffer;
};
#endif /* file_wrapper_hpp */
