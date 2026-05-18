#include "PQ.h"
#include "shot.h"
#define MAX_LEN 200

struct PQ {
    shot_t *heap;  // heap = the binary tree saw
    int max_len;  // max length of the heap
    int len;  // number of item in the array
};

PQ_t new_PQ(void) {
    PQ_t pq = (PQ_t) malloc(sizeof(*pq));
    pq->heap = (shot_t*) malloc(MAX_LEN*sizeof(shot_t)); 
    pq->max_len = MAX_LEN;
    pq->len = 0;

    return pq;
}

int PQ_len(PQ_t pq) {
    return pq->len;
}

int left_child(int idx) {
    return 2 * idx + 1;
}

int parent(int idx) {
    return (idx-2)/2;
}

void swap(PQ_t pq, int a, int b) {
    shot_t* heap = pq->heap;
    shot_t temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}

int nbchildren(PQ_t pq, int idx){
  return (idx*2 +1 < pq->len)+(idx*2 + 2 < pq->len);
}

void bubble_up(PQ_t pq, int idx) {
    shot_t *heap = pq->heap;
    while (parent(idx) >= 0 && get_priority(heap[parent(idx)]) < get_priority(heap[idx])) {
        swap(pq, idx, parent(idx));
        idx = parent(idx);
    }
}

void bubble_down(PQ_t pq, int idx) {
    int len = pq->len;
    int j;
    shot_t *heap = pq->heap;
    while (nbchildren(pq, idx) > 0) {
        j = left_child(idx);
        if (j != len-1 && get_priority(heap[j]) < get_priority(heap[j+1]))
            j++;  // get the left child if this one has a bigger priority
        if (get_priority(heap[idx]) > get_priority(heap[j]))
            break;  // stop the loop if the prority of the parent node is larger than the one of the children node
            
        swap(pq, idx, j);
        idx = j;
    }   
}

void enqueue(PQ_t pq, shot_t item) {
    pq->heap[pq->len] = item;
    bubble_up(pq, pq->len);
    pq->len++;
}

shot_t serve_max(PQ_t pq) {
    shot_t output = pq->heap[0];
    pq->heap[0] = pq->heap[pq->len -1];
    pq->len--;
    bubble_down(pq, 0);
    return output;
}

void free_PQ(PQ_t pq) {
    while(pq->len > 0) {
        free(serve_max(pq));
    }
    free(pq);
}


