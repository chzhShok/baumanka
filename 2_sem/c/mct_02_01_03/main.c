#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define N 10000

void get_input_until_four_zeros(char *buffer)
{
    char line[N - 1];
    char stop[4] = "0000";

    while (fgets(line, N - 1, stdin) != NULL)
    {
        if (strncmp(line, stop, 4) == 0)
            break;

        strcat(buffer, line);
    }

    buffer[sizeof(buffer)] = '\0';
}

int contain_letters(char *string)
{
    for (int i = 0; string[i] != '\n'; i++)
        if (!isalpha(string[i]))
            return 1;

    return 0;
}

void get_words(char *buffer)
{
    int n = (int) strlen(buffer);
    int ind = 0;
    while (ind < n)
    {
        char line[N] = "";
        int line_ind = 0;
        while (buffer[ind] != '\n')
        {
            line[line_ind] = buffer[ind];
            line_ind++;
            ind++;
        }

        printf("line: %s\n", line);

        char *token = strtok(line, "2");
        while (token != NULL)
        {
            if (contain_letters(token) == 0)
                printf("%s ", token);
            token = strtok(NULL, "2");
        }
    }
}

int main(void)
{
    char buffer[N] = "";
    get_input_until_four_zeros(buffer);
    get_words(buffer);
    return 0;
}
