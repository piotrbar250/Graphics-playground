#include <fstream>
#include <vector>
#include "Point.hpp"
#include "Polygon.hpp"

using namespace std;

void savePolygons(const vector<Polygon *> &polygons, const string &filename)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        throw runtime_error("Unable to open file for writing.");
    }

    for (const auto &poly : polygons)
    {
        file << "Polygon\n";
        file << poly->vertexes.size() << "\n";
        for (const auto &vertex : poly->vertexes)
        {
            file << vertex.x << " " << vertex.y << "\n";
        }
    }
    file.close();
}

vector<Polygon *> loadPolygons(const string &filename)
{
    ifstream file(filename);
    vector<Polygon *> polygons;

    if (!file.is_open())
    {
        throw runtime_error("Unable to open file for reading.");
    }

    string line;
    while (getline(file, line))
    {
        if (line == "Polygon")
        {
            auto poly = new Polygon();

            size_t vertexCount;
            file >> vertexCount;

            for (size_t i = 0; i < vertexCount; ++i)
            {
                Point vertex;
                file >> vertex.x >> vertex.y;
                poly->vertexes.push_back(vertex);
            }
            
            for (size_t i = 0; i < vertexCount; ++i)
            {
                Segment segment;
                segment.b = poly->vertexes[i];
                segment.e = poly->vertexes[(i + 1) % vertexCount];
                poly->segments.push_back(segment);
            }

            polygons.push_back(poly);
            getline(file, line);
        }
    }

    file.close();
    return polygons;
}
