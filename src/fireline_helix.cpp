#include "fireline_helix.h"
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair

FireLine_Helix::FireLine_Helix(float x,float y,color_t color,float angle)
{
	this->position = glm::vec3(x,y,0);
	this->speedx=0.04;
	this->theta = angle;
	GLfloat vertex_buffer_data[] ={		
		-0.45f,-0.0866f,0.0f,
		-0.55f,-0.0866f,0.0f,
		-0.4f,0.0f,0.0f,
		-0.55f,-0.0866f,0.0f,
		-0.6f,0.0f,0.0f,
		-0.4f,0.0f,0.0f,
		-0.6f,0.0f,0.0f,
		-0.4f,0.0f,0.0f,
		-0.55f,0.0866f,0.0f,
		-0.4f,0.0f,0.0f,
		-0.55f,0.0866f,0.0f,
		-0.45f,0.0866f,0.0f,

		0.45f,-0.0866f,0.0f,
		0.55f,-0.0866f,0.0f,
		0.4f,0.0f,0.0f,
		0.55f,-0.0866f,0.0f,
		0.6f,0.0f,0.0f,
		0.4f,0.0f,0.0f,
		0.6f,0.0f,0.0f,
		0.4f,0.0f,0.0f,
		0.55f,0.0866f,0.0f,
		0.4f,0.0f,0.0f,
		0.55f,0.0866f,0.0f,
		0.45f,0.0866f,0.0f,
	};
	for(int i=0;i<72;i+=3)
	{
		float x=vertex_buffer_data[i],y=vertex_buffer_data[i+1];
		vertex_buffer_data[i]=x*cos(this->theta)-y*sin(this->theta);
		vertex_buffer_data[i+1]=y*cos(this->theta)+x*sin(this->theta);
	}
	this->object = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data, color, GL_FILL);
}

void FireLine_Helix::draw(glm::mat4 VP)
{
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void FireLine_Helix::tick()
{
	this->position.x-=this->speedx;
}