#include <glad/glad.h>
#include "Shader.h"
#include <iostream>

Shader::Shader(char *vertex_path, char *fragment_path){
    this->vertex_path = vertex_path;
    File vertex_file(vertex_path);
    vertex_file.read_string();
    this->fragment_path = fragment_path;
    File fragment_file(fragment_path);
    fragment_file.read_string();

    init(vertex_file.contents, fragment_file.contents);
}

unsigned int Shader::init(char *vertex_code, char *fragment_code){
    this->vertex_shader   = create_shader(vertex_code, GL_VERTEX_SHADER);
    this->fragment_shader = create_shader(fragment_code, GL_FRAGMENT_SHADER);
    return create_shader_program();
}

unsigned int Shader::create_shader_program(){
    program  = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success){
        char error[512];
        glGetProgramInfoLog(program, 512, NULL, error);
        printf("Error linking shader program \"%s\" & \"%s\"\n", vertex_path, fragment_path);
        printf("%s\n", error);
    }
    return program;
}

void Shader::use(){
    glUseProgram(program);
}

void Shader::set_uniform_m4f(const char *name, float *value){
    unsigned int location = glGetUniformLocation(program, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, value);
}

void Shader::set_uniform_v3(const char *name, float *value){
    unsigned int location = glGetUniformLocation(program, name);
    glUniform3fv(location, 1, value);
}

Shader::~Shader(){
    glDeleteShader(this->vertex_shader);
    glDeleteShader(this->fragment_shader);
    glDeleteProgram(this->program);
}

unsigned int Shader::create_shader(char *source, unsigned int shader_type){
    unsigned int shader_index = glCreateShader(shader_type);
    glShaderSource(shader_index, 1, &source, NULL);
    glCompileShader(shader_index);

    int success;
    glGetShaderiv(shader_index, GL_COMPILE_STATUS, &success);
    if(!success){
        char error[512];
        glGetShaderInfoLog(shader_index, 512, NULL, error);
        printf("Error compiling shader (%s)\n%s\n", shader_type==GL_VERTEX_SHADER ? vertex_path : fragment_path, error);
        return -1;
    }
    return shader_index;
}