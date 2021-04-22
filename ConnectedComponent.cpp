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
