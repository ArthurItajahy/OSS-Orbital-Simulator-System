#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main()
{

	//Starting to create the window.
	glfwInit();// we inicialized the function

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // the verion of glf
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Also for the minor
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // package of functions

	GLFWwindow* window = glfwCreateWindow(800, 800, "OSS-Orbital Simulator System", NULL, NULL);// Parameter to create the window.
	if (window == NULL)// Just in case failed to created the window
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); //Created the window and Show.

	gladLoadGL();

	glViewport(0, 0, 800, 800);

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);//Coloring the window with the nice navi blue

	glClear(GL_COLOR_BUFFER_BIT);// Clearing the window.

	glfwSwapBuffers(window); // Now swaps the buffers. 

	while (!glfwWindowShouldClose(window)) { // Loop to make the window still open and don't close imedially. 

		glfwPollEvents();//TO be able to interact with the window and close.
	}

	glfwDestroyWindow(window); // Terminate the window.


	glfwTerminate(); // But also Terminate the function in the end of the code.
	return 0;
}