#ifndef BOUNCE_ENGINE_GAME_COMPONENT_TYPE_H_
#define BOUNCE_ENGINE_GAME_COMPONENT_TYPE_H_

namespace bounce {
    enum GameComponentType : unsigned short {
        RENDER_COMPONENT,
        BODY_COMPONENT,
        CAMERA_COMPONENT,
        CONTROL_COMPONENT,
        AI_COMPONENT,
        POINT_LIGHT_COMPONENT,
        COMPONENT_COUNT
    };
}

#endif // BOUNCE_GAME_COMPONENT_TYPE_H_
