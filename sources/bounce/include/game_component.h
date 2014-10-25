#ifndef BOUNCE_GAME_COMPONENT_H
#define BOUNCE_GAME_COMPONENT_H

#include "mesh.h"

namespace bounce{

    class GameComponentType {
        int id_;
    public:
        static const GameComponentType* Render;
        
        GameComponentType(int id) : id_(id) {}
    };
    
    class GameComponent {
    private:
        
    public:
        virtual void startup() = 0;
        
        virtual void shutdown() = 0;
        
        virtual void update() = 0;
        
        virtual const GameComponentType* component_type() = 0;
        
        bool isOfType(GameComponentType* component_type) {
            return this->component_type() == component_type;
        }
    };
    
    class RenderComponent : public GameComponent
    {
    private:
        static const GameComponentType* component_type_s_;
        const int matrix_id_;
        const Mesh* mesh_;
        
    public:
        RenderComponent(Mesh* mesh, int matrix_id) : matrix_id_(matrix_id), mesh_(mesh) {}
        
        virtual void startup();
        
        virtual void shutdown();
        
        virtual void update();
        
        virtual const GameComponentType* component_type();
    };
}

#endif