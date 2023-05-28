#include "../main.hpp"
#include "interface.hpp"
#include <cstdio>
#include <iterator>
#include <random>

pInterface::pInterface(void(*pRender)(void)) {
    render = pRender;
    NULLSQ.val = -1;
}

pInterface::~pInterface() {

}

void pInterface::init() {
    if (!bInit) {
        spawnSquare();
        spawnSquare();
        undoBoard = board;
    } 
    bInit = true;
}

void pInterface::spawnSquare() {
    pSquare sq;
    int r = generateRandomNumber({ 0, 100 });
    if (r <= 10)
        sq.val = 4, sq.color = graphics.color4;
    else
        sq.val = 2, sq.color = graphics.color2;
    int valx = generateRandomNumber({ 0, 3});
    int valy = generateRandomNumber({ 0, 3 });
    std::pair<int, int> pos = { 
        valx * data.squareSize + (valx+1) * data.spacing,
        (valy * data.squareSize + (valy+1) * data.spacing) + data.offset
    };
    while (1) {
        int cnt = 0;
        for (auto i : board) {
            while (i.pos == pos) {
                valx = generateRandomNumber({ 0, 3});
                valy = generateRandomNumber({ 0, 3 });
                pos = { 
                    valx * data.squareSize + (valx+1) * data.spacing,
                    (valy * data.squareSize + (valy+1) * data.spacing) + data.offset
                };
                ++cnt;
            }
        }
        if (cnt == 0)
            break;
    }
    sq.pos = pos;
    board.push_back(sq);
}

void pInterface::modSquare(pSquare sq, pSquare newSq) {
    for (auto &i : board) {
        if (i.pos == sq.pos) {
            std::swap(i, newSq);
            break;
        }
    }
}

