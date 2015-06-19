/*
 * name:wenford 
 * email:26597925@qq.com
 *
*/
#include "File.h"

int file_init(InputFile *f, char *file){
	int ret;
	struct stat buf;
	ret = open(file, O_RDONLY, 0);
	if(ret < 0) return 0;
	f->file_name = file;
	f->fd = ret;
	fstat(f->fd, &buf);
	f->size = buf.st_size;
	return 1;
}

u_long file_by_line(InputFile *f)  
{  
    register u_char *p;  
    register short gotsp;  
    register int ch, len;  
    register u_long linect = 0;  
    u_char buf[MAXBSIZE];
	gotsp = 1;
	while ((len = read(f->fd, buf, MAXBSIZE)) > 0) {
		for (p = buf; len--;) {  
			ch = *p++;  
			if (ch == '\n'){
				++linect;  
			}
			if (isspace(ch))
				gotsp = 1;  
			else if (gotsp) {  
				gotsp = 0;
			}
		}
	}
	//如果最后一行不为空，说明数据还多一行
	if(!gotsp){
		++linect;
	}
	//重新启用还是需要重新设置，所以直接释放
	close(f->fd);
    return linect;  
}
//用内存映射防止内核重复复制带来的io消耗
u_long file_mmap_line(InputFile *f)  
{
    register u_long linect = 0;
	register short gotsp;
	int ch = '\n';
	f->addr = mmap(NULL, f->size, PROT_READ, MAP_PRIVATE, f->fd, 0);
	if(f->addr == MAP_FAILED) return -1;
	gotsp = 1;
	while (*f->addr){
		if (*f->addr == (char)ch){
			++linect;
		}
		if (isspace(*f->addr))
			gotsp = 1;  
		else if (gotsp) {  
			gotsp = 0;
		}
		f->addr++;
	}
	if(!gotsp){
		++linect;
	}
	return linect;
}

//单行读取
void parse_line_block(InputFile *f, InputBlock *b){
	register u_char *p;
	register int ch, len;
	register short gotsp;
    u_char buf[MAXBSIZE];
	ch = 0;
	gotsp = 1;
	//已经使用需要重新设置文件标识符
	f->fd = open(f->file_name, O_RDONLY, 0);
	while (f->fd && (len = read(f->fd, buf, MAXBSIZE)) > 0) {
		for (p = buf; len--;) {  
			ch = *p++;  
			if (ch == '\n'){
				
			}
		}
		if (isspace(ch))
			gotsp = 1;  
		else if (gotsp) {  
			gotsp = 0;
		}
		if(!gotsp){
			
		}
	}
}

//mmap内存映射读取
void parse_mmap_block(InputFile *f, void (*callline)(u_char *)){
	
}

void destroy_file(InputFile *f){
	if(f->is_mmap) munmap(f->addr, f->size);
	close(f->fd);
}
