#include "Core/Sprite/SpriteExport.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

SpriteExport::SpriteExport(std::string path) {
    slicing = nullptr;
    usePath(path);
    readRaw();
    slice();
}

SpriteExport::~SpriteExport() {}

SpriteExport SpriteExport::asUnsliced(){
    SpriteExport copy = *this;
    copy.slicing = nullptr;
    return copy;
}

void SpriteExport::usePath(std::string path) {
    this->path = std::move(path);
}

void SpriteExport::useSlicing(Slicing slicing) {
    this -> slicing = std::move(&slicing);
}

void SpriteExport::readRaw() {
    if (path.empty()) {
        throw std::runtime_error("Path is not set.");
    }

    std::ifstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open the file.");
    }

    std::vector<std::vector<char>> image;
    std::string line;
    size_t maxWidth = 0;

    while (std::getline(file, line)) {
        //-1 neglects end line characters
        maxWidth = std::max(maxWidth, line.size()-1);
        std::vector<char> row(line.begin(), line.end()-1);
        image.push_back(row);
    }

    for (auto& row : image) {
        while (row.size() < maxWidth) {
            row.push_back('_');
        }
    }

    file.close();
    raw = image;
}

std::vector<std::vector<char>> SpriteExport::rawImage(){
    return raw;
}

void SpriteExport::slice() {
    auto image = rawImage();

    if (!slicing) {
        sliced_arr = {image};
        return;
    }

    std::vector<std::vector<std::vector<char>>> slices;

    int rows = slicing->rows;
    int cols = slicing->columns;
    int cellWidth = slicing->cellWidth;
    int cellHeight = slicing->cellHeight;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            std::vector<std::vector<char>> slice;
            for (int i = 0; i < cellHeight; ++i) {
                std::vector<char> row;
                for (int j = 0; j < cellWidth; ++j) {
                    int x = r * cellHeight + i;
                    int y = c * cellWidth + j;
                    if (x < image.size() && y < image[0].size()) {
                        row.push_back(image[x][y]);
                    }
                }
                slice.push_back(row);
            }
            slices.push_back(slice);
        }
    }
    sliced_arr = slices;
}

std::vector<std::vector<std::vector<char>>> SpriteExport::sliced(){
    return sliced_arr;
}


