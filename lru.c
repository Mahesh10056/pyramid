#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct LRUCache {
    int capacity;
    int size;
    Node* head;
    Node* tail;
} LRUCache;

LRUCache* createCache(int capacity) {
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
    cache->capacity = capacity;
    cache->size = 0;
    cache->head = cache->tail = NULL;
    return cache;
}

Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = newNode->prev = NULL;
    return newNode;
}

void moveToHead(LRUCache* cache, Node* node) {
    if (cache->head == node) return;

    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;

    if (cache->tail == node) cache->tail = node->prev;

    node->next = cache->head;
    node->prev = NULL;
    if (cache->head) cache->head->prev = node;
    cache->head = node;

    if (!cache->tail) cache->tail = cache->head;
}

void put(LRUCache* cache, int key) {
    Node* temp = cache->head;

    while (temp) {
        if (temp->key == key) {
            moveToHead(cache, temp);
            return;
        }
        temp = temp->next;
    }

    Node* newNode = createNode(key);
    if (cache->size < cache->capacity) {
        if (cache->head) {
            newNode->next = cache->head;
            cache->head->prev = newNode;
        }
        cache->head = newNode;
        if (!cache->tail) cache->tail = cache->head;
        cache->size++;
    } else {
        if (cache->tail) {
            Node* toRemove = cache->tail;
            cache->tail = toRemove->prev;
            if (cache->tail) cache->tail->next = NULL;
            free(toRemove);
        }

        newNode->next = cache->head;
        cache->head->prev = newNode;
        cache->head = newNode;
    }
}

void display(LRUCache* cache) {
    Node* temp = cache->head;
    printf("Cache: ");
    while (temp) {
        printf("%d ", temp->key);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int capacity;
    printf("Enter the cache capacity: ");
    scanf("%d", &capacity);

    LRUCache* cache = createCache(capacity);

    int choice, key;
    while (1) {
        printf("1. Add Key\n2. Display Cache\n3. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key: ");
                scanf("%d", &key);
                put(cache, key);
                break;
            case 2:
                display(cache);
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
