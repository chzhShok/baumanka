#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

void free_graph(int **graph, int n)
{
    for (int i = 0; i < n; i++)
        free(graph[i]);

    free(graph);
}

int **input_graph(int *n)
{
    printf("Введите количество вершин графа: ");
    if (scanf("%d", n) != 1)
    {
        printf("Ошибка ввода\n");
        return NULL;
    }
    if (*n < 1)
    {
        printf("Ошибка ввода\n");
        return NULL;
    }

    int **graph = malloc(*n * sizeof(int *));
    for (int i = 0; i < *n; i++)
    {
        graph[i] = malloc(*n * sizeof(int));
        for (int j = 0; j < *n; j++)
            graph[i][j] = 0;
    }

    int u, v, weight;
    printf("Введите рёбра графа в формате: вершина_1 вершина_2 вес (введите -1 -1 -1 для завершения ввода):\n");
    while (1)
    {
        if (scanf("%d%d%d", &u, &v, &weight) != 3)
        {
            printf("Ошибка: некорректные данные\n");
            fseek(stdin, SEEK_END, 0);
            continue;
        }

        if (u == -1 && v == -1 && weight == -1)
            break;

        if (u > 0 && u <= *n && v > 0 && v <= *n && weight > 0)
        {
            u--;
            v--;
            graph[u][v] = weight;
            graph[v][u] = weight;
        }
        else
            printf("Ошибка: некорректные данные\n");
    }

    for (int i = 0; i < *n; i++)
        for (int j = 0; j < *n; j++)
            if (graph[i][j] == 0 && i != j)
                graph[i][j] = INF;

    return graph;
}

int **read_graph_from_file(FILE *file, int *n)
{
    fscanf(file, "%d", n);

    int **graph = malloc(*n * sizeof(int *));
    for (int i = 0; i < *n; i++)
    {
        graph[i] = malloc(*n * sizeof(int));
        for (int j = 0; j < *n; j++)
            graph[i][j] = 0;
    }

    int u, v, weight;
    while (fscanf(file, "%d %d %d", &u, &v, &weight) == 3)
    {
        if (u > 0 && u <= *n && v > 0 && v <= *n && weight > 0)
        {
            u--;
            v--;
            graph[u][v] = weight;
            graph[v][u] = weight;
        }
        else
            printf("Ошибка: некорректные данные в файле\n");
    }

    for (int i = 0; i < *n; i++)
        for (int j = 0; j < *n; j++)
            if (graph[i][j] == 0 && i != j)
                graph[i][j] = INF;

    return graph;
}

void print_adjacency_matrix(int **graph, int n)
{
    if (n > 30)
    {
        printf("Граф слишком большой для вывода матрицы смежности\n");
        return;
    }

    char *inf = "INF";
    printf("\nМатрица смежности графа:\n");

    printf("\n   ");
    for (int i = 0; i < n; i++)
        printf("%5d", i + 1);
    printf("\n");
    for (int i = 0; i <= n; i++)
        printf("-----");
    printf("\n");

    for (int i = 0; i < n; i++)
    {
        printf("%2d |", i + 1);
        for (int j = 0; j < n; j++)
        {
            if (graph[i][j] == INF)
                printf("%5s", inf);
            else
                printf("%5d", graph[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void generate_dot_file(int **graph, int n, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Ошибка открытия файла\n");
        return;
    }

    fprintf(file, "graph G {\n");

    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            if (graph[i][j] != 0 && graph[i][j] != INF)
                fprintf(file, "    %d -- %d [label=\"%d\"];\n", i + 1, j + 1, graph[i][j]);

    fprintf(file, "}\n");
    fclose(file);
    printf("DOT файл '%s' успешно создан\n", filename);
}

void save_to_png_from_graphviz(int **graph, int n)
{
    char *base_filename = "graph";

    char *countEnv = getenv("count");
    int count = 1;

    if (countEnv)
        count = atoi(countEnv);

    char filename[256];
    snprintf(filename, sizeof(filename), "../graph_svg/%s%d.dot", base_filename, count);

    generate_dot_file(graph, n, filename);

    char command[512];
    snprintf(command, sizeof(command),
             "/usr/local/Cellar/graphviz/12.2.0/bin/dot -Tsvg %s -o ../graph_svg/%s%d.svg",
             filename, base_filename, count);
    system(command);

    printf("Дерево сохранено в файл '../graph_svg/%s%d.svg'\n", base_filename, count);

    count++;
    char newCountEnv[10];
    snprintf(newCountEnv, sizeof(newCountEnv), "%d", count);
    setenv("count", newCountEnv, 1);
}

void find_reachable_vertices(int **graph, int n, int start, int max_distance)
{
    int *dist = malloc(n * sizeof(int));
    int *visited = calloc(n, sizeof(int));

    for (int i = 0; i < n; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[start] = 0;

    for (int i = 0; i < n; i++)
    {
        int min_dist = INF;
        int u = -1;

        for (int j = 0; j < n; j++)
            if (!visited[j] && dist[j] < min_dist)
            {
                min_dist = dist[j];
                u = j;
            }

        if (u == -1)
            break;

        visited[u] = 1;

        for (int v = 0; v < n; v++)
            if (graph[u][v] > 0 && graph[u][v] != INF && !visited[v])
                if (dist[u] + graph[u][v] < dist[v])
                    dist[v] = dist[u] + graph[u][v];
    }

    printf("\nВершины, достижимые от вершины %d с длиной пути <= %d:\n", start + 1, max_distance);
    for (int i = 0; i < n; i++)
        if (dist[i] <= max_distance && i != start)
            printf("Вершина %d (расстояние: %d)\n", i + 1, dist[i]);

    free(dist);
    free(visited);
}
