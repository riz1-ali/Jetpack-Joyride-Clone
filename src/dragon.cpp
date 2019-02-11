#include "dragon.h"

Dragon::Dragon(float x,float y,color_t color)
{
	this->position = glm::vec3(x,y,0);
	this->speedx=0.05;
	this->shoot=0;
    GLfloat vertex_buffer_data[]={
    	0.15f,0.01f,0.0f,
    	0.1f,0.1f,0.0f,
    	0.2f,0.1f,0.0f,

    	0.35f,0.01f,0.0f,
    	0.3f,0.1f,0.0f,
    	0.4f,0.1f,0.0f,

    	0.15f,-0.01f,0.0f,
    	0.1f,-0.1f,0.0f,
    	0.2f,-0.1f,0.0f,
    	
    	0.35f,-0.01f,0.0f,
    	0.3f,-0.1f,0.0f,
    	0.4f,-0.1f,0.0f,

    	0.05f,0.15f,0.0f,
    	0.05f,0.1f,0.0f,    	
    	0.5f,0.15f,0.0f,

		0.5f,0.1f,0.0f,
    	0.05f,0.1f,0.0f,    	
    	0.5f,0.15f,0.0f,

    	0.05f,-0.15f,0.0f,
    	0.05f,-0.1f,0.0f,    	
    	0.5f,-0.15f,0.0f,

		0.5f,-0.1f,0.0f,
    	0.05f,-0.1f,0.0f,    	
    	0.5f,-0.15f,0.0f,
    
    	0.5f,0.15f,0.0f,
    	0.5f,-0.15f,0.0f,
    	0.6f,-0.15f,0.0f,

    	0.5f,0.15f,0.0f,
    	0.6f,0.15f,0.0f,
    	0.6f,-0.15f,0.0f
    };
    this->object = create3DObject(GL_TRIANGLES, 10*3, vertex_buffer_data, color, GL_FILL);
}

void Dragon::draw(glm::mat4 VP)
{
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Dragon::tick()
{
	this->position.x-=this->speedx;
    this->position.x=max(this->position.x,2.8f);
	if(glfwGetTime() - this->iceball_time > 3)
	{
		this->iceball_time=glfwGetTime();
		this->shoot=1;
	}
	else
		this->shoot=0;
}