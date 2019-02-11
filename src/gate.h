#include "main.h"

#ifndef GATE_H
#define GATE_H


class Gate {
public:
    Gate() {}
    Gate(float x, float y, color_t color);
    glm::vec3 position;
    float speedx;
    int direction;
    void draw(glm::mat4 VP);
    void tick();
    private:
        VAO *object;
};

#endif