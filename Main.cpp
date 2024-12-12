#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main()
{

	//Starting to create the window.
	glfwInit();// we inicialized the function

	// Telling GLFW he is using OPENGL 3.3 version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Telling GLFW he is using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
	};

	GLFWwindow* window = glfwCreateWindow(800, 800, "OSS-Orbital Simulator System", NULL, NULL);// Parameter to create the window.
	if (window == NULL)// Just in case failed to created the window
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); //Created the window and Show.

	gladLoadGL();// Load GLAD so it configures OpenGL

	// Specify the viewport of OpenGL in the window
	// In this case the viewport goes from x = 0, y=0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);


	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// Creating a vertex BUFFERS.

	GLuint VAO, VBO;

	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);









	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);//Coloring the background color window with the nice navi blue

	glClear(GL_COLOR_BUFFER_BIT);// Clearing the window.

	glfwSwapBuffers(window); // Now swaps the buffers. 

	while (!glfwWindowShouldClose(window)) { // Loop to make the window still open and don't close imedially. 

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);//Coloring the background color window with the nice navi blue

		glClear(GL_COLOR_BUFFER_BIT);// Clearing the window.

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window); // Now swaps the buffers. 


		glfwPollEvents();//TO be able to interact with the window and close.
	}

	// DELETE ALL THE OBJECTS CREATED SO FAR.

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window); // Terminate the window.


	glfwTerminate(); // But also Terminate the function in the end of the code.
	return 0;
}