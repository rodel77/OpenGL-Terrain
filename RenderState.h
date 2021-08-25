#ifndef RENDER_STATE_H
#define RENDER_STATE_H

#include <glm/glm.hpp>
#include <stack>

class RenderState {
    public:
        void push() {
            glm::mat4 last = stack.empty() ? glm::mat4(1.0f) : stack.top();
            stack.push(last);
        }

        std::stack<glm::mat4> stack;
};

#endif