#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/fcntl.h>
#include <unistd.h>

#include "../constants.h"

#define LDP_DEV "/dev/ldp"

int main() {
	int channels = 0;
	int status   = 0;
	int fd	     = 0;

	printf("Opening %s\n", LDP_DEV);

	if ((fd = open(LDP_DEV, O_RDWR)) == -1) {
		perror("Failed: ");
		return -1;
	}

	printf("Will try to perform ioctl on %s\n", LDP_DEV);
	
	if ((status = ioctl(fd, LDP_IOGCHANNELS, &channels)) == -1) {
		perror("Failed to get channels");
		goto hard_release;
	}

	printf("Channels: %d\n", channels);

	if ((status = ioctl(fd, LDP_IOSCHANNELS, &channels)) == -1) {
		perror("Failed to get channels: ");
		goto hard_release;
	}

	return 0;

hard_release:
	if (!fd) {
		close(fd);
	}
	return -1;
}
