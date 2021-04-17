//Author: Ian Edwards - EDWIAN004

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>
#include <exception>
#include "PGMimageProcessor.h"

//Class method definitions
int EDWIAN004::PGMimageProcessor::extractComponents(unsigned char  threshold, int minValidSize){
    return 0;
};

int EDWIAN004::PGMimageProcessor::filterComponentsBySize(int minSize, int maxSize){
    return 0;
};

bool EDWIAN004::PGMimageProcessor::writeComponents(const std::string & outFileName){
    return 0;
};

int EDWIAN004::PGMimageProcessor::getComponentCount(void) const {
    return 0;
};

int EDWIAN004::PGMimageProcessor::getLargestSize(void) const{
    return 0;
}

int EDWIAN004::PGMimageProcessor::getSmallestSize(void) const{
    return 0;
};

void EDWIAN004::PGMimageProcessor::printComponentData(const ConnectedComponent & theComponent) const{

};