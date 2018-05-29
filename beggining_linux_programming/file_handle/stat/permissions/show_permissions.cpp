/*
 *	author	:	Gu-hwan Bae
 *	date	:	May 29, 2018
 */

/* showing file's permissions. */

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>	/* int chmod(const char* pathname, mode_t mode)
						   int stat(const char* pathname, struct stat* statbuf) */

std::string show_permission(mode_t);

int main(int argc, char* argv[]) {
	if(argc != 2) {
		std::cerr << "Usage : " << argv[0] << " filename\n";
		return -1;
	}

	const char* target = argv[1];
	struct stat st;

	if(stat(target, &st) < 0) {
		perror("stat()");
		return -1;
	}

	std::cout << "File permissions : " << show_permission(st.st_mode) << std::endl;

	return 0;
}

std::string show_permission(mode_t mode) {
    static const mode_t mask = 0x1ff, ps_mask = 0x7;
    static const mode_t is_r = 0x4, is_w = 0x2, is_x = 0x1;
    std::string buf;

	mode = mode & mask;
	mode_t permission = 0;
	for(;mode > 0; mode >>= 3) {
		std::string def {"---"};
		permission = mode & ps_mask;
		if(permission & is_r) {
			def[0] = 'r';
		}
		if(permission & is_w) {
			def[1] = 'w';
		}
		if(permission & is_x) {
			def[2] = 'x';
		}
		buf += def;
	}

	return buf;
}
