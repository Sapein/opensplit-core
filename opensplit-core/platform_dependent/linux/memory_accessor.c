#if defined(__linux__) && ((__GNUC__ > 2 || (__GNUC__ == 2 && __GNUC__MINOR__ > 15)))
#define MEMORY_ACCESSOR
#define _GNU_SOURCE
#include <stddef.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include "general_memory.h"
#include "memory_accessor.h"


unsigned int read_memory(char *process_name, void *address, void *output, size_t size){
  pid_t os_pid = pidof(process_name);
  switch(OpenSplit_Core_Memory_Error){
  case(PROCESS_ID_NOT_FOUND):
    return PROCESS_NOT_FOUND;
    break;
  case(MEMORY_ALLOCATION_FAILURE):
    return MEMORY_ALLOCATION_FAILURE;
    break;
  default:
    ; /*NOOP*/
  }
  return read_memory_pid(os_pid, address, output, size); 
}

unsigned int read_memory_pid(pid_t os_pid, void *address, void *output, size_t size){
  struct iovec local_address_space[1] = {
                                         { .iov_base = output,
					   .iov_len = size}
                                        };

  struct iovec remote_address_space[1] = {
                                          { .iov_base = output,
					    .iov_len = size}
                                         };
  int mem_error = 0;

  if(size == 0){
    return INVALID_SIZE;
  }

  mem_error = process_vm_readv(os_pid, local_address_space, 1, remote_address_space, 1, 0);
  if(mem_error == 0){
    return READ_FORBIDDEN;
  }else if(mem_error < size){
    return PARTIAL_READ;
  }else if(mem_error > size){
    return UNKNOWN_ERROR;
  }
  return NONE;
}
#endif
