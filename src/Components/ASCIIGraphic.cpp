#include "../.././includes/Components/ASCIIGraphic.h"
#include <vector>

ASCIIGraphic::ASCIIGraphic() {}
ASCIIGraphic::~ASCIIGraphic() {}

int ASCIIGraphic::width(){
    auto mat = ascii();
    if(mat.size() > 0){
	return mat[0].size();
    }
    return 0;
}

int ASCIIGraphic::height(){
    auto mat = ascii();
    return mat.size();
}

std::vector<std::vector<char>> ASCIIGraphic::ascii(){
    return {};
}

