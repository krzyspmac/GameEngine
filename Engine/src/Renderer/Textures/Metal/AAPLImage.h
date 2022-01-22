/*
See LICENSE folder for this sample’s licensing information.

Abstract:
Header for a very simple container for image data
*/

#include "common.h"
#include <Metal/Metal.hpp>

namespace engine
{
    class TextureMetalTGA
    {
        int m_width;
        int m_height;
        void *m_data;
    public:
        TextureMetalTGA(std::string filename, bool *horizontallyFlipped, bool *verticallyFlipped);

        static MTL::Texture* CreateFrom(std::string filename, MTL::Device *device, bool *horizontallyFlipped, bool *verticallyFlipped);
        
        int GetWidth() { return m_width; };
        int GetHeight() { return m_height; };
        void *GetData() { return m_data; };
    };
};
