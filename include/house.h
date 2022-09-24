#ifndef _HOUSE_H_
    #define _HOUSE_H_
    
        #include "picture.h"	

        class House : public Picture
        {
            public:

                House();

                void get_Vertexes();
                void get_Idx_Lines();
                void get_Idx_Triangles();

            private:


        };
    
        House::House()
        {
            get_Vertexes();
            get_Idx_Triangles();
        }

        void House::get_Vertexes()
        {
            vertexes =
            {
                -0.4f, -0.6f, 0.0f,
                 0.4f, -0.6f, 0.0f,
                 0.4f,  0.0f, 0.0f,
                 0.9f,  0.0f, 0.0f,
                 0.0f,  0.6f, 0.0f,
                -0.9f,  0.0f, 0.0f,
                -0.4f,  0.0f, 0.0f
            };
            
            size_vertexes = vertexes.size();
        }
        
        void House::get_Idx_Lines()
        {
            std::cout << "No Lines Idx\n";
        }

        void House::get_Idx_Triangles()
        {
            idx_triangles =
            {
                 0, 1, 2,
                 2, 3, 4,
                 2, 4, 6,
                 4, 5, 6,
                 6, 0, 2
            };
            
            size_idx_triangles = idx_triangles.size();
        }
#endif
