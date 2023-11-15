//
// Created by WuXiangGuJun on 2023/11/14.
//
#pragma once

namespace MinecraftClone{
    struct Window;
    
    namespace Cubes{
        void init(const Window& window);
        void destroy();
        
        void update(float dt);
    }
}