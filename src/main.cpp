#include <iostream>

#include "image.h"
#include "io.h"

int main()
{
  Image* img = image_allocate(640, 400, 3);

  for(int i=0; i<400; i++)
  {
    for(int j=0; j<640; j++)
    {
      image_write_pixel(img, j, i, 0, j/640.0f);
      image_write_pixel(img, j, i, 1, i/640.0f);
      image_write_pixel(img, j, i, 2, 0.0);
    }
  }
  
  io_image_write("output.png", img);
  image_free(img);
}