
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "some_heap.h"

#define KEY_NOT_PRESENT -1

heap_t *heap_create(int capacity) {
    heap_t *heapArray = malloc(sizeof(int));
    heapArray -> size = 0;
    heapArray -> capacity = capacity;
    heap_node_t *data = malloc(capacity*sizeof(heap_node_t));
    return heapArray;
}

void heap_free(heap_t *heap) {
    free(heap);
}

unsigned int heap_size(heap_t *heap) { return heap->size; }

unsigned int heap_parent(unsigned int index) { return (index-1)/2; }

unsigned int heap_left_child(unsigned int index) { return (2*index)+1; }

unsigned int heap_right_child(unsigned int index) { return (2*index)+2; }

unsigned int heap_level(unsigned int index) { return log2(index+1); }

void heap_print(heap_t *heap) {
    for (int ix = 0; ix < heap_size(heap); ix++) {
        printf("%3d - %3d : " HEAP_KEY_FORMAT "\n", heap_level(ix), ix,
               heap->data[ix].key);
    }
    printf("\n");
}

void heap_swap(heap_t *heap, int index1, int index2) { 
    heap_node_t temp = heap->data[index1];
    heap->data[index1] = heap->data[index2];
    heap->data[index2] = temp;
}

void heap_bubble_up(heap_t *heap, int index) {
    int curr_heap_level = heap_level(index);
    int parent = heap_parent(index);
    //heap_node_t currentNode = heap-> data[index];
    //heap_node_t parentNode = heap->data[parent];
    while(index>0){
        if(heap->data[index].key < heap->data[parent].key){
        heap_swap(heap, index, parent);
        //curr_heap_level--;
        index = parent;
        parent = heap_parent(index);
     } else break;
    }
}

void heap_bubble_down(heap_t *heap, int index) {
    int leftChild = heap_left_child(index);
    int rightChild = heap_right_child(index);
    heap_node_t current_root = heap->data[index];
    heap_node_t leftNode = heap->data[leftChild];
    heap_node_t rightNode = heap->data[rightChild];

    if (&current_root >= &leftNode) heap_swap(heap, index, leftChild);
    if (&current_root >= &rightNode) heap_swap(heap, index, rightChild);
}

void heap_insert(heap_t *heap, heap_key_t key, heap_value_t data) {
    if (heap_size(heap) == heap->capacity) {
        return;
    }

    heap->data[heap_size(heap)].key = key;
    heap->data[heap_size(heap)].value = data;
    heap->size++;

    heap_bubble_up(heap, heap_size(heap) - 1);
}


heap_value_t heap_remove_min(heap_t *heap) {
    if (heap_size(heap) == 0) {
        return (heap_value_t){.as_int = KEY_NOT_PRESENT};
    }

    heap_value_t min = heap->data[0].value;

    heap->size--;

    // move last element to the root
    heap->data[0] = heap->data[heap_size(heap)];

    // then bubble it down to its correct position
    heap_bubble_down(heap, 0);

    return min;
}
