#pragma once

struct Image
{
    int width, height;
    unsigned int channels;
    float* data = nullptr;
};
