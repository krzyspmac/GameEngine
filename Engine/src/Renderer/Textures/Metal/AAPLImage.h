/*
See LICENSE folder for this sample’s licensing information.

Abstract:
Header for a very simple container for image data
*/

#include "common.h"

namespace engine
{
    class TextureMetalTGA
    {
        int m_width;
        int m_height;
        void *m_data;
    public:
        TextureMetalTGA(std::string filename);
        
        int GetWidth() { return m_width; };
        int GetHeight() { return m_height; };
        void *GetData() { return m_data; };
    };
};
