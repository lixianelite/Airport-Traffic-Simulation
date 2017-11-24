//
//  main.c
//  Assignment5
//
//  Created by Bravado on 11/21/17.
//  Copyright © 2017 Bravado. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "PriorityQueue.h"

#define RED 0
#define BLACK 1


typedef struct Node{
    AirportEvent* value;
    int color;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
}Node;

typedef struct PriorityQueue{
    Node* root;
    Node* nil;
}Queue;


void leftRotate(Node *node, Queue* queue);
void rightRotate(Node* node, Queue* queue);
void preOrder(Queue* queue);
void preOrderHelp(Node* head, Node* nil);
void RB_Insert_Fix(Node* node, Queue* queue);
void RB_delete(Node* node, Queue* queue);
void RB_Delete_Fix(Queue* queue, Node* node);
void RB_Insert(Queue* queue, AirportEvent* event);
Node* findMostLeft(Node* node, Queue* queue);
void inOrderPrint(Node* root, Node* nil);


Queue* create_Queue(){
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    
    queue -> root = (Node*)malloc(sizeof(Node));
    queue -> nil = (Node*)malloc(sizeof(Node));
    queue -> nil -> color = BLACK;
    queue -> root = queue -> nil;
    
    return queue;
}

bool isEmpty(Queue* queue){
    return queue -> root == queue -> nil;
}

void Insert_value(Queue* queue, AirportEvent* event){
    RB_Insert(queue, event);
}

AirportEvent* Delete_Least(Queue* queue){
    Node* lest = findMostLeft(queue -> root, queue);
    AirportEvent* data = lest -> value;
    RB_delete(lest, queue);
    return data;
}


void leftRotate(Node *node, Queue* queue){
    if (node -> right == queue -> nil) return;
    
    Node* right = node -> right;
    Node* parent = node -> parent;
    
    node -> right = right -> left;
    if (right -> left != queue -> nil) {
        right -> left -> parent = node;
    }
    
    right -> left = node;
    node -> parent = right;
    
    if(parent != queue -> nil && parent -> left == node){
        parent -> left = right;
    }else if(parent != queue -> nil && parent -> right == node){
        parent -> right = right;
    }else{
        queue -> root = right;
    }
    right -> parent = parent;
}

void rightRotate(Node* node, Queue* queue){
    if (node -> left == queue -> nil) return;
    
    Node* left = node -> left;
    Node* parent = node -> parent;
    
    node -> left = left -> right;
    
    if (left -> right != queue -> nil) left -> right -> parent = node;
    left -> right = node;
    node -> parent = left;
    
    if (parent == queue -> nil) {
        queue -> root = left;
    }else if(node == parent -> left){
        parent -> left = left;
    }else{
        parent -> right = left;
    }
    left -> parent = parent;
}

void RB_Insert(Queue* queue, AirportEvent* event){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode -> value = event;
    newNode -> color = RED;
    
    Node* cur = queue -> root;
    Node* pre = queue -> nil;
    
    while (cur != queue -> nil) {
        pre = cur;
        if (event_getTime(event) < event_getTime(cur -> value)) {
            cur = cur -> left;
        }else{
            cur = cur -> right;
        }
    }
    newNode -> parent = pre;
    if (pre == queue -> nil) {
        queue -> root = newNode;
    }else if(event_getTime(event) < event_getTime(pre -> value)){
        pre -> left = newNode;
    }else{
        pre -> right = newNode;
    }
    newNode -> left = queue -> nil;
    newNode -> right = queue -> nil;
    RB_Insert_Fix(newNode, queue);
    
}

void RB_Insert_Fix(Node* node, Queue* queue){
    while (node -> parent -> color == RED){
        if (node -> parent == node -> parent -> parent -> left) {
            Node* uncle = node -> parent -> parent -> right;
            if (uncle -> color == RED) {
                node -> parent -> color = BLACK;
                uncle -> color = BLACK;
                node -> parent -> parent -> color = RED;
                node = node -> parent -> parent;
                continue;
            }else if(node == node -> parent -> right){
                node = node -> parent;
                leftRotate(node, queue);
            }
            node -> parent -> color = BLACK;
            node -> parent -> parent -> color = RED;
            rightRotate(node -> parent -> parent, queue);
        }else{
            Node* uncle = node -> parent -> parent -> left;
            if (uncle -> color == RED) {
                node -> parent -> color = BLACK;
                uncle -> color = BLACK;
                node -> parent -> parent -> color = RED;
                node = node -> parent -> parent;
                continue;
            }else if(node == node -> parent -> left){
                node = node -> parent;
                rightRotate(node, queue);
            }
            node -> parent -> color = BLACK;
            node -> parent -> parent -> color = RED;
            leftRotate(node -> parent -> parent, queue);
        }
        
    }
    queue -> root -> color = BLACK;
}

