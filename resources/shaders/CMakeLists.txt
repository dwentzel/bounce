set(SHADERS
    triangleShader.vert.glsl
    triangleShader.frag.glsl
)

add_custom_target(shaders SOURCES ${SHADERS})