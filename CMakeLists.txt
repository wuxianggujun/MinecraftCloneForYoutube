# CMakeList.txt: MinecraftCloneForYoutube 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.16)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("MinecraftCloneForYoutube")

include(cmake/CPM.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(GLAD_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}" CACHE STRING "Output directory" FORCE)

CPMAddPackage("gh:glfw/glfw#3.3.8")
CPMAddPackage("gh:g-truc/glm#0.9.9.8")
CPMAddPackage("gh:gabime/spdlog@1.12.0")
CPMAddPackage("gh:Dav1dde/glad@0.1.36")
#CPMAddPackage("gh:Dav1dde/glad@2.0.4")
#CPMAddPackage("gh:nothings/stb#master")

set(PROJECT_SOURCES
        include/core.hpp
        src/main.cpp
        include/stb_image.h
        include/core/Window.hpp
        include/core/Input.hpp
        include/challenges/Cubes.hpp
        include/renderer/Shader.hpp
        include/renderer/ShaderProgram.hpp
        src/core/Input.cpp
        src/core/VendorImplementations.cpp
        src/core/Window.cpp
        src/challenges/Cubes.cpp
        src/renderer/Shader.cpp
        src/renderer/ShaderProgram.cpp)

#FILE(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)

# 将源代码添加到此项目的可执行文件。
add_executable (${PROJECT_NAME} ${PROJECT_SOURCES})


add_custom_target(
    copy-assets ALL
   COMMENT "Copying assets"
   COMMAND ${CMAKE_COMMAND} -E copy_directory
   ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad glm spdlog)
        #glfw glad glm stb_image)