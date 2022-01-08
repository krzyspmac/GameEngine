//
//  polygon_loader.cpp
//  Engine
//
//  Created by krzysp on 29/12/2021.
//

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
