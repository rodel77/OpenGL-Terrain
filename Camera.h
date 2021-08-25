#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
    public:
        Camera(glm::vec3 position, glm::vec3 up = glm::vec3(0.0f, 0.1f, 0.0f), float yaw = -90.0f, float pitch = 0.0f) : front(glm::vec3(0.0f, 0.0f, -0.1f)) {
            this->position = position;
            this->world_up = up;
            this->yaw = yaw;
            this->pitch = pitch;
            update();
        }

        glm::mat4 get_view_matrix(){
            return glm::lookAt(position, position + front, up);
        }

        void update(){
            glm::vec3 front;
            front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            front.y = sin(glm::radians(pitch));
            front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

            this->front = glm::normalize(front);
            this->right = glm::normalize(glm::cross(this->front, this->world_up));
            this->up    = glm::normalize(glm::cross(this->right, this->front));
        }

        void move_relative(glm::vec3 direction, float speed){
            this->position += direction * speed;
        }

        // glm::ivec2 get_chunk_position(){
        //     int x = position.x, z = position.z;
        //     return 
        // }

        glm::vec3 position, front, up, right, world_up;
        float yaw, pitch;
        float fov = 45.0f;
};

#endif