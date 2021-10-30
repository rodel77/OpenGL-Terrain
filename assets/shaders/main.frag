#version 410 core
out vec4 fragment_color;

in vec3 normal;
in vec3 fragment_position;
in vec2 texture_coords;
in vec4 color;

uniform vec3 light_direction;

float near = 0.1; 
float far  = 200.0; 
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main(){
    vec3 norm = normalize(normal);
    //vec3 light_dir = normalize(light_position - fragment_position);

    float diff = max(dot(norm, light_direction), 0.0) * .8 + .2;
    //vec3 diffuse = (diff * vec3(0.3f, 0.7f, 0.3f)) * .5 + .5;
    vec3 diffuse = (diff) * vec3(color);

    float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
    fragment_color = vec4(diffuse, 1.0f);
    //fragment_color = vec4(vec3(1-depth), 1.0);
    //fragment_color = vec4(vec3(gl_FragCoord.z), 1.0);
}