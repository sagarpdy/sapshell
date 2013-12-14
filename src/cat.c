#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define ERROR_STR_LEN 30
#define BUFFER_LEN    1024
int cat_main(int argc, char* argv[]) {
	int i, fd = -1, ret = -EINVAL;
	char error_str[ERROR_STR_LEN + 1] = {0};
	char buffer[BUFFER_LEN + 1] = {0};
	if (argc < 2) {
		fprintf(stderr, "USAGE : %s file1 [file2 ...]\n", argv[0]);
		return -EINVAL;
	}
	for (i = 1; i < argc; ++i) {
		memset(buffer, 0, BUFFER_LEN + 1);
		fd = open(argv[i], O_RDONLY);
		if (fd < 0) {
			ret = errno;
			strerror_r(ret, error_str, ERROR_STR_LEN) ? \
			fprintf(stderr, "Unable to open file : %s\n", argv[i]) : \
			fprintf(stderr, "Error - %s - when opening : %s\n", error_str, argv[i]);
		} else {
			while(ret = read(fd, buffer, BUFFER_LEN)) {
				buffer[ret] = 0;
				printf("%s", buffer);
				if (ret < BUFFER_LEN) break;
			}
			if (!ret) {
				ret = errno;
				strerror_r(ret, error_str, ERROR_STR_LEN) ? \
				fprintf(stderr, "Unable to read file : %s\n", argv[i]) : \
				fprintf(stderr, "Error - %s - when reading : %s\n", error_str, argv[i]);
			} else
				ret = 0;
			close(fd);
		}
		if (ret)
			return ret;
		else
			ret = 0;
	}
	return ret;
}
