// Copyright (c) 2022 Krzysztof Pawłowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

#include "polygon_loader.hpp"
#include "cJSON.h"
#include "easy.h"

using namespace engine;

std::vector<Polygon> PolygonLoader::Load(FileStreamI *stream)
{
    do {
        std::vector<Polygon> outputPolygons;

        LOGGER().Log("Loading polygon %s", stream->GetFilename().c_str());

        std::string buffer = stream->ReadBufferString();
        const char *jsonSource = buffer.c_str();
        if (jsonSource == nullptr) {
            LOGGER().Log("Could not the polygon.");
            break;
        };

        cJSON *root;

        root = cJSON_Parse(jsonSource);
        if (root == nullptr) { break; };

        cJSON *polyArray = cJSON_GetObjectItem(root, "polys");
        if (polyArray == nullptr) { break; };

        size_t polyArrayCount = cJSON_GetArraySize(polyArray);
        for (int i = 0; i < polyArrayCount; i++)
        {
            std::vector<Vector2> points;

            cJSON *polyDictionary = cJSON_GetArrayItem(polyArray, i);
            if (polyDictionary == nullptr) { continue; };

            cJSON *pointsArray = cJSON_GetObjectItem(polyDictionary, "points");
            if (pointsArray == nullptr) { continue;; };

            size_t pointsCount = cJSON_GetArraySize(pointsArray);
            for (int n = 0; n < pointsCount; n++)
            {
                cJSON *pointDictionary = cJSON_GetArrayItem(pointsArray, n);
                if (pointDictionary == nullptr) { continue;; };

                cJSON *x = cJSON_GetObjectItem(pointDictionary, "x");
                if (x == nullptr) { continue; };

                cJSON *y = cJSON_GetObjectItem(pointDictionary, "y");
                if (y == nullptr) { continue; };

                float xVal = x->valuedouble;
                float yVal = y->valuedouble;
                points.push_back(Vector2Make(xVal, yVal));
            }

            outputPolygons.push_back(Polygon(points));
        }

        return outputPolygons;
    } while(false);

    return std::vector<Polygon>();
}
