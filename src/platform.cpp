#include "platform.h"

Platform::Platform(float x,float y,color_t color){
	this->position = glm::vec3(x,y,0);
	static const GLfloat vertex_buffer_data[] ={
		-1e18,1,0,
		-1e18,-1e18,0,
		1e18,1,0,
		-1e18,-1e18,0,
		1e18,1,0,
		1e18,-1e18,0
	};
	this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
};

void Platform::draw(glm::mat4 VP)
{
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}