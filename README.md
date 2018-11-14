#include <stdio.h>
#include <stdlib.h>
typedef struct node {
	void* data_ptr;
	struct node* link;
} STN;			// node 구조체를 정의하고 STN으로 typedef 선언한다.
typedef struct stack {
	int count;
	STN* top;
} ST;			// stack 구조체를 정의하고 ST로 typedef 선언한다.
ST* create_stack();
int push(ST* stack,void* in);
void* pop(ST* stack);	// 사용할 함수들을 미리 선언한다.
int main() {
	ST* s1 = create_stack();
	printf("s1\n");
	ST* s2 = create_stack();
	printf("s2\n");			// 스택 s1,s2를 생성한다.
	int a[10];
	int b=0;
	while(b<5) {
		a[b]=b;
		push(s1,&a[b]);
		b;
	}		// 5개의 변수를 초기화하고 s1스택에 push한다.
	while(b<10) {
		a[b]=b;
		push(s2,&a[b]);
		b;
	}		// 5개의 변수를 초기화하고 s2스택에 push한다.
	
	printf("s1's size: %d\ns2's size: %d\n",s1->count,s2->count);
			// 정상작동을 확인하기 위해 스택의 size를 출력한다.
	int* temp;
	printf("s1 pop: ");
	b=0;
	while(b<5) {
		temp=(int*)pop(s1);
		printf("%d ",*temp);
		b;
	}		// 스택 s1의 모든 데이터를 pop한다.
	printf("\ns2 pop: ");
	while(b<10) {
		temp=(int*)pop(s2);
		printf("%d ",*temp);
		b;
	}			// 스택 s2의 모든 데이터를 pop한다.
	printf("\ns1's size: %d\ns2's size: %d\n",s1->count,s2->count);
				// 스택이 모두 비었음을 확인한다.
	ST* s3 = create_stack();
	printf("s3\n");		// 새로운 스택 s3를 생성한다.
	b=0;
	while(b<10) {
		push(s3,&a[b]);
		b;
	}			// s3 스택에 data를 ‘구현내용1’순으로 push한다.
	printf("s3 pop: ");
	b=0;
	while(b<10) {
		temp=(int*)pop(s3);
		printf("%d ",*temp);
		b;
	}
// s3를 pop한다. push의 역순으로 출력됨을 보아 ‘구현내용1’의 순서를 확인할 수 있다.
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
	push(s3,&a[9]);		// 다시 s3스택에 ‘구현내용2’순으로 push한다.
	printf("s3 pop: ");
	b=0;
	while(b<10) {
		printf("%d ",*(int*)pop(s3));
		b;
	}
// s3를 pop한다. push의 역순으로 출력됨을 보아 ‘구현내용2’의 순서를 확인할 수 있다.
	printf("\n");
}
ST* create_stack() {
	printf("creating stack ...");
	ST* stack = (ST*)malloc(sizeof(ST));
	if(!stack)
		return 0;
	stack->count=0;
	stack->top=0;
}	// create_stack함수를 정의한다. 함수를 벗어나도 데이터가 유지되도록 malloc함수로 메모리를 할당한다. 메모리가 정상적으로 할당되지 않았을 경우에는 0을 반환하여 충돌을 방지한다. 처음 생성되었으므로 count는 0이고 top은 0을 가리키고 있다.
int push(ST* stack,void* in) {
	printf("pushing a data into stack ...\n");
	STN* node = (STN*)malloc(sizeof(STN));
	if (!node)
		return 0;
	node->data_ptr = in;
	node->link = stack->top;
	stack->top = node;
	stack->count;
	return 1;
}	// push함수를 정의한다. 마찬가지로 malloc함수를 사용하여 데이터를 node구조체로 생성하고 충돌을 방지하기 위한 if문을 작성한다. 이전의 top을 push한 node의 link로, push한 node를 스택의 top으로 설정한다. 그리고 스택의 count를 1 증가시킨다.
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
	}	// pop함수를 정의한다. 스택의 count가 0일 경우엔 0을 반환하게 한다. 그 외의 경우엔 top의 주소를 임시변수 temp에 저장해놓은 뒤, 스택의 top을 이전 top의 link로 설정하고 기존 top의 data를 data_out변수에 저장한다. 그 후 temp가 가리키는 메모리 공간을 free함수로 해제하고 스택의 count를 1 감소시키며 data_out의 값을 출력한다.
}
