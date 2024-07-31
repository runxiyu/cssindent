/*
 * Indent some fucking CSS.
 * Runxi Yu <https://runxiyu.org>
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define nl() { putchar('\n'); front = 1; }
#define indent() { for (unsigned int j = 0; j < depth; ++j) { putchar('\t'); } }
#define debug() { fprintf(stderr, "(qt=%d cm=%d fr=%d dp=%u c=%c)", quoted, commented, front, depth, buf[i]); }

				
int main(int argc, char **argv) {
	_Bool quoted = 0, commented = 0, front = 1;
	unsigned int depth = 0;
	unsigned int source_lines = 1; 
	int fd;
	if (argc == 1) {
		fd = 0;
	} else if (argc == 2) {
		fd = open(argv[1], 0);
	} else {
		fprintf(stderr, "Too many arguments\n");
		return 1;
	}
	for (;;) {                             
	        auto char buf[4096];                    
	        ssize_t len = read(fd, &buf, 4096);
	        if (len <= 0)                      
	                break;
	        for (ssize_t i = 0; i < len; ++i) {
			if (buf[i] == '/' && buf[i+1] == '*') {
				commented = 1;
				write(1, "/*", 2);
				continue;
			} else if (buf[i] == '*' && buf[i+1] == '/') {
				if (commented) {
					commented = 0;
					write(1, "*/", 2);
					continue;
				} else {
					fprintf(stderr, "%u: too many */\n", source_lines);
					return 1;
				}
			}
			if (commented) {
				putchar(buf[i]);
				continue;
			}
			if (buf[i] == '}') {
				if (!front) {
					putchar(';');
					nl();
				}
				if (--depth == (unsigned int) -1) {
					fprintf(stderr, "%u: too many }\n", source_lines);
					return 1;
				}
				indent();
				putchar('}');
				nl();
				continue;
			}
			if (buf[i] == '\n') {
				++ source_lines;
				continue;
			} else if (buf[i] == '\t') {
				continue;
			}
			if (buf[i] == ' ') {
				if (front) {
				} else if (!quoted && !commented) {
					if (buf[i+1] == ' ') {
						continue;
					}
					putchar(' ');
				}
				continue;
			} else if (buf[i] == '\t') {
				continue;
			}
			if (front) {
				indent();
			}
			if (buf[i] == ';') {
				putchar(';');
				nl();
			} else if (buf[i] == '{') {
				++depth;
				putchar('{');
				nl();
			} else {
				front = 0;
				putchar(buf[i]);
			}
		}
	}
}
