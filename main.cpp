#include "include/openglmanager.h"
#include "include/config.h"

int main()
{
    OpenGLManager openGL(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);
    
    /* Shaders */
    Shader cubeShader(VERTEXSHADER, cubeFRAGMENTSHADER);

    /* Pictures */
    vector<COLOUR> myColors = {BLUE, GREEN, YELLOW, RED, WHITE, ORANGE};
    Cube myCube(0.3f, {0,0,0}, myColors);

    myCube.set_Shader(&cubeShader);
    
    while (!openGL.close())
    {
        openGL.clear_and_Specifications();

        myCube.send_Data_Shaders();

        myCube.bind_Textures();
        myCube.bind_Transform(enable_transformation, current_transform);
        
        myCube.draw(primitive);

        openGL.listen_buffers_and_Events();
    }

    return 0;
}
