#include "opensplit_core.h"
#include <stdlib.h>
#include <string.h>
#include "deps/crypto-algorithms/base64.h"

size_t OpenSplit_Core_Encode_To_Base64(const unsigned char *data, unsigned char *out,
				     size_t data_len, bool newline_flag){
  return base64_encode(data, out, data_len, newline_flag);
}

size_t OpenSplit_Core_Decode_From_Base64(const unsigned char *data, unsigned char *out, size_t data_len){
  return base64_decode(data, out, data_len);
}
