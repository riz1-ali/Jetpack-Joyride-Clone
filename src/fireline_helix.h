#include "main.h"
#ifndef FIRELINEHELIX_H
#define FIRELINEHELIX_H


class FireLine_Helix {
public:
    FireLine_Helix() {}
    FireLine_Helix(float x, float y, color_t color,float angle);
    glm::vec3 position;
    float speedx,theta;
    void draw(glm::mat4 VP);
    void tick();
    private:
        VAO *object;
};

#endif