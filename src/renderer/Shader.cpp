//
// Created by WuXiangGuJun on 2023/11/15.
//
#include <iostream>
#include "renderer/Shader.hpp"

namespace MinecraftClone{
    
    static std::string ReadFile(const char* filePath);
    
    bool Shader::compile(ShaderType type, const char *shaderFilePath) {
        int strLength = (int)std::strlen(shaderFilePath);
        filePath = (char *) malloc(sizeof(char) * (strLength + 1));
        std::strcpy(filePath, shaderFilePath);
        filePath[strLength] = '\0';
        
        std::string shaderSourceCode = ReadFile(filePath);
        GLenum shaderType = toGlShaderType(type);
        if (shaderType == GL_INVALID_ENUM) {
            return false;
        }
        
        shaderId = glCreateShader(shaderType);
        
        const GLchar* sourceCStr = shaderSourceCode.c_str();
        glShaderSource(shaderId,1,&sourceCStr,0);
        
        glCompileShader(shaderId);
        
        GLint isCompiled = 0;
        glGetShaderiv(shaderId,GL_COMPILE_STATUS,&isCompiled);
        if (isCompiled == GL_FALSE){
            GLint maxLength = 0;
            glGetShaderiv(shaderId,GL_INFO_LOG_LENGTH,&maxLength);
            
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shaderId,maxLength,&maxLength,&infoLog[0]);
            
            glDeleteShader(shaderId);
            
            shaderId = UINT32_MAX;
            return false;
        }
        return true;
    }

    void Shader::destroy() {
        if (shaderId != UINT32_MAX){
            glDeleteShader(shaderId);
            shaderId = UINT32_MAX;
        }

        if (filePath != nullptr){
            free(filePath);
            filePath = nullptr;
        }
    }

    GLenum Shader::toGlShaderType(ShaderType type) {
        switch (type) {
            case ShaderType::Vertex:
                return GL_VERTEX_SHADER;
            case ShaderType::Fragment:
                return GL_FRAGMENT_SHADER;
        }
        return GL_INVALID_ENUM;
    }

    static std::string ReadFile(const char * filePath){
        std::string result;
        std::ifstream in(filePath, std::ios::in | std::ios::binary);
        if (in){
            in.seekg(0,std::ios::end);
            result.resize(in.tellg());
            in.seekg(0,std::ios::beg);
            in.read(&result[0],result.size());
            in.close();
        }else{
            std::cerr << "Could not open file: '%s'" <<filePath << std::endl;
        }
        return result;
    }

}