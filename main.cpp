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
    Star myStar(5, 0.5f, 0.9f); House myHouse; Pizza myPizza(36, 0.5f);
   
    vector<Picture*> myPictures = { &myStar, &myHouse, &myPizza};

    while (!openGL.close())
    {
        glClearColor(0.0901f, 0.1176f, 0.1529f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        starShader.use();
        glPointSize(7);
        
        myPictures[current_picture]->draw(primitive);
       
        if (current_picture == 2 && primitive == GL_LINE_LOOP)
            myPizza.draw_divisions();

        openGL.listen_buffers_and_Events();
    }

    return 0;
}
