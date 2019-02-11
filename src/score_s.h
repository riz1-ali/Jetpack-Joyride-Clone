#include "main.h"

#ifndef SCORES_H
#define SCORES_H


class Score_S {
public:
    Score_S() {}
    Score_S(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    private:
        VAO *object;
};

#endif