#include "main.h"

#ifndef FIREBEAM_H
#define FIREBEAM_H


class FireBeam {
public:
    FireBeam() {}
    FireBeam(float x, float y, color_t color,int ori);
    glm::vec3 position;
    float speedx,speedy;
    int direction;
    void draw(glm::mat4 VP);
    void tick();
    private:
        VAO *object;
};

#endif