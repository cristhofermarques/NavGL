#include<nav.h>
#include<nav_gl.h>
#include<nav_io.h>
#include<nav_gfx.h>
#include<nav_api.h>
#include<nav_log.h>
#include<nav_mem.h>
#include<nav_str.h>
#include<nav_input.h>
#include<stdlib.h>

char consoleVisible = 1;

struct mesh_t
{
    GLuint vao, vbo, ibo;
};
typedef struct mesh_t Mesh;

void LoadPrimitivesModels();

Mesh quad;

NAV_GAME_API void Run()
{  

    unsigned int desc[] = 
    {
        SET_STACK_SIZE, 10000000,
        NEW_FIELD, sizeof(GLuint), 1000,
        NEW_FIELD, sizeof( float), 10070,
        NEW_FIELD, sizeof( size_t), 1400,
        END_DESC
    };
    CreateNavDataBuffer( desc);
    
    CreateGLContextToWND( GetNavWND(), 3, 3, 32, 24);
    GetGLFuncsPtrs();
    glClearColor( 1, 0, 0, 1);
    
    int shader = GLShaderFromFile("data\\shaders\\shader.glsl");
    int tex = GL2DTextureFromNif("data\\textures\\repack.nif");
    LOG( DEC DEC, shader, tex);
    LoadPrimitivesModels();
    glUseProgram( shader);
    glActiveTexture( GL_TEXTURE0);
    //glBindTexture();
}

NAV_GAME_API void Update( float deltaTime)
{
    glViewport(0, 0, GetWNDClientSize( GetNavWND()).x, GetWNDClientSize( GetNavWND()).y);
    glClear(GL_COLOR_BUFFER_BIT);
	if( GetKeyDown( ESCAPE_KEY)){ ExitGame();}
	if( GetKeyDown( F8_KEY)){ consoleVisible = !consoleVisible; SetWNDVisibility( NULL, consoleVisible); }
	glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    SwapWNDBuffers( GetNavWND());
}

NAV_GAME_API void End()
{
    DeleteGLContextOfWND( GetNavWND());
}

void LoadPrimitivesModels()
{
    float quadVert[] = 
    {
        -1, -1, -1, 0, 0,
         1, -1, -1, 1, 0,
        -1,  1, -1, 0, 1,
         1,  1, -1, 1, 1
    };
    
    unsigned int quadIdx[] =
    {
        0, 1, 3,
        0, 3, 2
    };
    
    glGenVertexArrays( 1, &quad.vao);
    glBindVertexArray( quad.vao);

    
    glGenBuffers( 1, &quad.vbo);
    glBindBuffer( GL_ARRAY_BUFFER, quad.vbo);
    glBufferData( GL_ARRAY_BUFFER, sizeof( quadVert), quadVert, GL_STATIC_DRAW);
    glEnableVertexAttribArray( 0);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    glEnableVertexAttribArray( 1);
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    
    glGenBuffers( 1, &quad.ibo);
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, quad.ibo);
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( quadIdx), quadIdx, GL_STATIC_DRAW);
}
