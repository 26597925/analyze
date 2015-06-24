/*
 * name:wenford 
 * email:26597925@qq.com
 *
*/
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "DefType.h"
#include "Util.h"
#define MAXBSIZE 65536

typedef struct InputFile {
	int fd;//文件描述符
	char *file_name;//文件名称
	u_long line;//总行数
	size_t size;//文件大小
	
	short is_mmap;//是否是内存映射
	u_char *addr;
} InputFile;

int file_init(InputFile *f, char *file);

u_long file_by_line(InputFile *f);

u_long file_mmap_line(InputFile *f);

void destroy_file(InputFile *f);