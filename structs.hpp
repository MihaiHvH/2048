#pragma once

#include <utility>
#include <string>

struct pColor {
    int r;
    int g;
    int b;
    int a;
};

struct pScreen {
    std::string windowName = "2048";
    std::pair<int, int> size = { 640, 740 };
    std::pair<int, int> initialSize = { 640, 740 };
    std::pair<int, int> mousePointer;
    bool leftClick = false;
    bool rightClick = false;
    bool leftClickDrag = false;

    bool gameOver = false;
    bool win = false;
    int score = 0;
    int oScore = 0;
    int bestScore = 0;
};