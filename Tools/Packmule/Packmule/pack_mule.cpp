//
//  pack_mule.cpp
//  Packmule
//
//  Created by krzysp on 24/12/2021.
//

#include "pack_mule.hpp"
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "pack_bundle.hpp"

#define FILENAME_MAX 4096

PackMule::PackMule(std::string folder, std::string outfile)
 : m_folder(folder), m_outfile(outfile)
{
}

void PackMule::LoadFolderStructure()
{
    std::cout << "Folder: " << m_folder << std::endl;

    struct dirent *dp;
    DIR *dfd;

    const char *dir = m_folder.c_str();

    if ((dfd = opendir(dir)) == NULL)
    {
        fprintf(stderr, "Can't open %s\n", dir);
    }

    char filename_qfd[FILENAME_MAX] ;

    while ((dp = readdir(dfd)) != NULL)
    {
        // skip files
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
        {
            continue;
        }

        struct stat stbuf ;
        sprintf( filename_qfd , "%s/%s",dir,dp->d_name) ;
        if( stat(filename_qfd,&stbuf ) == -1 )
        {
            printf("Unable to stat file: %s\n",filename_qfd) ;
            continue;;
        }

        if ((stbuf.st_mode & S_IFMT ) == S_IFDIR)
        {
            continue; // Skip directories
        }
        else
        {
            FileWrapper *wrapper = new FileWrapper(dp->d_name, m_folder);
            m_files.emplace_back(std::move(wrapper));
            continue;;
        }
    }
}

void PackMule::PrintTargetList()
{
    for(auto it = std::begin(m_files); it != std::end(m_files); ++it)
    {
        FileWrapper *fw = it->get();
        std::cout << fw->GetFullPath() << std::endl;
    };
};

void PackMule::SavePack()
{
    FILE *fp = fopen(m_outfile.c_str(), "wb");
    if (fp)
    {
        int32_t count = (int32_t)m_files.size();
        size_t packItemSize = sizeof(PacItem) * count;

        PacItem *items = (PacItem*)malloc(packItemSize);
        if (items)
        {
            bzero(items, packItemSize);

            fwrite(&count, sizeof(int32_t), 1, fp);
            uint64_t totalOffset = packItemSize;

            for(auto it = std::begin(m_files); it != std::end(m_files); ++it)
            {
                FileWrapper *fw = it->get();

                PacItem item;
                strcpy(item.m_filename, fw->GetFilename().c_str());
                item.size = fw->GetSize();
                item.offset = totalOffset;
                fwrite(&item, sizeof(PacItem), 1, fp);

                totalOffset += item.size;
            };

            for(auto it = std::begin(m_files); it != std::end(m_files); ++it)
            {
                FileWrapper *fw = it->get();
                void *memory = fw->LoadIntoMemory();
                fwrite(memory, fw->GetSize(), 1, fp);
                fw->ClearMemory();
            };

            free(items);
        }

        fclose(fp);
    }
}
