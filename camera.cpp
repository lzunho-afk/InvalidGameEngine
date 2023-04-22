#include "camera.hpp"

Camera::Camera(GLfloat fov, GLfloat width, GLfloat height, GLfloat near_plane, GLfloat far_plane, glm::vec3 cam_position) {
    this->camera_pos = cam_position;
    glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);

    this->view_mtx = glm::lookAt(this->camera_pos, camera_front, camera_up);
    this->proj_mtx = glm::perspective(fov, width / height, near_plane, far_plane);
}

Camera::~Camera() {
    
}

glm::mat4 Camera::get_view_mtx() {
    return this->view_mtx;
}

glm::mat4 Camera::get_proj_mtx() {
    return this->proj_mtx;
}

glm::vec3 Camera::get_camera_pos() {
    return this->camera_pos;
}
