#include "fireline.h"
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair

FireLine::FireLine(float x,float y,color_t color,float angle)
{
	this->position = glm::vec3(x,y,0);
	this->speedx=0.04;
	// srand(time(NULL));
	// this->theta = 15+(rand()%(59-15+1)); // between 15 and 75
	// this->theta = (this->theta*3.14159265359)/180;
	this->theta = angle;
	GLfloat vertex_buffer_data[] ={
		-0.4f,0.01f,0.0f,
		0.4f,0.01f,0.0f,
		-0.4f,-0.01f,0.0f,
		0.4f,0.01f,0.0f,
		-0.4f,-0.01f,0.0f,
		0.4f,-0.01f,0.0f,
	};
	for(int i=0;i<18;i+=3)
	{
		float x=vertex_buffer_data[i],y=vertex_buffer_data[i+1];
		vertex_buffer_data[i]=x*cos(this->theta)-y*sin(this->theta);
		vertex_buffer_data[i+1]=y*cos(this->theta)+x*sin(this->theta);
	}
	this->minx=vertex_buffer_data[0],this->maxx=vertex_buffer_data[15];
	this->miny=vertex_buffer_data[7],this->maxy=vertex_buffer_data[4];
	this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void FireLine::draw(glm::mat4 VP)
{
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void FireLine::tick()
{
	this->position.x-=this->speedx;
}