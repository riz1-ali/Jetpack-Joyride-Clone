#include "boomerang.h"

Boomerang::Boomerang(float x,float y,color_t color)
{
	this->position = glm::vec3(x,y,0);
	this->speedx=0.05;
	this->speedy=0.03;
	this->theta=23;
    GLfloat vertex_buffer_data[]={
    	0.2f,0.2f,0.0f,
    	0.0f,0.0f,0.0f,
    	0.0f,-0.2f,0.0f,
    	0.0f,0.0f,0.0f,
    	0.0f,-0.2f,0.0f,
    	-0.2f,0.2f,0.0f
    };
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP)
{
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate    = glm::rotate((float) (this->theta * 3.14159 / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Boomerang::tick(bool flag)
{
	if(!flag)
		this->position.x-=this->speedx;
	else
	{
		this->position.y-=this->speedy;
		this->theta=(this->theta + 23)%360;
		this->position.x=this->position.y*this->position.y-this->position.y-3;
	}
}