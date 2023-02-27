#include "polyomino.h"
#include <iostream>
#include "../states/game_state.h"

Polyomino::Polyomino()
    : pField(nullptr), RESOLUTION(660, 680)
{
}

sf::String Polyomino::getElementOfPiece(int x, int y)
{
    if(Polyomino::COUNT_OF_BLOCKS == 2)
    {
        return domino[x][y];
    }
    else if(Polyomino::COUNT_OF_BLOCKS == 3)
    {
        return triomino[x][y];
    }
    else if(Polyomino::COUNT_OF_BLOCKS == 4)
    {
        return tetromino[x][y];
    }
    else if(Polyomino::COUNT_OF_BLOCKS == 5)
    {
        return pentomino[x][y];
    }

    return sf::String();
}

sf::String Polyomino::pentomino[] =
{
    //F
    sf::String      ("....."
                     "..XX."
                     ".XX.."
                     "..X.."
                     "....."),
    //RF
    sf::String      ("....."
                     ".XX.."
                     "..XX."
                     "..X.."
                     "....."),
    //I
    sf::String      ("..X.."
                     "..X.."
                     "..X.."
                     "..X.."
                     "..X.."),
    //J
    sf::String      ("..X.."
                     "..X.."
                     "..X.."
                     ".XX.."
                     "....."),
    //N
    sf::String      ("....."
                     ".XX.."
                     "..XXX"
                     "....."
                     "....."),
    //RN
    sf::String      ("....."
                     "..XX."
                     "XXX.."
                     "....."
                     "....."),
    //P
    sf::String      ("....."
                     "..XX."
                     "..XX."
                     "..X.."
                     "....."),
    //RP
    sf::String      ("....."
                     ".XX.."
                     ".XX.."
                     "..X.."
                     "....."),
    //T
    sf::String      ("....."
                     ".XXX."
                     "..X.."
                     "..X.."
                     "....."),
    //V
    sf::String      ("..X.."
                     "..X.."
                     "..XXX"
                     "....."
                     "....."),
    //W
    sf::String       ("....."
                     ".X..."
                     ".XX.."
                     "..XX."
                     "....."),
    //X
    sf::String      ("....."
                     "..X.."
                     ".XXX."
                     "..X.."
                     "....."),
    //Y
    sf::String      ("....."
                     "..X.."
                     "XXXX."
                     "....."
                     "....."),
    //RY
    sf::String      ("....."
                     "....."
                     "XXXX."
                     "..X.."
                     "....."),
    //Z
    sf::String      ("....."
                     ".XX.."
                     "..X.."
                     "..XX."
                     "....."),
    //RZ
    sf::String      ("....."
                     "..XX."
                     "..X.."
                     ".XX.."
                     ".....")
};

sf::String Polyomino::tetromino[] =
{
    //I
    sf::String("..X."
               "..X."
               "..X."
               "..X."),
    //O
    sf::String("...."
               ".XX."
               ".XX."
               "...."),
    //T
    sf::String("...."
               "XXX."
               ".X.."
               "...."),
    //S
    sf::String("...."
               ".XX."
               "XX.."
               "...."),
    //Z
    sf::String("...."
               "XX.."
               ".XX."
               "...."),
    //J
    sf::String(".X.."
               ".X.."
               "XX.."
               "...."),
    //L
    sf::String(".X.."
               ".X.."
               ".XX."
               "....")
};

sf::String Polyomino::triomino[] = {
    //I
    sf::String(".X."
               ".X."
               ".X."),
    //L
    sf::String(".X."
               ".XX"
               "..."),
    //J
    sf::String(".X."
               "XX."
               "...")
};

sf::String Polyomino::domino[] =
{
    sf::String(".X"
               ".X")
};

sf::String Polyomino::monomino[] = {
  sf::String("X")
};

void Polyomino::initBoard(int level)
{
    if(level == 1)
    {
        setMonomino();
    }
    else if(level == 2)
    {
        setDomino();
    }
    else if(level == 3)
    {
        setTriomino();
    }
    else if(level == 4)
    {
        setTetromino();
    }
    else if(level == 5)
    {
        setPentomino();
    }
    if(pField)
    {
        delete [] pField;
    }
    pField = new unsigned char[FIELD_WIDTH*FIELD_HEIGHT];

    for (int x = 0; x < FIELD_WIDTH; x++) // Board Boundary
    {
        for (int y = 0; y < FIELD_HEIGHT; y++)
        {
            pField[y*FIELD_WIDTH + x] = (x == 0 || x == FIELD_WIDTH - 1 || y == FIELD_HEIGHT - 1) ? Polyomino::BOUNDARY_BLOCK : 0;
        }
    }
}

void Polyomino::setPentomino()
{
    OFFSET_X = 100;
    OFFSET_Y = 10;

    COUNT_OF_PIECES = 16;
    FIELD_WIDTH = 13;
    FIELD_HEIGHT = 21;
    COUNT_OF_BLOCKS = 5;
}

void Polyomino::setTetromino()
{
    OFFSET_X = 150;
    OFFSET_Y = 30;

    COUNT_OF_PIECES = 7;
    FIELD_WIDTH = 10;
    FIELD_HEIGHT = 20;
    COUNT_OF_BLOCKS = 4;
}

void Polyomino::setTriomino()
{
    OFFSET_X = 250;
    OFFSET_Y = 130;
    COUNT_OF_PIECES = 3;
    FIELD_WIDTH = 8;
    FIELD_HEIGHT = 15;
    COUNT_OF_BLOCKS = 3;

}

