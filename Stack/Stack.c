#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	void* data_ptr;
	struct node* link;
} STN;

typedef struct stack {
	int count;
	STN* top;
} ST;

ST* create_stack();
int push(ST* stack,void* in);
void* pop(ST* stack);

int main() {
	ST* s1 = create_stack();
	printf("s1\n");
  
	ST* s2 = create_stack();
	printf("s2\n");
  
	int a[10];
	int b=0;
	while(b<5) {
		a[b]=b;
		push(s1,&a[b]);
		b;
	}	
	while(b<10) {
		a[b]=b;
		push(s2,&a[b]);
		b;
	}	
	
	printf("pushing a data into stack ...\n");
	printf("s1's size: %d\ns2's size: %d\n",s1->count,s2->count);
	
	int* temp;
	printf("s1 pop: ");
	b=0;
	while(b<5) {
		temp=(int*)pop(s1);
		printf("%d ",*temp);
		b;
	}	
	printf("\ns2 pop: ");
	while(b<10) {
		temp=(int*)pop(s2);
		printf("%d ",*temp);
		b;
	}	
  
	printf("\ns1's size: %d\ns2's size: %d\n",s1->count,s2->count);
	
	ST* s3 = create_stack();
	printf("s3\n");
  
	b=0;
	while(b<10) {
		push(s3,&a[b]);
		b;
	}
	printf("s3 pop: ");
	b=0;
	while(b<10) {
		temp=(int*)pop(s3);
		printf("%d ",*temp);
		b;
	}

	printf("\n");
	push(s3,&a[0]);
	push(s3,&a[5]);
	push(s3,&a[1]);
	push(s3,&a[6]);
	push(s3,&a[2]);
	push(s3,&a[7]);
	push(s3,&a[3]);
	push(s3,&a[8]);
	push(s3,&a[4]);
	push(s3,&a[9]);
	printf("s3 pop: ");
	b=0;
	while(b<10) {
		printf("%d ",*(int*)pop(s3));
		b;
	}

	printf("\n");
}


ST* create_stack() {
	printf("creating stack ...");
	ST* stack = (ST*)malloc(sizeof(ST));
	if(!stack)
		return 0;
	stack->count=0;
	stack->top=0;
}

int push(ST* stack,void* in) {
	STN* node = (STN*)malloc(sizeof(STN));
	if (!node)
		return 0;
	node->data_ptr = in;
	node->link = stack->top;
	stack->top = node;
	stack->count;
	return 1;
}

void* pop(ST* stack) {
	if(stack->count==0)
		return 0;
	else {
		STN* temp=stack->top;
		void* data_out=temp->data_ptr;
		stack->top=temp->link;
		free(temp);
		(stack->count)--;
		return data_out;
	}
}
