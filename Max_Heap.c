#include <stdio.h>
#include <stdlib.h>

#define SOLIDERDATA 1000
#define INVALIDATE_VALUE -1000
typedef int e_t;

typedef struct Maxheap {
	e_t *Element;
	int Size;
	int Capacity;
} Maxheap_T;

Maxheap_T *Maxheap_Create(int Capacity)
{
	Maxheap_T *Root = malloc(sizeof(Maxheap_T));
	if (!Root) {
		return NULL;
	}
	Root->Element = malloc((sizeof(e_t)+1)*Capacity);
	if(!Root->Element) {
		free(Root);
		return NULL;
	}
	Root->Element[0] = SOLIDERDATA;
	Root->Size = 0;
	Root->Capacity = Capacity;
	
	return Root;
}

Maxheap_T *Maxheap_Insert(Maxheap_T *Root, e_t Value)
{
	if(!Root || Value > Root->Element[0]) {
		return NULL;
	}
	if(Maxheap_Isfull(Root)) {
		return NULL;
	}

	int i = ++Root->Size;
	for(; Value > Root->Element[i/2]; i/=2 ) {
		Root->Element[i] = Root->Element[i/2];
	}
	Root->Element[i] = Value;

	return Root;
}

e_t Maxheap_Delete(Maxheap_T *Root)
{
	if(Maxheap_Isempty(Root)) {
		return INVALIDATE_VALUE;
	}
	
	e_t MaxVal = Root->Element[1];
#if 0	
	int Parent, Child;
	e_t TmpVal = Root->Element[Root->Size--];
	for(Parent=1; Parent*2<Root->Size; Parent=Child ) {
		Child = Parent * 2;
		if(Child != Root->Size && Root->Element[Child] < Root->Element[Child+1]) {
			Child++;
		}
		if(TmpVal > Root->Element[Child]) {
			break;
		}
		Root->Element[Parent] = Root->Element[Child];
	}
	Root->Element[Parent] = Tmpval;
#endif

	PrecDown(Root, 1);

	return MaxVal;
}

static void PercDown(Maxheap_T *Root, int i)
{
	int Parent, Child;
	e_t TmpVal = Root->Element[i];
	for(Parent=i; Parent*2<Root->Size; Parent=Child) {
		if(Child!=Root->Size && Root->Element[Child] < Root->Element[Child+1]) {
			Child ++;
		}
		if(TmpVal > Root->Element[Child]) {
			break;
		}
		Root->Element[Parent] = Root->Element[Child];
	}
	Root->Element[Parent] = TmpVal;
}

Maxheap_T *Maxheap_Build(Maxheap_T *Root, e_t *Data, int Len)
{
	if(!Root || !Data) {
		return NULL;
	}

	int i = 0;
	while( i < Len ) {
		Root->Element[Root->Size++] = Data[i++];
	}
	
	i = Root->Size/2;
	for(; i>0; i--) {
		PrecDown(Root, i);
	}
	return Root;
}

