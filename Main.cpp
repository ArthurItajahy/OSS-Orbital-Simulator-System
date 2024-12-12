#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex Shader Source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// Fragment Shader source code
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

	// Verices Coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,// Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,// Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f// Upper corner
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

	// Create Vertex Shader Object and get reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);


	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	GLuint shaderProgram = glCreateProgram();
	
	// Attach the Vertex and Fragment Shader to the Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(shaderProgram);

	// Delete the now useless Vertex and Fragment Shaders Objects

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// Create the reference containers for the Vertex Array Object
	// And the Vertex Buffer Object
	GLuint VAO, VBO;

	// Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Make the VAO the Current Vertex Array Object by binding it
	glBindVertexArray(VAO);
	
	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO 
	// and VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);









	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);//Coloring the background color window with the nice navi blue

	glClear(GL_COLOR_BUFFER_BIT);// Clearing the window.

	glfwSwapBuffers(window); // Now swaps the buffers. 

	while (!glfwWindowShouldClose(window)) { // Loop to make the window still open and don't close imedially. 

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Tell OpenGL which Shader Program we want to use
		glUseProgram(shaderProgram);
		// Bind the VAO so OpenGL know to use it
		glBindVertexArray(VAO);

		// Draw the triangle using GL_TRIANGLES
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