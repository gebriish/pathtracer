#include "../io.h"
#include "../internals/image_internal.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb/stb_image_write.h"

bool io_image_write(const char* path, Image* image)
{
    if (!path || !image || !image->data)
        return false;

    unsigned char* stbData = new unsigned char[image->width * image->height * image->channels];

    for (int y = 0; y < image->height; ++y)
    {
        for (int x = 0; x < image->width; ++x)
        {
            int pixel_index = (image->width * y + x) * image->channels;
            for (int i = 0; i < image->channels; i++)
            {
                float value = image->data[pixel_index + i];
                value = value < 0.0f ? 0.0f : (value > 1.0f ? 1.0f : value);
                stbData[pixel_index + i] = static_cast<unsigned char>(value * 255);
            }
        }
    }

    int stride_in_bytes = image->width * image->channels;
    bool success = stbi_write_png(path, image->width, image->height, image->channels, stbData, stride_in_bytes) != 0;

    delete[] stbData;
    return success;
}