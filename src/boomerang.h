#include "main.h"

#ifndef BOOMERANG_H
#define BOOMERANG_H


class Boomerang {
public:
    Boomerang() {}
    Boomerang(float x, float y, color_t color);
    glm::vec3 position;
    float speedx,speedy,time;
    int theta;
    void draw(glm::mat4 VP);
    void tick(bool flag);
    private:
        VAO *object;
};

#endif