#include "main.h"
#ifndef FIRELINE_H
#define FIRELINE_H


class FireLine {
public:
    FireLine() {}
    FireLine(float x, float y, color_t color,float angle);
    glm::vec3 position;
    float speedx;
    float theta;
    float minx,maxx,miny,maxy;
    void draw(glm::mat4 VP);
    void tick();
    private:
        VAO *object;
};

#endif