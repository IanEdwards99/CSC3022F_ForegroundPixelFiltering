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



unsigned char **readData(std::string PGMfilename, int * rows, int * cols){
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
		*cols = std::stoi(line.substr(0, line.find_first_of(" ")));
		*rows = std::stoi(line.substr(line.find_first_of(" ")+1, line.length() - line.find_first_of(" ")-1));
		unsigned char ** matrix = new unsigned char*[*rows];
		for (int i = 0; i < *rows; i++){
			matrix[i] = new unsigned char[*cols];
		}

		//read in a chunk of values from file into matrix row.
		int x = 0; int y = 0;
		getline(ifs, line);
		while (!ifs.eof()){
			for (int y = 0; y < *rows; y++){
				ifs.read((char*)matrix[y], *cols);
			}
		}
		ifs.close();
		return matrix;
	}
}

int main (int argc, char *argv[])
{ 
	//findcomp options PGMfile

	std::string PGMfilename;
	int * rows =new int[1]; int * cols=new int[1];
	int min = 3; int max = 0; //imgwidth * imgheight
	 int threshold = 128; //default
	bool p = false; //print out component data.
	bool w = false; //write out retained components.
	std::string outPGMfile = "";

	if (argc < 2) { std::cout << "Incorrect options inputted." << std::endl;} //basic error checking.
	else{
		if (argc == 2)
			PGMfilename = argv[argc-1]; //filename comes last in given format
		else{
			PGMfilename = argv[argc-1]; //filename comes last in given format
			int i = 1;
			while (i < argc){
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
	
	std::cout << min << " " << max << std::endl;
	std::cout << threshold <<  std::endl;
	std::cout << p << std::endl;
	std::cout << w << std::endl;

	std::cout << "1st." << std::endl;
	unsigned char ** data = readData(PGMfilename, rows, cols); //load up matrix.
		std::ofstream wf("./output/" + PGMfilename + "TEST.pgm", std::ios::out | std::ios::binary);
		if(!wf) {
			std::cout << "Cannot open file!" << std::endl;
		}
		wf << "P5" << std::endl << *cols << " " << *rows << std::endl << 255 << std::endl;
		for (int i = 0; i < *rows; i ++){
			wf.write((char*)(data[i]), *cols); //write out each row in frame_matrix in question from imageSequence.
		}
		wf.close();


	std::cout << "Program exited." << std::endl;
	return 0; // always return a value to calling system

}

