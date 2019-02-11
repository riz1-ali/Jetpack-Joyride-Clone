#include "main.h"

#ifndef RING_H
#define RING_H


class Ring {
public:
    Ring() {}
    Ring(float x, float y, color_t color);
    glm::vec3 position;
    float speedx,speedy,theta,radius,time;
    void draw(glm::mat4 VP);
    void tick();
    private:
        VAO *object;
};

#endif