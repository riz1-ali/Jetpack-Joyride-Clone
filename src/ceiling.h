#include "main.h"
#include "ball.h"

#ifndef CEILING_H
#define CEILING_H

class Ceiling{
	public:
		Ceiling(){}
		Ceiling(float x,float y,color_t color);
		glm::vec3 position;
		void draw(glm::mat4 VP);
		void set_position(float x,float y);
	private:
		VAO *object;
};

#endif