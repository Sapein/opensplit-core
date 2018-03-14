#ifndef OPENSPLIT_CORE
#define OPENSPLIT_CORE

#include <stdbool.h>
#include <stddef.h>

size_t OpenSplit_Core_Encode_To_Base64(const unsigned char *data, unsigned char *out,
				     size_t data_len, bool newline_flag);

size_t OpenSplit_Core_Decode_From_Base64(const unsigned char *data, unsigned char *out, size_t data_len);
#endif
