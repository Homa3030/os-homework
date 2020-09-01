#include <stdio.h> 
#include <stdlib.h> 

struct Node{
    int data;
    struct Node* next;
};

void print_list(struct Node* head){
    printf("Linked list: ");

    struct Node* currevt_node = head;
    while (currevt_node != NULL) {
        printf(" %d ", currevt_node->data);

        if (currevt_node->next != NULL)
            printf("->");
        else
            printf("\n");
        
        currevt_node = currevt_node->next;
    }
}

void insert_node(struct Node* new_node, struct Node* head, struct Node* previous_node){
    struct Node* current_node = head;
    
    while (current_node != previous_node)
    {
        current_node = current_node->next;
    }

    new_node->next = current_node->next;
    current_node->next = new_node;
}

void delete_node(struct Node* node_to_delete, struct Node** head){
    struct Node* current_node = *head;

    if (current_node == node_to_delete){
        *head = (*head)->next;
        free(node_to_delete);
        return;
    }

    while (current_node->next != node_to_delete)
    {
        current_node = current_node->next;
    }

    current_node->next = node_to_delete->next;
    free(node_to_delete);
}

int main(){
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    struct Node* second_node = (struct Node*)malloc(sizeof(struct Node)); 
    struct Node* third_node = (struct Node*)malloc(sizeof(struct Node)); 
    struct Node* fourth_node = (struct Node*)malloc(sizeof(struct Node)); 

    head->data = 1;
    second_node->data = 2;
    third_node->data = 3;
    fourth_node->data = 4;

    head->next = NULL;
    second_node->next = NULL;
    third_node->next = NULL;
    fourth_node->next = NULL;

    insert_node(second_node, head, head);
    insert_node(third_node, head, second_node);
    insert_node(fourth_node, head, third_node);

    print_list(head);

    delete_node(second_node, &head);
    print_list(head);

    delete_node(fourth_node, &head);
    print_list(head);

    delete_node(head, &head);
    print_list(head);

    return 0;
}