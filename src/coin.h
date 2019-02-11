#include "main.h"

#ifndef COIN_H
#define COIN_H

class Coin{
	public:
		Coin(){}
		Coin(float x,float y,color_t color,int score);
		glm::vec3 position;
		float speedx;
		int score;
		void draw(glm::mat4 VP);
		void set_position(float x,float y);
		void tick();
	private:
		VAO *object;
};

#endif