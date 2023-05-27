#pragma once

#include <vector>

#include "../structs.hpp"
#include "../graphics/graphics.hpp"

class pInterface {
    private:
    void(*render)(void);
    bool bInit = false;

    public:
    pInterface(void(*pRender)(void));
    ~pInterface();

    void init();
    void spawnSquare();
    int generateRandomNumber(std::pair<int, int> range);
    void handleInput(unsigned char key);
    pColor getColorFromVal(int val);

    void drawGameOver();
    void drawScore();
    void retry();
    void undo();

    struct pSquare {
        int val;
        pColor color;
        std::pair<int, int> pos;
    };

    pSquare NULLSQ;

    void delSquare(pSquare sq);
    void modSquare(pSquare sq, pSquare newSq);
    std::pair<std::pair<bool, int>, pSquare> extN(int dir, pSquare sq);

    struct pData {
        int score = 0;
        bool gameOver = false;
        int squareSize;
        int spacing;
        int offset = 100;
    } data;

    std::vector<pSquare> board;
    std::vector<pSquare> undoBoard;

    pScreen screen;
    pGraphics graphics;
};