//
//  main.c
//  Packmule
//
//  Created by krzysp on 24/12/2021.
//

#include <stdio.h>
#include "pack_mule.hpp"
#include "pack_bundle.hpp"

static char *command;
static char *inFile;
static char *rootDir;
static char *outFile;

static void handleCommandLine(int argc, char *argv[])
{
    int i;

    for (i = 0 ; i < argc ; i++)
    {
        if (strcmp(argv[i], "-command") == 0)
        {
            command = argv[i + 1];
        }
        else if (strcmp(argv[i], "-in") == 0)
        {
            inFile = argv[i + 1];
        }
        else if (strcmp(argv[i], "-dir") == 0)
        {
            rootDir = argv[i + 1];
        }
        else if (strcmp(argv[i], "-out") == 0)
        {
            outFile = argv[i + 1];
        }
    };
};

int main(int argc, char * argv[]) {
    handleCommandLine(argc, argv);

    if (strcmp(command, "create") == 0)
    {
        PackMule mule(rootDir, outFile);
        mule.LoadFolderStructure();
        mule.PrintTargetList();
        mule.SavePack();
    }
    else if (strcmp(command, "unpack") == 0)
    {
        FILE *fp = fopen(inFile, "rb");
        if (fp)
        {
            PackList *packList = new PackList(fp);
            packList->PrintTable();

            PacItem *lua = packList->GetItemNamed("main.lua");
            void *mmm = packList->LoadMemory(lua);
            delete packList;
            fclose(fp);
        }
    }

    return 0;
}
