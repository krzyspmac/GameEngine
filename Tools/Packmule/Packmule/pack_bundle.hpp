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

    /// Get item at an index; Returns NULL if out of bounds.
    PacItem *GetItemAtIndex(int index);

    /// Get an item by its filename. Returns NULL if not found.
    PacItem *GetItemNamed(std::string);

    /// Load the memory for the item. Memory management is
    /// passed to the caller. FILE *fp must be open and exist.
    void *LoadMemory(PacItem *);

    /// Print the file table.
    void PrintTable();

    ~PackList();

private:
    FILE *m_fp;
    PacItem *m_items;
    int64_t m_numItems;
};

class PackBundle
{

};

#endif /* PackBundle_hpp */
