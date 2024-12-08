#include "../image.h"
#include "../internals/image_internal.h"

Image* image_allocate(int width, int height, int channels)
{
    if (width <= 0 || height <= 0 || channels <= 0 || channels > 4)
    {
        return nullptr;
    }

    Image* image = new Image;

    image->width    = width;
    image->height   = height;
    image->channels = channels;

    image->data = new float[width * height * channels]{};

    return image;
}

void image_write_pixel(Image* image, int x, int y, unsigned int channel, float value)
{
    if (image == nullptr || x < 0 || y < 0 || channel >= static_cast<unsigned int>(image->channels))
    {
        return;
    }

    if (x >= image->width || y >= image->height)
    {
        return;
    }

    image->data[(y * image->width + x) * image->channels + channel] = value;
}

void image_free(Image*& image)
{
    if (image == nullptr)
        return;

    delete[] image->data;
    image->data = nullptr;
    delete image;
    image = nullptr;
}