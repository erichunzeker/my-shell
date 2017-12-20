#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    char** inputArray;
    char* cmd, *curr, *delim = " ()<>|&;\n";
    char token[100], input[100], arguments[100];
    int inputSize;

    while(1)
    {
        printf("myshell $ ");
        fgets(input, 100, stdin);
        inputSize = 0;
        strcpy(arguments, input);
        curr = strtok(arguments, delim);                                                //tokenize arguments using delimiters

        while(curr != NULL)                                                             //iterate through those arguments to count them
        {
            inputSize = inputSize + 1;
            curr = strtok(NULL, delim);
        }

        inputArray = malloc(sizeof(char*) * (inputSize + 1));
        strcpy(token, input);
        cmd = strtok(token, delim);
        int i = 0;

        while(cmd != NULL)
        {
            inputArray[i] = (char*) malloc(sizeof(char) * strlen(cmd));
            strcpy(inputArray[i], cmd);
            cmd = strtok(NULL, delim);
            i++;
        }

        inputArray[inputSize] = NULL;

        if(strcmp(inputArray[0], "exit") == 0)                                          //check if first argument is exit - ignore the rest
            exit(0);

        else if(inputArray[0] == NULL)                                                  //if someone types blank input, continue to new iteration (anti - segmentation fault)
            continue;

        else if(strcmp(inputArray[0], "cd") == 0)
        {
            int dir = chdir(inputArray[1]);

            if(dir == -1)
            {
                if(inputArray[1] == NULL)
                    inputArray[1] = " ";

                printf("cd: %s: no such file or directory \n", inputArray[1]);
            }
        }

        else if(fork() == 0)
        {

            if(strstr(input, ">") != NULL)
            {
                freopen(inputArray[inputSize - 1], "w", stdout);                        //write to filename specified at (inputArray[inputSize-1]
                free(inputArray[inputSize - 1]);                                        //free inputArray index of filename
                inputArray[inputSize - 1] = NULL;                                       //set index of filename to null
            }

            else if(strstr(input, ">>") != NULL)
            {
                freopen(inputArray[inputSize - 1], "a", stdout);                        //append to filename specified at (inputArray[inputSize-1]
                free(inputArray[inputSize - 1]);                                        //free inputArray index of filename
                inputArray[inputSize - 1] = NULL;                                       //set index of filename to null
            }

            else if(strstr(input, "<") != NULL)
            {
                freopen(inputArray[inputSize - 1], "r", stdin);                         //read from filename specified
                free(inputArray[inputSize - 1]);                                        //free inputArray at index of filename
                inputArray[inputSize - 1] = NULL;                                       //set index at filename to null
            }

            int err = execvp(inputArray[0], inputArray);
            if(err == -1)
                printf("-bash : %s: command not found\n", inputArray[0]);
            exit(0);
        }

        else
        {
            int status;
            wait(&status);
        }
    }
}