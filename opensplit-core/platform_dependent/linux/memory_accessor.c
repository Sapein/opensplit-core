#if defined(__linux__) && ((__GNUC__ > 3 || __GNUC__ == 3) && __GNUC__MINOR__ > 1)
#define MEMORY_ACCESSOR
#define _GNU_SOURCE
#include <stddef.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>

#endif
