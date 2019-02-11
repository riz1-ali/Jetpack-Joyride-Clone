#include "waterballoon.h"
using namespace std;

Water_Balloon::Water_Balloon(float x,float y,color_t color){
	this->position = glm::vec3(x,y,0);
	this->y1=y;
	int n=100;
	GLfloat vertex_buffer_data[9*n];
	int flag=0;
	this->speedx=0.05;
	this->speedy=8;
	float k=1,pi=3.1415,dn=n;
	for(int i=0;i<9*n;i+=3)
	{
		if(flag==0)
		{
			vertex_buffer_data[i]=0.0f;
			vertex_buffer_data[i+1]=0.0f;
			vertex_buffer_data[i+2]=0.0f;	
			flag=1;
		}
		else if(flag==1)
		{
			vertex_buffer_data[i]=0.1*cos((pi*2*k)/dn);
			vertex_buffer_data[i+1]=0.1*sin((pi*2*k)/dn);
			vertex_buffer_data[i+2]=0.0f;
			flag=2;
		}
		else
		{
			float x;
			k==1?x=n:x=k-1;
			vertex_buffer_data[i]=0.1*cos((pi*2*x)/dn);
			vertex_buffer_data[i+1]=0.1*sin((pi*2*x)/dn);
			vertex_buffer_data[i+2]=0.0f;
			k++;
			flag=0;
		}
	}
	this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
}

void Water_Balloon::draw(glm::mat4 VP)
{
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
void Water_Balloon::tick()
{
	this->position.x+=this->speedx;
	float time = glfwGetTime() - this->time;
	this->position.y=this->y1 + this->speedy*(time) - 7.9*time*time;
}