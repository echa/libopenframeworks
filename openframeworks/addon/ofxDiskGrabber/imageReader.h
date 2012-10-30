#ifndef _IMAGE_READER_H_
#define _IMAGE_READER_H_

#include <string>

class ImageReader
{
 public:
    virtual bool readFrame(std::string file, int width, int height, unsigned char *pixels) = 0;
    virtual bool checkExtension(std::string file) = 0;
};

#endif
