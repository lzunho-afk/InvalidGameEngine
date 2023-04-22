#ifndef LIGHT_RENDERER_HPP
#define LIGHT_RENDERER_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "mesh.hpp" // Light source shape
#include "shader_loader.hpp"
#include "camera.hpp"

class LightRenderer
{
public:
    LightRenderer(MeshType meshtype, Camera *cam);
    ~LightRenderer();

    void draw();
    void set_position(glm::vec3 _pos);
    void set_color(glm::vec3 _color);
    void set_program(GLuint prog);
    glm::vec3 get_position();
    glm::vec3 get_color();

private:
    Camera *camera;
    std::vector<Vertex> vtxs;
    std::vector<GLuint> idxs;
    glm::vec3 position, color;
    GLuint vbo, ebo, vao, program;
};

#endif // LIGHT_RENDERER_HPP
