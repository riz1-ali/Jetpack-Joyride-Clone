#include "main.h"

#ifndef ICEBALL_H
#define ICEBALL_H


class IceBall {
public:
    IceBall() {}
    IceBall(float x, float y, color_t color);
    glm::vec3 position;
    float speedx,speedy,time;
    void draw(glm::mat4 VP);
    void tick();
    private:
        VAO *object;
};

#endif