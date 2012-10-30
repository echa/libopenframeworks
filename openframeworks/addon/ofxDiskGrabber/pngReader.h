#ifndef _PNG_READER_H_
#define _PNG_READER_H_

#include <stdint.h>
#include <string>

#include "imageReader.h"

class PngReader : public ImageReader {
 public:
    bool readFrame(std::string file, int width, int height, unsigned char *pixels);
    bool checkExtension(std::string file) {
        if(file.size() < 5) {
            return false;
        }
        return (file.compare(file.size() - 4, 4, extension) == 0) ? true : false;
    }
 private:
    static std::string extension;
};

#endif
