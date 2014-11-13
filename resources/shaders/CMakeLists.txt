set(SHADERS
    triangleShader.vert.glsl
    triangleShader.frag.glsl
    geometry_pass.vert.glsl
    geometry_pass.frag.glsl
    light_pass.vert.glsl
    dir_light_pass.frag.glsl
    point_light_pass.frag.glsl
)

add_custom_target(shaders SOURCES ${SHADERS})