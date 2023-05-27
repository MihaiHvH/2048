#include "../main.hpp"
#include "graphics.hpp"
#include <GL/gl.h>

#ifndef M_PI
    #define M_PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067
#endif

pGraphics::pGraphics() {
    black =  createNewColor(0, 0, 0);
    white =  createNewColor(255, 255,255);
    red =    createNewColor(255, 0, 0);
    green =  createNewColor(0, 255, 0);
    blue =   createNewColor(0, 0, 255);
    yellow = createNewColor(255, 255, 0);
    cyan =   createNewColor(0, 255, 255);
    purple = createNewColor(255, 0, 255);

    color2 = createNewColor(238, 228, 218);
    color4 = createNewColor(237, 224, 200);
    color8 = createNewColor(242, 177, 121);
    color16 = createNewColor(245, 149, 99);
    color32 = createNewColor(246, 124, 95);
    color64 = createNewColor(246, 94, 59);
    color128 = createNewColor(237, 207, 114);
    color256 = createNewColor(237, 204, 97);
    color512 = createNewColor(237, 200, 80);
    color1024 = createNewColor(237, 197, 63);
    color2048 = createNewColor(237, 194, 46);

    bkgColor = createNewColor(204, 192, 179);
    gameOverColor = createNewColor(238, 228, 218, 76);
}
 
pGraphics::~pGraphics() {

}

pColor pGraphics::createNewColor(int r, int g, int b, int a) {
    pColor color{};
    color.a = a;
    color.r = r;
    color.g = g;
    color.b = b;
    return color;
}

bool pGraphics::mouseInRegion(std::pair<int, int> mousePointer, std::pair<int, int> pos, std::pair<int, int> size) {
    if (mousePointer.first >= pos.first &&
        mousePointer.first <= pos.first + size.first &&
        mousePointer.second >= pos.second &&
        mousePointer.second <= pos.second + size.second)
        return true;
    return false;
}

void pGraphics::drawRect(std::pair<int, int> pos, std::pair<int, int> size, pColor color) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    glBegin(GL_POLYGON);
    glVertex2i(pos.first, pos.second); //corner down
    glVertex2i(pos.first + size.first, pos.second); //right down corner
    glVertex2i(pos.first + size.first, pos.second + size.second); //right up corner
    glVertex2i(pos.first, pos.second + size.second); //corner up
    glEnd();
}

void pGraphics::drawFilledCircle(std::pair<int, int> pos, double r, pColor color) {
    glDisable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glBegin(GL_POLYGON);
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    for (double i = 0; i <= 360;) {
        double angle = 2 * M_PI * i / 360;
        double x = cos(angle) * r;
        double y = sin(angle) * r;
        glVertex2d(pos.first + x, pos.second + y);
        i += 0.25;
    }
    glEnd();
}

void pGraphics::drawTriangle(std::pair<int, int> point1, std::pair<int, int> point2, std::pair<int, int> point3, pColor color) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    glBegin(GL_TRIANGLES);
    glVertex2i(point1.first, point1.second);
    glVertex2i(point2.first, point2.second);
    glVertex2i(point3.first, point3.second);
    glEnd();
}

void pGraphics::drawText(std::pair<int, int> pos, void *font, const char *str, pColor color) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    glRasterPos2i(pos.first, pos.second);
    
    for (size_t i = 0; i < strlen(str); ++i)
        glutBitmapCharacter(font, str[i]);
}