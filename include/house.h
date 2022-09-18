#ifndef _HOUSE_H
    #define _HOUSE_H
    
    #include <glad/glad.h>
    
    #include <iostream>
    #include <string>
    #include <vector>
    
    using std::vector;
    
    class House
    {
        public:

            const size_t sizeVertexs = 21, sizeTriangles = 15;

            float verticesHouse[21] = { 
                -0.4f, -0.6f, 0.0f, 
                 0.4f, -0.6f, 0.0f,
                 0.4f,  0.0f, 0.0f,
                 0.9f,  0.0f, 0.0f,
                 0.0f,  0.6f, 0.0f,
                -0.9f,  0.0f, 0.0f,
                -0.4f,  0.0f, 0.0f,                 
            };

            unsigned int idxHouseTriangles[15] = {
                0, 1, 2,
                2, 3, 4,
                2, 4, 6,
                4, 5, 6,
                6, 0, 2 
            };

            House()
            {
                std::cout << " Hello";
            }
            
    
        private:
    
            
    
    };
    
#endif