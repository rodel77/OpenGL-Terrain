#include <SDL.h>
#define GLEW_STATIC
// #include <gl/glew.h>
#include <glad/glad.h>
#include <SDL_opengl.h>
//#include <gl/GLU.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "File.h"
#include "Shader.h"
#include "Chunk.h"
#include "Camera.h"
#include "RenderState.h"
#include "Input.h"
#include "World.h"
#include "Utils.h"

double CAMERA_SPEED = 7;

Window window;
Input input;

int main(int arc, char *args[]){
    window.init();

    if(!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)){
	    printf("Could not initialize glad!\n");
		return false;
	}

    // File vertex_file((char*)"assets/shaders/main.vert");
    // Shader vertex(&vertex_file, GL_VERTEX_SHADER);
    // vertex_file.close();

    // File fragment_file((char*)"assets/shaders/main.frag");
    // Shader fragment(&fragment_file, GL_FRAGMENT_SHADER);
    // fragment_file.close();

    Shader program((char*) "assets/shaders/main.vert", (char*) "assets/shaders/main.frag");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float vertices[] = {
        0.5f, -0.5f, 0.5f,  // br
        -0.5f, -0.5f, 0.5f, // bl
        -0.5f,  0.5f, 0.5f, // tl
        0.5f, 0.5f, 0.5f, // tr

        0.5f, -0.5f, -0.5f,  // br
        -0.5f, -0.5f, -0.5f, // bl
        -0.5f,  0.5f, -0.5f, // tl
        0.5f, 0.5f, -0.5f, // tr
        // 0.5f, -0.5f, 0.0f,
        // -0.5f,  0.5f, 0.0f,
    };
    
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        0, 1, 4,
        4, 5, 1,

        3, 2, 7,
        7, 6, 2,

        1, 2, 6,
        6, 5, 1,

        5, 6, 4,
    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    program.use();

    // glm::mat4 world(1.0f);

    glm::mat4 model(1.0f);
    
    glm::vec3 light_direction(0.3f, 1.0f, 0.3f);

    // unsigned int transform_location = glGetUniformLocation(program, "asd");
    // glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(mat));

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    float ratio = (float)640.0f/(float)480.0f;
    glm::mat4 proj = glm::perspective(45.0f, ratio, 0.1f, 100.0f);

    glm::mat4 view = glm::mat4(1.0f);
    
    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f)); 

    glEnable(GL_DEPTH_TEST);

    glShadeModel(GL_FLAT);
    glEnable(GL_CULL_FACE);

    Chunk chunka(0, 0);
    chunka.create_mesh();
    Chunk chunkb(1, 0);
    chunkb.create_mesh();
    Chunk chunkc(1, 1);
    chunkc.create_mesh();
    Chunk chunkd(0, 1);
    chunkd.create_mesh();

    World world;
    world.queue_chunk(0, 0);

    Camera camera(glm::vec3(1.0f, 2.0f, 3.0f));
    // camera.pitch -=10;
    // camera.update();

    RenderState render_state;

    unsigned int a, b = SDL_GetTicks(), SDL_GetTicks();
    double delta = 0;
    double dt = 0;

    int fps = 0;

    unsigned int timer = SDL_GetTicks();

    unsigned int last_frame = SDL_GetTicks();

    bool quit = false;
    while(!quit){
        a = SDL_GetTicks();
        delta += a - b;
        if(delta>1000/60.0f){
            b = a;
        }else continue;

        if(SDL_GetTicks()-timer>1000){
            timer = SDL_GetTicks();
            printf("FPS: %i\n", fps);
            fps = 0;
        }

        dt = (float)(SDL_GetTicks()-last_frame)/1000;
        last_frame = SDL_GetTicks();

        fps++;

        SDL_Event event;
        while(SDL_PollEvent(&event)!=0){
            input.handle_event(&event);

            if(event.type==SDL_QUIT || (event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_ESCAPE)){
                quit = true;
                break;
            }

            if(event.type==SDL_WINDOWEVENT && event.window.event==SDL_WINDOWEVENT_RESIZED){
                window.resize();
                int w, h;
                SDL_GetWindowSize(window.window, &w, &h);
                proj = glm::perspective(45.0f, (float)w/(float)h, 0.1f, 100.0f);
            }

            if(event.type==SDL_KEYDOWN) {
                SDL_Keycode key = event.key.keysym.sym;
                switch(key){
                }
            }

            if(event.type==SDL_MOUSEMOTION && SDL_GetRelativeMouseMode()){
                camera.pitch -= event.motion.yrel * dt * CAMERA_SPEED;
                camera.yaw += event.motion.xrel * dt * CAMERA_SPEED;
                camera.update();
            }

            if(event.type==SDL_MOUSEWHEEL){
                camera.fov += event.wheel.y * dt;
                int w, h;
                SDL_GetWindowSize(window.window, &w, &h);
                proj = glm::perspective(camera.fov, (float)w/(float)h, 0.1f, 100.0f);
            }
        }

        if(input.is_down(SDLK_w)){
            camera.move_relative(camera.front, dt * CAMERA_SPEED);
        }
        if(input.is_down(SDLK_s)){
            camera.move_relative(camera.front, -dt * CAMERA_SPEED);
        }
        if(input.is_down(SDLK_d)){
            camera.move_relative(camera.right, dt * CAMERA_SPEED);
        }
        if(input.is_down(SDLK_a)){
            camera.move_relative(camera.right, -dt * CAMERA_SPEED);
        }
        if(input.is_down(SDLK_q)){
            camera.move_relative(camera.up, dt * CAMERA_SPEED);
        }
        if(input.is_down(SDLK_e)){
            camera.move_relative(camera.up, -dt * CAMERA_SPEED);
        }
        SDL_SetRelativeMouseMode(input.is_down(SDLK_LSHIFT) ? SDL_TRUE : SDL_FALSE);

        // mat = glm::rotate(mat, .01f, glm::vec3(0.0f, 1.0f, 1.0f));
        view = camera.get_view_matrix();
        // view = glm::lookAt(glm::vec3(8.0f * cos((float)SDL_GetTicks()/1000), 4.0f, 8.0f * sin((float)SDL_GetTicks()/1000)), glm::vec3(4.0f, 0.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        program.use();
        // light_direction = glm::vec3(3.0f, 3.0f * cos((float)SDL_GetTicks()/1000), 3.0f);
        // model = glm::mat4(1);
        program.set_uniform_v3("light_direction", glm::value_ptr(light_direction));
        program.set_uniform_m4f("projection", glm::value_ptr(proj));
        program.set_uniform_m4f("view", glm::value_ptr(view));
        program.set_uniform_m4f("model", glm::value_ptr(model));
        // program.set_uniform_m4f("asd", glm::value_ptr(proj * view * model));
        // glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(proj * view * mat));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 1.0f, 1.0f, 0.0f);

        // auto asd = glm::vec3(view[3]);
        int chunk_x = camera.position.x;
        int chunk_z = camera.position.z;
        chunk_x >>= 2;
        chunk_z >>= 2;

        for(int x = -16; x < 16; x++){
            for(int z = -16; z < 16; z++){
                if(!world.has_chunk(chunk_x+x, chunk_z+z)){
                    world.queue_chunk(chunk_x+x, chunk_z+z);
                }
            }
        }

        for(auto const& pair : world.chunks){
            if(abs(pair.second->x-chunk_x)>20 || abs(pair.second->z-chunk_z)>20){
                // world.chunks.erase(pair.first);
                // printf("delete");
            }
            // pair.second->render();
        }

        // if(!world.has_chunk(chunk_x, chunk_z)){
        //     world.queue_chunk(chunk_x, chunk_z);
        // }
        world.render();

        // model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
        // const *float a = glm::value_ptr(glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f))));
        // program.set_uniform_m4f("model", glm::value_ptr(model));
        // chunkb.render();
        // chunkd.render();
        // chunkc.render();
        // chunkd.render();
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        // glDrawElements(GL_TRIANGLES, 33, GL_UNSIGNED_INT, 0);

        SDL_GL_SwapWindow(window.window);
    }

    window.destroy();

    return 1;
}