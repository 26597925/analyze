/*
 * name:wenford 
 * email:26597925@qq.com
 *
*/
#include "File.h"

u_long file_line(char *file)  
{  
    register u_char *p;  
    register short gotsp;  
    register int ch, len;  
    register u_long linect = 0;  
    int fd;  
    u_char buf[MAXBSIZE];
    if (file) {
        if ((fd = open(file, O_RDONLY, 0)) < 0) 
            return -1;  
		gotsp = 1;
        while ((len = read(fd, buf, MAXBSIZE)) > 0) {
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
		close(fd);
    }
    return linect;  
}