#include "gate.h"

Gate::Gate(float x,float y,color_t color)
{
	this->position = glm::vec3(x,y,0);
	this->speedx=0.05;
	static const GLfloat vertex_buffer_data[] ={
		-1.0f,3.246f,0.0f,
		1.0f,3.246f,0.0f,
		-1.0f,-2.5f,0.0f,
		1.0f,3.246f,0.0f,
		-1.0f,-2.5f,0.0f,
		1.0f,-2.5f,0.0f,
	};
	this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Gate::draw(glm::mat4 VP)
{
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Gate::tick()
{
	this->position.x-=this->speedx;
}