void pInterface::handleInput(unsigned char key) {
    if (!screen.gameOver && !screen.win) {
        screen.oScore = screen.score;
        undoBoard = board;
        if (key == 'w') {
            int cnt = 0, ch = 0;
            while (cnt <= 4) {
                for (auto &sq : board)
                    while (!extN(1, sq).first.first && extN(1, sq).first.second != 1)
                        sq.pos.second -= data.spacing + data.squareSize, ++ch;
                ++cnt;
            }
            cnt = 0;
            for (int i = 0; i <= 3; ++i) {
                for (int j = 0; j <= 3; ++j) {
                    for (auto &sq : board) {
                        if (sq.pos == std::make_pair(data.spacing * (i+1) + data.squareSize * i, data.spacing * (j+1) + data.squareSize * j + data.offset)) {
                            if (extN(2, sq).first.first && extN(2, sq).second.val == sq.val) {
                                sq.val *= 2;
                                screen.score += sq.val;
                                sq.color = getColorFromVal(sq.val);
                                delSquare(extN(2, sq).second);
                                ++ch;
                            }
                        }
                    }
                }
            }
            while (cnt <= 4) {
                for (auto &sq : board)
                    while (!extN(1, sq).first.first && extN(1, sq).first.second != 1)
                        sq.pos.second -= data.spacing + data.squareSize;
                ++cnt;
            }
            if (board.size() != 16 && ch != 0)
                spawnSquare();
        }
        else if (key == 's') {
            int cnt = 0, ch = 0;
            while (cnt <= 4) {
                for (auto &sq : board)
                    while (!extN(2, sq).first.first && extN(2, sq).first.second != 1)
                        sq.pos.second += data.spacing + data.squareSize, ++ch;
                ++cnt;
            }
            cnt = 0;
            for (int i = 0; i <= 3; ++i) {
                for (int j = 3; j >= 0; --j) {
                    for (auto &sq : board) {
                        if (sq.pos == std::make_pair(data.spacing * (i+1) + data.squareSize * i, data.spacing * (j+1) + data.squareSize * j + data.offset)) {
                            if (extN(1, sq).first.first && extN(1, sq).second.val == sq.val) {
                                sq.val *= 2;
                                screen.score += sq.val;
                                sq.color = getColorFromVal(sq.val);
                                delSquare(extN(1, sq).second);
                                ++ch;
                            }
                        }
                    }
                }
            }
            while (cnt <= 4) {
                for (auto &sq : board)
                    while (!extN(2, sq).first.first && extN(2, sq).first.second != 1)
                        sq.pos.second += data.spacing + data.squareSize;
                ++cnt;
            }
            if (board.size() != 16 && ch != 0)
                spawnSquare();
        }
        else if (key == 'a') {
            int cnt = 0, ch = 0;
            while (cnt <= 4) {
                for (auto &sq : board)
                    while (!extN(3, sq).first.first && extN(3, sq).first.second != 1)
                        sq.pos.first -= data.spacing + data.squareSize, ++ch;
                ++cnt;
            }
            cnt = 0;
            for (int j = 0; j <= 3; ++j) {
                for (int i = 0; i <= 3; ++i) {
                    for (auto &sq : board) {
                        if (sq.pos == std::make_pair(data.spacing * (i+1) + data.squareSize * i, data.spacing * (j+1) + data.squareSize * j + data.offset)) {
                            if (extN(4, sq).first.first && extN(4, sq).second.val == sq.val) {
                                sq.val *= 2;
                                screen.score += sq.val;
                                sq.color = getColorFromVal(sq.val);
                                delSquare(extN(4, sq).second);
                                ++ch;
                            }
                        }
                    }
                }
            }
            while (cnt <= 4) {
                for (auto &sq : board)
                    while (!extN(3, sq).first.first && extN(3, sq).first.second != 1)
                        sq.pos.first -= data.spacing + data.squareSize;
                ++cnt;
            }
            if (board.size() != 16 && ch != 0)
                spawnSquare();
        }
        else if (key == 'd') {
            int cnt = 0, ch = 0;
            while (cnt <= 4) {
                for (auto &sq : board)
                    while (!extN(4, sq).first.first && extN(4, sq).first.second != 1)
                        sq.pos.first += data.spacing + data.squareSize, ++ch;
                ++cnt;
            }
            cnt = 0;
            for (int i = 3; i >= 0; --i) {
                for (int j = 0; j <= 3; ++j) {
                    for (auto &sq : board) {
                        if (sq.pos == std::make_pair(data.spacing * (i+1) + data.squareSize * i, data.spacing * (j+1) + data.squareSize * j + data.offset)) {
                            if (extN(3, sq).first.first && extN(3, sq).second.val == sq.val) {
                                sq.val *= 2;
                                screen.score += sq.val;
                                sq.color = getColorFromVal(sq.val);
                                delSquare(extN(3, sq).second);
                                ++ch;
                            }
                        }
                    }
                }
            }
            while (cnt <= 4) {
                for (auto &sq : board)
                    while (!extN(4, sq).first.first && extN(4, sq).first.second != 1)
                        sq.pos.first += data.spacing + data.squareSize;
                ++cnt;
            }
            if (board.size() != 16 && ch != 0)
                spawnSquare();
        }
        if (screen.score > screen.bestScore)
            screen.bestScore = screen.score;
    }
    
    {
        //simGameOver

        int ch = 0;
        for (auto sq : board) {
            if ((extN(1, sq).first.second != 1 && !extN(1, sq).first.first) || (extN(1, sq).first.first && extN(1, sq).second.val == sq.val))
                ++ch;
            if ((extN(2, sq).first.second != 1 && !extN(2, sq).first.first) || (extN(2, sq).first.first && extN(2, sq).second.val == sq.val))
                ++ch;
            if ((extN(3, sq).first.second != 1 && !extN(3, sq).first.first) || (extN(3, sq).first.first && extN(3, sq).second.val == sq.val))
                ++ch;
            if ((extN(4, sq).first.second != 1 && !extN(4, sq).first.first) || (extN(4, sq).first.first && extN(4, sq).second.val == sq.val))
                ++ch;
        }
        if (ch == 0 && board.size() == 16)
            screen.gameOver = true;
    }

    {
        //ifWin
        for (auto sq : board)
            if (sq.val == 2048)
                screen.win = true;
    }

    render();
}

void pInterface::drawGameOver() {
    graphics.drawRect({ 0, data.offset }, { screen.size.first, screen.size.second - data.offset }, graphics.gameOverColor);
    std::string gvStr = "Game over !";
    std::pair<int, int> textSize = { glutBitmapLength(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char*>(gvStr.c_str())), 0};
    for (size_t i = 0; i < strlen(gvStr.c_str()); ++i)
        if (textSize.second < glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, gvStr.c_str()[i]))
            textSize.second = glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, gvStr.c_str()[i]);
    graphics.drawText({ (screen.size.first / 2) - (textSize.first / 2), ((screen.size.second + data.offset) / 2) - (textSize.second / 2) }, GLUT_BITMAP_HELVETICA_18, gvStr.c_str(), graphics.black);
}

