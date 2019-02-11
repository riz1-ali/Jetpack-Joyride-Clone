#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y, color_t color);
    glm::vec3 position;
    float speedx,time;
    void draw(glm::mat4 VP);
    void tick(bool flag);
    private:
        VAO *object;
};

#endif