void RB_Transplant(Queue* queue, Node* node1, Node* node2){
    if (node1 -> parent == queue -> nil) {
        queue -> root = node2;
    }else if(node1 == node1 -> parent -> left){
        node1 -> parent -> left = node2;
    }else{
        node1 -> parent -> right = node2;
    }
    node2 -> parent = node1 -> parent;
}

Node* findMostLeft(Node* node, Queue* queue){
    if (node == queue -> nil) return node;
    while (node -> left != queue -> nil) {
        node = node -> left;
    }
    return node;
}

void RB_delete(Node* node, Queue* queue){
    if (node == queue -> nil) return;
    
    Node* y = node;
    Node* x = queue -> nil;
    int y_original_color = node -> color;
    if (node -> left == queue -> nil) {
        x = node -> right;
        RB_Transplant(queue, node, node -> right);
    }else if(node -> right == queue -> nil){
        x = node -> left;
        RB_Transplant(queue, node, node -> left);
    }else{
        y = findMostLeft(node -> right, queue);
        y_original_color = y -> color;
        x = y -> right;
        if (y != node -> right) {
            RB_Transplant(queue, y, y -> right);
            y -> right = node -> right;
            node -> right -> parent = y;
        }
        RB_Transplant(queue, node, y);
        y -> left = node -> left;
        y -> left -> parent = y;
        y -> color = node -> color;
    }
    if (y_original_color == BLACK) {
        RB_Delete_Fix(queue, x);
    }
    free(node);
}

void RB_Delete_Fix(Queue* queue, Node* node){
    while (node != queue -> root && node -> color == BLACK) {
        if (node == node -> parent -> left) {
            Node* w = node -> parent -> right;
            if (w -> color == RED) {
                w -> color = BLACK;
                node -> parent -> color = RED;
                leftRotate(node -> parent, queue);
                w = node -> parent -> right;
            }
            if (w -> left -> color == BLACK && w -> right -> color == BLACK) {
                w -> color = RED;
                node = node -> parent;
                continue;
            }else if(w -> right -> color == BLACK){
                w -> left -> color = BLACK;
                w -> color = RED;
                rightRotate(w, queue);
                w = node -> parent -> right;
            }
            w -> color = node -> parent -> color;
            node -> parent -> color = BLACK;
            w -> right -> color = BLACK;
            leftRotate(node -> parent, queue);
            node = queue -> root;
        }else{
            Node* w = node -> parent -> left;
            if (w -> color == RED) {
                w -> color = BLACK;
                node -> parent -> color = RED;
                rightRotate(node -> parent, queue);
                w = node -> parent -> left;
            }
            if (w -> left -> color == BLACK && w -> right -> color == BLACK) {
                w -> color = RED;
                node = node -> parent;
                continue;
            }else if(w -> left -> color == BLACK){
                w -> color = RED;
                w -> right -> color = BLACK;
                leftRotate(w, queue);
                w = node -> parent -> left;
            }
            w -> color = node -> parent -> color;
            node -> parent -> color = BLACK;
            w -> left -> color = BLACK;
            rightRotate(node -> parent, queue);
            node = queue -> root;
        }
    }
    node -> color = BLACK;
}

void printQueue(Queue* queue){
    inOrderPrint(queue -> root, queue -> nil);
    printf("============================================\n");
    printf("\n");
}

void inOrderPrint(Node* root, Node* nil){
    if (root == nil) return;
    inOrderPrint(root -> left, nil);
    printf("time: %.2f, eventType: %d, airport: %s\n", event_getTime(root -> value), event_getType(root -> value), airport_getName(event_getAirport(root -> value)));
    inOrderPrint(root -> right, nil);
}

