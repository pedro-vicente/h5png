#include <png.h>
#include <hdf5.h>
#include <hdf5_hl.h>
#include <iostream>
#include <stdlib.h>
#include "h5png.hh"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//usage
/////////////////////////////////////////////////////////////////////////////////////////////////////

void usage()
{
  std::cout << "h5png -f <file_name> -i <image_name_in_file_at_root>" << std::endl;
  exit(1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//main
/////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
  const char *file_name = NULL;
  const char *image_name = NULL;

  if (argc != 5)
  {
    usage();
  }

  for (int i = 1; i < argc; i++)
  {
    if (argv[i][0] == '-')
    {
      switch (argv[i][1])
      {
      case 'f':
        file_name = argv[i + 1];
        i++;
        break;
      case 'i':
        image_name = argv[i + 1];
        i++;
        break;
      default:
        usage();
      }
    }
    else
    {
      usage();
    }
  }

  if (hdf5_to_png(file_name, image_name) < 0)
  {
    exit(1);
  }

  std::cout << file_name << " " << image_name << std::endl;
  return 0;
}
