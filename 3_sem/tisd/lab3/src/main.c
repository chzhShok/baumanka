#include <stdio.h>
#include <stdlib.h>

#include "inc/errors.h"
#include "inc/header.h"

void menu(void)
{
    printf("--- MENU ---\n");
    printf("0: quit\n");
    printf("1: input matrix\n");
    printf("2: read matrix from file\n");
    printf("3: multiply matrices by fast algorithm\n");
    printf("4: multiply matrices by ordinary algorithm\n");
}

int main(void)
{
    int rc = OK;
    int command;

    int *A = NULL;
    int *IA = NULL;
    int *JA = NULL;

    int *B = NULL;
    int *IB = NULL;
    int *JB = NULL;

    do
    {
        menu();
        printf("Input command:");
        if (scanf("%d", &command) != 1)
        {
            printf("ERROR: command input\n");
            rc = IO_ERROR;
            goto exit;
        }
        getchar();

        if (command == 1)
        {
            rc = enter_first_matrix(A, IA, JA);
            if (rc)
                goto exit;

            rc = enter_second_matrix(B, IB, JB);
            if (rc)
                goto exit;
        }
        else if (command == 2)
        {
            char *filename;
            printf("Enter file name with matrix: ");
            if (fgets(filename, FILENAME_MAX, stdin) == NULL)
            {
                printf("ERROR: too long file name\n");
                return IO_ERROR;
            }

            FILE *f = fopen(filename, "r");

            read_matrix();
        }
        else if (command == 0)
        {
            continue;
        }
        else
        {
            printf("ERROR: command doesn't exist\n");
            return COMMAND_ERROR;
        }
    