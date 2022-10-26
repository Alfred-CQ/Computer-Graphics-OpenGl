#ifndef _PICTURE_H_
	#define _PICTURE_H_
		
		#include "global.h"
		#include "shader.h"
		#include "math_entities.h"
		
		class Picture 
		{
			public:
				
				/* Attributes */
				vector<uint>		attributes;

				vector<Point<3>>	vertexes; // 0
				vector<float>		colors;   // 1
				vector<float>		texture;  // 2

				/* Indexs and ID's */
				vector<uint> idx_lines;
				vector<uint> idx_triangles;
				
				vector<uint> id_textures;
				
				size_t size_vertexes, size_idx_lines, size_idx_triangles;

				// OpenGL Variables
				uint VAO, VBO, EBO;
				Shader* shader;
				
				Picture();
				~Picture();

				// Setters
				void set_Texture(std::string file_name, uint index_texture, int type = GL_RGB);
				void set_Shader(Shader* shader);

				// Getters
				virtual void get_Vertexes() = 0;
				virtual void get_Idx_Lines() = 0;
				virtual void get_Idx_Triangles() = 0;
				
				virtual void get_Transformation(int i) = 0;

				// Core
				void draw(int primitive);
				void send_Data_Shader();
				void bind_Textures();

				virtual void bind_Transform(bool& enable, int current_transform) = 0;

			protected:

				// Binds
				void bind_Buffers();
				void bind(vector<float>& buffer, uint index_attribute, uint size = 3);

			private:			

				float	location_x, location_y;

		};

		Picture::Picture() 
		{
			for (int i = 0; i < 13; i++)
			{
				attributes.push_back(-1);
				id_textures.push_back(-1);
			}
		}

		Picture::~Picture()
		{
			glDeleteVertexArrays(1, &(this->VAO));
			glDeleteBuffers(1, &(this->VBO));
			glDeleteBuffers(1, &(this->EBO));
		}

		void Picture::set_Texture(std::string file, uint index_texture, int type)
		{
			glGenTextures(1, &(id_textures[index_texture]));
			glBindTexture(GL_TEXTURE_2D, id_textures[index_texture]);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			
			int width, height, nrChannels;

			stbi_set_flip_vertically_on_load(true);

			unsigned char* data = stbi_load(&(file.front()), &width, &height, &nrChannels, 0);
			
			if (data)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, type, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
				std::cout << "Failed to load texture" << std::endl;

			stbi_image_free(data);
		}

		void Picture::set_Shader(Shader* shader)
		{
			this->shader = shader;
		}

		void Picture::draw(int primitive)
		{
			glBindVertexArray(this->VAO);
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
			
			if (primitive == GL_TRIANGLES)
			{
				shader->setFloat4("null_matrix", 1.0f);
				shader->setFloat4("default_colors", 0.0f);
				glDrawElements(GL_TRIANGLES, size_idx_triangles, GL_UNSIGNED_INT, 0);
			}
			else
				glDrawArrays(primitive, 0, this->size_vertexes - 1);
		}

		void Picture::send_Data_Shader()
		{
			shader->use();

			shader->setFloat4("null_matrix", 0.0f);
			shader->setFloat4("default_colors", vertex_colors);

			shader->setMat4("transform", glm::mat4(1.0f));
		}

		void Picture::bind_Textures()
		{
			size_t i = 0;
			while (id_textures[i] != -1)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, id_textures[i]);
				++i;
			}
		}

		void Picture::bind_Buffers()
		{
			glGenVertexArrays(1, &(this->VAO));
			glGenBuffers(1, &(this->VBO));
			glGenBuffers(1, &(this->EBO));

			glBindVertexArray(this->VAO);

			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBufferData(GL_ARRAY_BUFFER, this->size_vertexes * 3 * sizeof(this->vertexes), &(this->vertexes.front()), GL_DYNAMIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->size_idx_triangles * sizeof(this->idx_triangles), &(this->idx_triangles.front()), GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

			glEnableVertexAttribArray(0);
		}

		void Picture::bind(vector<float>& buffer, uint index_attribute, uint size)
		{
			glGenBuffers(1, &(attributes[index_attribute]));
			glBindBuffer(GL_ARRAY_BUFFER, attributes[index_attribute]);
			glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(buffer), &(buffer.front()), GL_STATIC_DRAW);

			glVertexAttribPointer(index_attribute, size, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glEnableVertexAttribArray(index_attribute);
		}

#endif
