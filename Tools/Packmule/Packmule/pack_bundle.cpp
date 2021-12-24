//
//  PackBundle.cpp
//  Packmule
//
//  Created by krzysp on 24/12/2021.
//

#include "pack_bundle.hpp"

PackList::PackList(FILE *fp)
{
    fread(&m_numItems, sizeof(int32_t), 1, fp);
    m_items = (PacItem*)malloc(sizeof(PacItem) * m_numItems);
    fread(m_items, sizeof(PacItem), m_numItems, fp);
}

PackList::PackList(PacItem *items, int numItem)
{
    m_items = (PacItem*)malloc(sizeof(PacItem) * numItem);
    m_numItems = numItem;
}

PackList::~PackList()
{
    if (m_items)
    {
        free(m_items);
        m_items = NULL;
    }
}

PacItem *PackList::GetItemAtIndex(int index)
{
    return m_items + index;
}

void PackList::PrintTable()
{
    int i = 0;

    for(i = 0; i < m_numItems; i++)
    {
        PacItem *item = GetItemAtIndex(i);
        std::cout << item->m_filename << ", " << item->size << " bytes" << std::endl;
    }
}
