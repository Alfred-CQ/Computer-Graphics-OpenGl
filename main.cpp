#include "include/config.h"
#include "include/openglmanager.h"

int main()
{
    OpenGLManager openGL(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);
    
    /* Shaders */
    Shader cubeShader(VERTEXSHADER, cubeFRAGMENTSHADER);

    /* Rubik Cube */

    Rubik myRubik(0.1f, 0.03f);
    myRubik.set_Shader(&cubeShader);

    while (!openGL.close())
    {
        openGL.clear_and_Specifications();

        myRubik.send_Data_Shaders();

        myRubik.bind_Textures();
        myRubik.bind_Transform(enable_transformation, current_transform);

        myRubik.draw(primitive);

        openGL.listen_buffers_and_Events();
    }

    return 0;
}
