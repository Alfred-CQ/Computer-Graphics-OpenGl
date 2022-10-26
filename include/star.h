#ifndef _STAR_H
	#define _STAR_H
    
        #include "picture.h"
        #include "matrix.h"	

	    class Star: public Picture
	    {
	    	public:

                Star(size_t tips, float in_radius, float out_radius, float location_x = 0.0f, float location_y = 0.0f);

                void get_Vertexes();
                void get_Idx_Lines();
                void get_Idx_Triangles();
                void get_Transformation(int i);

                void bind_Transform(bool& enable, int current_transform);

            private:

                uint s_tips;
                float  s_inRadius, s_outRadius, s_location_x, s_location_y, s_rotation;

                Matrix<4,4>* X_Rotation_Matrix  = new Matrix<4,4>(50.0f, 'x');
                Matrix<4,4>* Z_Rotation_Matrix  = new Matrix<4,4>(63.0f, 'z');
                Matrix<4,4>* Translation_Matrix = new Matrix<4,4>(0.2f, 0.35f, 0.175f, 'T');
                Matrix<4,4>* Scale_Matrix       = new Matrix<4,4>(1.25f, 1.0f, 1.25f, 'S');
                
                Matrix<4, 11>* vertex_Matrix = nullptr;
                Matrix<4, 4> transform;

                vector<Matrix<4, 4>>    history_transformation;
                vector<Point<3>>        vertexes_transform;
                
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

            for (size_t i = 0; i < 10; i++)
                history_transformation.push_back(Matrix<4,4>(0.0f, 0.0f, 0.0f, 'T'));
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

            vertexes_transform = vertexes;
            vertex_Matrix = new Matrix<4, 11>(vertexes);

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
        
        void Star::get_Transformation(int current_transform)
        {
            if (current_transform == 0)
            { 
                Matrix<4,4> identy(0.0f, 0.0f, 0.0f, 'T');
                transform = (*Translation_Matrix) * identy;
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
            history_transformation[current_transform] = transform;
            get_Vertexes_Transform(history_transformation[current_transform] * (*vertex_Matrix), vertexes_transform);
            transform.print();
            
        }

        void Star::bind_Transform(bool& enable, int current_transform)
        {
            if (enable_transformation)
            {
                get_Transformation(current_transform);
                glBufferData(GL_ARRAY_BUFFER, vertexes_transform.size() * 3 * sizeof(vertexes_transform), &(vertexes_transform.front()), GL_DYNAMIC_DRAW);
                enable_transformation = false;
            }
        }

#endif
