//
//  PackBundle.hpp
//  Packmule
//
//  Created by krzysp on 24/12/2021.
//

#ifndef PackBundle_hpp
#define PackBundle_hpp

#include <stdio.h>
#include <iostream>

#define MAX_FILENAME 256

typedef struct
{
    char m_filename[MAX_FILENAME];
    int64_t size;
    int64_t offset;
} PacItem;

class PackList
{
public:
    /// Read a pack list from the file handle.
    PackList(FILE *fp);

    /// Setup with given data. Copies data.
    PackList(PacItem *items, int numItem);
    PacItem *GetItemAtIndex(int index);
    PacItem *GetItemNamed(std::string);

    void PrintTable();

    ~PackList();

private:
    PacItem *m_items;
    int m_numItems;
};

class PackBundle
{

};

#endif /* PackBundle_hpp */
