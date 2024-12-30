#include "Components/ASCIIGraphic.h"
#include <iostream>
#include <ostream>
#include <vector>

ASCIIGraphic::ASCIIGraphic() {}
ASCIIGraphic::~ASCIIGraphic() {}

int ASCIIGraphic::width(){
    auto mat = pixelMatrix();
    if(mat.size() > 0){
	return mat[0].size();
    }
    return 0;
}

int ASCIIGraphic::height(){
    auto mat = pixelMatrix();
    return mat.size();
}

std::vector<std::vector<wchar_t>> ASCIIGraphic::pixelMatrix(){
    return {};
}

void ASCIIGraphic::debugPrint(){
    std::wcout << std::endl;
    for(auto line : pixelMatrix()){
	for(auto c: line){
	    std::wcout << c;
	}
	std::wcout << std::endl;
    }
}

