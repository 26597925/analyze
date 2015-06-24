/*
 * name:wenford 
 * email:26597925@qq.com
 *
*/
#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include <time.h>

#include "IniParser.h"
#include "Util.h"
#include "File.h"

#define	 BIGSIZE 	 32212254720
#define	 MEDIUMSIZE  10737418240
#define  SMALLSIZE   1073741824

typedef struct Config{
	struct read_ini *ini_r;
	struct ini *ini;
	char *file_name;
	char *nginx_formart;
	char *apache_formart;
} Config;

extern InputFile  	**input_files;
extern int        	nb_input_files;