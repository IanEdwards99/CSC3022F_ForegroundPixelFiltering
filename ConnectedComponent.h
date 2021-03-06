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
            ConnectedComponent(void);
            ConnectedComponent(int nrPixels, int identifier, std::vector<std::pair<int, int>> pixels);
            ~ConnectedComponent(void);

            ConnectedComponent(const ConnectedComponent& p);
            ConnectedComponent(ConnectedComponent && p);

            ConnectedComponent& operator=(const ConnectedComponent& rhs);
            ConnectedComponent& operator=(ConnectedComponent&& rhs);

            int getID() const;
            int getNrPixels() const;
            std::vector<std::pair<int,int>> getPixels(){ return pixels; };
            void setNrPixels(int nrPixels);
            void setIdentifier(int identifier);
            void addToPixels(std::pair<int, int> vals);
        //implement copy and copy operator

        //implement movable

    };

    #endif
}