#include "include/openglmanager.h"
#include "include/config.h"

int main()
{
    OpenGLManager openGL(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);
    
    /* Shaders */
    Shader starShader(VERTEXSHADER, starFRAGMENTSHADER), houseShader(VERTEXSHADER, houseFRAGMENTSHADER), pizzaShader(VERTEXSHADER, pizzaFRAGMENTSHADER);
    vector<Shader*> myShaders = { &starShader, &houseShader, &pizzaShader};

    /* Pictures */
    Star myStar(5, 0.5f, 0.9f); House myHouse; Pizza myPizza(36, 0.9f);
    vector<Picture*> myPictures = { &myStar, &myHouse, &myPizza};
    
    // Textures and shader
    pizzaShader.use();
    glUniform1i(glGetUniformLocation(pizzaShader.ID, "texture_1"), 0);
    pizzaShader.setInt("texture_2", 1);

    while (!openGL.close())
    {
        glClearColor(0.0901f, 0.1176f, 0.1529f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glPointSize(7);
        
        myShaders[current_picture]->use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, myPictures[current_picture]->id_textures[0]);

        myPictures[current_picture]->draw(primitive);

        if (current_picture == 2)
        {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, myPictures[current_picture]->id_textures[1]);
            
            if (primitive == GL_LINE_LOOP)
                myPizza.draw_divisions();
        }

        openGL.listen_buffers_and_Events();
    }

    return 0;
}
