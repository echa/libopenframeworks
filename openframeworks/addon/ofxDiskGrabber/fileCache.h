#ifndef _FILECACHE_
#define _FILECACHE_

#include "imageReader.h"

#include <string>
#include <map>

/*
  Cache proxy that caches the first n elements requested.
  Note: This cache assumes that the requests for the same image are always
  made with the same height and width.
  If you need something else subclass it.
*/
class FileCache : public ImageReader
{
 public:
    /**
       @param imgReader  image reader to use (etc. png reader)
       @param size       number of images to cache
       @param pixelSize  number of bytes per pixel
    */
    FileCache(ImageReader* imgReader, int size, int pixelSize);
    virtual ~FileCache(void);

    virtual bool readFrame(std::string file, int width, int height, unsigned char *pixels);
    virtual bool checkExtension(std::string file);

 protected:
    static unsigned long hash(std::string str);

    int size;
    int pixelSize;
    ImageReader *imgReader;
    std::map<unsigned long, unsigned char *> cache;
};

#endif
