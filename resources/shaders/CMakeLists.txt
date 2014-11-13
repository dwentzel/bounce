set(SHADERS
    triangleShader.vert.glsl
    triangleShader.frag.glsl
    geometry_pass.vert.glsl
    geometry_pass.frag.glsl
)

add_custom_target(shaders SOURCES ${SHADERS})