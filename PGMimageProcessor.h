//Author: Ian Edwards EDWIAN004

#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include "ConnectedComponent.h"

#ifndef PGMimageProcessor_h
#define PGMimageProcessor_h

namespace EDWIAN004 {

	class PGMimageProcessor
	{
        private:
            std::vector<ConnectedComponent> components;

        public:
            int extractComponents(unsigned char  threshold, int minValidSize);

            int  filterComponentsBySize(int minSize, int maxSize);

            bool writeComponents(const std::string & outFileName);

            int getComponentCount(void) const;

            int getLargestSize(void) const;

            int getSmallestSize(void) const;

            void printComponentData(const ConnectedComponent & theComponent) const;
    };

    #endif
}