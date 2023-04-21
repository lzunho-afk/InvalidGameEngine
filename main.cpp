#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "yaml-cpp/yaml.h"
#include "version.h"

#define WINDOW_HEADNAME "IGE - Invalid Game Engine"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void process_input(GLFWwindow *window);
void render_scene();

int main(void) {
    // Yaml configuration file specs
    YAML::Node config = YAML::LoadFile("config.yml");
    if (!(config["window"]["dimentions"]["width"] && config["window"]["dimentions"]["height"])) {
	std::cerr << "err. incomplete window dimentions config...\n";
	return 1;
    }
    const int window_width = config["window"]["dimentions"]["width"].as<int>();
    const int window_height = config["window"]["dimentions"]["height"].as<int>();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // GLFW window creation
    GLFWwindow *window = glfwCreateWindow(window_width, window_height, WINDOW_HEADNAME, NULL, NULL);
    if (window == NULL) {
	std::cerr << "Failed to create GLFW window context\n";
	glfwTerminate();
	return -1;
    }

    // Creating OpenGL window context
    glfwMakeContextCurrent(window);

    // Starting GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err) {
	std::cerr << glewGetErrorString(err) << '\n';
	glfwTerminate();
	return -1;
    }
    std::cout << "=> Using GLEW " << glewGetString(GLEW_VERSION) << '\n';

    // OpenGL Viewport
    glViewport(0, 0, window_width, window_height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Window loop
    while (!glfwWindowShouldClose(window)) {
	process_input(window);
	render_scene();

	glfwSwapBuffers(window);
	glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void render_scene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0); // Clearing with black
    
}
