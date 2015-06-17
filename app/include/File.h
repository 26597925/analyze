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
#define MAXBSIZE 65536

typedef struct InputFile {
	int fd;//文件描述符
	char *file_name;//文件名称
	u_long line;//总行数
	int block;//多少个区块,每个区块分为一个输入流
	size_t size;//文件大小
	
	short is_mmap;//是否是内存映射
	u_char *addr;
} InputFile;

typedef struct InputBlock {
	int file_index;
	long start_line;//起始行
	long end_line;//终止行
} InputBlock;

int file_init(InputFile *f, char *file);

u_long file_by_line(InputFile *f);

u_long file_mmap_line(InputFile *f);

void parse_by_line(InputFile *f, void (*callline)(u_char *));

void destroy_file(InputFile *f);