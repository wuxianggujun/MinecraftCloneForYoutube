//
// Created by WuXiangGuJun on 2023/11/14.
//
#include "core/Input.hpp"

namespace MinecraftClone::Input{
        bool keyPressedDate[GLFW_KEY_LAST] = {};
        bool mouseButtonPressedData[GLFW_MOUSE_BUTTON_LAST] = {};
        float mouseX = 0.0f;
        float mouseY = 0.0f;
        float mouseScrollX = 0.0f;
        float mouseScrollY = 0.0f;

        void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
            if (key >= 0 && key < GLFW_KEY_LAST) {
                keyPressedDate[key] = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
            }
        }

        void mouseCallback(GLFWwindow *window, double xPos, double yPos) {
            mouseX = (float)xPos;
            mouseY = (float)yPos;
        }

        void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
            if (button >= 0 && button < GLFW_MOUSE_BUTTON_LAST) {
                mouseButtonPressedData[button] = (action == GLFW_PRESS);
            }
        }

        void mouseScrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
            mouseScrollX = (float)xOffset;
            mouseScrollY = (float)yOffset;
        }

        bool isKeyDown(int key) {
            if (key >= 0 && key < GLFW_KEY_LAST) {
                return keyPressedDate[key];
            }
            return false;
        }

        bool isMouseButtonPressed(int mouseButton) {
            if (mouseButton >= 0 && mouseButton < GLFW_MOUSE_BUTTON_LAST) {
                return mouseButtonPressedData[mouseButton];
            }
            return false;
        }
    }
    
