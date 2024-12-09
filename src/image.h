#pragma once
#include <tuple>

struct Image;

struct PixelHandle {
    float* base;
    unsigned int channels;
};


Image* image_allocate(int width, int height, int channels);
std::pair<int, int> image_get_resolution(Image* image);
unsigned int image_get_channels(Image* image);
float image_read_pixel(Image* image, int x, int y, unsigned int channel);
PixelHandle image_get_pixel_handle(Image* image, int x, int y);
void image_pixel_write(PixelHandle handle, unsigned int channel, float value);
void image_free(Image*& image);
