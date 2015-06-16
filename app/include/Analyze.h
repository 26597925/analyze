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
	char *file_name;//�ļ�����
	u_long line;//������
	int block;//���ٸ�����,ÿ�������Ϊһ��������
} InputFile;
typedef struct InputBlock {
	int file_index;
	int start_line;//��ʼ��
	int end_line;//��ֹ��
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