void pInterface::drawWinScreen() {
    graphics.color2048.a = 76;
    graphics.drawRect({ 0, data.offset }, { screen.size.first, screen.size.second - data.offset }, graphics.color2048);
    graphics.color2048.a = 255;
    std::string gvStr = "You win !";
    std::pair<int, int> textSize = { glutBitmapLength(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char*>(gvStr.c_str())), 0};
    for (size_t i = 0; i < strlen(gvStr.c_str()); ++i)
        if (textSize.second < glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, gvStr.c_str()[i]))
            textSize.second = glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, gvStr.c_str()[i]);
    graphics.drawText({ (screen.size.first / 2) - (textSize.first / 2), ((screen.size.second + data.offset) / 2) - (textSize.second / 2) }, GLUT_BITMAP_HELVETICA_18, gvStr.c_str(), graphics.black);
}

void pInterface::drawScore() {
    graphics.drawText({ 10, 28 }, GLUT_BITMAP_HELVETICA_18, std::string("Score: ").append(std::to_string(screen.score)).c_str(), graphics.black);
    graphics.drawText({ 10, 2 * 28 }, GLUT_BITMAP_HELVETICA_18, std::string("Best score: ").append(std::to_string(screen.bestScore)).c_str(), graphics.black);
}

void pInterface::retry() {
    screen.gameOver = false;
    screen.win = false;
    bInit = false;
    screen.score = 0;
    board.clear();
    init();
}

void pInterface::undo() {
    screen.score = screen.oScore;
    screen.win = false;
    screen.gameOver = false;
    board = undoBoard;
}

int pInterface::generateRandomNumber(std::pair<int, int> range) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(range.first, range.second);
    return dist(gen);
}

std::pair<std::pair<bool, int>, pInterface::pSquare> pInterface::extN(int dir, pSquare sq) {
    if (dir == 1) { // up
        int ePos = sq.pos.second - data.spacing - data.squareSize;
        if (ePos < data.spacing)
            return { { false, 1 }, NULLSQ };
        for (auto i : board)
            if (i.pos == std::make_pair(sq.pos.first, ePos))
                return {{ true, 0 }, i };
    }
    else if (dir == 2) { // down
        int ePos = sq.pos.second + data.spacing + data.squareSize;
        if (ePos > screen.size.second - data.spacing - data.squareSize)
            return {{ false, 1 }, NULLSQ };
        for (auto i : board)
            if (i.pos == std::make_pair(sq.pos.first, ePos))
                return {{ true, 0 }, i };
    }
    else if (dir == 3) { // left
        int ePos = sq.pos.first - data.spacing - data.squareSize;
        
        if (ePos < data.spacing)
            return {{ false, 1 }, NULLSQ };
        for (auto i : board)
            if (i.pos == std::make_pair(ePos, sq.pos.second))
                return {{ true, 0 }, i};
                
    }
    else if (dir == 4) { // right
        int ePos = sq.pos.first + data.spacing + data.squareSize;
        if (ePos > screen.size.first - data.spacing - data.squareSize)
            return {{ false, 1 }, NULLSQ };
        for (auto i : board)
            if (i.pos == std::make_pair(ePos, sq.pos.second))
                return {{ true, 0 }, i };
    }
    return {{ false, 2 }, NULLSQ } ;
}

pColor pInterface::getColorFromVal(int val) {
    if (val == 2)
        return graphics.color2;
    if (val == 4)
        return graphics.color4;
    if (val == 8)
        return graphics.color8;
    if (val == 16)
        return graphics.color16;
    if (val == 32)
        return graphics.color32;
    if (val == 64)
        return graphics.color64;
    if (val == 128)
        return graphics.color128;
    if (val == 256)
        return graphics.color256;
    if (val == 512)
        return graphics.color512;
    if (val == 1024)
        return graphics.color1024;
    if (val >= 2048)
        return graphics.color2048;
    return graphics.black;
}

void pInterface::delSquare(pSquare sq) {
    for (size_t i = 0; i < board.size(); ++i) {
        if (board.at(i).pos == sq.pos) {
            board.erase(board.begin() + i);
            break;
        }
    }
}