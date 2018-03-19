#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livesplit.h"
#include "livesplit_core.h"
#include "../opensplit_core.h"
#define URL_OFFSET 13

enum OpenSplit_LiveSplit_Errors OpenSplit_Core_LiveSplit_Error = None;

struct decoded_image * OpenSplit_Core_Get_LiveSplit_Icon(RunRef Loaded_Run, size_t Segment_Index){
  long int decode_size;
  long int actual_size_decoded = 0;
  struct decoded_image *image = NULL;
  SegmentRef Segment = Run_segment(Loaded_Run, Segment_Index);
  const char *const_encoded_icon = Segment_icon(Segment);
  unsigned char *encoded_icon = (unsigned char *)const_encoded_icon;
  unsigned char *decoded_icon = 0;

  decode_size = OpenSplit_Core_Decode_From_Base64(encoded_icon + URL_OFFSET, NULL,
						  strlen((char *)encoded_icon + URL_OFFSET));
  decoded_icon = (unsigned char *)malloc(decode_size);
  if(decoded_icon != NULL){
    actual_size_decoded = OpenSplit_Core_Decode_From_Base64(encoded_icon + URL_OFFSET, decoded_icon,
							    strlen(const_encoded_icon + URL_OFFSET));
    if(decode_size > actual_size_decoded || decoded_icon == NULL){
      OpenSplit_Core_LiveSplit_Error = Base64_Decode_Error;
    }

    image = (struct decoded_image *)malloc(sizeof(struct decoded_image) * actual_size_decoded);
    image->image = decoded_icon;
    image->approximate_size = actual_size_decoded;

  }else{
    image = NULL;
    OpenSplit_Core_LiveSplit_Error = Allocation_Error;
  }

  return image;
}

Run OpenSplit_Core_Load_LiveSplit_Config(char *file_path, bool load_files){
  static ParseRunResult result;
  Run Loaded_Run;
  FILE *lss = NULL;
  lss = fopen(file_path, "r");
  if(lss){
    result = Run_parse_file_handle(fileno(lss), file_path, load_files);
    Loaded_Run = ParseRunResult_unwrap(result);

    fclose(lss);
  }else if(!lss){
    OpenSplit_Core_LiveSplit_Error = File_Not_Found_Error;
    Loaded_Run = Run_new();
  }

  return Loaded_Run;
}
