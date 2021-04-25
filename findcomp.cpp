//Author: Ian Edwards EDWIAN004
//Driver file for C++ program which
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <cctype>
#include <cmath>
#include "PGMimageProcessor.h"

int main (int argc, char *argv[])
{ 
	//findcomp options PGMfile

	std::string PGMfilename; //input filename.
	int nrComponents = 0;
	int min = 3; int max = 0; //imgwidth * imgheight
	 int threshold = 128; //default
	bool p = false; //print out component data.
	bool w = false; //write out retained components.
	std::string outPGMfile = "";

	if (argc < 2) { std::cout << "Incorrect options inputted." << std::endl;} //basic error checking.
	else{
		if (argc == 2)
			PGMfilename = argv[1]; //filename comes last in given format
		else{
			PGMfilename = argv[argc-1]; //filename comes last in given format
			int i = 1;
			while (i < argc-1){
				if (argv[i] == std::string("-t")){
					threshold = std::stoi(argv[i+1]);
					i += 2;
				}
				else if (argv[i] == std::string("-s")){
					min = std::stoi(argv[i+1]);
					max = std::stoi(argv[i+2]);
					i += 3;
				}
				else if (argv[i] == std::string("-w")){
					w = true;
					outPGMfile = argv[i+1];
					i += 2;
				}
				else if (argv[i] == std::string("-p")){
					p = true;
					i += 1;
				}
			}
		}
	}
	EDWIAN004::PGMimageProcessor imageProc = EDWIAN004::PGMimageProcessor(PGMfilename); //PGMimageProcessor instance created on stack as automatic variable.

	//set default max component size.
	if (max ==0)
		max = imageProc.getImage_height() * imageProc.getImage_width();
	//basic range error handling.
	if (threshold > 255 or threshold < 0) 
		threshold = 128;

	std::cout << "filename:" << PGMfilename << std::endl;
	std::cout << "image width: " << imageProc.getImage_width() << " image height: " << imageProc.getImage_height() << std::endl;
	std::cout << "min: " << min << " max:" << max << std::endl;
	std::cout << "threshold: " << threshold <<  std::endl;
	std::cout << p << std::endl;
	std::cout << w << std::endl;

	nrComponents = imageProc.extractComponents(threshold, min);
	 
	int size = imageProc.filterComponentsBySize(min, max);
	if (p){
		imageProc.printComponents();
		std::cout << "Components: " << imageProc.getComponentCount() << std::endl;
		std::cout << "Smallest: " << imageProc.getSmallestSize() << std::endl;
		std::cout << "Largest: " << imageProc.getLargestSize() << std::endl;
	}
	if (w){
		bool passed = imageProc.writeComponents(outPGMfile);
		if (passed)
			std::cout << "Write successful." << std::endl;
		else
			std::cout << "Write failed!." << std::endl;
	}

	std::cout << "Program exited." << std::endl;
	return 0; // always return a value to calling system

}

