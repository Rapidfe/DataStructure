## Stack의 구현과 push,pop함수 활용
```
typedef struct node {
	void* data_ptr;
	struct node* link;
} STN;
```
node 구조체를 정의하고 STN으로 typedef 선언한다.<br>
구조체의 정의에 해당 구조체가 속해있으므로 이 구조체의 이름 'node'는 생략해선 안된다.
```
typedef struct stack {
	int count;
	STN* top;
} ST;
```
stack 구조체를 정의하고 ST로 typedef 선언한다.<br>
여기서는 구조체의 이름 'stack'을 생략해도 된다.
```
ST* create_stack();
int push(ST* stack,void* in);
void* pop(ST* stack);
```
사용할 함수들을 선언한다.<br><br>
여기까지는 원래 헤더파일에 들어갈 내용이다. stack을 할 때는 헤더,소스,메인 파일을 따로 나누지않았다.<br>
아래부터는 소스파일에 들어갈 내용이다.
```
ST* create_stack() {
	printf("creating stack ...");
	ST* stack = (ST*)malloc(sizeof(ST));
	if(!stack)
		return 0;
	stack->count=0;
	stack->top=0;
}
```
create_stack함수를 정의한다. <br>
>### malloc함수를 사용하는 이유?<br>
>일반 구조체로 선언하면 create_stack()이라는 함수를 벗어나면서 데이터가 사라진다. 외부함수에서도 사용할 수 있는 stack 구조체를 생성하기 위해 malloc함수로 메모리를 할당한다. malloc으로 생성한 데이터는 free함수로 삭제할때까지 메모리를 차지하며 남아있으므로 삭제에 유의해야 한다.<br>

메모리가 정상적으로 할당되지 않았을 경우에는 0을 반환하게 하여 충돌을 방지한다.
```
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
}
```
stack에 새로운 데이터를 삽입하는 push함수를 정의한다. <br>
push하는 데이터를 담을 node구조체를 만든 뒤 stack의 top이었던 node가 새로운 node의 link가 되게하고, 새로운 node를 stack의 top으로 한다.
```
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
```
stack의 top 데이터를 뽑아내는 pop함수를 정의한다.<br>
pop되는 node는 malloc으로 할당된 데이터이므로 free함수로 삭제해야한다. pop되는 node의 link가 stack의 새로운 top이 되면 기존 top이 가리키고 있던 node, 즉 삭제해야할 node의 주소를 잃게되므로 top을 갱신하기 전에 top이 가지고있는 주소를 임시노드 temp에 백업해두어야 한다. pop되는 node의 data도 백업해두고 free해준다.

### 간단한 활용
2개의 stack을 하나로 merge해보기.
```
// 내용1			 // 내용2	
│ 4 │     │ 9 │     │ 9 │	│ 4 │     │ 9 │     │ 9 │
│ 3 │     │ 8 │     │ 8 │	│ 3 │     │ 8 │     │ 4 │
│ 2 │  +  │ 7 │  =  │ 7 │	│ 2 │  +  │ 7 │  =  │ 8 │
│ 1 │     │ 6 │     │ 6 │	│ 1 │     │ 6 │     │ 3 │
│ 0 │     │ 5 │     │ 5 │	│ 0 │     │ 5 │     │ 7 │
└───┘     └───┘     │ 4 │	└───┘     └───┘     │ 2 │
		    │ 3 │			    │ 6 │
		    │ 2 │			    │ 1 │
		    │ 1 │			    │ 5 │
		    │ 0 │			    │ 0 │
		    └───┘			    └───┘
```
```
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



