#include <iostream>
#include <GLFW/glfw3.h>
#include <functional>

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

    std::function<void(int,int)> m_framebuffer_size_callback=nullptr;
    std::function<void(int,int,int,int)> m_key_callback=nullptr;
    std::function<void(double,double)> m_cursor_pos_callback=nullptr;
    std::function<void(int,int,int)> m_mouse_button_callback=nullptr;

private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    GLFWwindow* _window;
};
