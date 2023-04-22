#ifndef SHADER_LOADER_HPP
#define SHADER_LOADER_HPP

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <vector>

class ShaderLoader {
public:
    GLuint create_program(const char *vtx_shader_filename, const char *fragment_shader_filename);

private:
    std::string read_shader(const char *filename);
    GLuint create_shader(GLenum shader_type, std::string src, const char *shader_name);
};

#endif // SHADER_LOADER_HPP
