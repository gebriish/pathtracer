#pragma once

struct Image;

Image* image_allocate(int width, int height, int channels);
void image_write_pixel(Image* image, int x, int y, unsigned int channel, float value);
void image_free(Image*& image);