#include "../io.h"
#include "../internals/image_internal.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb/stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

#include "../log.h"

#include <fstream>
#include <sstream>
#include <iostream>

TxtFile io_load_txt_file(const char* filePath) {
    TxtFile load_file;
    load_file.content = "";

    std::ifstream file(filePath);
    if (!file) {
        load_file.valid = false;
		LOG_SVER("IO Error: unable to open file: %s\n", filePath);
        return load_file;
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    load_file.content = buffer.str();
    load_file.valid = true;

    return load_file;
}

bool io_load_txt_file_lines(const char* filePath, std::vector<std::string>& lines)
{
    if(!lines.empty())
        lines.clear();

    std::ifstream input_stream(filePath);
    if(!input_stream.is_open())
    {
        LOG_SVER("IO Error: unable to open file: %s\n", filePath);
        return false;
    }

    std::string word;
    while(std::getline(input_stream, word))
    {
        lines.push_back(word);
    }

    input_stream.close();
    return true;
}

void io_write_txt_file(const char* filePath, const std::string& content) {
    std::ofstream file(filePath);
    if (!file) {
		LOG_SVER("IO Error: could not open file for writing: %s\n", filePath);
        return;
    }

    file << content;
    if (!file) {
		LOG_SVER("IO Error: writing to file failed: %s\n", filePath);
    }

    file.close();
}

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
