#include "../image.h"
#include "../internals/image_internal.h"
#include <cstddef>

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

std::pair<int, int> image_get_resolution(Image* image)
{
    return std::make_pair(image->width, image->height);
}

unsigned int image_get_channels(Image* image)
{
    return image->channels;
}

float image_read_pixel(Image* image, int x, int y, unsigned int channel)
{
    if (image == nullptr || x < 0 || y < 0 || channel >= static_cast<unsigned int>(image->channels))
    {
        return -1.0;
    }

    if (x >= image->width || y >= image->height)
    {
        return -1.0;
    }

    return image->data[(y * image->width + x) * image->channels + channel];    
}

PixelHandle image_get_pixel_handle(Image* image, int x, int y)
{
    if (image == nullptr || x < 0 || y < 0 || x >= image->width || y >= image->height) {
        return {nullptr, 0};
    }
    size_t base_index = (y * image->width + x) * image->channels;
    return {&image->data[base_index], image->channels};
}

void image_pixel_write(PixelHandle handle, unsigned int channel, float value) {
    if (handle.base == nullptr || channel >= handle.channels) {
        return;
    }
    handle.base[channel] = value;
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
