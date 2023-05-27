#pragma once

#include <utility>
#include "../structs.hpp"

class pGraphics {
    private:

    public:
    pGraphics();
    ~pGraphics();
    
    class pButon;
    class pTextBox;
    class pCheckBox;
    class pImage;
    class pSlider;

    pColor white, black, red, green, blue, yellow, cyan, purple;
    pColor color2, color4, color8, color16, color32, color64, color128, color256, color512, color1024, color2048;
    pColor bkgColor, gameOverColor;

    void drawRect(std::pair<int, int> pos, std::pair<int, int> size, pColor color);
    void drawFilledCircle(std::pair<int, int> pos, double r, pColor color);
    void drawText(std::pair<int, int> pos, void *font, const char* str, pColor color);
    void drawTriangle(std::pair<int, int> point1, std::pair<int, int> point2, std::pair<int, int> point3, pColor color);
    bool mouseInRegion(std::pair<int, int> mousePointer, std::pair<int, int> pos, std::pair<int, int> size);

    pColor createNewColor(int r, int g, int b, int a = 255);
};