/* Libraries */
#include "include/openglmanager.h"
#include "include/path.h"

#include "include/shader.h"
#include "include/star.h"
#include "include/house.h"

using std::vector;

int typeShape = -1, rangeMax = -1, typePrimi = -1;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void getPizzaCoords(vector<float>& p, int tips, float useRadius);
void getPizzaLines(vector<int>& v, int tips, int m);

int main(int argc, char* argv[])
{
    unsigned int SCR_WIDTH = 800, SCR_HEIGHT = 600;

    OpenGLManager openGL(SCR_WIDTH, SCR_HEIGHT);
   
    glfwSetKeyCallback(openGL.window, key_callback);

    Shader starShader ( &(vertexShader.front()), &(starFragmentShader.front()));
    Shader houseShader( &(vertexShader.front()), &(houseFragmentShader.front()));

    Star myStar(5, 0.5, 0.9);
    House myHouse;

    // starting to model - Pizza
    // -----------------
    vector<float> verticesPizza;
    vector<int> idxPizzaLines;

    getPizzaCoords(verticesPizza, 26, 0.8);
    getPizzaLines(idxPizzaLines, 26, verticesPizza.size());

    unsigned int VBOs[2], VAOs[2], EBOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    glGenBuffers(2, EBOs);

    glBindVertexArray(VAOs[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, myStar.sizeVertexs * sizeof(myStar.vertexs), &(myStar.vertexs.front()), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, myStar.sizeIdxStarTriangles * sizeof(myStar.idxStarTriangles), &(myStar.idxStarTriangles.front()), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);

    // Other
    glBindVertexArray(VAOs[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(myHouse.verticesHouse), myHouse.verticesHouse, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(myHouse.idxHouseTriangles), myHouse.idxHouseTriangles, GL_STATIC_DRAW);

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
            {
                glDrawArrays(GL_LINE_LOOP, 0, 10);
            }
            else if (typePrimi == 2)
            {
                glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);
            }
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
            {
                glPointSize(10);
                glDrawArrays(GL_LINE_LOOP, 0, 7);
            }
            else if (typePrimi == 2)
            {
                glDrawElements(GL_TRIANGLES, rangeMax, GL_UNSIGNED_INT, 0);
            }

        }

        glfwSwapBuffers(openGL.window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteBuffers(2, EBOs);

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
        rangeMax = 15;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS &&
        glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        typeShape = 0;
        typePrimi = 1;
        rangeMax = 10;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS &&
        glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        typeShape = 0;
        typePrimi = 2;
        rangeMax = 24;
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS &&
        glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        typeShape = 1;
        typePrimi = 0;
        rangeMax = 7;
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS &&
        glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        typeShape = 1;
        typePrimi = 1;
        rangeMax = 7;
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS &&
        glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        typeShape = 1;
        typePrimi = 2;
        rangeMax = 15;
    }

    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS &&
        glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        typeShape = 2;
        typePrimi = 1;
        rangeMax = 75;
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void getPizzaCoords(vector<float>& p, int tips, float useRadius)
{

    float t = 0.0f, t_rot = (2 * F_PI) / tips;

    p.push_back(0.0f);
    p.push_back(0.0f);
    p.push_back(0.0f);

    for (int i = 0; i < tips; ++i)
    {
        p.push_back(sin(t) * useRadius);
        p.push_back(cos(t) * useRadius);
        p.push_back(0.0f);

        // std::cout << "x: " << sin(t) * useRadius << " y: " << cos(t) * useRadius << '\n';

        t += t_rot;
    }
}

void getPizzaLines(vector<int>& v, int tips, int m)
{
    for (int i = 1; i < (tips - 1); ++i)
    {
        v.push_back(i);
        v.push_back(0);
        v.push_back(i + 1);
    }
}