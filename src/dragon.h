#include "main.h"

#ifndef DRAGON_H
#define DRAGON_H


class Dragon {
public:
    Dragon() {}
    Dragon(float x, float y, color_t color);
    glm::vec3 position;
    float speedx,speedy,time,iceball_time;
    int shoot;
    void draw(glm::mat4 VP);
    void tick();
    private:
        VAO *object;
};

#endif