#include <math.h>
#include <stdio.h>

#define N 10
#define OK 0
#define ERR_IO 1

size_t scan_array(int arr[], int max_elements)
{
    size_t i = 0;
    int x;

    while ((scanf("%d", &x) == 1) && (x > 0))
        if (i <= max_elements - 1)
        {
            arr[i] = x;
            i++;
        }
        else
            return max_elements;

    return i;
}

void print_array(int arr[], size_t length)
{
    for (size_t i = 0; i < length; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

int is_square(int a)
{
    return ((int) sqrt(a)) * ((int) sqrt(a)) == a;
}

int delete_squares(int source[restrict], int destination[restrict], int source_length)
{
    int j = 0;
    for (size_t i = 0; i < source_length; i++)
        if (is_square(source[i]) == 0)
        {
            destination[j] = source[i];
            j++;
        }

    return j;
}

int main(void)
{
    int arr[N];
    int repeat;

    do
    {
        printf("Input numbers: ");
        size_t length = scan_array(arr, N);
        fseek(stdin, 0, SEEK_END);

        int arr_without_squares[N];
        int length_arr_without_squares = delete_squares(arr, arr_without_squares, length);

        printf("Array: ");
        print_array(arr, length);
        printf("Array without squares: ");
        print_array(arr_without_squares, length_arr_without_squares);

        printf("\nRepeat the program? [0 - exit]: ");
        if (scanf("%d", &repeat) != 1)
        {
            printf("Error: variable wasn't enter\n");
            return ERR_IO;
        }
    }
    while (repeat != 0);

    return OK;
}