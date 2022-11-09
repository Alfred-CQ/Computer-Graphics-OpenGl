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
                bool get_Local_Transformation(int i);
                void get_World_Positions();

                void draw_Houses();

                void bind_Transform(bool& enable, int current_transform);

                void send_VShader_Transform();

            private:
                
                vector<glm::vec3> house_Positions;
        };
    
        House::House()
        {
            get_Vertexes();
            get_Idx_Triangles();
            get_World_Positions();

            bind_Buffers();
            bind(colors, 1);
        }

        void House::get_Vertexes()
        {
            vertexes =
            {
              { -0.4f, -0.6f, 0.0f }, // 0
              {  0.4f, -0.6f, 0.0f }, // 1
              {  0.4f,  0.0f, 0.0f }, // 2
              {  0.9f,  0.0f, 0.0f }, // 3
              {  0.0f,  0.6f, 0.0f }, // 4
              { -0.9f,  0.0f, 0.0f }, // 5
              { -0.4f,  0.0f, 0.0f }, // 6
              {  0.0f,  0.0f, 0.0f }, // 7
                
              { -0.4f, -0.6f, -0.5f }, // 8
              {  0.4f, -0.6f, -0.5f }, // 9
              {  0.4f,  0.0f, -0.5f }, // 10
              {  0.9f,  0.0f, -0.5f }, // 11
              {  0.0f,  0.6f, -0.5f }, // 12
              { -0.9f,  0.0f, -0.5f }, // 13
              { -0.4f,  0.0f, -0.5f }, // 14
              {  0.0f,  0.0f, -0.5f }, // 15

            };

            colors = 
            {
                 1.0f, 0.0f, 0.0f,
                 0.0f, 1.0f, 0.0f,
                 0.0f, 0.0f, 1.0f,
                 0.0f, 1.0f, 0.0f,
                 1.0f, 0.0f, 0.0f,
                 0.0f, 1.0f, 0.0f,
                 0.0f, 0.0f, 1.0f,
                 0.0f, 1.0f, 0.0f,

                 1.0f, 0.0f, 0.0f,
                 0.0f, 1.0f, 0.0f,
                 0.0f, 0.0f, 1.0f,
                 0.0f, 1.0f, 0.0f,
                 1.0f, 0.0f, 0.0f,
                 0.0f, 1.0f, 0.0f,
                 0.0f, 0.0f, 1.0f,
                 0.0f, 1.0f, 0.0f
            };
            
            size_vertexes = GLsizei(vertexes.size());
        }
        
        void House::get_Idx_Lines()
        {
            std::cout << "No Lines Idx\n";
        }

        void House::get_Idx_Triangles()
        {
            idx_triangles =
            {
                 0 , 1 , 2 ,
                 2 , 3 , 4 ,
                 2 , 4 , 6 ,
                 4 , 5 , 6 ,
                 6 , 0 , 2 ,

                  8,  9, 10,
                 10, 11, 12,
                 10, 12, 14,
                 12, 13, 14,
                 14,  8, 10,

                  1,  9, 10,
                  1, 10,  2,
                  0,  8, 14,
                  0, 14,  6,

                  3, 11, 10,
                  3, 10,  2,
                  5, 13, 14,
                  5, 14,  6,

                  3, 11, 12,
                  3, 12,  4,
                  4, 12, 13,
                  4, 13,  5
            };
            
            size_idx_triangles = GLsizei(idx_triangles.size());
        }

        bool House::get_Local_Transformation(int i)
        {
            return 1;
        }

        void House::get_World_Positions()
        {
            house_Positions = 
            {
                glm::vec3(0.0f,  0.0f, 0.0f),
                glm::vec3(2.0f,  5.0f, -15.0f),
                glm::vec3(-1.5f, -2.2f, -2.5f),
                glm::vec3(-3.8f, -2.0f, -12.3f),
                glm::vec3(2.4f, -0.4f, -3.5f),
            };
        }

        void House::draw_Houses()
        {
            for (unsigned int i = 0; i < house_Positions.size(); i++)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, house_Positions[i]);
                float angle = 20.0f * i;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                shader->setMat4("model", model);

                glDrawElements(GL_TRIANGLES, size_idx_triangles, GL_UNSIGNED_INT, 0);
            }
        }

        void House::bind_Transform(bool& enable, int current_transform)
        {

        }

        void House::send_VShader_Transform()
        {
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 projection = glm::mat4(1.0f);

            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.5f));
            projection = glm::perspective(glm::radians(45.0f), WINDOW_ASPECT, 0.1f, 100.0f);

            shader->setMat4("model", model);
            shader->setMat4("view", view);
            shader->setMat4("projection", projection);
        }

#endif
