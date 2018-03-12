#ifndef LIVESPLIT_OPENSPLIT_IMPORT
#define LIVESPLIT_OPENSPLIT_IMPORT
#include <stdbool.h>
#include "livesplit_core.h"
enum OpenSplit_LiveSplit_Errors { None, Base64_Decode_Error, File_Not_Found_Error};
extern enum OpenSplit_LiveSplit_Errors OpenSplit_Core_LiveSplit_Error;

struct decoded_image{
  unsigned long int approximate_size;
  unsigned char *image;
};

struct decoded_image * OpenSplit_Core_Get_LiveSplit_Icon(RunRef Loaded_Run, size_t Segment_Index);
Run OpenSplit_Core_Load_LiveSplit_Config(char *file_path, bool load_files);
#endif
