#ifndef _OPENGLMANAGER_H_
	#define _OPENGLMANAGER_H_

		#include "include/global.h"

		class OpenGLManager 
		{
			public:

				GLFWwindow* window;
				
				OpenGLManager(uint windowWidth, uint windowHeight, char* windowTitle);

				void bind_Buffer_Data(uint* VAO, uint* VBO, uint* EBO, std::vector<Point3d> vertexs, std::vector<int> idxs);
				void bind_Simple_Buffer_Data(uint* VAO, uint* VBO, std::vector<Point3d> vertexs);

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

		void OpenGLManager::bind_Buffer_Data(uint* VAO, uint* VBO, uint* EBO, std::vector<Point3d> vertexs, std::vector<int> idxs)
		{
			glGenVertexArrays(1, VAO);
			glGenBuffers(1, VBO);
			glGenBuffers(1, EBO);

			glBindVertexArray(*VAO);

			glBindBuffer(GL_ARRAY_BUFFER, *VBO);
			glBufferData(GL_ARRAY_BUFFER, vertexs.size() * sizeof(vertexs), &(vertexs.front()), GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, idxs.size() * sizeof(idxs), &(idxs.front()), GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

			glEnableVertexAttribArray(0);
		}

		void  OpenGLManager::bind_Simple_Buffer_Data(uint* VAO, uint* VBO, std::vector<Point3d> vertexs)
		{
			glGenVertexArrays(1, VAO);
			glGenBuffers(1, VBO);

			glBindVertexArray(*VAO);

			glBindBuffer(GL_ARRAY_BUFFER, *VBO);
			glBufferData(GL_ARRAY_BUFFER, vertexs.size() * sizeof(vertexs), &(vertexs.front()), GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

			glEnableVertexAttribArray(0);
		}
#endif
