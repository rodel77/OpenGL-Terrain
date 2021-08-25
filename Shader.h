#ifndef SHADER_H
#define SHADER_H

#include "File.h"

class Shader {
    public:
        Shader(char *vertex_path, char *fragment_path);
        ~Shader();

        void set_uniform_m4f(const char *name, float *value);
        void set_uniform_v3(const char *name, float *value);
        void use();

        File *file;
        unsigned int shader_index;
        unsigned int vertex_shader, fragment_shader, program;
        char *vertex_path, *fragment_path;
    private:
        unsigned int init(char *vertex_code, char *fragment_code);
        unsigned int create_shader_program();
        unsigned int create_shader(char *source_code, unsigned int shader_type);
};



#endif