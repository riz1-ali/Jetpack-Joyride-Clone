#include "main.h"

#ifndef POWERUP_H
#define POWERUP_H


class Powerup {
public:
    Powerup() {}
    Powerup(float x, float y, color_t color,int ori,string type,int value);
    glm::vec3 position;
    float speedx;
    int direction,val;
    string base;
    void draw(glm::mat4 VP);
    void tick();
    private:
        VAO *object;
};

#endif