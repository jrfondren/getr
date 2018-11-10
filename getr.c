#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#ifdef __linux__
#define REPORT \
	"User time      : %ld s, %ld us\n" \
	"System time    : %ld s, %ld us\n" \
	"Time           : %lld ms (%.3f ms/per)\n" \
	"Max RSS        : %ld kB\n" \
	"Page reclaims  : %ld\n" \
	"Page faults    : %ld\n" \
	"Block inputs   : %ld\n" \
	"Block outputs  : %ld\n" \
	"vol ctx switches   : %ld\n" \
	"invol ctx switches : %ld\n"
#define VALS \
	usage.ru_maxrss, \
	usage.ru_minflt, \
	usage.ru_majflt, \
	usage.ru_inblock, \
	usage.ru_oublock, \
	usage.ru_nvcsw, \
	usage.ru_nivcsw
#else
#define REPORT \
	"User time      : %ld s, %ld us\n" \
	"System time    : %ld s, %ld us\n" \
	"Time           : %lld ms (%.3f ms/per)\n" \
	"Max RSS        : %ld kB\n" \
	"Shared RSS     : %ld kB\n" \
	"Unshared Data  : %ld\n" \
	"Unshared Stack : %ld\n" \
	"Page reclaims  : %ld\n" \
	"Page faults    : %ld\n" \
	"Swaps          : %ld\n" \
	"Block inputs   : %ld\n" \
	"Block outputs  : %ld\n" \
	"Sigs received  : %ld\n" \
	"vol ctx switches   : %ld\n" \
	"invol ctx switches : %ld\n"
#define VALS \
	usage.ru_maxrss, \
	usage.ru_ixrss, \
	usage.ru_idrss, \
	usage.ru_isrss, \
	usage.ru_minflt, \
	usage.ru_majflt, \
	usage.ru_nswap, \
	usage.ru_inblock, \
	usage.ru_oublock, \
	usage.ru_nsignals, \
	usage.ru_nvcsw, \
	usage.ru_nivcsw
#endif

int main (int argc, char **argv, char **environ) {
	struct rusage usage;
	int i, count;
	pid_t child;
	if (argc > 2) {
		count = atoi(argv[1]);
		for (i = 0; i < count; i++) {
			if (0 != posix_spawn(&child, argv[2], NULL, NULL, &argv[2], environ)) {
				fprintf(stderr, "posix_spawn failed: %s", strerror(errno));
				return 1;
			}
			waitpid(child, NULL, 0);
		}
		getrusage(RUSAGE_CHILDREN, &usage);
		fprintf(stderr, REPORT,
			(long int)usage.ru_utime.tv_sec,
			(long int)usage.ru_utime.tv_usec,
			(long int)usage.ru_stime.tv_sec,
			(long int)usage.ru_stime.tv_usec,
			(((usage.ru_utime.tv_usec + usage.ru_stime.tv_usec)/1000) + ((usage.ru_utime.tv_sec + usage.ru_stime.tv_sec)*1000)),
			(((usage.ru_utime.tv_usec + usage.ru_stime.tv_usec)/1000.0) + ((usage.ru_utime.tv_sec + usage.ru_stime.tv_sec)*1000.0))/count,
			VALS
		);
	} else {
		fprintf(stderr, "usage: %s <n> <command> [<args> ...]\n", argv[0]);
		return 1;
	}
	return 0;
}
