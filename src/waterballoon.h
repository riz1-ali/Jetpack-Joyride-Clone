#include "main.h"

#ifndef WATERBALLOON_H
#define WATERBALLOON_H


class Water_Balloon{
	public:
		Water_Balloon(){}
		Water_Balloon(float x,float y,color_t color);
		glm::vec3 position;
		float speedx,speedy,time;
		float y1;
		void draw(glm::mat4 VP);
		void set_position(float x,float y);
		void move_up();
		void tick();
	private:
		VAO *object;
};

#endif