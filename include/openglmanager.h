#ifndef _OPENGLMANAGER_H_
	#define _OPENGLMANAGER_H_

		#include "include/global.h"
		#include "picture.h"

		class OpenGLManager 
		{
			public:

				GLFWwindow* window;
				
				OpenGLManager(uint windowWidth, uint windowHeight, char* windowTitle);
				~OpenGLManager();

				void bind_Buffer_Data(uint* VAO, uint* VBO, uint* EBO, Picture* picture);
				void bind_Simple_Buffer_Data(uint* VAO, uint* VBO, std::vector<Point<3>>* vertexs);

				void update_Buffer(uint* VAO, uint* VBO, std::vector<Point<3>>* vertexs);	

				// Utils
				bool close();
				void listen_buffers_and_Events();
				
			private:

				uint windowWidth, windowHeight;
				char* windowTitle;

				void set_GLFW_Context();
				void set_Window();				
		};

		OpenGLManager::OpenGLManager(uint screenWidth, uint screenHeight, char* windowTitle)
		{
			this->windowWidth  = screenWidth;
			this->windowHeight = screenHeight;
			this->windowTitle  = windowTitle;

			glfwInit();

			set_GLFW_Context();
			set_Window();
		}

		OpenGLManager::~OpenGLManager()
		{
			glfwTerminate();
		}

		void OpenGLManager::set_GLFW_Context()
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		}

		void OpenGLManager::set_Window()
		{
			window = glfwCreateWindow(windowWidth,windowHeight, windowTitle, NULL, NULL);

			if (window == NULL)
			{
				std::cout << "Failed to create GLFW window" << std::endl;
				glfwTerminate();
				exit(-1);
			}

			glfwMakeContextCurrent(window);

			glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
			glfwSetKeyCallback(window, key_callback);

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cout << "Failed to initialize GLAD" << std::endl;
				exit(-1);
			}
		}

		void OpenGLManager::update_Buffer(uint* VAO, uint* VBO, std::vector<Point<3>>* vertexs)
		{
			glBindVertexArray(*VAO);
			glBindBuffer(GL_ARRAY_BUFFER, *VBO);
			glBufferData(GL_ARRAY_BUFFER, vertexs->size() * 3 * sizeof(vertexs), &(vertexs->front()), GL_DYNAMIC_DRAW);
		}

		bool OpenGLManager::close()
		{
			return glfwWindowShouldClose(this->window);
		}

		void OpenGLManager::listen_buffers_and_Events()
		{
			glfwSwapBuffers(this->window);
			glfwPollEvents();
		}

#endif
