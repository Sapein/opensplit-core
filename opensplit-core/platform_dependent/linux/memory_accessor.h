#if defined(__linux__) && ((__GNUC__ > 2 || (__GNUC__ == 2 && __GNUC__MINOR__ > 15)))
#include <sys/types.h>

/* Change to use _'s prior to name, and have special numberspace */
enum OpenSplit_Memory_Access_Errors { NONE, INVALID_SIZE, PROCESS_NOT_FOUND,
				      READ_FORBIDDEN, PARTIAL_READ, UNKNOWN_ERROR};

/* This is the main method to be used for reading memory if you have the process name.
 *
 * Arguments:
 *   - process_name = The name of the process
 *   - address = The address of the data you are looking for
 *   - output = where to store the data
 *   - size = the size of the data you are looking for.
 * 
 * Returns: an integer that represents on the of the memory errors
 *
 * Note: This _could_ fail on getting the process_id. 
 */     
unsigned int read_memory(char *process_name, void *address, void *output, size_t size);

/* This is the main method to be used for reading memory if you have the process ID.
 *
 * Arguments:
 *   - os_id = The ID of the process
 *   - address = The address of the data you are looking for
 *   - output = where to store the data
 *   - size = the size of the data you are looking for.
 * 
 * Returns: an integer that represents on the of the memory errors
 *
 */     
unsigned int read_memory_pid(pid_t os_pid, void *address, void *output, size_t size);
#endif
