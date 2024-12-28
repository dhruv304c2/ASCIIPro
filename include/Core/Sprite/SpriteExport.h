#ifndef SPRITEEXPORT_H
#define SPRITEEXPORT_H

#include <algorithm>
#include <random>
#include <string>
#include <vector>

struct Slicing{
    int rows = 0;
    int columns = 0;
    int cellWidth = 0;
    int cellHeight = 0;

    Slicing(int rows, int columns, int cellWidth, int cellHeight){
        this -> rows = std::move(rows);
        this -> columns = std::move(columns);
        this -> cellWidth = std::move(cellWidth);
        this -> cellHeight = std::move(cellHeight);
    }
};

class SpriteExport {
public:
    SpriteExport(std::string path);
    ~SpriteExport();
    void useSlicing(Slicing slicing);
    SpriteExport asUnsliced();
    std::vector<std::vector<std::vector<char>>> sliced();
    std::vector<std::vector<char>> rawImage();
private:
    std::string path;
    Slicing* slicing;
    std::vector<std::vector<char>> raw;
    std::vector<std::vector<std::vector<char>>> sliced_arr;

    void usePath(std::string path);
    void readRaw();
    void slice();
};

#endif
