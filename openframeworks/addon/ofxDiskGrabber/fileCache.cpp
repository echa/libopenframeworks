#include <string.h>
#include <ofUtils.h>
#include "fileCache.h"

typedef std::map<unsigned long int, unsigned char *>::iterator cache_itr;

FileCache::FileCache(ImageReader *p, int s, int ps) :
    size(s),
    pixelSize(ps),
    imgReader(p)
{
}

FileCache::~FileCache(void)
{
    cache_itr itr;

    for(itr = cache.begin(); itr != cache.end(); itr++)
    {
        delete[] itr->second;
    }
}

bool FileCache::readFrame(std::string file, int width, int height, unsigned char *pixels)
{
    unsigned long h;
    int nbytes = height * width * pixelSize;

    h = hash(file);

    cache_itr itr = cache.find(h);
    if(itr != cache.end())
    {
        memcpy(pixels, itr->second, nbytes);
        // DBG("Serving from cache %s", file.c_str());
        return true;
    }

    if(! imgReader->readFrame(file, width, height, pixels))
    {
        return false;
    }

    // cache first 'size' elements
    if((int) cache.size() < size)
    {
        ofLog(OF_LOG_NOTICE, "Caching %s (%d Bytes)", file.c_str(), nbytes);
        unsigned char *cp = new unsigned char[nbytes];
        memcpy(cp, pixels, nbytes);
        cache[h] = cp;
    } else {
        ofLog(OF_LOG_NOTICE, "Cache full %s", file.c_str());
    }

    return true;
}

bool FileCache::checkExtension(std::string file)
{
    return imgReader->checkExtension(file);
}

unsigned long FileCache::hash(std::string str)
{
    const char *s = str.c_str();
    unsigned long hash = 0;
    char c;

    while((c = *s++))
    {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}
