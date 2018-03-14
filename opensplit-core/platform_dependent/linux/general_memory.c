/* #if defined(__linux__) && ((__GNUC__ > 3 || __GNUC__ == 3) && __GNUC__MINOR__ > 1) */
#define _GNU_SOURCE
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/uio.h>

#include "general_memory.h"

enum Core_Memory_errors OpenSplit_Core_Memory_Error = 0;

/* This is a bit hacky, but should work. Probaby should refactor in the future */
/* This also has some eror checking, but it may not be comprehensive */
pid_t pidof(char *process_name){
  int i = 0;
  unsigned short int alloc_failures = 0;
  FILE *proc_status_file = NULL;
  char *location_name;
  char *test_name = malloc(strlen(process_name));
  char status = 0;
  unsigned long int maximum_process_count = 0;
  unsigned long int process_number = 1000; /* Userland PIDS start at 1,000*/
  pid_t os_pid = 0;

  if(test_name == NULL){
    for(i = 0; test_name != NULL && alloc_failures < ALLOCATION_FAILURE_LIMIT; i++){
      test_name = malloc(strlen(process_name));
      if(test_name == NULL){
	alloc_failures++;
      }
    }
    if(alloc_failures >= ALLOCATION_FAILURE_LIMIT){
      goto get_pid_alloc_fail;
    }else{
      maximum_process_count = 0;
    }
  }

  maximum_process_count = get_maximum_count();
  if(OpenSplit_Core_Memory_Error != MEMORY_ALLOCATION_FAILURE || maximum_process_count > 0){
    for(; process_number < maximum_process_count; process_number++){
      if(alloc_failures >= ALLOCATION_FAILURE_LIMIT){
	goto get_pid_alloc_fail;
      }
      location_name = malloc(strlen("/proc/") + (sizeof(char) * process_number) +
			     strlen("/cmdline") + 2);
      if(location_name != NULL){
	sprintf(location_name, "/proc/%ld/cmdline", process_number);

	proc_status_file = fopen(location_name, "r");
	if(proc_status_file != NULL){
	  fscanf(proc_status_file, "%d %s %c %d", (int *)NULL, test_name, &status, (int *)NULL);
	  if(strcmp(test_name, process_name) == 0){
	    if(status == 'R' || status == 'S' || status == 'D'){
	      free(location_name);
	      fclose(proc_status_file);
	      break;
	    }else{
	      status = 0;
	    }
	  }
	  fclose(proc_status_file);
	}
	
	free(location_name);
      }else{
	alloc_failures++;
      }
    }
  }

  free(test_name);
  if(status == 0){
    process_number = 0;
    OpenSplit_Core_Memory_Error = PROCESS_NOT_FOUND;
  }

 get_pid_alloc_fail:
  if(alloc_failures >= ALLOCATION_FAILURE_LIMIT){
    OpenSplit_Core_Memory_Error = MEMORY_ALLOCATION_FAILURE;
    process_number = 0;
  }

 get_pid_end:
  return process_number;
}

/* Here be dragons :P */
unsigned long int get_maximum_count(void){
  FILE *max_file = NULL;
  long int i = 0;
  unsigned long int maximum_pid = 0;
  unsigned char *size_string = malloc(sizeof(unsigned char) * 1);
  char held_char = 1;
  if(size_string != NULL){
    max_file = fopen(MAX_PID_LOCATION, "r");
    for(i = 1; held_char != '\0' || held_char != EOF ; i++){
      held_char = fgetc(max_file);
      size_string = realloc(size_string, sizeof(unsigned char) * i);
    }
    size_string = realloc(size_string, sizeof(unsigned char) * (i + 1));
    *(size_string + (i + 1)) = '\0';
    fclose(max_file);
    maximum_pid = strtoul((char *)size_string, NULL, 10);
    free(size_string);
  }else{
    OpenSplit_Core_Memory_Error = MEMORY_ALLOCATION_FAILURE;
  }
  return maximum_pid;
}
/* #endif */
