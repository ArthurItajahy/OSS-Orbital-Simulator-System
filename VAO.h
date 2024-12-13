#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO {
	public:
		GLuint ID;
		VAO();
		
		void LinkVBO(VBO VBO, GLuint layout);
		void Bind();
		void Unvind();
		void Delete();
};

#endif