//Author: Ian Edwards - EDWIAN004

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>
#include <exception>
#include "PGMimageProcessor.h"
#include <queue>
#include <memory>

//Class method definitions
EDWIAN004::PGMimageProcessor::PGMimageProcessor(std::string PGMfilename) : image_height(0), image_width(0), data(nullptr){
    data = EDWIAN004::PGMimageProcessor::readData(PGMfilename); //load in 2D array image.
};

int EDWIAN004::PGMimageProcessor::extractComponents(unsigned char  threshold, int minValidSize){
    
	int identifier = 0;

	//Start at top left pixel of image and scan image rows to find a foreground pixel.
	for (int y = 0; y < image_height; y++){
		for (int x=0; x < image_width; x++) {
			if (data[y][x] >= threshold){ //start BFS.
				std::queue<std::pair<int,int>> neighbours; //queue holding coordinates to unprocessed neighbours, initially empty.
				neighbours.push(std::pair<int, int> {y, x}); //push coordinates to queue.

				EDWIAN004::ConnectedComponent component = EDWIAN004::ConnectedComponent();
				++identifier;
				component.setIdentifier(identifier);
				
				while (!neighbours.empty()){
					std::pair<int,int> val = neighbours.front();
					neighbours.pop();
					if (data[val.first][val.second] >=threshold){
						//set the n
						component.addToPixels(val); 
						component.setNrPixels(component.getNrPixels()+1);
						
						data[val.first][val.second] = 0;				//set foreground pixel to background now that its processed.
						
						if (val.second>0){
							neighbours.push(std::pair<int, int> {val.first, val.second-1});
						}
						if (val.second < image_width-1){
							neighbours.push(std::pair<int, int> {val.first, val.second+1});
						}
						if (val.first > 0){
							neighbours.push(std::pair<int, int> {val.first-1, val.second});
						}
						if (val.first < image_height-1){
							neighbours.push(std::pair<int, int> {val.first+1, val.second});
						}
						
					}
				}

				//is it big enough? 
				
				if (component.getNrPixels() > minValidSize){
					std::unique_ptr<ConnectedComponent> ptr(new ConnectedComponent(component));
					components.push_back(std::move(ptr));
				}
				
			}
		}
	}

	//Clear memory of PGM input image.
	if (data != nullptr){ //matrix deconstructor.
        for (int k = 0; k < image_height; k++){
            if (data[k] != nullptr){
                delete[] data[k];
            }
        }
	    delete[] data;
    }

    return components.size();
};

int EDWIAN004::PGMimageProcessor::filterComponentsBySize(int minSize, int maxSize){
	for (std::vector<std::unique_ptr<ConnectedComponent>>::iterator it = components.begin(); it < components.end(); it++){
		if ((*it)->getNrPixels() < minSize or (*it)->getNrPixels() > maxSize)
			components.erase(it);
	}
	return components.size();
};

bool EDWIAN004::PGMimageProcessor::writeComponents(const std::string & outFileName){
	unsigned char ** output = new unsigned char*[image_height];
	for (int i= 0; i < image_height; i++){
		output[i] = new unsigned char[image_width];
		for (int j = 0; j<image_width; j++)
			output[i][j] = 0; //set all values to white.
	}
	//loop through vector of components and add each pixel coord to image as 255.
	
	for (int k = 0; k < components.size(); k++){
		std::vector<std::pair<int,int>> pixelArray = components[k]->getPixels();
		for (int j = 0; j < pixelArray.size(); j++){
			output[pixelArray[j].first][pixelArray[j].second] = 255;
		}
	}
	std::ofstream wf("./output/" + outFileName, std::ios::out | std::ios::binary);
	if(!wf) {
		std::cout << "Cannot open file!" << std::endl;
		return false;
	}
	wf << "P5" << std::endl << image_width << " " << image_height << std::endl << 255 << std::endl;
	for (int i = 0; i < image_height; i ++){
		wf.write((char*)(output[i]), image_width); //write out each row in frame_matrix in question from imageSequence.
	}
	wf.close();
    return true;
};

int EDWIAN004::PGMimageProcessor::getComponentCount(void) const {
    return components.size();
};

int EDWIAN004::PGMimageProcessor::getLargestSize(void) const{
	int largest = 0;
    for (auto& it : components){
		int pixels = it->getNrPixels();
		if (pixels > largest)
			largest = pixels;
	}
	return largest;
}

int EDWIAN004::PGMimageProcessor::getSmallestSize(void) const{
	int smallest = components[0]->getNrPixels();
    for (auto& it : components){
		int pixels = it->getNrPixels();
		if (pixels < smallest)
			smallest = pixels;
	}
	return smallest;
};

void EDWIAN004::PGMimageProcessor::printComponentData(const ConnectedComponent & theComponent) const{
	std::cout << "Component ID: " << theComponent.getID() << "| Number of pixels: " << theComponent.getNrPixels() << std::endl;
};

void EDWIAN004::PGMimageProcessor::printComponents() const{
	for (int i =0; i < components.size(); i++){
		EDWIAN004::PGMimageProcessor::printComponentData(*(components[i]));
	}
}

unsigned char ** EDWIAN004::PGMimageProcessor::readData(std::string PGMfilename){
    int rows, cols;
	//read file data function: (args: filename)
	std::string line;
	std::ifstream ifs;

	ifs.open(PGMfilename, std::ios::binary);
	if (!ifs){std::cerr << "File open failed!" << std::endl;} //check if file exists
   	else
	{
		//initial block reads in header info.
   		getline(ifs >> std::ws, line);
		getline(ifs >> std::ws,line);
		while (line[0] == '#'){ getline(ifs >> std::ws, line);}
		cols = std::stoi(line.substr(0, line.find_first_of(" ")));
		image_width = cols;
		rows = std::stoi(line.substr(line.find_first_of(" ")+1, line.length() - line.find_first_of(" ")-1));
		image_height = rows;

		unsigned char ** matrix = new unsigned char*[rows];
		for (int i = 0; i < rows; i++){
			matrix[i] = new unsigned char[cols];
		}
		
		//read in a chunk of values from file into matrix row.
		int x = 0; int y = 0;
		getline(ifs, line);
		while (!ifs.eof()){
			for (int y = 0; y < rows; y++){
				ifs.read((char*)matrix[y], cols);
			}
		}
		ifs.close();
		return matrix; //no matrix was created due to file error.
	}
    return nullptr;
};

int EDWIAN004::PGMimageProcessor::getImage_width() const{
    return image_width;
};

int EDWIAN004::PGMimageProcessor::getImage_height() const{
    return image_height;
};

void EDWIAN004::PGMimageProcessor::setImage_width(const int width){
    image_width = width;
};

void EDWIAN004::PGMimageProcessor::setImage_height(const int height){
    image_height = height;
};
