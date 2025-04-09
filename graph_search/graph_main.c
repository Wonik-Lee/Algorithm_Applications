#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "graph.h"

int main() {
    int V, E;

    // 인접 행렬 입력/출력 및  탐색

    input_adjmatrix(GM, &V, &E);
    print_adjmatrix(GM, V);

    //DFS_adjmatrix(GM, V);
    //nrDFS_adjmatrix(GM, V);

    //BFS_adjmatrix(GM, V);

    
    
    input_adjlist(GL, &V, &E);
    print_adjlist(GL, V);

    //DFS_adjlist(GL, V);
    //nrDFS_adjlist(GL, V);

    //BFS_adjlist(GL, V);



    count_components(GM, V);
    
}
