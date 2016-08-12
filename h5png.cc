#include <png.h>
#include <hdf5.h>
#include <hdf5_hl.h>
#include <stdint.h>
#include <malloc.h>
#include <string>
#include "h5png.hh"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//hdf5_to_png
/////////////////////////////////////////////////////////////////////////////////////////////////////

int hdf5_to_png(const char *file_name, const char *img_name)
{
  hid_t fid;
  hsize_t width;
  hsize_t height;
  hsize_t pixel_size;
  char interlace[20];
  hssize_t npals;
  unsigned char *buf;

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  //HDF5
  /////////////////////////////////////////////////////////////////////////////////////////////////////

  if((fid = H5Fopen(file_name, H5F_ACC_RDONLY, H5P_DEFAULT)) < 0)
  {
    return -1;
  }

  if(H5IMget_image_info(fid, img_name, &width, &height, &pixel_size, interlace, &npals) < 0)
  {

  }

  buf = (unsigned char*)malloc((size_t)width * (size_t)height *  (size_t)pixel_size * sizeof(unsigned char));

  if(H5IMread_image(fid, img_name, buf) < 0)
  {

  }

  if(H5Fclose(fid) < 0)
  {

  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  //PNG
  /////////////////////////////////////////////////////////////////////////////////////////////////////

  FILE *fp;
  png_structp png_ptr = NULL;
  png_infop info_ptr = NULL;
  int bit_depth = 8;
  png_byte **row_pointers = NULL;
  size_t x, y;
  size_t idx_buf = 0;

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
    (png_uint_32)width,
    (png_uint_32)height,
    (int)bit_depth,
    PNG_COLOR_TYPE_RGB,
    PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_DEFAULT,
    PNG_FILTER_TYPE_DEFAULT);

  //add the extension .png to input HDF5 file name
  std::string str_file_name(file_name);
  str_file_name += ".png";

  if((fp = fopen(str_file_name.c_str(), "wb")) == NULL)
  {

  }

  row_pointers = (png_byte **)png_malloc(png_ptr, (png_uint_32)height * sizeof(png_byte *));
  for(y = 0; y < height; ++y)
  {
    png_byte *row = (png_byte *)png_malloc(png_ptr, sizeof(uint8_t) * (png_uint_32)width * (int)pixel_size);
    row_pointers[y] = row;
    for(x = 0; x < width; ++x)
    {

      *row++ = buf[idx_buf];   //red
      *row++ = buf[idx_buf+1]; //green;
      *row++ = buf[idx_buf+2]; //blue;
      idx_buf  += 3;
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

  free(buf);

  return 0;
}

