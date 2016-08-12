
#include <png.h>
#include <hdf5.h>
#include <hdf5_hl.h>
#include <stdint.h>
#include <malloc.h>
#include <string>
#include "h5png.hh"

int save_hdf5_image(const char *file_name, const char *img_name);
int save_png_image(const char *file_name);


/////////////////////////////////////////////////////////////////////////////////////////////////////
//main
/////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char *argv[])
{
  if(save_png_image("test.png") < 0)
  {

  }

  if(save_hdf5_image("image.h5", "image") < 0)
  {

  }

  if(hdf5_to_png("image.h5", "image") < 0)
  {

  }

  return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//save_png_image
/////////////////////////////////////////////////////////////////////////////////////////////////////

int save_png_image(const char *file_name)
{
  FILE *fp;
  png_structp png_ptr = NULL;
  png_infop info_ptr = NULL;
  png_uint_32 width = 200;
  png_uint_32 height = 100;
  int bit_depth = 8;
  int pixel_size = 3;
  png_byte **row_pointers = NULL;
  size_t x, y;

  if((png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL)) == NULL)
  {

  }

  if((info_ptr = png_create_info_struct(png_ptr)) == NULL)
  {

  }

  //set up error handling. 
  if(setjmp(png_jmpbuf(png_ptr)))
  {

  }

  png_set_IHDR(png_ptr,
    info_ptr,
    width,
    height,
    bit_depth,
    PNG_COLOR_TYPE_RGB,
    PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_DEFAULT,
    PNG_FILTER_TYPE_DEFAULT);

  if((fp = fopen(file_name, "wb")) == NULL)
  {

  }

  row_pointers = (png_byte **)png_malloc(png_ptr, height * sizeof(png_byte *));
  for(y = 0; y < height; ++y)
  {
    png_byte *row = (png_byte *)png_malloc(png_ptr, sizeof(uint8_t) * width * pixel_size);
    row_pointers[y] = row;
    for(x = 0; x < width; ++x)
    {

      *row++ = 255; //red
      *row++ = 0;   //green;
      *row++ = 0;   //blue;
    }
  }

  png_init_io(png_ptr, fp);
  png_set_rows(png_ptr, info_ptr, row_pointers);
  png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  //free
  /////////////////////////////////////////////////////////////////////////////////////////////////////

  for(y = 0; y < height; y++)
  {
    png_free(png_ptr, row_pointers[y]);
  }
  png_free(png_ptr, row_pointers);
  png_destroy_write_struct(&png_ptr, &info_ptr);
  fclose(fp);

  return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//save_hdf5_image
/////////////////////////////////////////////////////////////////////////////////////////////////////

int save_hdf5_image(const char *file_name, const char *img_name)
{
  hid_t fid;
  unsigned char *buf;
  hsize_t width = 200;
  hsize_t height = 100;
  const int pixel_size = 3;
  size_t x, y;
  size_t idx = 0;

  buf = (unsigned char*)malloc((size_t)width * (size_t)height * pixel_size * sizeof(unsigned char));

  for(y = 0; y < height / 2; ++y)
  {
    for(x = 0; x < width; ++x)
    {
      buf[idx]   = 255; //red
      buf[idx+1] = 0;   //green
      buf[idx+2] = 0;   //blue
      idx += 3;
    }
  }

  for(y = height / 2; y < height; ++y)
  {
    for(x = 0; x < width; ++x)
    {
      buf[idx]   = 0;   //red
      buf[idx+1] = 255; //green
      buf[idx+2] = 0;   //blue
      idx += 3;
    }
  }

  if((fid = H5Fcreate(file_name, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT)) < 0)
  {

  }

  if((H5IMmake_image_24bit(fid, img_name, width, height, "INTERLACE_PIXEL", buf)) < 0)
  {

  }

  if(H5Fclose(fid) < 0)
  {

  }

  free(buf);
  return 0;
}


