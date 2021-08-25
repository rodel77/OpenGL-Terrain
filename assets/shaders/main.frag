#version 410 core
out vec4 fragment_color;

in vec3 normal;
in vec3 fragment_position;
in vec2 texture_coords;

uniform vec3 light_direction;

void main(){
    vec3 norm = normalize(normal);
    //vec3 light_dir = normalize(light_position - fragment_position);

    float diff = max(dot(norm, light_direction), 0.0);
    vec3 diffuse = diff * vec3(0.3f, 0.7f, 0.3f);

    fragment_color = vec4(diffuse, 1.0f);
}