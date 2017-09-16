#include "LUtil.h"
#include "misc/Cgdi.h"
#include "misc/PrecisionTimer.h"
#include "constants.h"
#include "CallbackHandler.h"
#include "misc/utils.h"
#include "GameWorld.h"
#include "ParamLoader.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void initGL()
{
    GLenum glewError = glewInit();
    if( glewError != GLEW_OK )
    {
        printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
        exit(EXIT_FAILURE);
    }

    if( !GLEW_VERSION_3_0 )
    {
        printf( "OpenGL 3.0 not supported!\n" );
        exit(EXIT_FAILURE);
    }

    glViewport( 0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glClearColor( 1.f, 1.f, 1.f, 1.f );

    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        exit(EXIT_FAILURE);
    }

}




