#ifndef _STAR_H
	#define _STAR_H
    
        #include "picture.h"	

	    class Star: public Picture
	    {
	    	public:
                
                Star(size_t tips, float in_radius, float out_radius, float location_x = 0.0f, float location_y = 0.0f);

                void get_Vertexes();
                void get_Idx_Lines();
                void get_Idx_Triangles();
                

            private:

                size_t s_tips;
                float  s_inRadius, s_outRadius, s_location_x, s_location_y, s_rotation;

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
        }

	    void Star::get_Vertexes()
	    {
            float useRadius, begin = 0.0f;

            for (int i = 0; i < s_tips; ++i)
            {
                for (int j = 0; j < 2; ++j)
                {
                    useRadius = s_inRadius;

                    if (!(j % 2))
                        useRadius = s_outRadius;

                    vertexes.push_back( { (sin(begin) * useRadius) + s_location_x, (cos(begin) * useRadius) + s_location_y, 0.0f });

                    begin += s_rotation;
                }
            }

            vertexes.push_back( { 0.0f + s_location_x, 0.0f + s_location_y, 0.0f} );

            size_vertexes = vertexes.size();
	    }
        
        void Star::get_Idx_Lines()
        {
            std::cout << "No Lines Idx\n";
        }
        
        void Star::get_Idx_Triangles()
        {
            size_t vertex_idx = (s_tips * 2) - 1, i, j;
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
        
#endif