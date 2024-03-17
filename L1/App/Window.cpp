#include "glad/glad.h"
#include "Window.h"
#include "L1/Lib/IO/imageLoader.h"
#include "L1/App/Config.h"
void set_window_icon(GLFWwindow* window) {
    int w, h, c;
    ImageLoader image_loader;
    unsigned char* data = image_loader.loadImage(
        Config::getInstance().get("icon_path").c_str(), &w, &h, &c);
    GLFWimage image = {w, h, data};
    glfwSetWindowIcon(window, 1, &image);
    image_loader.free_data(data);
}
void Window::create(int width, int height, const char* title) {
    // 初始化GLFW
    if (!glfwInit()) {
        throw std::runtime_error("无法初始化GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    _window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    
    set_window_icon(_window);

    if (!_window) {
        glfwTerminate();
        throw std::runtime_error("无法创建GLFW窗口");
    }
    glfwMakeContextCurrent(_window);


    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
    glfwSetKeyCallback(_window, key_callback);
    glfwSetCursorPosCallback(_window,cursor_pos_callback);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        throw std::runtime_error("无法初始化GLAD");
    }
    //
    glfwSetWindowUserPointer(_window,this);
    glViewport(0, 0, width, height);
    glfwSwapInterval(1);
    std::cout<<"<<<<<<"<<std::endl;
    }
    Window::Window() {        
    }
    Window::~Window() {
        glfwDestroyWindow(_window);
        glfwTerminate();
    }
bool Window::should_close(){
    return glfwWindowShouldClose(_window);
}
void Window::poll_events(){   
    glfwPollEvents();    
}

float Window::get_time() {
    return (float)glfwGetTime();
}

GLFWwindow* Window::get_window() {
    return _window;
}

void Window::framebuffer_size_callback(GLFWwindow* window,int width,int height){
    glViewport(0, 0, width, height);
    Window* self=(Window*)glfwGetWindowUserPointer(window);
    if(self->framebuffer_size_callback)
        self->m_framebuffer_size_callback(width,height);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Window* self=(Window*)glfwGetWindowUserPointer(window);
    if(self->m_key_callback)
        self->m_key_callback(key,scancode,action,mods);
}
void Window::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
    Window* self=(Window*)glfwGetWindowUserPointer(window);
    if(self->m_cursor_pos_callback)
        self->m_cursor_pos_callback(xpos,ypos);
}
void Window::swap_buffers() {
    glfwSwapBuffers(_window);
}
