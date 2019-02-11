#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation,time;
    int up,down,lives,score,immune;
    float speed,speedx,gravity;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void move_up();
    void tick(bool &flag);
private:
    VAO *object;
};

#endif // BALL_H
