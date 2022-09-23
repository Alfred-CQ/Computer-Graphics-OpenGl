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
    Star myStar(6, 0.5, 0.9);
    unsigned int star_VAO, star_VBO, star_EBO;
    openGL.bind_Buffer_Data(&star_VAO, &star_VBO, &star_EBO, &myStar);

    while (!glfwWindowShouldClose(openGL.window))
    {
        glClearColor(0.0901f, 0.1176f, 0.1529f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        starShader.use();

        glBindVertexArray(star_VAO);
        glDrawArrays(primitive, 0, 12);
        
        glfwSwapBuffers(openGL.window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
