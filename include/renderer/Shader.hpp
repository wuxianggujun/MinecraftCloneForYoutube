//
// Created by WuXiangGuJun on 2023/11/14.
//
#pragma once

#include <core.hpp>

namespace MinecraftClone{
    enum class ShaderType : uint8 {
        Vertex,
        Fragment
    };
    
    struct Shader{
        char* filePath;
        uint32 shaderId;
        ShaderType type;
        
        bool compile(ShaderType type,const char* shaderFilePath);
        void destroy();
        
        static GLenum toGlShaderType(ShaderType type);
    };
}