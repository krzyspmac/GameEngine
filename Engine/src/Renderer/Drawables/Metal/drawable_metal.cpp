//
//  drawable_metal.cpp
//  Engine
//
//  Created by krzysp on 12/01/2022.
//

#include "drawable_metal.hpp"

using namespace engine;

DrawableMetal::DrawableMetal(float width, float height)
    : DrawableI(width, height)
    , m_scale(1.0)
{
    m_triangleVertices = (AAPLVertex*)malloc(6 * sizeof(AAPLVertex));
    m_position[0] = 0;
    m_position[1] = 1;

//    width = 1280;
//    height = 720;

    /*static const*/ /*AAPLVertex*//* triangleVertices[3] =*/
//    const AAPLVertex data[] =
//    {
//        // 2D positions,    RGBA colors
//        { {  -250,  -250 }, { 1, 0, 0, 1 } },       // bottom left
//        { {  -250,   250 }, { 0, 1, 0, 1 } },       // upper left
//        { {   250,   250 }, { 0, 0, 1, 1 } },       // upper right
//
//        { {   250,   250 }, { 0, 0, 1, 1 } },       // upper right
//        { {   250,  -250 }, { 0, 0, 1, 1 } },       // bottom right
//        { {  -250,  -250 }, { 0, 0, 1, 1 } },       // bottom left
//    };

    m_size[0] = width;
    m_size[1] = height;

    float width2 = width/2;
    float height2 = height/2;

//    const AAPLVertex data[] =
//    {
//        // 2D positions,    RGBA colors
//        { {  -width2,     -height2 } , { 1, 0, 0, 1 } },       // bottom left
//        { {  -width2,      height2 } , { 0, 1, 0, 1 } },       // upper left
//        { {   width2,      height2 } , { 0, 0, 1, 1 } },       // upper right
//
//        { {   width2,      height2 } , { 0, 0, 1, 1 } },       // upper right
//        { {   width2,     -height2 } , { 0, 0, 1, 1 } },       // bottom right
//        { {  -width2,     -height2 } , { 0, 0, 1, 1 } },       // bottom left
//    };

    const AAPLVertex data[] =
    {
        // 2D positions,    RGBA colors
        { {   -width2,          -height2 } , { 1, 0, 0, 1 } },       // bottom left
        { {   -width2,           height2 } , { 0, 1, 0, 1 } },       // upper left
        { {   width2,      height2 } , { 0, 0, 1, 1 } },       // upper right

        { {   width2,      height2 } , { 0, 0, 1, 1 } },       // upper right
        { {   width2,     -height2 } , { 0, 0, 1, 1 } },       // bottom right
        { {  -width2,     -height2 } , { 0, 0, 1, 1 } },       // bottom left
    };

    m_triangleVerticiesDataSize = sizeof(data);
    memcpy(m_triangleVertices, data, m_triangleVerticiesDataSize);
}

void DrawableMetal::SetPosition(float x, float y)
{
    m_position[0] = x;
    m_position[1] = y;
}

void DrawableMetal::SetScale(float scale)
{
    m_scale = scale;
}

vector_float2 *DrawableMetal::GetSize()
{
    return &m_size;
}

simd_float2 *DrawableMetal::GetPosition()
{
    return &m_position;
}

float *DrawableMetal::GetScale()
{
    return &m_scale;
}

AAPLVertex *DrawableMetal::GetVertexData()
{
    return m_triangleVertices;
}

size_t DrawableMetal::GetVertexDataSize()
{
    return m_triangleVerticiesDataSize;
}

size_t DrawableMetal::GetVertexCount()
{
    return 6;
}
