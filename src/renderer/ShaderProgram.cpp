//
// Created by WuXiangGuJun on 2023/11/15.
//
#include "renderer/Shader.hpp"
#include "renderer/ShaderProgram.hpp"
#include <unordered_set>

namespace MinecraftClone{
    struct ShaderVariable{
        std::string name;
        GLint varLocation;
        uint32 shaderProgramId;
        
        bool operator==(const ShaderVariable& other) const {
            return other.shaderProgramId == shaderProgramId && other.name == name;
        }
    };
    
    struct hashShaderVar{
        std::size_t operator()(const ShaderVariable& var) const {
            std::size_t seed = std::hash<std::string>{}(var.name);
            seed ^= std::hash<uint32>{}(var.shaderProgramId) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            return seed;
        }
    };
    
    static auto allShaderVariableLocations = std::unordered_set<ShaderVariable,hashShaderVar>();
    
    static GLint getVariableLocation(const ShaderProgram& shader,const char* varName);
    
    bool ShaderProgram::compileAndLink(const char *vertexShaderFile, const char *fragmentShaderFile) {
        GLuint program = glCreateProgram();
        
        Shader vertexShader;
        if (!vertexShader.compile(ShaderType::Vertex, vertexShaderFile)) {
            vertexShader.destroy();
            return false;
        }
        Shader fragmentShader;
        if (!fragmentShader.compile(ShaderType::Fragment, fragmentShaderFile)) {
            fragmentShader.destroy();
            return false;
        }
        
        glAttachShader(program, vertexShader.shaderId);
        glAttachShader(program, fragmentShader.shaderId);
        glLinkProgram(program);
        
        GLint isLinked = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
            
            glDeleteProgram(program);
            vertexShader.destroy();
            fragmentShader.destroy();
            
            programID = UINT32_MAX;
            
            return false;
        }
        glDetachShader(program, vertexShader.shaderId);
        glDetachShader(program,fragmentShader.shaderId);
        vertexShader.destroy();
        fragmentShader.destroy();
        
        int numUniforms;
        glGetProgramiv(program,GL_ACTIVE_UNIFORMS,&numUniforms);
        
        int maxCharLength;
        glGetProgramiv(program,GL_ACTIVE_UNIFORM_MAX_LENGTH,&maxCharLength);
        if (numUniforms > 0 && maxCharLength > 0){
            char* charBuffer = (char*) malloc(sizeof(char )* maxCharLength);

            for (int i = 0; i < numUniforms; ++i) {
                int length,size;
                GLenum  dataType;
                glGetActiveUniform(program,i,maxCharLength,&length,&size,&dataType,charBuffer);
                GLint varLocation = glGetUniformLocation(program,charBuffer);
                ShaderVariable shaderVar;
                shaderVar.name = std::string(charBuffer,length);
                shaderVar.varLocation = varLocation;
                shaderVar.shaderProgramId = program;
                allShaderVariableLocations.emplace(shaderVar);
            }
            free(charBuffer);
        }
        programID = program;
        return true;
    }

    void ShaderProgram::destroy() {
        if (programID != UINT32_MAX){
            glDeleteProgram(programID);
            programID = UINT32_MAX;
        }
    }

    void ShaderProgram::bind() const {
        glUseProgram(programID);
    }

    void ShaderProgram::unbind() const {
        glUseProgram(0);
    }

    void ShaderProgram::uploadVec4(const char* varName, const glm::vec4& vec4) const
    {
        int varLocation = getVariableLocation(*this, varName);
        glUniform4f(varLocation, vec4.x, vec4.y, vec4.z, vec4.w);
    }

    void ShaderProgram::uploadVec3(const char* varName, const glm::vec3& vec3) const
    {
        int varLocation = getVariableLocation(*this, varName);
        glUniform3f(varLocation, vec3.x, vec3.y, vec3.z);
    }

    void ShaderProgram::uploadVec2(const char* varName, const glm::vec2& vec2) const
    {
        int varLocation = getVariableLocation(*this, varName);
        glUniform2f(varLocation, vec2.x, vec2.y);
    }

    void ShaderProgram::uploadIVec4(const char* varName, const glm::ivec4& vec4) const
    {
        int varLocation = getVariableLocation(*this, varName);
        glUniform4i(varLocation, vec4.x, vec4.y, vec4.z, vec4.w);
    }

    void ShaderProgram::uploadIVec3(const char* varName, const glm::ivec3& vec3) const
    {
        int varLocation = getVariableLocation(*this, varName);
        glUniform3i(varLocation, vec3.x, vec3.y, vec3.z);
    }

    void ShaderProgram::uploadIVec2(const char* varName, const glm::ivec2& vec2) const
    {
        int varLocation = getVariableLocation(*this, varName);
        glUniform2i(varLocation, vec2.x, vec2.y);
    }

    void ShaderProgram::uploadFloat(const char* varName, float value) const
    {
        int varLocation = getVariableLocation(*this, varName);
        glUniform1f(varLocation, value);
    }

    void ShaderProgram::uploadInt(const char* varName, int value) const
    {
        int varLocation = getVariableLocation(*this, varName);
        glUniform1i(varLocation, value);
    }

    void ShaderProgram::uploadUInt(const char* varName, uint32 value) const
    {
        int varLocation = getVariableLocation(*this, varName);
        glUniform1ui(varLocation, value);
    }

    void ShaderProgram::uploadMat4(const char* varName, const glm::mat4& mat4) const
    {
        int varLocation = getVariableLocation(*this, varName);
        glUniformMatrix4fv(varLocation, 1, GL_FALSE, glm::value_ptr(mat4));
    }

    void ShaderProgram::uploadMat3(const char* varName, const glm::mat3& mat3) const
    {
        int varLocation = getVariableLocation(*this, varName);
        glUniformMatrix3fv(varLocation, 1, GL_FALSE, glm::value_ptr(mat3));
    }

    void ShaderProgram::uploadIntArray(const char* varName, int length, const int* array) const
    {
        int varLocation = getVariableLocation(*this, varName);
        glUniform1iv(varLocation, length, array);
    }

    void ShaderProgram::uploadBool(const char* varName, bool value) const
    {
        int varLocation = getVariableLocation(*this, varName);
        glUniform1i(varLocation, value ? 1 : 0);
    }

    void ShaderProgram::clearAllShaderVariables()
    {
        allShaderVariableLocations.clear();
    }

    // Private functions
    static GLint getVariableLocation(const ShaderProgram& shader, const char* varName)
    {
        ShaderVariable match = {
                varName,
                0,
                shader.programID
        };
        auto iter = allShaderVariableLocations.find(match);
        if (iter != allShaderVariableLocations.end())
        {
            return iter->varLocation;
        }

        return -1;
    }
}