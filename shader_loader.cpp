#include "shader_loader.hpp"

/*
 * Attach and compile both vertex and fragment shaders
 *
 * @arg const char* vtx_shader_filename      "Vertex shader filename"
 * @arg const char* fragment_shader_filename "Fragment shader filename"
 * @return GLuint program ""
 */
GLuint ShaderLoader::create_program(const char *vtx_shader_filename, const char *fragment_shader_filename)
{
    // Reading & Compilling shaders
    std::string vtx_shader_code = this->read_shader(vtx_shader_filename);
    std::string fragment_shader_code = this->read_shader(fragment_shader_filename);
    GLuint vtx_shader = this->create_shader(GL_VERTEX_SHADER, vtx_shader_code, "vertex shader");
    GLuint fragment_shader = this->create_shader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragment shader");

    // program handling (attaching and linking shaders)
    int link_res = 0;
    GLuint program = glCreateProgram();
    glAttachShader(program, vtx_shader);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &link_res);
    if (link_res == GL_FALSE) {
	int info_log_length = 0;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
	std::vector<char> program_log(info_log_length);

	glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
	std::cerr << "err. loading shader :: LINK ERROR\n" << &program_log[0] << '\n';
	return 0;
    }
    return program;
}

/*
 * Returns a string with all shader code from a filename
 *
 * @arg    const string filename
 * @return string       shader_code
 */
std::string ShaderLoader::read_shader(const char *filename)
{
    std::string shader_code;
    std::ifstream file(filename, std::ios::in);

    if (!file.good()) {
	std::cerr << "err. Can't read shader file " << filename << '\n';
	std::terminate();
    }

    file.seekg(0, std::ios::end);
    shader_code.resize((unsigned int)file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&shader_code[0], shader_code.size());
    file.close();
    return shader_code;
}

/*
 * Returns a compiled shader from it source code
 *
 * @arg enum GLenum shader_type "specifies the type of shader"
 * @arg string      src         "shader code string"
 * @arg string      shader_name "shader type warning string"
 * @return GLuint shader "compiled shader"
 */
GLuint ShaderLoader::create_shader(GLenum shader_type, std::string src, const char *shader_name)
{
    int compile_res = 0;

    GLuint shader = glCreateShader(shader_type);
    const char *shader_code_ptr = src.c_str();
    const int shader_code_size = src.size();

    // Compiles shader & get status code
    glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_res);

    if (compile_res == GL_FALSE) {
	int info_log_length = 0;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
	std::vector<char> shader_log(info_log_length);
	glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
	std::cerr << "err. compiling shader " << shader_name << '\n' << &shader_log[0] << '\n';
	return 0;
    }
    return shader;
}
