/*
 * name:wenford 
 * email:26597925@qq.com
 *
*/
#include "Analyze.h"
InputFile   **input_files   = NULL;
int         nb_input_files   = 0;
Config 	   *config;


//打开文件计算文件行数，设置区块以及输入
static int open_input_file(char *file_name)
{
	if((access(file_name,F_OK))==-1) return -1;
	InputFile *f;
	GROW_ARRAY(input_files, nb_input_files);
	f = m_mallocz(sizeof(*f));
    if (!f)
        return -1;
	int index = nb_input_files - 1;
	input_files[index] = f;
	file_init(f, file_name);
	if(f->size >= BIGSIZE){
		f->is_mmap = 1;
		f->line = file_mmap_line(f);
	}else{
		f->line = file_by_line(f);
	}
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
	value = ini_get_value(config->ini, "nginx", "formart");
	config->nginx_formart = value;
	value = ini_get_value(config->ini, "apache", "formart");
	config->apache_formart = value;
}
/*static void call_line(u_char *buffer){
	printf("buffer:%s/n", buffer);
}*/

int main(int argc, char **argv)
{
	clock_t start, finish;
	double duration;
	int ret, i;
	char *split = ",";
	ret = 1;
	start = clock();
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
		printf("size:%ld \n", input_files[i]->size);
		//parse_line_block(input_files[i], call_line);
		destroy_file(input_files[i]);
	}
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf( "%f seconds\n", duration );
	destroy_ini(config->ini);
    cleanup_readini(config->ini_r);
	return 0;
}