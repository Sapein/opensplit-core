#if defined(__linux__) && ((__GNUC__ > 2 || (__GNUC__ == 2 && __GNUC__MINOR__ > 15)))
#include <unistd.h>

#define ALLOCATION_FAILURE_LIMIT 5
#define MAX_PID_LOCATION "/proc/sys/kernel/pid_max"

enum Core_Memory_errors {NO_ERRORS, MEMORY_ALLOCATION_FAILURE, PROCESS_ID_NOT_FOUND};
extern enum Core_Memory_errors OpenSplit_Core_Memory_Error;

pid_t pidof(char *process_name);
unsigned long int get_maximum_count(void);
#endif
