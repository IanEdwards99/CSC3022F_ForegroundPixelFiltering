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

EDWIAN004::ConnectedComponent::ConnectedComponent(int nrPixels, int identifier, std::vector<std::pair<int, int>> pixels) : nrPixels(nrPixels), identifier(identifier), pixels(pixels){};

EDWIAN004::ConnectedComponent::~ConnectedComponent(){
    for (int i = 0; i < pixels.size(); i++){
        pixels.pop_back();
    }
    //pixels vector is deleted when out of scope.
};

EDWIAN004::ConnectedComponent::ConnectedComponent(const EDWIAN004::ConnectedComponent & p) : nrPixels(p.nrPixels), identifier(p.identifier), pixels(NULL){
    if (&p.pixels != nullptr){
        pixels = p.pixels;
    }
};

EDWIAN004::ConnectedComponent& EDWIAN004::ConnectedComponent::operator=(const EDWIAN004::ConnectedComponent & rhs){
    if (this != &rhs){
        this-> nrPixels = rhs.nrPixels;
        this->identifier = rhs.identifier;
        if (&this->pixels != nullptr){
            for (int i = 0; i<pixels.size(); i++){
                if (&this->pixels[i] != nullptr)
                    delete &this->pixels[i];
            }
            this->pixels.clear();
        }
        if (&rhs.pixels != nullptr)
            this->pixels = rhs.pixels;
    }
    return *this;
};

EDWIAN004::ConnectedComponent::ConnectedComponent(EDWIAN004::ConnectedComponent && p) : nrPixels(p.nrPixels), identifier(p.identifier), pixels(NULL){
    p.pixels.clear();
};

EDWIAN004::ConnectedComponent& EDWIAN004::ConnectedComponent::operator=(EDWIAN004::ConnectedComponent && rhs){
    if (this != &rhs){
        this-> nrPixels = rhs.nrPixels;
        this-> identifier = rhs.identifier;
        if (&this->pixels != nullptr){
            for (int i = 0; i<pixels.size(); i++){
                if (&this->pixels[i] != nullptr)
                    delete &this->pixels[i];
            }
           this->pixels.clear();
           if (!rhs.pixels.empty())
            this->pixels = std::move(rhs.pixels);
        }
    }
    return *this;
}

int EDWIAN004::ConnectedComponent::getID() const{
    return this->identifier;
}

int EDWIAN004::ConnectedComponent::getNrPixels() const{
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
