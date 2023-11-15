//
// Created by WuXiangGuJun on 2023/11/14.
//

#pragma once
#include "core.hpp"

namespace MinecraftClone{
    
    namespace Input{
        extern bool keyPressedData[GLFW_KEY_LAST];
        extern bool mouseButtonPressedData[GLFW_MOUSE_BUTTON_LAST];
        extern float mouseX;
        extern float mouseY;
        extern float mouseScrollX;
        extern float mouseScrollY;
        
        void keyCallback(GLFWwindow* window,int key,int scancode,int action,int mods);
        void mouseCallback(GLFWwindow* window,double xPos,double yPos);
        void mouseButtonCallback(GLFWwindow* window,int button,int action,int mods);
        void mouseScrollCallback(GLFWwindow* window,double xOffset,double yOffset);
        
        bool isKeyDown(int key);
        bool isMouseButtonPressed(int mouseButton);
    }
    
}
