//
//  pack_mule.hpp
//  Packmule
//
//  Created by krzysp on 24/12/2021.
//

#ifndef pack_mule_hpp
#define pack_mule_hpp

#include <iostream>
#include <vector>
#include "file_wrapper.hpp"

class PackMule
{
public:
    PackMule(std::string folder, std::string outfile);

    void LoadFolderStructure();
    void PrintTargetList();
    void SavePack();
    
private:
    std::string m_folder;
    std::string m_outfile;
    std::vector<std::unique_ptr<FileWrapper>> m_files;
};

#endif /* pack_mule_hpp */
