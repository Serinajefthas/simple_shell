#include "main.h"

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
        /* check if user input is a path */
        /* if(stat(command, &buffer) == 0) */
        /*     return (command); */
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
            /* stat gets file status(if exists or not), placed in buffer */
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

    if (argv)
    {
        /* first index is command, second is file/path */
        cmd = argv[0];
        test_path = get_path(cmd);
        if (execve(test_path, argv, NULL) == -1)
            /* formatted error by execve function */
            perror("Error");
    }
}

/**
 * main - executes inputted command(s)
 * @argc: argument count
 * @argv: argument array
 * Return: 0
*/
int main(int argc __attribute__((unused)), char *argv[])
{
    char *prompt = "$ ";
    /*store address of buffer holding user input */
    char *cmd = NULL, *cmd_cp = NULL, *word = NULL;
    const char *delim = " \n";
    size_t size = 0;
    ssize_t chars_read = 0;
    int num_words = 0, i;

    while (1)
    {
        printf("%s", prompt);
        chars_read = getline(&cmd, &size, stdin);

        /* Can create sep method for parsing input: */
        
        /* exit shell, ctrl d*/
        if (chars_read == -1)
        {
            printf("Exit shell\n");
            return (-1);
        }
        /* parsing/tokenising user input */ 
        cmd_cp = malloc(sizeof(char) * chars_read);
        if (!cmd_cp)
        {
            perror("tsh: Parsing memory alloc error");
            return (-1);
        }
        /* copy to cmd copy ptr variable to alter*/
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
        /* argv[i] = "NULL"; */
        /* End of separate method */
            
            /* test: prints content of argv array */
            /* for (j = 0; j < num_words-1; j++) */
            /* printf("%s\n", argv[j]); */
            
        cmd_exe(argv);
    }
    free(cmd);
    free(cmd_cp);
    return (0);
}
