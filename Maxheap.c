#include <stdio.h>
#include <stdlib.h>

// Heap(in this file): Complete Binary Tree made by Array

#define debug(msg)	printf("[%s]: %s\n", __FUNCTION__, msg )
#define MAXDATA		99999999

typedef int e_t
typedef struct maxheap {
	e_t *element;//array
	int size;//current element number
	int capacity;//max element number
} maxheap_t;

maxheap_t *maxheap_create(int maxsize);
maxheap_t *maxheap_insert(maxheap_t *root, e_t val);
e_t	maxheap_delete(maxheap_t *root);
int	maxheap_isempty(maxheap_t *root);
int	maxheap_isfull(maxheap_t *root);


maxheap_t *maxheap_create(int maxsize)
{
	maxheap_t *root = malloc(sizeof(maxheap_t));
	if(!root) {
		return NULL;
	}
	root->element = malloc(maxsize*(sizeof(e_t)+1));
	if(!root->element) {
		return NULL;
	}
	root->element[0] = MAXDATA;// solider
	root->size = 0;
	root->capacity = maxsize;
	return root;
}

maxheap_t *maxheap_insert(maxheap_t *root, e_t val)
{
	if(!root) {
		return NULL;
	}
	if(maxheap_isfull()) {
		debug("heap is full");
		return root;
	}
	int i = ++root->size;
	for(; val > root->element[i/2]; i/=2) {
		root->element[i] = root->element[i/2];	
	}
#if 0	
	while(val > root->element[i/2]) { //if child is larger then parent
		root->element[i] = root->element[i/2]; // move parent to his child
		i /= 2;
	}
#endif	
	root->element[i] = val;
	return root;
}

// return max value and delete this node
e_t maxheap_delete(maxheap_t *root)
{
	if(!root) {
		return -1;
	}
	if(maxheap_isempty()) {
		return -1;
	}

	e_t maxdata = root->element[1];// get max data
	e_t thelastval = root->element[root->size--];
	int parent, child;
	for(parent=1; parent*2<root->size; parent=child) {
		child = parent*2;
		if(child!=root->size && root->element[child] < root->element[child+1]) {
			child++;// if right child large than left, then move child index
		}
		if(thelastval > root->element[child]) {
			break;// find place to store the  last value
		}
		else {
			root->element[parent] = root->element[child];
		}
	}
	root->element[parent] = thelastval;
	return maxdata;
}

static void perc_down(maxheap_t *root, int p)
{
	int parent, child;
	e_t tmp = root->element[p];
	for(parent = p; parent*2<root->size; parent=child) {
		child = parent*2;
		if( child!=root->size && root->element[child] < root->element[child+1]) {
			child++;
		}
		if(root->element[parent] > root->element[child]) {
			break;
		}
		root->element[parent] = root->element[child];
	}
	root->element[parent] = tmp;
}

maxheap_t *maxheap_build(maxheap_t *root, e_t *data)
{
	int size = sizeof(data);
	if(size > root->capacity || !root || !data) {
		return NULL;
	}
	root->size = size;
	
	int i;	
	for(i=0; i<root->size; i++) {
		root->element[i+1] = data[i];
	}
	// adjust every child heap to be a maxheap from bottom
	for(i=root->size/2; i>0; /*i/=2*/i--) {
		perc_down(root, i);
	}	
	return root;
}

int maxheap_isempty(maxheap_t *root)
{
	return root->size == 0;
}

int maxheap_isfull(maxheap_t *root)
{
	return root->capacity == root->size;
}
