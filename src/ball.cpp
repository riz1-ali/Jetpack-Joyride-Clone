#include "ball.h"
#include "main.h"
#include<bits/stdc++.h>
using namespace std;
Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->time =0;
    this->up=0;
    this->down=0;
    this->lives=3;
    this->speed = 0.05;
    this->speedx=0;
    this->gravity = 1;
    this->score=0;
    this->immune=0;
    static const GLfloat vertex_buffer_data[] = {
		0.2f,0.2f,0.0f,
		0.2f,-0.2f,0.0f,
		-0.2f,0.2f,0.0f,
		-0.2f,0.2f,0.0f,
        0.2f,-0.2f,0.0f,
   		-0.2f,-0.2f,0.0f
   	};
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // Matrices.model *= (translate * rotate);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::move_up(){
	this->up=1;
	this->speed+=1;
	this->time=glfwGetTime();
}

void Ball::tick(bool &flag) {
    if(!this->immune)
    {
    	if(glfwGetTime() - this->time >= 0.20 and this->position.y > -2.3 && this->down)
    	{
    		this->position.y-=0.25*(glfwGetTime() - this->time)*(glfwGetTime() - this->time);
    		this->up=0;
    	}
        if(glfwGetTime() - this->time <0.20 and this->position.y < 3.5 && this->up)
        {
        	this->position.y+=(1-0.25*(0.2- (glfwGetTime() - this->time)))*(0.2- (glfwGetTime() - this->time));
        	this->down=0;
        }
        if(glfwGetTime() - this->time >0.2)
        	this->up=0,this->down=1;
        this->position.x+=this->speedx;
        this->position.y=min(max(this->position.y,-2.3f),3.046f);
        this->position.x=min(3.5f,max(-3.3f,this->position.x));
    }
    else if(flag)
    {
        this->position.x+=this->speedx;
        if(0.6*0.6 - this->position.x*this->position.x >=0.000003f)
            this->position.y=sqrtf((0.6*0.6-(this->position.x*this->position.x)));
        else
        {
            this->immune=0;
            this->speedx-=0.001;
            // this->position.y-=0.1;
            this->up=0,this->down=1;
            this->time=glfwGetTime()-0.2;
            flag=0;
        }
    }
}