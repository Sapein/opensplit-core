#include "criterion/criterion.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../opensplit-core/opensplit_core.h"
#define DATA_TO_ENCODE "test"
#define ENCODED_OUTPUT "dGVzdA=="

void setup(void){
}

void teardown(void){
}

TestSuite(OpenSplit_Encryption);

Test(OpenSplit_Encryption, Base_64_Encode){
  const unsigned char *data_to_encode = (unsigned char *)DATA_TO_ENCODE;
  unsigned char *encoded_data = malloc(strlen(ENCODED_OUTPUT));
  int data_size = strlen((char *)data_to_encode);
  int encoded_size;
  encoded_size = OpenSplit_Core_Encode_To_Base64(data_to_encode, encoded_data, data_size, false);
  cr_assert_eq(encoded_size, strlen(ENCODED_OUTPUT));
  cr_assert_str_eq((char *)encoded_data, ENCODED_OUTPUT);
  free(encoded_data);
}

Test(OpenSplit_Encryption, Base_64_Decode){
  const unsigned char *data_to_decode = (unsigned char *)ENCODED_OUTPUT;
  unsigned char *decoded_data = malloc(strlen(DATA_TO_ENCODE));
  int data_size = strlen(ENCODED_OUTPUT);
  int decoded_size;
  decoded_size = OpenSplit_Core_Decode_From_Base64(data_to_decode, decoded_data, data_size);
  cr_assert_eq(decoded_size, strlen(DATA_TO_ENCODE));
  cr_assert_str_eq((char *)decoded_data, DATA_TO_ENCODE);
  free(decoded_data);
}

/* TestSuite(LiveSplit_Usage); */

