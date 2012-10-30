#include <png.h>
#include <stdlib.h>
#include <stdio.h>

#include <ofUtils.h>
#include "pngReader.h"

std::string PngReader::extension = ".png";

bool PngReader::readFrame(std::string file, int width, int height, unsigned char *mem)
{
    png_structp png_ptr;
    png_infop info_ptr;
    png_bytepp row_pointers;
    unsigned int sig_read = 0;
    int i, channels, img_w, img_h;
    FILE *f;

    if(! (f = fopen(file.c_str(), "r"))) {
        ofLog(OF_LOG_NOTICE, "PngReader - can't open file %s", file.c_str());
        return false;
    }

    if((png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0)) == 0)
    {
        goto close;
    }

    if((info_ptr = png_create_info_struct(png_ptr)) == 0)
    {
        goto free_png;
    }

    if(setjmp(png_jmpbuf(png_ptr)))
    {
        goto free_info;
    }

    png_init_io(png_ptr, f);
    png_set_sig_bytes(png_ptr, sig_read);
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING |
                 PNG_TRANSFORM_EXPAND | PNG_TRANSFORM_STRIP_ALPHA, 0);

//    unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    row_pointers = png_get_rows(png_ptr, info_ptr);
    img_w = png_get_image_width(png_ptr, info_ptr);
    img_h = png_get_image_height(png_ptr, info_ptr);
    channels = png_get_channels(png_ptr, info_ptr);

    // image to small to be clipped
    if(img_w < width || img_h < height)
    {
        ofLog(OF_LOG_NOTICE, "PngReader - can't clip file %s to %dx%d",
              file.c_str(), width, height);
        goto free_info;
    }

    for(i = 0; i < height; i++)
    {
        memcpy(mem + (i * width * channels),
               row_pointers[i],
               width * channels);
    }

    fclose(f);
    // TODO: check png_info is really freed
    png_destroy_read_struct(&png_ptr, &info_ptr, 0);
    return true;

 free_info:
    // TODO png_destroy_info_struct(&png_info, png_infopp_NULL, png_infopp_NULL);
 free_png:
    png_destroy_read_struct(&png_ptr, 0, 0);
 close:
    fclose(f);
    return false;
}
