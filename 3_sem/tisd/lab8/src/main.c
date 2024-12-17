#include <stdio.h>
#include <string.h>

#include "graph.h"
#include "ui.h"

#define FILENAME 100

int main(void)
{
    int command;
    char graph_filename[FILENAME];

    graph_t graph = NULL;
    int n = 0;

    menu();

    while (1)
    {
        printf("\nВведите команду: ");
        if (scanf("%d", &command) != 1)
            command = 123;
        getchar();

        switch (command)
        {
            case 1:
                graph = input_graph(&n);
                break;
            case 2:
            {
                printf("Введите название файла (ограничение 100 символов): ");
                if (!fgets(graph_filename, FILENAME, stdin))
                {
                    printf("Ошибка ввода файла\n");
                    break;
                }
                graph_filename[strcspn(graph_filename, "\n")] = '\0';

                FILE *f = fopen(graph_filename, "r");
                if (!f)
                {
                    printf("Ошибка открытия файла\n");
                    break;
                }

                graph = read_graph_from_file(f, &n);

                fclose(f);
                break;
            }
            case 3:
                print_adjacency_matrix(graph, n);
                break;
            case 4:
                save_to_png_from_graphviz(graph, n);
                break;
            case 5:
            {
                int start, max_distance;

                printf("Введите начальную вершину: ");
                if (scanf("%d", &start) != 1)
                {
                    printf("Ошибка ввода начальной вершины\n");
                    break;
                }
                if (start < 1 || start > n)
                {
                    printf("Ошибка ввода начальной вершины\n");
                    break;
                }
                start--;

                printf("Введите максимальное расстояние: ");
                if (scanf("%d", &max_distance) != 1)
                {
                    printf("Ошибка ввода максимального расстояния\n");
                    break;
                }

                find_reachable_vertices(graph, n, start, max_distance);
                break;
            }
            case 6:
                menu();
                break;
            case 0:
                free_graph(graph, n);
                return 0;
            case 123:
                printf("Неверная команда\n");
        }
    }
}
