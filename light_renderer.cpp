#include "light_renderer.hpp"

/*
 * Initialize camera object & Bind mesh buffers
 *
 * @arg enum MeshType meshtype "Primitive mesh enum"
 * @arg Camera*       cam      "Camera object"
 */
LightRenderer::LightRenderer(MeshType meshtype, Camera *cam)
{
    this->camera = cam;
    switch(meshtype) {
    case kTriangle:
	Mesh::set_triangle_data(this->vtxs, this->idxs);
	break;
    case kQuad:
	Mesh::set_quad_data(this->vtxs, this->idxs);
	break;
    case kCube:
	Mesh::set_cube_data(this->vtxs, this->idxs);
	break;
    case kSphere:
	Mesh::set_sphere_data(this->vtxs, this->idxs);
	break;
    }

    // bounding vao
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    // generating vbo
    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    // storing buffer
    glBufferData(GL_ARRAY_BUFFER,
		 sizeof(Vertex) * this->vtxs.size(),
		 &this->vtxs[0],
		 GL_STATIC_DRAW);

    // draw attrib ptr
    glEnableVertexAttribArray(0); // setting index "0"
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

    // coloring attrib ptr
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			  (void*)(offsetof(Vertex, Vertex::color)));

    // buffer obj. buffer type binding
    glGenBuffers(1, &this->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) *this->idxs.size(), &this->idxs[0], GL_STATIC_DRAW);

    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

LightRenderer::~LightRenderer()
{
    
}

/*
 * Get models data & draw it
 */
void LightRenderer::draw()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(glm::mat4(1.0), this->position);
    glUseProgram(this->program);

    // model
    GLint model_location = glGetUniformLocation(this->program, "model");
    glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));

    // view & project mtxs
    glm::mat4 view = this->camera->get_view_mtx();
    GLint view_location = glGetUniformLocation(this->program, "view");
    glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 proj = this->camera->get_proj_mtx();
    GLint proj_location = glGetUniformLocation(this->program, "projection");
    glUniformMatrix4fv(proj_location, 1, GL_FALSE, glm::value_ptr(proj));

    // draw
    glBindVertexArray(this->vao);
    glDrawElements(GL_TRIANGLES, this->idxs.size(), GL_UNSIGNED_INT, 0);

    // unbinding
    glBindVertexArray(0);
    glUseProgram(0);
}

void LightRenderer::set_position(glm::vec3 _pos)
{
    this->position = _pos;
}

void LightRenderer::set_color(glm::vec3 _color)
{
    this->color = _color;
}

void LightRenderer::set_program(GLuint prog)
{
    this->program = prog;
}

glm::vec3 LightRenderer::get_position()
{
    return this->position;
}

glm::vec3 LightRenderer::get_color()
{
    return this->color;
}
