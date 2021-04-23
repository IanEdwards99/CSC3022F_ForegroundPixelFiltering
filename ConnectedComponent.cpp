//Author: Ian Edwards - EDWIAN004

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>
#include <exception>
#include <memory>
#include "ConnectedComponent.h"

//Class method definitions
//Constructors:
EDWIAN004::ConnectedComponent::ConnectedComponent() : nrPixels(0), identifier(0), pixels(NULL) {}

EDWIAN004::ConnectedComponent::~ConnectedComponent(){
    for (int i = 0; i < pixels.size(); i++){
        pixels.pop_back();
    }
    //pixels vector is deleted when out of scope.
};

int EDWIAN004::ConnectedComponent::getNrPixels(){
    return this->nrPixels;
}
void EDWIAN004::ConnectedComponent::setNrPixels(int nrPixels){
    this->nrPixels = nrPixels;
};
void EDWIAN004::ConnectedComponent::setIdentifier(int identifier){
    this->identifier = identifier;
};
void EDWIAN004::ConnectedComponent::addToPixels(std::pair<int, int> vals){
    this->pixels.push_back(vals);
};
