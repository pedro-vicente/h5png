/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Purpose: Convert HDF5 image format to PNG format 
// 
//  History:
//     ver   YYYY-MM-DD   Programmer       Description
//    -----  ----------  --------------  ------------------------------------------------
//     v1   2016-07-07   Pedro Vicente    Read HDF5 file, export to PNG
//
// Usage is
// h5png -f <file_name> -i <image_name_in_file>
// with sample data
// h5png -f image.h5 -i image
//
/////////////////////////////////////////////////////////////////////////////////////////////////////



#include <png.h>
#include <hdf5.h>
#include <hdf5_hl.h>
#include <stdint.h>
#include <malloc.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "h5png.hh"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//main
/////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char *argv[])
{
  const char *file_name = NULL;
  const char *image_name = NULL;

  //check arguments
  if (argc < 5)
  {
    std::cout << "h5png -f <file_name> -i <image_name_in_file>" << std::endl;
    exit(1);
  }

  for (int i = 1; i < argc && argv[i][0] == '-'; i++)
  {
    switch (argv[i][1])
    {
    case 'i':
      image_name = argv[i+1];
      i++;
      break;
    case 'f':
      file_name = argv[i+1];
      i++;
      break;

    }
  }


  if(hdf5_to_png(file_name, image_name) < 0)
  {
    exit(1);
  }

  std::cout << file_name << " " << image_name << std::endl;

  return 0;
}
