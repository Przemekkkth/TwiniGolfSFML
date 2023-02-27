#ifndef POLYOMINO_H
#define POLYOMINO_H
#include <SFML/System/String.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/String.hpp>

class Polyomino
{
public:
    static sf::String pentomino[16];
    static sf::String tetromino[7];
    static sf::String triomino[3];
    static sf::String domino[1];
    static sf::String monomino[1];
    constexpr static const int ANIM_BLOCK = 17;
    constexpr static const int BOUNDARY_BLOCK = 18;
    constexpr static const int GRID_SIZE = 32;

    Polyomino();
    void initBoard(int level);
    void setPentomino();
    void setTetromino();
    void setTriomino();
    void setDomino();
    void setMonomino();
    sf::String getElementOfPiece(int x, int y);
    int rotate(int px, int py, int r);
    bool doesPieceFit(int nBlock, int nRotation, int nPosX, int nPosY);

    unsigned char* field() const;

    int OFFSET_X;
    int OFFSET_Y;
    int COUNT_OF_PIECES;
    int FIELD_WIDTH;
    int FIELD_HEIGHT;
    int COUNT_OF_BLOCKS;
    unsigned char *pField;
    const sf::Vector2i RESOLUTION;
};

#endif // POLYOMINO_H
