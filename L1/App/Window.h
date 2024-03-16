#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class Window {
public: 
    Window();
    void create(int width, int height, const char* title);
    ~Window();

    bool should_close();

    void poll_events();

    void swap_buffers();

    float get_time();
    GLFWwindow* get_window();
private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    GLFWwindow* _window;
};
