#include "mesh.hpp"

void Mesh::set_triangle_data(std::vector<Vertex>& vtxs, std::vector<uint32_t>& idxs) {
    std::vector<Vertex> _vtxs = {
	{
	    { 0.0f, -1.0f, 0.0f }, // Position
	    { 0.0f, 0.0f, 1.0 },   // Normal
	    { 1.0f, 0.0f, 0.0 },   // Color
	    { 0.0, 1.0 }           // Texture Coordinates
	},
	{
	    { 1.0f, 1.0f, 0.0f },
	    { 0.0f, 0.0f, 1.0 },
	    { 0.0f, 1.0f, 0.0 },
	    { 0.0, 0.0 }
	},
	{
	    { -1.0f, 1.0f, 0.0f },
	    { 0.0f, 0.0f, 1.0 },
	    { 0.0f, 0.0f, 1.0 },
	    { 1.0, 0.0 }
	},
    };

    std::vector<uint32_t> _idxs = {
	0, 1, 2,
    };
    
    vtxs.clear();
    idxs.clear();
    vtxs = _vtxs;
    idxs = _idxs;
}

void Mesh::set_quad_data(std::vector<Vertex>& vtxs, std::vector<uint32_t>& idxs) {
    
}

void Mesh::set_cube_data(std::vector<Vertex>& vtxs, std::vector<uint32_t>& idxs) {
    
}

void Mesh::set_sphere_data(std::vector<Vertex>& vtxs, std::vector<uint32_t>& idxs) {
    
}
