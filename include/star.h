#ifndef _STAR_H
	#define _STAR_H
    
        #include "picture.h"
        #include "matrix.h"	
        #include "transformations.h"

	    class Star: public Picture
	    {
	    	public:

                Star(size_t tips, float in_radius, float out_radius, float location_x = 0.0f, float location_y = 0.0f);

                void get_Vertexes();
                void get_Idx_Lines();
                void get_Idx_Triangles();
                bool get_Local_Transformation(int current_transform);

                void bind_Transform(bool& enable, int current_transform);

                void send_VShader_Transform();

            private:

                uint s_tips;
                float  s_inRadius, s_outRadius, s_location_x, s_location_y, s_rotation;
                
                Transformation<11>* star_transformation = new Transformation<11> (50.0f, 0.0f, 63.0f,
                                                                                  { 0.2f, 0.35f, 0.175f }, 
                                                                                  { 1.25f, 1.0f, 1.25f  });
                
	    };
        
        Star::Star(size_t tips, float in_radius, float out_radius, float location_x, float location_y)
        {
            s_tips = tips;
            s_inRadius = in_radius;
            s_outRadius = out_radius;
            s_rotation = F_PI / s_tips;
            s_location_x = location_x;
            s_location_y = location_y;
            
            get_Vertexes();
            get_Idx_Triangles();
            
            bind_Buffers();
            // Texture
            bind(texture, 2, 2); // [2] texture attribute
            set_Texture(root_path + "textures\\container.jpg", 0);

        }

	    void Star::get_Vertexes()
	    {
            float useRadius, begin = 0.0f, x_value, y_value;

            for (int i = 0; i < s_tips; ++i)
            {
                for (int j = 0; j < 2; ++j)
                {
                    useRadius = s_inRadius;

                    if (!(j % 2))
                        useRadius = s_outRadius;
                    
                    x_value = sin(begin) * useRadius + s_location_x;
                    y_value = cos(begin) * useRadius + s_location_y;

                    vertexes.push_back( { x_value,  y_value, 0.0f });

                    texture.push_back((x_value * 0.5) + 0.5);
                    texture.push_back((y_value * 0.5) + 0.5);

                    begin += s_rotation;
                }
            }

            vertexes.push_back( { 0.0f + s_location_x, 0.0f + s_location_y, 0.0f} );
            
            texture.push_back((0.0f + s_location_x) * 0.5 + 0.5);
            texture.push_back((0.0f + s_location_y) * 0.5 + 0.5);

            star_transformation->copy_Vertexes(vertexes);

            size_vertexes = vertexes.size();
	    }
        
        void Star::get_Idx_Lines()
        {
            std::cout << "No Lines Idx\n";
        }
        
        void Star::get_Idx_Triangles()
        {
            uint vertex_idx = (s_tips * 2) - 1, i, j;
            for (i = 1; i <= s_tips * 3; ++i)
            {
                idx_triangles.push_back(vertex_idx);
                if ((i % 3))
                    vertex_idx = (vertex_idx + 1) % 10;
            }

            for (i = 1, j = 0; j < s_tips; ++j, i += 2)
            {
                idx_triangles.push_back(i);
                idx_triangles.push_back((i + 2) % (s_tips * 2));
                idx_triangles.push_back(s_tips * 2);
            }

            size_idx_triangles = idx_triangles.size();
        }
        
        bool Star::get_Local_Transformation(int current_transform)
        {
            bool status;
            if (current_transform == 0)
            {
                status = star_transformation->make_Translation(current_transform);
            }

            /*
            if (current_transform == 0)
            { 
                float prev1 = Translation_Matrix->matrix[0][4 - 1];
                float prev2 = Translation_Matrix->matrix[1][4 - 1];
                float prev3 = Translation_Matrix->matrix[2][4 - 1];

                float norm = sqrt((0.2f * 0.2f) + (0.35f * 0.35f) + (0.175f * 0.175f)) * beg;
                std::cout << "NORM: " << Translation_Matrix->matrix[0][4 - 1] << " * " << norm << "\n";
                Translation_Matrix->matrix[0][4 - 1] *= norm;
                Translation_Matrix->matrix[1][4 - 1] *= norm;
                Translation_Matrix->matrix[2][4 - 1] *= norm;

                Matrix<4,4> identy(1.0f, 1.0f, 1.0f, 'S');
                identy.print();
                transform = (*Translation_Matrix) * identy;
                beg++;
                Translation_Matrix->matrix[0][4 - 1] = prev1;
                Translation_Matrix->matrix[1][4 - 1] = prev2;
                Translation_Matrix->matrix[2][4 - 1] = prev3;
                
            }     
            else if (current_transform == 1)
                transform = (history_transformation[current_transform - 1]) * (*Z_Rotation_Matrix);
            else if (current_transform == 2)
                transform = (history_transformation[current_transform - 1]) * (*Translation_Matrix);
            else if (current_transform == 3)
                transform = (history_transformation[current_transform - 1]) * (*Z_Rotation_Matrix);
            else if (current_transform == 4)
                transform = (history_transformation[current_transform - 1]) * (*X_Rotation_Matrix);
            else if (current_transform == 5)
                transform = (history_transformation[current_transform - 1]) * (*Scale_Matrix);
            else if (current_transform == 6)
            {
                std::cout << "*** RESET ***\n";
                vertexes_transform = vertexes;
                return;
            }

            std::cout << "\n***" << current_transform << " ***\n";
           // history_transformation[current_transform] = transform;
            
            //transform.print();*/
            return status;
        }

        void Star::bind_Transform(bool& enable, int current_transform)
        {
            if (enable_transformation)
            {
                bool keep = get_Local_Transformation(current_transform);
                glBufferData(GL_ARRAY_BUFFER, star_transformation->vertexes_transform.size() * 3 * sizeof(star_transformation->vertexes_transform), &(star_transformation->vertexes_transform.front()), GL_DYNAMIC_DRAW);
                if (keep)
                    enable_transformation = false;
                
            }
        }

        void Star::send_VShader_Transform()
        {
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 projection = glm::mat4(1.0f);

            model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.5f));
            projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);

            shader->setMat4("model", model);
            shader->setMat4("view", view);
            shader->setMat4("projection", projection);
        }

#endif
