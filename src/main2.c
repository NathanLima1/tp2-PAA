#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdbool.h>
#include "solve.h"


int main(int argc, char *argv[]){
    FILE *fp = stdin;
    FILE *fp_out = stdin;

    // Começa a medir o tempo real
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    int option = 1;

    char *input_file = "entrada.txt";
    char *output_file = "saida.txt";
    int opt;

    while ((opt = getopt(argc, argv, "i:o:f:")) > 0 ) {
        switch (opt) {
            case 'i':
                input_file = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case 'f':
                option = atoi(optarg);
                if(option == 2){
                    printf("Heuristica selecionada.\n");
                }else{
                    printf("Programacao Dinamica selecionada.\n");
                }
                break;
            default:
                printf("Entrada inválida, use -i:-o:-f\n");
                return 0;
        }
    }

    fp = fopen(input_file, "r");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    fp_out = fopen(output_file, "w");

    // Começa a medir o tempo de usuário
    struct rusage usage_start, usage_end;
    getrusage(RUSAGE_SELF, &usage_start);

    int k;
    int p, d, w, c;
    int pi, pj, wi, hi, di;
    if(fscanf(fp, "%d", &k) != 1){
        printf("Erro ao ler o arquivo\n");
        exit(1);
    }

    // Loop principal
    while(k > 0){
        if(fscanf(fp, "%d %d %d %d", &p, &d, &w, &c) != 4){
            printf("Erro ao ler o arquivo\n");
            exit(1);
        }
        // Graph* graph = create_graph(p, c);

        int **g = init_graph(p);
        int *pesos = malloc(sizeof(int)*p); // Pesos
        int *valores = malloc(sizeof(int)*p); // Habilidades
        int num_vertices = p;
        int max_depth = d;
        int capacidade = w;

        for(int i = 0; i < p; i++){
            if(fscanf(fp, "%d %d %d", &pi, &wi, &hi) != 3){
                printf("Erro ao ler o arquivo\n");
                exit(1);
            }

            pesos[pi - 1] = wi;
            valores[pi - 1] = hi;

            // add_town(graph, pi, wi, hi);
        }

        for(int i = 0; i < c; i++){
            if(fscanf(fp, "%d %d %d", &pi, &pj, &di) != 3){
                printf("Erro ao ler o arquivo\n");
                exit(1);
            }
            add_conn(pi - 1, pj - 1, di);
            // add_edge(graph, pi, pj, di);
        }

        // prepare_adjacency(graph);
        // solve_bf(graph, d, w);
        // print_solution();

        Dp *dp = dp_init(max_depth, num_vertices, capacidade)
        calc(dp, pesos, valores, g);
        reconstruir(dp, g, pesos);

        free_graph(graph);
        free_adjacency();
        reset_globals();
        k--;
    }
    

    // Termina medição
    gettimeofday(&end_time, NULL);
    getrusage(RUSAGE_SELF, &usage_end);

    // Calculando o tempo real (tempo total de execução)
    long seconds = end_time.tv_sec - start_time.tv_sec;
    long microseconds = end_time.tv_usec - start_time.tv_usec;
    if (microseconds < 0) {
        seconds--;
        microseconds += 1000000;
    }

    // Calculando tempo de usuário e sistema
    long user_time_sec = usage_end.ru_utime.tv_sec - usage_start.ru_utime.tv_sec;
    long user_time_usec = usage_end.ru_utime.tv_usec - usage_start.ru_utime.tv_usec;

    long sys_time_sec = usage_end.ru_stime.tv_sec - usage_start.ru_stime.tv_sec;
    long sys_time_usec = usage_end.ru_stime.tv_usec - usage_start.ru_stime.tv_usec;

    if (user_time_usec < 0) {
        user_time_sec--;
        user_time_usec += 1000000;
    }

    if (sys_time_usec < 0) {
        sys_time_sec--;
        sys_time_usec += 1000000;
    }

    printf("Tempo Real: %ld.%06ld segundos\n", seconds, microseconds);
    printf("Tempo de Usuário: %ld.%06ld segundos\n", user_time_sec, user_time_usec);
    printf("Tempo de Sistema: %ld.%06ld segundos\n", sys_time_sec, sys_time_usec);


    fclose(fp);
    fclose(fp_out);
    
    return 0;
}