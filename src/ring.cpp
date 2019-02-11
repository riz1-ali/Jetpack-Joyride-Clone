#include "ring.h"

Ring::Ring(float x,float y,color_t color)
{
	this->position = glm::vec3(x,y,0);
	this->speedx=0.01;
	int n=10000;
	this->theta=-(180/((float)n))*((3.14159265359)/180);
	GLfloat vertex_buffer_data[18*n];
	vertex_buffer_data[0]=-0.6f,vertex_buffer_data[1]=0.0f,vertex_buffer_data[2]=0.0f;
	vertex_buffer_data[3]=-0.59f,vertex_buffer_data[4]=0.0f,vertex_buffer_data[5]=0.0f;
	vertex_buffer_data[6]=-0.6f,vertex_buffer_data[7]=0.01f,vertex_buffer_data[8]=0.0f;
	vertex_buffer_data[9]=-0.59f,vertex_buffer_data[10]=0.0f,vertex_buffer_data[11]=0.0f;
	vertex_buffer_data[12]=-0.6f,vertex_buffer_data[13]=0.01f,vertex_buffer_data[14]=0.0f;
	vertex_buffer_data[15]=-0.59f,vertex_buffer_data[16]=0.01f,vertex_buffer_data[17]=0.0f;
	for(int i=18;i<18*n;i+=3)
	{
		float x=vertex_buffer_data[i-18],y=vertex_buffer_data[i-17];
		vertex_buffer_data[i+2]=vertex_buffer_data[i-16];
		vertex_buffer_data[i]=x*cos(this->theta)-y*sin(this->theta);
		vertex_buffer_data[i+1]=y*cos(this->theta)+x*sin(this->theta);
	}
	this->object = create3DObject(GL_TRIANGLES, 2*n*3, vertex_buffer_data, color, GL_FILL);
}

void Ring::draw(glm::mat4 VP)
{
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ring::tick()
{
	this->position.x-=this->speedx;
}