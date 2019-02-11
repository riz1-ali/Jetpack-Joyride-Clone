#include "powerup_cover.h"

Powerup_Cover::Powerup_Cover(float x,float y,color_t color)
{
	this->position = glm::vec3(x,y,0);
	this->speedx=0.015;
	int n=100;
	GLfloat vertex_buffer_data[]={
		0.0f,0.1f,0.0f,
		0.0f,-0.1f,0.0f,
		-0.1f,0.0f,0.0f,

		0.2f,0.1f,0.0f,
		0.2f,-0.1f,0.0f,
		0.3f,0.0f,0.0f
	};
	this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Powerup_Cover::draw(glm::mat4 VP)
{
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Powerup_Cover::tick()
{
	this->position.x-=this->speedx;
	this->position.y=2*sin(6*this->position.x);
}