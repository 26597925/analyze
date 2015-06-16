/*
 * name:wenford 
 * email:26597925@qq.com
 *
*/
#include "Analyze.h"
InputFile   **input_files   = NULL;
int         nb_input_files   = 0;
InputBlock **input_blocks = NULL;
int        nb_input_blocks = 0;
Config 	   *config;

/*static int add_input_streams(int file_index){
	InputBlock *ibk = m_mallocz(sizeof(*ibk));
	if (!ibk) return -1;
	GROW_ARRAY(input_blocks, nb_input_blocks);
	input_blocks[nb_input_blocks - 1] = ibk;
	ibk->file_index = file_index;
}*/

//打开文件计算文件行数，设置区块以及输入
static int open_input_file(char *file_name)
{
	InputFile *f;
	GROW_ARRAY(input_files, nb_input_files);
	f = m_mallocz(sizeof(*f));
    if (!f)
        return -1;
	input_files[nb_input_files - 1] = f;
	f->file_name = file_name;
	f->line = file_line(file_name);
	f->block = ceil(f->line/(float)config->block_line);
	return 1;
}

//解析配置文件
static void parse_config(){
	config = m_mallocz(sizeof(*config));
	char *value;
	config->ini_r = NULL;
	config->ini = read_ini(&config->ini_r, "./config/config.ini");
	value = ini_get_value(config->ini, "base", "filename");
	config->file_name = value;
	value = ini_get_value(config->ini, "base", "blockline");
	config->block_line = atoi(value);
	value = ini_get_value(config->ini, "nginx", "formart");
	config->nginx_formart = value;
	value = ini_get_value(config->ini, "apache", "formart");
	config->apache_formart = value;
}

int main(int argc, char **argv)
{
	int ret, i;
	char *split = ",";
	ret = 1;
	parse_config();
	char *file_name;
    while((file_name = str_split( &config->file_name, split)))
	{
		open_input_file(file_name);
	}
	printf("nb_input_files:%d \n", nb_input_files);
	for(i =0; i< nb_input_files; i++){
		printf("filename:%s \n", input_files[i]->file_name);
		printf("line:%ld \n", input_files[i]->line);
		printf("block:%d \n", input_files[i]->block);
	}
	destroy_ini(config->ini);
    cleanup_readini(config->ini_r);
	return 0;
}