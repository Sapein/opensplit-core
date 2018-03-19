#ifndef OPENSPLIT_CORE
#define OPENSPLIT_CORE

#include <stdbool.h>
#include <stddef.h>

struct decoded_image{
  unsigned long int approximate_size;
  unsigned char *image;
};

typedef struct decoded_image image;

void OpenSplit_Core_LiveSplit_Free_Image(struct decoded_image *image);

size_t OpenSplit_Core_Encode_To_Base64(const unsigned char *data, unsigned char *out,
				     size_t data_len, bool newline_flag);

size_t OpenSplit_Core_Decode_From_Base64(const unsigned char *data, unsigned char *out, size_t data_len);
#endif
