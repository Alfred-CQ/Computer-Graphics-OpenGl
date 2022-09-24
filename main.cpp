#include "include/openglmanager.h"
#include "include/config.h"

#include "include/shader.h"
#include "include/star.h"
#include "include/house.h"
#include "include/pizza.h"

int main()
{
    OpenGLManager openGL(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);
    
    /* Shaders */
    Shader starShader(VERTEXSHADER, starFRAGMENTSHADER);
    Shader houseShader(VERTEXSHADER, houseFRAGMENTSHADER);

    /* Pictures */
    // Star
    Star myStar(6, 0.5f, 0.9f);
    uint star_VAO, star_VBO, star_EBO;
    openGL.bind_Buffer_Data(&star_VAO, &star_VBO, &star_EBO, &myStar);

    // House
    House myHouse;
    uint house_VAO, house_VBO, house_EBO;
    openGL.bind_Buffer_Data(&house_VAO, &house_VBO, &house_EBO, &myHouse);
    
    // Pizza
    Pizza myPizza(36, 0.5f);
    uint pizza_VAO, pizza_VBO, pizza_EBO;
    openGL.bind_Buffer_Data(&pizza_VAO, &pizza_VBO, &pizza_EBO, &myPizza);

    while (!glfwWindowShouldClose(openGL.window))
    {
        glClearColor(0.0901f, 0.1176f, 0.1529f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        starShader.use();
        glPointSize(7);

        glBindVertexArray(star_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, star_VBO);
        glDrawArrays(primitive, 0, 12);
        
        houseShader.use();
        glBindVertexArray(house_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, house_VBO);
        glDrawArrays(primitive, 0, 7);

        houseShader.use();
        glBindVertexArray(pizza_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, pizza_VBO);
        glDrawArrays(primitive, 0, 37);
        
        glfwSwapBuffers(openGL.window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
