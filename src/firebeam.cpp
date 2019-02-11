#include "firebeam.h"

FireBeam::FireBeam(float x,float y,color_t color,int ori)
{
	this->position = glm::vec3(x,y,0);
	this->speedx=0.02;
	this->speedy=0.05;
	this->direction = ori;
	static const GLfloat vertex_buffer_data[] ={
		-0.6f,0.1f,0.0f,
		-0.4f,0.1f,0.0f,
		-0.6f,-0.1f,0.0f,
		-0.4f,0.1f,0.0f,
		-0.6f,-0.1f,0.0f,
		-0.4f,-0.1f,0.0f,
		-0.4f,0.01f,0.0f,
		0.4f,0.01f,0.0f,
		-0.4f,-0.01f,0.0f,
		0.4f,0.01f,0.0f,
		-0.4f,-0.01f,0.0f,
		0.4f,-0.01f,0.0f,
		0.6f,0.1f,0.0f,
		0.4f,0.1f,0.0f,
		0.6f,-0.1f,0.0f,
		0.4f,0.1f,0.0f,
		0.6f,-0.1f,0.0f,
		0.4f,-0.1f,0.0f
	};
	this->object = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, color, GL_FILL);
}

void FireBeam::draw(glm::mat4 VP)
{
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void FireBeam::tick()
{
	this->position.x-=this->speedx;
	if(this->direction)
		this->position.y-=this->speedy;
	else
		this->position.y+=this->speedy;
	if(this->position.y<=-1.3f || this->position.y>=1.8f)
		this->direction=!(this->direction);
}