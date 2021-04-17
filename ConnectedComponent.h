//Author: Ian Edwards EDWIAN004

#include <string>
#include <vector>
#include <cctype>
#include <cmath>

#ifndef ConnectedComponents_h
#define ConnectedComponents_h

namespace EDWIAN004 {

	class ConnectedComponent
	{
        private:
            int nrPixels;
            int identifier;
            std::vector<std::pair<int,int>> pixels;

        public:
            ConnectedComponent();
            ConnectedComponent(int nrPixels, int identifier, std::vector<std::pair<int, int>> pixels);
            ~ConnectedComponent(void);

        //implement movable

    };

    #endif
}