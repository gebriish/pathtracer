#pragma once

struct Image
{
    int width, height, channels;
    float* data = nullptr;
};