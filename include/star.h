#ifndef _STAR_H
	#define _STAR_H
    
        #include "picture.h"
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
                                                                                  { 1.25f, 1.0f, 1.25f  }, 1.0f);
                
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
            bool status = false;
            if (current_transform == 0)
                status = star_transformation->make_Translation(current_transform, false);
            else if (current_transform == 1)
                status = star_transformation->make_Rotation(current_transform, 'z');
            else if (current_transform == 2)
                status = star_transformation->make_Translation(current_transform);
            else if (current_transform == 3)
                status = star_transformation->make_Rotation(current_transform, 'z');
            else if (current_transform == 4)
                status = star_transformation->make_Rotation(current_transform, 'x');
            else if (current_transform == 5)
                status = star_transformation->make_Scale(current_transform);
            else if (current_transform == 6)
            {
                std::cout << "*** RESET ***\n";
                star_transformation->reset(vertexes);
                return true;
            }

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
            projection = glm::perspective(glm::radians(45.0f), WINDOW_ASPECT, 0.1f, 100.0f);

            shader->setMat4("model", model);
            shader->setMat4("view", view);
            shader->setMat4("projection", projection);
        }

#endif
