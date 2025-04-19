#define _CRT_SECURE_NO_WARNINGS
#include "PFS.h"

int main(void)
{
    int V, E;
    fp = fopen("graph.txt", "rt");
    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    input_adjlist(G, &V, &E);

    printf("\nOriginal graph\n");
    print_adjlist(G, V);

    PFS_adjlist(G, V);
    print_tree(parent, V);
    printf("\n\nMinimum Cost is ");
    print_cost(check, V);

    fclose(fp);
    return 0;
}
