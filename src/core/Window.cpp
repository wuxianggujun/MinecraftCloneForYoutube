//
// Created by WuXiangGuJun on 2023/11/14.
//
#include "core/Window.hpp"
#include "core/Input.hpp"

namespace MinecraftClone{
    
    static void resizeCallback(GLFWwindow* nativeWindow,int newWidth,int newHeight){
        Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(nativeWindow));
        window->windowWidth = newWidth;
        window->windowHeight = newHeight;
        glViewport(0,0,newWidth,newHeight);
    }
    
    void Window::installMainCallbacks() const {
        if (nativeWindow != nullptr){
            glfwSetKeyCallback(nativeWindow,Input::keyCallback);
            glfwSetCursorPosCallback(nativeWindow,Input::mouseCallback);
            glfwSetMouseButtonCallback(nativeWindow,Input::mouseButtonCallback);
            glfwSetWindowSizeCallback(nativeWindow,resizeCallback);
        }
    }

    void Window::close() const {
        if (nativeWindow != nullptr){
            glfwSetWindowShouldClose(nativeWindow,GLFW_TRUE);
        }
    }

    Window *Window::createWindow(int width, int height, const char *title, bool fullScreenMode) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,6);
        glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
        
        Window* res = new Window();
        // ��ȡmonitor��ͬʱ�ж��Ƿ�ȫ��
        GLFWmonitor* primaryMonitor =  fullScreenMode ? glfwGetPrimaryMonitor() : nullptr;
        // nativeWindow��ʵ����glfwWindow
        res->nativeWindow = glfwCreateWindow(width,height,title,primaryMonitor,nullptr);
        if (res->nativeWindow == nullptr){
            printf("Failed to create GLFW window\n");
            glfwTerminate();
            return nullptr;
        }
        // �л�������
        glfwMakeContextCurrent(res->nativeWindow);
        // ���ô��ڹ����û�����ָ��ĺ���
        glfwSetWindowUserPointer(res->nativeWindow,(void *)res);
        
        res->windowWidth = width;
        res->windowHeight = height;
        return res;
    }

    void Window::freeWindow(Window *window) {
        if (window){
            glfwDestroyWindow(window->nativeWindow);
            delete window;
        }
    }
}