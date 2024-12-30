#include "Core/Sprite/SpriteExport.h"
#include "unicode/stringpiece.h"
#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <unicode/unistr.h>

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
    std::cout << "reading raw sprite" << std::endl;
    if (path.empty()) {
        throw std::runtime_error("Path is not set.");
    }

    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + path);
    }

    std::vector<std::vector<wchar_t>> matrix;

    std::string line;
    while (std::getline(file, line)) {
        std::cout<< "raw: " << line << std::endl;
        icu::UnicodeString unicodeLine = icu::UnicodeString::fromUTF8(icu::StringPiece(line.c_str()));
        std::cout << "length: " << unicodeLine.length() << std::endl;
        std::wstring wideLine(unicodeLine.getBuffer(), unicodeLine.getBuffer() + unicodeLine.length());
        if(wideLine.size() <= 1) continue;
        std::vector<wchar_t> row(wideLine.begin(), wideLine.end() - 1);
        matrix.push_back(row);
    }

    file.close();

    raw = std::move(matrix);
}

std::vector<std::vector<wchar_t>> SpriteExport::rawImage(){
    return raw;
}

void SpriteExport::slice() {
    auto image = rawImage();

    if (!slicing) {
        sliced_arr = {image};
        return;
    }

    std::vector<std::vector<std::vector<wchar_t>>> slices;

    int rows = slicing->rows;
    int cols = slicing->columns;
    int cellWidth = slicing->cellWidth;
    int cellHeight = slicing->cellHeight;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            std::vector<std::vector<wchar_t>> slice;
            for (int i = 0; i < cellHeight; ++i) {
                std::vector<wchar_t> row;
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

std::vector<std::vector<std::vector<wchar_t>>> SpriteExport::sliced(){
    return sliced_arr;
}