void Polyomino::setDomino()
{
    OFFSET_X = 300;
    OFFSET_Y = 200;
    COUNT_OF_PIECES = 1;
    FIELD_WIDTH = 6;
    FIELD_HEIGHT = 12;
    COUNT_OF_BLOCKS = 2;
}

void Polyomino::setMonomino()
{
    OFFSET_X = 340;
    OFFSET_Y = 200;
    COUNT_OF_PIECES = 1;
    FIELD_WIDTH = 5;
    FIELD_HEIGHT = 10;
    COUNT_OF_BLOCKS = 1;
}

unsigned char *Polyomino::field() const
{
    return pField;
}

int Polyomino::rotate(int px, int py, int r)
{
    int pi = 0;
    if(COUNT_OF_BLOCKS == 2)
    {
        switch(r%4)
        {
        case 0://0
        {
            //0  1
            //2  3
            pi = py * COUNT_OF_BLOCKS + px;
        }
            break;
        case 1://90
        {
            //2  0
            //3  1
            pi = 2 + py - (px * COUNT_OF_BLOCKS);
        }
            break;
        case 2: //180
        {
            //3   2
            //1   0
            pi = 3 - (py * COUNT_OF_BLOCKS) - px;
        }
            break;
        case 3://270
        {
            // 1  3
            // 0  2
            pi = 1 - py + (px * COUNT_OF_BLOCKS);
        }
            break;
        }
    }
    else if(COUNT_OF_BLOCKS == 3)
    {
        switch(r%4)
        {
        case 0://0
        {
            //0  1   2
            //3  4   5
            //6  7   8
            pi = py * COUNT_OF_BLOCKS + px;
        }
            break;
        case 1://90
        {
            //6  3  0
            //7  4  1
            //8  5  2
            pi = 6 + py - (px * COUNT_OF_BLOCKS);
        }
            break;
        case 2: //180
        {
            //8   7   6
            //5   4   3
            //2   1   0
            pi = 8 - (py * COUNT_OF_BLOCKS) - px;
        }
            break;
        case 3://270
        {

            // 2  5  8
            // 1  4  7
            // 0  3  6
            pi = 2 - py + (px * COUNT_OF_BLOCKS);
        }
            break;
        }
    }
    else if(COUNT_OF_BLOCKS == 4)
    {
        switch(r%4)
        {
        case 0://0
        {
            //0  1   2  3
            //4  5   6  7
            //8  9   10 11
            //12 13  14 15
            pi = py * COUNT_OF_BLOCKS + px;
        }
            break;
        case 1://90
        {
            //  12  8  4  0
            //  13  9  5  1
            //  14 10  6  2
            //  15 11  7  3
            pi = 12 + py - (px * COUNT_OF_BLOCKS);
        }
            break;
        case 2: //180
        {
            // 15  14  13  12
            // 11  10   9   8
            //  7   6   5   4
            //  3   2   1   0
            pi = 15 - (py * COUNT_OF_BLOCKS) - px;
        }
            break;
        case 3://270
        {
            // 3  7  11  15
            // 2  6  10  14
            // 1  5   9  13
            // 0  4   8  12
            pi = 3 - py + (px * COUNT_OF_BLOCKS);
        }
            break;
        }
    }
    else if(COUNT_OF_BLOCKS == 5)
    {
        switch(r%4)
        {
        case 0://0
        {
            //0  1   2  3  4
            //5  6   7  8  9
            //10 11  12 13 14
            //15 16  17 18 19
            //20 21  22 23 24
            pi = py * COUNT_OF_BLOCKS + px;
        }
            break;
        case 1://90
        {
            //20  15 10  5  0
            //21  16 11  6  1
            //22  17 12  7  2
            //23  18 13  8  3
            //24  19 14  9  4
            pi = 20 + py - (px * COUNT_OF_BLOCKS);
        }
            break;
        case 2: //180
        {
            //24   23  22  21  20
            //19   18  17  16  15
            //14   13  12  11  10
            //9     8   7   6   5
            //4     3   2   1   0
            pi = 24 - (py * COUNT_OF_BLOCKS) - px;
        }
            break;
        case 3://270
        {
            // 4  9  14  19  24
            // 3  8  13  18  23
            // 2  7  12  17  22
            // 1  6  11  16  21
            // 0  5  10  15  20
            pi = 4 - py + (px * COUNT_OF_BLOCKS);
        }
            break;
        }
    }
    return pi;
}

bool Polyomino::doesPieceFit(int nBlock, int nRotation, int nPosX, int nPosY)
{
    // All Field cells >0 are occupied
    for (int px = 0; px < COUNT_OF_BLOCKS; px++)
        for (int py = 0; py < COUNT_OF_BLOCKS; py++)
        {
            // Get index into piece
            int pi = rotate(px, py, nRotation);

            // Get index into field
            int fi = (nPosY + py) * FIELD_WIDTH + (nPosX + px);

            // Check that test is in bounds. Note out of bounds does
            // not necessarily mean a fail, as the long vertical piece
            // can have cells that lie outside the boundary, so we'll
            // just ignore them
            if (nPosX + px >= 0 && nPosX + px < FIELD_WIDTH)
            {
                if (nPosY + py >= 0 && nPosY + py < FIELD_HEIGHT)
                {
                    // In Bounds so do collision check
                    if (getElementOfPiece(nBlock, pi) != '.' && pField[fi] != 0)
                        return false; // fail on first hit
                }
            }
        }

    return true;
}


