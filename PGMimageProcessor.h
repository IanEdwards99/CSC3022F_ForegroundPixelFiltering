//Author: Ian Edwards EDWIAN004

#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include "ConnectedComponent.h"
#include <memory>

#ifndef PGMimageProcessor_h
#define PGMimageProcessor_h

namespace EDWIAN004 {

	class PGMimageProcessor
	{
        private:
            std::vector<std::unique_ptr<ConnectedComponent>> components;
            unsigned char ** data; //Hold input image in 2D array.
            int image_width; int image_height; //number of rows and cols in input image.
        public:
            PGMimageProcessor(std::string PGMfilename);

            int extractComponents(unsigned char  threshold, int minValidSize);

            int  filterComponentsBySize(int minSize, int maxSize);

            bool writeComponents(const std::string & outFileName);

            int getComponentCount(void) const;

            int getLargestSize(void) const;

            int getSmallestSize(void) const;

            void printComponentData(const ConnectedComponent & theComponent) const;

            void printComponents() const;

            unsigned char ** readData(std::string PGMfilename);

            unsigned char ** getData(){
                return data;
            };
            int getImage_width() const;
            int getImage_height() const;

            void setImage_width(const int width);
            void setImage_height(const int height);


    };

    #endif
}