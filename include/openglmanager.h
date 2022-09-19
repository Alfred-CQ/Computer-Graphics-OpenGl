#ifndef _OPENGLMANAGER_H_
	#define _OPENGLMANAGER_H_
	
		#include <glad/glad.h>
		#include <GLFW/glfw3.h>

		#include <iostream>
		
		void framebuffer_size_callback(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		class OpenGLManager 
		{
			public:

				GLFWwindow* window;
				OpenGLManager(unsigned int screenWidth, unsigned int screenHeight)
				{
					SCR_WIDTH = screenWidth;
					SCR_HEIGHT = screenHeight;

					glfwInit();
					set_GLFW_Context();
					set_Window();

				}

			private:
				unsigned int SCR_WIDTH, SCR_HEIGHT;

				void set_GLFW_Context()
				{
					glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
					glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
					glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
				}

				void set_Window()
				{
					window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Chillitupa Quispihuanca Alfred", NULL, NULL);

					if (window == NULL)
					{
						std::cout << "Failed to create GLFW window" << std::endl;
						glfwTerminate();
						exit(-1);
					}

					glfwMakeContextCurrent(window);
					glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
					//glfwSetKeyCallback(window, key_callback);
					if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
					{
						std::cout << "Failed to initialize GLAD" << std::endl;
						exit(-1);
					}
				}
		};

#endif
