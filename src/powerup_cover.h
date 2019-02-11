#include "main.h"

#ifndef POWERUPCOVER_H
#define POWERUPCOVER_H


class Powerup_Cover {
public:
    Powerup_Cover() {}
    Powerup_Cover(float x, float y, color_t color);
    glm::vec3 position;
    float speedx;
    void draw(glm::mat4 VP);
    void tick();
    private:
        VAO *object;
};

#endif