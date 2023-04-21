#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <glm/glm.hpp>

enum MeshType {
    kTriangle = 0,
    kQuad = 1,
    kCube = 2,
    kSphere = 3
};

struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texture_coordinates;
};

class Mesh {
public:
    static void set_triangle_data(std::vector<Vertex>& vtxs, std::vector<uint32_t>& idxs);
    static void set_quad_data(std::vector<Vertex>& vtxs, std::vector<uint32_t>& idxs);
    static void set_cube_data(std::vector<Vertex>& vtxs, std::vector<uint32_t>& idxs);
    static void set_sphere_data(std::vector<Vertex>& vtxs, std::vector<uint32_t>& idxs);
};

#endif // MESH_HPP
