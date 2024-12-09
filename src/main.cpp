#include "image.h"
#include "io.h"
#include "log.h"

int main()
{
  Image* img = image_allocate(640, 400, 3);

  for(int i=0; i<400; i++)
  {
    for(int j=0; j<640; j++)
    {
      PixelHandle pixel = image_get_pixel_handle(img, j, i);
      image_pixel_write(pixel, 0, j / 640.0f);
      image_pixel_write(pixel, 1, i / 640.0f);
      image_pixel_write(pixel, 2, 0.0f);
    }
  }

  if(!io_image_write("output.png", img)) 
    LOG_SVER("failed to write image\n");
  
  image_free(img);
}
