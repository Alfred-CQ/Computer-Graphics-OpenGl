#include "include/openglmanager.h"
#include "include/config.h"

int main()
{
    OpenGLManager openGL(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);
    
    /* Shaders */
    Shader starShader(VERTEXSHADER, starFRAGMENTSHADER), houseShader(VERTEXSHADER, houseFRAGMENTSHADER), pizzaShader(VERTEXSHADER, pizzaFRAGMENTSHADER);

    /* Pictures */
    Star myStar(5, 0.5f, 0.9f); House myHouse; Pizza myPizza(36, 0.9f);
    vector<Picture*> myPictures = { &myStar, &myHouse, &myPizza};

    myStar.set_Shader(&starShader);
    myHouse.set_Shader(&houseShader);
    myPizza.set_Shader(&pizzaShader);
    
    myPizza.begin_Textures();

    while (!openGL.close())
    {
        glClearColor(0.0901f, 0.1176f, 0.1529f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glPointSize(7);
    
        myPictures[current_picture]->send_Data_Shader();
        myPictures[current_picture]->bind_Textures();

        myPictures[current_picture]->draw(primitive);

        if (current_picture == 2 && primitive == GL_LINE_LOOP)
            myPizza.draw_divisions();

        openGL.listen_buffers_and_Events();
    }

    return 0;
}
