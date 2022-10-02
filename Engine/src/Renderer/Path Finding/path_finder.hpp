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

#ifndef walking_boxes_hpp
#define walking_boxes_hpp

#include "polygon.hpp"
#include "path_finder_interface.h"
#include "path_finder_graph.hpp"

namespace engine
{

    class PathFinder: public PathFinderBaseI
    {
    public:
        PathFinder(std::vector<Polygon> polygonList);
        ~PathFinder();
        
    public:
        void Prepare();
        void Draw();

    public:
        PathI *CalculatePath(Vector2 fromPoint, Vector2 toPoint);
        Vector2 NudgedPosition(Vector2 position);

    private:
        bool IntersectsAnyline(Line &line);
        bool PointInsidePolygons(Vector2 &point, Polygon **outPolygon);
        void DrawLine(Line&);
        void DrawPoint(Vector2&);

    /// PathFinderCallbackI
    public:
        void DidFindPath(std::unique_ptr<PathI>&);

    /// PathFinderDataI
    public:
        std::vector<Vector2> &GetAllPoint() { return m_allPoints; };
        std::vector<Line> &GetAllLines() { return m_allLines; };

    private:
        std::vector<Polygon> m_polygons;
        std::vector<Line> m_connectionLines;

        std::vector<Vector2> m_allPoints;
        std::vector<Line> m_allLines;

        // path claculation
        std::unique_ptr<PathFinderGraphI> m_lineGraph;
        Vector2 m_startPosition;
        Vector2 m_targetPosition;
        std::vector<PathFinderLineGraphNodeI*> m_tempPathStack;
        float m_maxDistance;
        std::unique_ptr<PathI> m_calculatedPath;

        // tmp
        Line *m_nudgedLine;
        Vector2 m_nudgedPosition;
    };
};

#endif /* walking_boxes_hpp */
