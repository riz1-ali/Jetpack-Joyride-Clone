#include "main.h"

#ifndef JET_H
#define JET_H


class Jet {
public:
    Jet() {}
    Jet(float x, float y, color_t color);
    glm::vec3 position;
    float speedx;
    void draw(glm::mat4 VP);
    void tick();
    private:
        VAO *object;
};

#endif