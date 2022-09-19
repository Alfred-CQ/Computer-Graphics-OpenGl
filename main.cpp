/* Libraries */
#include "include/openglmanager.h"
#include "include/path.h"

#include "include/shader.h"
#include "include/star.h"
#include "include/house.h"
#include "include/pizza.h"


int typeShape = -1, rangeMax = -1, typePrimi = -1;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main()
{
    unsigned int SCR_WIDTH = 700, SCR_HEIGHT = 600;

    OpenGLManager openGL(SCR_WIDTH, SCR_HEIGHT);
   
    glfwSetKeyCallback(openGL.window, key_callback);

    Shader starShader ( &(vertexShader.front()), &(starFragmentShader.front()));
    Shader houseShader( &(vertexShader.front()), &(houseFragmentShader.front()));

    Star myStar(5, 0.5, 0.9);
    House myHouse;
    Pizza myPizza(36, 0.8);

    unsigned int VBOs[3], VAOs[3], EBOs[3];
    glGenVertexArrays(3, VAOs);
    glGenBuffers(3, VBOs);
    glGenBuffers(3, EBOs);

    glBindVertexArray(VAOs[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, myStar.sizeVertexs * sizeof(myStar.vertexs), &(myStar.vertexs.front()), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, myStar.sizeIdxStarTriangles * sizeof(myStar.idxStarTriangles), &(myStar.idxStarTriangles.front()), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);

    // House
    glBindVertexArray(VAOs[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(myHouse.verticesHouse), myHouse.verticesHouse, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(myHouse.idxHouseTriangles), myHouse.idxHouseTriangles, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);

    // Pizza
    glBindVertexArray(VAOs[2]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ARRAY_BUFFER, myPizza.vertexs.size() * sizeof(myPizza.vertexs), &myPizza.vertexs.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, myPizza.idxPizzaLine.size() * sizeof(myPizza.idxPizzaLine), &myPizza.idxPizzaLine.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(openGL.window))
    {
        glClearColor(0.0901f, 0.1176f, 0.1529f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (typeShape == 0)
        {
            starShader.use();
            glBindVertexArray(VAOs[0]);
            if (typePrimi == 0)
            {
                glPointSize(10);
                glDrawArrays(GL_POINTS, 0, 10);
            }
            else if (typePrimi == 1)
                glDrawArrays(GL_LINE_LOOP, 0, 10);
            else if (typePrimi == 2)
                glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);
        }
        else if (typeShape == 1)
        {
            float timeValue = glfwGetTime();
            float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
            houseShader.use();
            houseShader.setFloat4("ourColor", greenValue);
          
            glBindVertexArray(VAOs[1]);
           
            if (typePrimi == 0)
            {
                glPointSize(10);
                glDrawArrays(GL_POINTS, 0, 7);
            }
            else if (typePrimi == 1)
                glDrawArrays(GL_LINE_LOOP, 0, 7);
            else if (typePrimi == 2)
                glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);

        }
        else if (typeShape == 2)
        {
            starShader.use();
            glBindVertexArray(VAOs[2]);
            if (typePrimi == 0)
            {
                glPointSize(8);
                glDrawArrays(GL_POINTS, 0, 36);
            }
            else if (typePrimi == 1)
                glDrawElements(GL_LINE_LOOP, 38, GL_UNSIGNED_INT, 0);
            else if (typePrimi == 2)
                glDrawArrays(GL_TRIANGLES, 0, 18);
        }

        glfwSwapBuffers(openGL.window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(3, VAOs);
    glDeleteBuffers(3, VBOs);
    glDeleteBuffers(3, EBOs);

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS &&
        glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        typeShape = 0;
        typePrimi = 0;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS &&
        glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        typeShape = 0;
        typePrimi = 1;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS &&
        glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        typeShape = 0;
        typePrimi = 2;
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS &&
        glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        typeShape = 1;
        typePrimi = 0;
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS &&
        glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        typeShape = 1;
        typePrimi = 1;
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS &&
        glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        typeShape = 1;
        typePrimi = 2;
    }

    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS &&
        glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        typeShape = 2;
        typePrimi = 0;
    }

    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS &&
        glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        typeShape = 2;
        typePrimi = 1;
    }

    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS &&
        glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        typeShape = 2;
        typePrimi = 2;
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
