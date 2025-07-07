#ifndef MAP_COMPONENT_H
#define MAP_COMPONENT_H

#include "IComponent.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>

struct Vertex {
    float x, y;
};

struct Segment {
    int start_vertex;
    int end_vertex;
    int left_sector;
    int right_sector;
    std::string wall_texture;
    float top;
    float bottom;
    std::string type;
};

struct Sector {
    int id;
    std::vector<int> vertex_indices;
    float floor_height;
    float ceil_height;
    std::string floor_texture;
    std::string ceil_texture;
    float lighting;
};

struct MapEntity {
    std::string type;
    float x, y;
    float angle;
    std::string kind;
};

struct MapComponent : public IComponent {
    std::vector<Vertex> vertices;
    std::vector<Sector> sectors;
    std::vector<Segment> segments;
    std::vector<MapEntity> entities;
};

#endif // MAP_COMPONENT_H
