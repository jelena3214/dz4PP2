#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readLine() {
    char* inp = NULL;
    char c;
    int size = 0;
    while ((c = getchar()) != '\n') {
        size++;
        inp = realloc(inp, sizeof(char) * (size + 1));
        if (!inp) {
            printf("MEM_GRESKA\n");
            exit(0);
        }
        inp[size - 1] = c;
        inp[size] = '\0';
    }
    return inp;
}
struct node {
    char* id;
    struct node* next;
    int flag;
}NODE;

void freeNode(struct node* temp) {
    free(temp->id);
    free(temp);
}

struct node* createNode() {
    struct node* newnode = malloc(sizeof(struct node));
    if (!newnode) {
        printf("MEM_GRESKA\n");
        exit(0);
    }
    newnode->next = NULL;
    newnode->id = readLine();
    newnode->flag = 0;
    if (newnode->id == NULL) {
        freeNode(newnode);
        return NULL;
    }

    return newnode;
}

struct node* linkedList(int *elem_num) {
    struct node* head = createNode();
    struct node* p = head;
    if (head == NULL)return NULL;
    while (1) {
        struct node* new = createNode();
        if (new == NULL)break;
        p->next = new;
        p = p->next;
        (*elem_num)++;
    }
    
    p->next = head;
    return head;
}

void printLinked(struct node* head) {
    struct node* p = head;
    if (head == NULL)head = NULL;
    do
    {
        printf("%s\n", p->id);
        p = p->next;
    }while (p != head);
}

struct node* remo(struct node* head, struct node** remove) {
    struct node* p = head;
    struct node* n = (*remove)->next;
    if (head == NULL)return NULL;
    while (p->next != (*remove)) {
        p = p->next;
    }
    if ((*remove)->next == head && (*remove) == head) {
        head = NULL;
        freeNode((*remove));
        remove = NULL;
        return head;
    }
    p->next = n;
    if (head == (*remove)) {
        head = n;
    }
    freeNode((*remove));
    (*remove) = n;
    return head;
}

void josephProblem(struct node *head, int start, int n, int elemnum) {
    struct node* p = head;
    int j = 0;
    char* temp = "*\0";
    int i;
    
    int numofmoves = start;
    
    while (head != NULL) {
        i = 0;
        while (i < numofmoves) {
            p = p->next;
            i++;
        }
        numofmoves = n-1;
        int k = strlen(p->id);

        p->id = realloc(p->id, sizeof(char) * (k + 2));
        if (!p->id) {
            printf("MEM_GRESKA\n");
            exit(0);
        }
        strcat(p->id, temp);
        printf("STEP%d\n", j++);
        //funk za to
        p->flag = 1;
        printLinked(head);

        head = remo(head, &p);
        elemnum--;
    }
}


int main() {
    int elem_num = 1;
    int start, n;
    char* k = malloc(sizeof(char));
    scanf("%d %d%c", &start, &n, k);
    free(k); //gledaj da l ima bolji nacin osim ovoga??
    struct node* begin = linkedList(&elem_num);
    if (begin == NULL)exit(0);
    if (start > elem_num || start < 0 || n < 1) {
        if (begin == NULL)exit(0);
        printf("GRESKA\n");
        exit(0);
    }
    printLinked(begin);
    josephProblem(begin, start, n, elem_num);
    _CrtDumpMemoryLeaks();
	return 0;
}