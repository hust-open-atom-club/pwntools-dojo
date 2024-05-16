#include "util.h"
#include <libgen.h>
#include <limits.h>
#include <time.h>

static char guess[] = "我是谁???\0";
static char filename[] = "image.txt\0";

void get_dir_path(char *path) {
        // 获取当前可执行文件的绝对路径
        int ret = readlink("/proc/self/exe", path, UTIL_MAX_LEN);
        if (ret < 0) {
                perror("readlink error");
                path = NULL;
                return;
        }

        path = dirname(path);
        // printf("Directory is %s\n", path);
}

void print_color(char * str, char * color, char * bgcolor)
{
        char fmt[UTIL_MAX_LEN + 0x10] = {0};

        if (strlen(str) <= UTIL_MAX_LEN) {
                if (bgcolor != NULL)
                        sprintf(fmt, "%s%s%s %s %s", LOG_BOLD, bgcolor, color, str, LOG_RESET);
                else
                        sprintf(fmt, "%s%s %s %s", LOG_BOLD, color, str, LOG_RESET);
                printf("%s", fmt);
                return;
        }
}

void print_str_color(char * str, char * color, char * bgcolor)
{
        const int cnt = 68;
        int i, padding, remain = 0;
        char upper_str[UTIL_MAX_LEN] = {0};

        // upper string
        for (int i = 0; str[i] != '\0'; i++) {
                upper_str[i] = toupper(str[i]);
                if (i == UTIL_MAX_LEN) {
                        break;
                }
        }

        padding = (cnt - 2 - strlen(str)) / 2;
        remain = (cnt - 2 - strlen(str)) % 2;

        // padding
        for (i = 0; i < padding; i++) {
                printf("=");
        }

        // print string
        print_color(upper_str, color, bgcolor);

        // padding
        for (i = 0; i < padding; i++) {
                printf("=");
        }
        if (remain) {
                printf("=");
        }
        printf("\n");
}

static inline void print_time()
{
	time_t timep;
	struct tm *p;
	time (&timep);
	p = gmtime(&timep);
	printf("%d年%d月%d日%d:%d:%d",1900+p->tm_year, 1+p->tm_mon, p->tm_mday, 8+p->tm_hour, p->tm_min, p->tm_sec);
}

int get_abs_path(char * filename, char *abs_path)
{
        get_dir_path(abs_path);
        // get file absolute path
        if (abs_path == NULL) {
                return -1;
        }
        strcat(abs_path, "/");
        strcat(abs_path, filename);
        return 0;
}

int print_image(char * pokemon_name, char * filename)
{
	char read_string[UTIL_MAX_LEN], file_path[UTIL_MAX_LEN];
	FILE * fptr = NULL;
        int flag = 0;

        if (get_abs_path(filename, file_path) < 0) {
                fprintf(stderr, "error get absolute path %s\n", file_path);
                return -1;
        }
        
        // open pokemon text art file
	if((fptr = fopen(file_path,"r")) == NULL) {
		fprintf(stderr, "error opening %s\n", file_path);
		return -1;
	}

        // print pokemon text art
        print_str_color(guess, LOG_BLUE, NULL);
	while(fgets(read_string, sizeof(read_string), fptr) != NULL) {
                if (flag == 0) {
                        flag++;
                        continue;
                }
                printf("%s", read_string);
                usleep(100000);
        }

	printf("\n");
        sleep(2);
        
        // print pokemon name
        strcat(pokemon_name, "!");
        print_str_color(pokemon_name, LOG_CYAN, NULL);
        pokemon_name[strlen(pokemon_name) - 1] = '\0';

	fclose(fptr);
	return 0;
}

void print_desc_name(char * pokemon_name)
{
        printf("###\n");
        printf("### 在正式挑战");
        print_color(pokemon_name, LOG_CYAN, NULL);
        printf("之前，请仔细阅读并学习描述中的战斗技巧\n");
	printf("### 如果感到吃力，请先尝试战胜其他低等级的宝可梦\n");
	printf("### 祝你好运 :)\n");
	printf("###\n");
}

void get_pokemon_name(char * filename, char * name, int num)
{
        char fmt[UTIL_MAX_LEN]={0}, file_path[UTIL_MAX_LEN];
	FILE * fptr = NULL;

        // open pokemon text art file
        get_abs_path(filename, file_path);
	if((fptr = fopen(file_path, "r")) == NULL) {
		fprintf(stderr, "error opening %s\n", file_path);
                return;
	}
        
        // read until next line
        sprintf(fmt, "%s%d%s", "%", num, "s[^\n]");
        fscanf(fptr, fmt, name);
        fclose(fptr);
}

void print_exit()
{
        int name_len = 32;
        char name[name_len];

        // get pokemon name
        get_pokemon_name(filename, name, name_len);

        printf("\n### ");
	print_time();
        printf(" 战斗记录:");
        print_color(name, LOG_RED, NULL);
        printf("获胜\n");
	printf("### 努力提升自己的等级后，再来挑战吧！\n");
        fflush(stdout);
}

void print_desc()
{
        int name_len = 32;
        char name[name_len];

        // get pokemon name
        get_pokemon_name(filename, name, name_len);

        // print pokemon text art
        print_image(name, filename);

        // print pokemon name
	print_desc_name(name);
        fflush(stdout);
}