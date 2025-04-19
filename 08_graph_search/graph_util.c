#define _CRT_SECURE_NO_WARNINGS
#include "graph.h"


int GM[MAX_NODE][MAX_NODE];   // for adjacency matrix
node* GL[MAX_NODE];           // for adjacency list



int name2int(char c) {
    return c - 'A';
}
char int2name(int i) {
    return i + 'A';
}


void visit(int i) {
    printf("visit %c\n", int2name(i));
}



//===================================[adj matrix]================================

void input_adjmatrix(int a[][MAX_NODE], int* V, int* E) {
    char vertex[3];
    int i, j, k;
    printf("\nInput number of node & edge \n");
    scanf("%d %d", V, E);

    // Initialize the adjacency matrix to 0
    for (i = 0; i < *V; i++) {
        for (j = 0; j < *V; j++) {
            a[i][j] = 0;
        }
    }
    // Set diagonal elements to 1
    for (i = 0; i < *V; i++) {
        a[i][i] = 1;
    }

    printf("\nInput two nodes consisting edge\n");
    for (k = 0; k < *E; k++) {
        scanf("%s", vertex);
        i = name2int(vertex[0]);    // Convert node names to indices
        j = name2int(vertex[1]);
        a[i][j] = 1;
        a[j][i] = 1;
    }
}


void print_adjmatrix(int a[][MAX_NODE], int V) {
    int i, j;
    printf("\n<adjmatrix>\n");
    printf(" ");
    for (i = 0; i < V; i++) {
        printf("%3c", int2name(i));
    }
    printf("\n");
    for (i = 0; i < V; i++) {
        printf("%c", int2name(i));
        for (j = 0; j < V; j++) {
            printf("%3d", a[i][j]);
        }
        printf("\n");
    }
}


//===================================[adj list]=================================

void input_adjlist(node* a[], int* V, int* E) {
    char vertex[3];
    int i, j;
    node* t;
    printf("\nInput number of node & edge\n");
    scanf("%d %d", V, E);

    // Initialize all adjacency list heads to NULL
    for (i = 0; i < *V; i++) a[i] = NULL;

    for (j = 0; j < *E; j++) {
        printf("\nInput two node consisting edge\n");
        scanf("%s", vertex);

        // Create a new node and add it to the front of the adjacency list
        i = name2int(vertex[0]);
        t = (node*)malloc(sizeof(node));
        t->vertex = name2int(vertex[1]);
        t->next = a[i];   
        a[i] = t;     

        // Since the graph is undirected, add the reverse edge as well
        i = name2int(vertex[1]);
        t = (node*)malloc(sizeof(node));
        t->vertex = name2int(vertex[0]);
        t->next = a[i];
        a[i] = t;
    }
}


void print_adjlist(node* a[], int V) {
    int i;
    node* t;
    printf("\n<adjlist>\n");
    for (i = 0; i < V; i++) {
        printf("%c", int2name(i));
        t = a[i];
        while (t != NULL) {
            printf("%3c", int2name(t->vertex));
            t = t->next;
        }
        printf("\n");
    }
}

//===================================[Counting components]===========================

void count_components(int a[][MAX_NODE], int V)
{
    int cnt = 0;
    int i, j;
    init_stack();
    for (i = 0; i < V; i++) check[i] = 0;
    for (i = 0; i < V; i++) {
        if (check[i] == 0) {
            ++cnt;
            push(i);
            check[i] = 1;
            while (!stack_empty()) {
                i = pop();
                printf("%c ", int2name(i));
                for (j = 0; j < V; j++) {
                    if (a[i][j] != 0)
                        if (check[j] == 0) {
                            push(j);
                            check[j] = 1;
                        }
                }
            }
        }
    }
    printf("# of CC : %d\n", cnt);
}