#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(GLfloat fov, GLfloat width, GLfloat height, GLfloat near_plane, GLfloat far_plane, glm::vec3 cam_position);
    ~Camera();

    glm::mat4 get_view_mtx();
    glm::mat4 get_proj_mtx();
    glm::vec3 get_camera_pos();

private:
    glm::mat4 view_mtx;
    glm::mat4 proj_mtx;
    glm::vec3 camera_pos;
};

#endif // CAMERA_HPP 
