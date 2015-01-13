#include <iostream>
#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>

void drawTriangle();
void drawCube();

int main()
{

    if(SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr<<"error init SDL\n";
        exit(EXIT_FAILURE);
    }

    SDL_Rect screenSize;
    SDL_GetDisplayBounds(0, &screenSize); //get screen size

    //create window
    SDL_Window *window = SDL_CreateWindow(
                "OpenGL Demo",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                screenSize.w/2,
                screenSize.h/2,
                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
                );

    SDL_GLContext glContext;
    //set openGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    glContext = SDL_GL_CreateContext(window);

    //make it active context
    SDL_GL_MakeCurrent(window, glContext);

    //turn window white
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0f, (float)screenSize.w/screenSize.h, 0.5, 100);

    //camera setup
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(2, 2, 2, 0, 0, 0, 0, 1, 0);
    glEnable(GL_DEPTH_TEST);

    //exit control
    bool quit = false;
    SDL_Event event;
    while (!quit){
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT : quit = true; break;
            case SDL_KEYDOWN :
                switch(event.key.keysym.sym)
                {
                    //keyboard shortcuts
                    case SDLK_ESCAPE : quit = true; break;
                    case SDLK_w :glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break; //wireframe mode
                    case SDLK_s : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break; //solid mode
                }
                break;
            }
        }

        //draw here
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clears buffer
        //drawTriangle();
        drawCube();
        SDL_GL_SwapWindow(window);

    } // end of infinite loop

}

void drawTriangle()
{
    static int rot = 0;

    //tab in - easier to follow code
    glPushMatrix();
        glRotated(++rot, 0, 1, 0);
        glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 1.0f, 0.0f);
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, 0.0f);
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(-1.0f, -1.0f, 0.0f);
        glEnd();
    glPopMatrix();
}

void drawCube()
{
    static int rot = 0;

    //tab in - easier to follow code
    glPushMatrix();
        glRotated(++rot, 0, 1, 0);
        glBegin(GL_QUADS);
            glColor3f(1.0, 0.0, 0.0);
            glVertex3f(-1, -1, 1);
            glVertex3f(-1, 1, 1);
            glVertex3f(1, 1, 1);
            glVertex3f(1, -1, 1);

            glColor3f(0.0, 1.0, 0.0);
            glVertex3f(1, -1, 1);
            glVertex3f(1, 1, 1);
            glVertex3f(1, 1, -1);
            glVertex3f(1, -1, -1);

            glColor3f(0.0, 0.0, 1.0);
            glVertex3f(1, -1, -1);
            glVertex3f(1, 1, -1);
            glVertex3f(-1, 1, -1);
            glVertex3f(-1, -1, -1);

            glColor3f(1.0, 1.0, 0.0);
            glVertex3f(-1, -1, -1);
            glVertex3f(-1, 1, -1);
            glVertex3f(-1, 1, 1);
            glVertex3f(-1, -1, 1);

            glColor3f(0.0, 1.0, 1.0);
            glVertex3f(-1, 1, 1);
            glVertex3f(1, 1, 1);
            glVertex3f(1, 1, -1);
            glVertex3f(-1, 1, -1);

            glColor3f(1.0, 0.0, 1.0);
            glVertex3f(-1, -1, 1);
            glVertex3f(1, -1, 1);
            glVertex3f(1, -1, -1);
            glVertex3f(-1, -1, -1);

        glEnd();
    glPopMatrix();
}
