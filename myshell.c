#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


char *delim = " ()<>|&;\n\t";

int get_arglength(char* input)
{
    char arguments[100];
    char* curr;
    int count = 0;

    strcpy(arguments, input);

    curr = strtok(arguments, delim);

    while(curr != NULL)
    {
        count = count + 1;
        curr = strtok(NULL, delim);
    }
    return count;
}

int main()
{
    char** inputArray;
    char* arg;
    char input[100];
    char token[100];
    int inputSize = 0;

    while(1){
        printf("myshell $ ");

        fgets(input, 100, stdin);

        inputSize = get_arglength(input);

        inputArray = malloc(sizeof(char*) * (inputSize + 1));

        strcpy(token, input);

        arg = strtok(token, delim);
        int i = 0;

        while(arg != NULL)
        {
            inputArray[i] = (char*) malloc(sizeof(char) * strlen(arg));
            strcpy(inputArray[i], arg);
            arg = strtok(NULL, delim);
            i++;
        }

        inputArray[inputSize] = NULL;

        if(strcmp(inputArray[0], "exit") == 0)
            exit(0);

        else if(inputArray[0] == NULL)
            continue;


        else if(strcmp(inputArray[0], "cd") == 0)
        {
            if(chdir(inputArray[1]) == -1)
            {
                if(inputArray[1] == NULL)
                    inputArray[1] = " ";

                printf("cd: %s: No such file or directory\n", inputArray[1]);
            }
        }

        else
        {
            if(fork() == 0)
            {

                if(strstr(input, ">") != NULL)
                {
                    freopen(inputArray[inputSize-1], "w", stdout);
                    free(inputArray[inputSize-1]);
                    inputArray[inputSize-1] = NULL;
                }

                else if(strstr(input, ">>") != NULL)
                {
                    freopen(inputArray[inputSize-1], "a", stdout);
                    free(inputArray[inputSize-1]);
                    inputArray[inputSize-1] = NULL;
                }

                else if(strstr(input, "<") != NULL)
                {
                    freopen(inputArray[inputSize-1], "r", stdin);
                    free(inputArray[inputSize-1]);
                    inputArray[inputSize-1] = NULL;
                }

                execvp(inputArray[0], inputArray);
                exit(0);
            }

            else {
                int status;
                wait(&status);
            }


        }
    }
}


