#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#define MAX 2048

struct block{
  int begin;
  int end;
  int size;
  block* prev=null;
  block* next=null;
};

block* freeHeader; block* freeTail;
block* busyHeader; block* busyTail;

void init(){
	freeHeader=new block;
	freeTail=new back;
	busyHeader=new back;
	busyTail=new block;
	block* first = new block;
	first->begin=0;
	first->end=MAX;
	first->size=MAX;
	first->prev=freeHeader;
	first->next=freeTail;
	freeHeader->next=first;
	freeTail->prev=first;
	busyHeader->next=busyTail;
	busyTail->prev=busyHeader;
}

block* allocmem(int size){
	block* p=freeHeader->next;
	while(p!=freeTail){
		if(p->size == size){
			p->prev->next=p->next;
			p->next->prev=p->prev;
			block* posi=find(p,busyHeader);
			posi->next->prev=p;
			p->next=posi->next;
			posi->next=p;
			p->prev=posi;
			return p;
		}
		else if(p->size >size){
			p->begin+=size;
			p->size-=size;
			block* more=new block;
			more->begin=p->begin-size;
			more->end=p->begin;
			more->size=size;
			block* posi=find(more,busyHeader);
			posi->next->prev=more;
			more->next=posi->next;
			posi->next=more;
			more->prev=posi;
			return more;
		}
		p=p->next;
	}
	return null;
}

void freemem(block* b){
	block* p=busyHeader->next;
	while(p!=b && p!=busyTail) p=p->next;
	p->prev->next=p->next;
    p->next->prev=p->prev;
	block* before=find(p,freeHeader);
	block* after=before->next;
	if(p->begin > befor->end+1 && p->end+1 < after->begin){
		after->prev=p;
		p->next=after;
		before->next=p;
		p->prev=before;
	}
	else if(p->begin == befor->end+1 && p->end+1 < after->begin){
		befor->size+=p->size;
		befor->end=before->begin+before->size;
	}
	else if(p->begin > befor->end+1 && p->end+1 == after->begin){
		after->size+=p->size;
		after->begin=after->end-after->size;
	}
	else if(p->begin == befor->end+1 && p->end+1 == after->begin){
		before->end=after->end;
		before->size=before->end-before->begin;
		after->next->prev=before;
		before->next=after->next;
		delete after;
	}
}

int main(){
	init();
	
	//test
	block* first = allocmem(32);
	block* second = allocmem(456);
	
	freemem(first);
	freemem(second);
	return 0;
}

	
