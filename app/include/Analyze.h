/*
 * name:wenford 
 * email:26597925@qq.com
 *
*/
#include <stdio.h>
#include <inttypes.h>
#include <math.h>

#include "IniParser.h"
#include "Util.h"
#include "File.h"

typedef struct InputFile {
	char *file_name;//文件名称
	u_long line;//总行数
	int block;//多少个区块,每个区块分为一个输入流
} InputFile;
typedef struct InputBlock {
	int file_index;
	int start_line;//起始行
	int end_line;//终止行
	uint64_t start;
} InputBlock;
typedef struct Config{
	struct read_ini *ini_r;
	struct ini *ini;
	char *file_name;
	int block_line;
	char *nginx_formart;
	char *apache_formart;
} Config;

extern InputFile  	**input_files;
extern int        	nb_input_files;
extern InputBlock **input_blocks;
extern int        nb_input_blocks;