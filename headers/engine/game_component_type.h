#ifndef BOUNCE_ENGINE_GAME_COMPONENT_TYPE_H_
#define BOUNCE_ENGINE_GAME_COMPONENT_TYPE_H_

namespace bounce {
    enum GameComponentType {
        RENDER_COMPONENT,
        BODY_COMPONENT,
        CONTROL_COMPONENT,
        AI_COMPONENT,
        MOVEMENT_COMPONENT,
        POINT_LIGHT_COMPONENT,
        POSITION_COMPONENT,
        COMPONENT_COUNT
    };
}

#endif // BOUNCE_GAME_COMPONENT_TYPE_H_