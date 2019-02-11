#include "coin.h"

Coin::Coin(float x,float y,color_t color,int score){
	this->position = glm::vec3(x,y,0);
	int n=100;
	GLfloat vertex_buffer_data[9*n];
	int flag=0;
	this->speedx=0.05;
	float k=1,pi=3.1415,dn=n;
	this->score=score;
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
	this->object = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_data, color, GL_FILL);
}

void Coin::draw(glm::mat4 VP)
{
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Coin::tick()
{
	this->position.x-=this->speedx;
}