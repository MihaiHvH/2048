#include "main.hpp"
#include "graphics/graphics.hpp"
#include "include/GL/freeglut_std.h"
#include "interface/interface.hpp"
#include <GL/gl.h>
#include <string>
#include <sys/types.h>

void Render();

pInterface interface(Render);
pGraphics::pButon retryBtn({ interface.screen.size.first - interface.data.offset,  10 }, { 90, 30 }, interface.graphics.color4, interface.graphics.color4, GLUT_BITMAP_TIMES_ROMAN_24, interface.graphics.black, "Retry", [](bool s) {
    interface.retry();
});

pGraphics::pButon undoBtn({ interface.screen.size.first - interface.data.offset,  50 }, { 90, 30 }, interface.graphics.color4, interface.graphics.color4, GLUT_BITMAP_TIMES_ROMAN_24, interface.graphics.black, "Undo", [](bool s) {
    interface.undo();
    Render();
});

void Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_TEXTURE_2D);

    glDisable(GL_BLEND);
    glClearColor(interface.graphics.bkgColor.r / 255.f, interface.graphics.bkgColor.g / 255.f, interface.graphics.bkgColor.b / 255.f, interface.graphics.bkgColor.a / 255.f);

    for (auto i : interface.board) {
        interface.graphics.drawRect({ i.pos.first, i.pos.second }, { interface.data.squareSize, interface.data.squareSize }, i.color);
        std::pair<int, int> textSize = {
            glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char*>(std::to_string(i.val).c_str())),
            glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, std::to_string(i.val)[0])
        };
        interface.graphics.drawText({ i.pos.first + ((interface.data.squareSize - textSize.first) / 2), i.pos.second + (interface.data.squareSize / 2) + textSize.second / 2 }, GLUT_BITMAP_TIMES_ROMAN_24, std::to_string(i.val).c_str(), interface.graphics.black);
    }
    interface.drawScore();
    if (interface.screen.gameOver) interface.drawGameOver();
    retryBtn.draw(interface);
    undoBtn.draw(interface);
    glutSwapBuffers();
}

void Resize(GLint newWidth, GLint newHeight) {
    if (newWidth >= 8 && newHeight >= 8) {
        interface.data.spacing = (int)(0.02125 * interface.screen.size.first);
        interface.data.squareSize = (interface.screen.size.first - (5 * interface.data.spacing)) / 4;

        interface.init();

        glViewport( 0, 0, interface.screen.size.first, interface.screen.size.second );
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glOrtho( 0, GLdouble (interface.screen.size.first), GLdouble (interface.screen.size.second), 0, 0, 100);
        Render();
        glutPostRedisplay();
    }
}

void ProcessSpecialInput(int key, int x, int y) {
}

void ProcessInput(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
        case 's':
        case 'd':
        case 'a':
            interface.handleInput(key);
        break;
    }
}

void HandleMouseKeys(int button, int state, int x, int y) {
    switch(button) {
        case GLUT_LEFT_BUTTON: {
            interface.screen.leftClick = state;

            retryBtn.checkClick(interface);
            undoBtn.checkClick(interface);

            if (state != GLUT_DOWN)
                break;

            break;
        }
        case GLUT_RIGHT_BUTTON: {
            interface.screen.rightClick = state;

            if (state != GLUT_DOWN)
                break;

            break;
        }
    }
    Render();
}

void HandleMouseMovement(int x, int y) {
    interface.screen.mousePointer = { x, y };
}

void HandleMouseDrag(int x, int y) {
    interface.screen.mousePointer = { x, y };
    if (interface.screen.leftClick != interface.screen.leftClickDrag)
        interface.screen.leftClickDrag = interface.screen.leftClick;
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(interface.screen.initialSize.first, interface.screen.initialSize.second);
    glutCreateWindow (interface.screen.windowName.c_str());

    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho( 0, 640, 640, 0, 0, 100);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    /*image loading --start--*/

    ilInit();

    /*image loading --end--*/

    glutDisplayFunc(Render);
    glutKeyboardFunc(ProcessInput);
    glutSpecialFunc(ProcessSpecialInput);
    glutReshapeFunc(Resize);
    glutMouseFunc(HandleMouseKeys);
    glutPassiveMotionFunc(HandleMouseMovement);
    glutMotionFunc(HandleMouseDrag);

    glutMainLoop();
    return 0;
}