#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
void cmd_exe(char **argv);
char *get_path(char *command);
void main_loop(char *cmd, char *cmd_cp, char *argv[]);
int main(int argc __attribute__((unused)), char *argv[]);
void *_realloca(void *, unsigned int, unsigned int);
char *memryset(char *, char, unsigned int);
void _freestr(char **);
void handComm(char *ln);
