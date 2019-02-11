#include "main.h"

#ifndef LIVESL_H
#define LIVESL_H


class Lives_L {
public:
    Lives_L() {}
    Lives_L(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    private:
        VAO *object;
};

#endif