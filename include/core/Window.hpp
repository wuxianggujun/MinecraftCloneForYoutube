//
// Created by WuXiangGuJun on 2023/11/14.
//

#pragma once
#include "core.hpp"

namespace MinecraftClone{
    struct Window{
        GLFWwindow* nativeWindow;
        int windowWidth;
        int windowHeight;
        
        void installMainCallbacks() const;
        
        void close() const;
        
        static Window* createWindow(int width, int height, const char* title,bool fullScreenMode = false);
        static void freeWindow(Window* window);
    };
    
}
