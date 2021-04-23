//Author: Ian Edwards - EDWIAN004

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>
#include <exception>
#include "PGMimageProcessor.h"
#include <queue>

//Class method definitions
EDWIAN004::PGMimageProcessor::PGMimageProcessor(std::string PGMfilename) : components(NULL), image_height(0), image_width(0), data(nullptr){
    data = EDWIAN004::PGMimageProcessor::readData(PGMfilename); //load in 2D array image.
	std::cout << data[0][0] << std::endl;
};

EDWIAN004::PGMimageProcessor::~PGMimageProcessor(void){
    	//Clear memory of PGM input image.
	if (data != nullptr){ //matrix deconstructor.
        for (int k = 0; k < image_height; k++){
            if (data[k] != nullptr){
                delete data[k];
            }
        }
	    delete data;
    }
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

				while (!neighbours.empty()){
					std::pair<int,int> val = neighbours.front();
					neighbours.pop();
					if (data[val.first][val.second] >=threshold){
						//set the n
						component.addToPixels(val); 
						component.setNrPixels(component.getNrPixels());
						component.setIdentifier(identifier++);
						data[val.first][val.second] = 0;//set foreground pixel to background now that its processed.

						if (x>0)
							neighbours.push(std::pair<int, int> {y, x-1});
						if (x < image_width-1)
							neighbours.push(std::pair<int, int> {y, x+1});
						if (y > 0)
							neighbours.push(std::pair<int, int> {y-1, x});
						if (y < image_height-1)
							neighbours.push(std::pair<int, int> {y+1, x});

					}
				}

				//is it big enough? 
				if (component.getNrPixels() > minValidSize)
					components.push_back(component);
				
				//data[y][x] = 0; //set foreground pixel to background now that its processed.
			};
		}
	}


    //found a value, push to queue, find neighbours, if foreground pixels, add to component, push to queue. Set current foreground pixel to 0 in image.
    EDWIAN004::ConnectedComponent *component = new EDWIAN004::ConnectedComponent(); //create component on heap.
    //at a point, check neighbours, if foreground pixels, add to ConnectedComponent. Push 
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
				//std::cout << matrix[y] << std::endl;
			}
		}
		ifs.close();
		return matrix; //no matrix was created due to file error.
	}
    return nullptr;
};

int EDWIAN004::PGMimageProcessor::getImage_width(){
    return image_width;
};

int EDWIAN004::PGMimageProcessor::getImage_height(){
    return image_height;
};

void EDWIAN004::PGMimageProcessor::setImage_width(const int width){
    image_width = width;
};

void EDWIAN004::PGMimageProcessor::setImage_height(const int height){
    image_height = height;
};
