#include "include/config.h"
#include "include/openglmanager.h"

int main()
{
    OpenGLManager openGL(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);
    
    /* Shaders */
    Shader starShader(VERTEXSHADER, starFRAGMENTSHADER), houseShader(VERTEXSHADER, houseFRAGMENTSHADER), pizzaShader(VERTEXSHADER, pizzaFRAGMENTSHADER);

    /* Pictures */
    Star myStar(5, 0.5f, 0.9f); House myHouse; Pizza myPizza(36, 0.9f);
    vector<Picture*> myPictures = { &myStar, &myHouse, &myPizza};

    myStar.set_Shader(&starShader); myHouse.set_Shader(&houseShader); myPizza.set_Shader(&pizzaShader);
    
    myPizza.begin_Textures();

    while (!openGL.close())
    {
        openGL.clear_and_Specifications();

        myPictures[current_picture]->send_Data_Shaders();

        myPictures[current_picture]->bind_Textures(); 
        myPictures[current_picture]->bind_Transform(enable_transformation, current_transform);

        if (current_picture == 1 && primitive == GL_TRIANGLES)
            myHouse.draw_Houses();
        else if (current_picture == 2 && primitive == GL_LINE_LOOP)
            myPizza.draw_divisions();
        
        myPictures[current_picture]->draw(primitive);

        openGL.listen_buffers_and_Events();
    }

    return 0;
}
