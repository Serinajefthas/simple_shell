#include "main.h"

/* output must match /bin/sh output(incl errors) -  use as checker! */
extern char **environ;

/**
 * get_path - returns path for each cmd typed
 * @command: command from user input
 * Return: char pointer to path 
*/
char *get_path(char *command)
{
    /* variables to get value of PATH environment var */
    char *path, *path_cp, *path_loc, *full_path;
    int cmd_len = strlen(command);
    int path_len, total_len;
    struct stat buffer;
    
    path = getenv("PATH");
    if (path)
    {
        path_cp = strdup(path); /* dynamically allocats memory for path*/
        /* again breaks path into indiv path locations */
        path_loc = strtok(path_cp, ":");     
        /* while loop for exact path name by getting each path token and adding it to
        * full path name, separated by '/' and ending with '\0'
        */
        while (path_loc != NULL)
        {
            path_len = strlen(path_loc);
            total_len = cmd_len + path_len + 2;
            full_path = malloc(total_len);
            strcpy(full_path, path_loc);
            strcat(full_path, "/");
            strcat(full_path, command);
            strcat(full_path, "\0");
            /*stat gets file status(if exists or not), placed in buffer*/
            if(stat(full_path, &buffer) == 0)
            {
                    free(path_cp);
                    return (full_path);
            }
            else /*free memory to check another path in next loop iteration*/
            {
                free(full_path);
                path_loc = strtok(NULL, ":");
            }
        }
        free(path_cp);
        /* check if user input is a path */
        if(stat(command, &buffer) == 0)
            return (command);
        
        return (NULL);
    }
    return (NULL);
}

/**
 * cmd_exe - handles command execution
 * @argv: array of arguments
 * Return: 0 on success
*/
void cmd_exe(char **argv)
{
    char *cmd, *test_path = NULL;
    char **env = environ;
    pid_t pid;
    pid_t ppid;

    if (argv)
    {
        /* first index is command, second is file/path */
        cmd = argv[0];
        if (strcmp(cmd, "exit") == 0) /*exit functionality w 'exit' input*/
        {
            printf("exit\n");
            exit(0);
        }
        /* prints environnment variables */
        if (strcmp(cmd, "env") == 0)
        {
            for (; *env; env++)
                printf("%s\n", *env);
            return;
        }
        if (strcmp(cmd, "pid") == 0)
        {
            pid = getpid(); printf("%u\n", pid); 
	    return;
        }
        if (strcmp(cmd, "ppid") == 0)
        {
            ppid = getppid(); printf("%u\n", ppid); 
	    return; 
        }
        test_path = get_path(cmd);
        if (execve(test_path, argv, NULL) == -1){
            /* formatted error by execve function */
            perror("Error");
            return;
        }
        else if (execve(test_path, argv, NULL) == 0)
        {
            execve(test_path, argv, NULL);
            return;
        }
    }
}

/**
 * main_loop - main while loop for shell
 * @cmd: command inputted by user
 * @cmd_cp: copy of cmd ptr
 * @argv: argument vector
 * 
*/
void main_loop(char *cmd, char *cmd_cp, char *argv[])
{
    char *prompt = "($) ", *word = NULL;
    const char *delim = " \n";
    int num_words = 0, i;
    size_t size = 0; ssize_t chars_read = 0;

    while (1)
    {
        printf("%s", prompt);
        chars_read = getline(&cmd, &size, stdin);
        /* exit shell, ctrl d*/
        if (chars_read == -1)
        {
            printf("exit\n");
            exit(0);
        }
        /* parsing/tokenising user input */ 
        cmd_cp = malloc(sizeof(char) * chars_read);
        if (!cmd_cp)
        {
            perror("tsh: Parsing memory alloc error");
            exit(0);
        }
        
        /* copy to cmd_copy ptr variable to manipulate*/
        strcpy(cmd_cp, cmd);
        
        /* splits input into array of words to interpret indiv */
        word = strtok(cmd, delim);
        while (word != NULL)
        {
            num_words++;
            word = strtok(NULL, delim);
        }
        num_words++;
        argv = malloc(sizeof(char *) * num_words);

        word = strtok(cmd_cp, delim);
        /* add words to array */
        for (i = 0; word != NULL; i++)
        {
            argv[i] = malloc(sizeof(char) * strlen(word));
            strcpy(argv[i], word);
            word = strtok(NULL, delim);
        }
        cmd_exe(argv);
    }
}

/**
 * main - executes inputted command(s)
 * @argc: argument count
 * @argv: argument array
 * Return: 0
*/
int main(int argc, char *argv[])
{
    /*store address of buffer holding user input */
    char *cmd = NULL, *cmd_cp = NULL;
    int j;

    if (argc == 1)
        printf("No arguments\n");
    else
    {
        printf("Number of arguments: %d\n", argc -1);
        printf("Arguments: ");
        for (j = 1; j < argc; j++)
        {
            printf("%s ", argv[j]);
        }
        printf("\n");
    }
    main_loop(cmd, cmd_cp, argv);
    free(cmd);
    free(cmd_cp);
    return (0);
}
