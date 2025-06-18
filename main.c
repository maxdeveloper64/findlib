#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <unistd.h>
#include <dlfcn.h>
#include <string.h>

unsigned long long findLibrary(const char *library, pid_t pid) {
char mapFilename[1024];
char buffer[9076];
FILE *fd;
unsigned long long addr = 0;

	if (pid == -1) {
		snprintf(mapFilename, sizeof(mapFilename), "/proc/self/maps");
	} else {
		snprintf(mapFilename, sizeof(mapFilename), "/proc/%d/maps", pid);
	}

	fd = fopen(mapFilename, "r");

	while(fgets(buffer, sizeof(buffer), fd)) {
		if (strstr(buffer, library)) {
			addr = strtoull(buffer, NULL, 16);
			break;
		}
	}

	fclose(fd);

	return addr;
}


int main(int argc, char * argv[]) {
    printf("Hello !!\n");
    return 0;
}
