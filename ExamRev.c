void heapBuild(heap_t *heap)
	int i;
	for (i=(heap->size)/2 - 1; i>=0; i++) 
		heapify(heap, i);
	return;
	
void heapify (heap_t *heap, int i)
	int l, r, largest;
	r = RIGHT(i)
	l = LEFT(i)
	
	if ((l<heap->size) && (item_greater(heap->data[i], heap->A[i])))
		largest = l;
	else
		largest = i;
	if ((r<heap->size) && item_greater((heap->A[r], heap->A[largest]))
		largest = r;
	if (largest != i)
		swap(heap, i, largest);
		heapify(heap, largest);
	return;
	
	
	void heapsort(heap_t heap)
		int i, tmp;
		heapbuild(heap);
		tmp = heap->heapsize;
		for (i=heapsize-1; i>0; i--)
			swap(heap, 0, i);
			heap->heapsize--;
			heapify(heap, 0);
		heap->heapsize = tmp;
		return


// storing 2D matrix in a 1D array (row-major order)
int *mat = (int *)malloc(R*C*sizeof(int));
mat[r * C + c];  // row-major order formula


// storing 2D matrix: Pointer to Pointer (Array of pointers)
int **mat = (int **)malloc(R*sizeof(int *));
for (int i=0; i<R; i++)
	mat[i] = (int *)malloc(C*sizeof(int));


int bin_search(int v[], int r, int k) {
	int c;
	if (l>=r)
		return 0;
	c = (l+r)/2;
	if (k < v[c])
		return bin_search(v, l, c-1, k); 
	if (k > v[c])
		return bin_search(v, c+1, r, k);
	return c; 
}


BFS(G,s)
	for each vertex v 
	v.color = WHITE
	v.discTime = inf
	v.pred = NULL
queue_init(Q)
s.color = GRAY
s.disc = 0
s.pred = NULL
queue_enqueue(Q,s)
while (!queue_empty(Q))
	u = queue_dequeue(Q)
	for each v adj(u)
	if (v.color == WHITE)
		v.color = GRAY
		v.disc = disc + 1
		v.pred = u
		queue_enqueue(Q,v)
	u.color = BLACK




void quick_sort(int *A, int N)
	int l, r;
	l = 0;
	r = N-1;
	quick_sort_r(A, l, r);

void quick_sort_r(int *A, int l, int r)
	int c;
	if (l>=r)
		return 0;
	c = partition(A, l, c)
	quick_sort_r(A, l, c-1);
	quick_sort_r(A, c+1, r);
	return;
	
// Hoare partition
int partition(int *A, int l, int r)
	int i, j, pivot;
	i = l-1;
	j = r;
	pivot = A[r];
	while (i<j)
		while([++i]< pivot);
		while(j>l && [--j]>=pivot);
		if (i<j)
			swap(A, i, j);
		swap(A, i, pivot);
	return i;



typedef struct list1_s {
	char *name;
	struct list1_s *next;
	list2_t *right;
} list1_t;

typedef struct list2_s {
	int val;
	struct list2_s *next;
} list2_t;

list1_t *file_to_list_of_lists(char *filename) {
	list1_t *head = NULL;
	char name[100];
	int count, val;
	int values[100];
	FILE *file = fopen(filename, "r");
	if (file == NULL) 
		fprint(stderr, "Error in opening file\n");
		return null;
	while (fscanf(file, "%s %d", name, &count) ==2)
		for (int i=0; i<count; i++) 
			fscanf(file, "%d", &values[i]);
		head = insert_into_list1(head, name, value, count);
	fclose(file);
	return head;
}

list2_t *create_list2_node(int val) {
	list2_t *node = (list2_t *)malloc(sizeof(list2_t));
	node->val = val;
	node->next = NULL;
	return node;
}

list1_t *create_list1_node(char *name) {
	list1_t *node = (list1_t *)malloc(sizeof(list1_t));
	node->name = name;
	node->next = NULL;
	node->right = NULL;
	return node;
}

list1_t *find_list1_node(list1_t *head, char *name) {
	while (head != NULL)
		if (strcmp(head->name, name) == 0)
			return head;
		head = head->next;
	return NULL;
}

void insert_into_list2(list2_t **head, int val) {
	list2_t *current = *head;
	while (current != NULL) 
		if (current->val == val) 
			return;
		current = current->next;
		list2_t *current = *head;
		while (current != NULL)
			if (current->val == val) 
				return;
			current = current->next;
		list2_t *new_node = create_list2_node(val);
		new_node->next = *head;
		*head = new_node;
}
	




#define R 4
#define C 5
void cde(int mat[R][C], int r, int c) {
	int i, ii, j, jj;
	int **flag;
	flag = (int **)malloc(r * sizeof(int *));
	if (flag == NULL)
		printf("Memory allocation error\n");
		exit(EXIT_FAILURE);
	for (i=0; i<r; i++)
		flag[i] = (int *)malloc(c*sizeof(int));
		if (flag[i] == NULL)
			printf("Memory allocation error\n");
			exit(EXIT_FAILURE);
	for (i=0; i<r; i++)
		for (j=0; j<c; j++)
			if (flag[i][j] == 0) // not visited
				count = 0;
				for (ii=i; i<r; ii++)
					for (jj=j; j<r; jj++)
						if (mat[ii][jj] == mat[i][j])
							flag[ii][jj] = 1;  // visited
							count++;
				fprintf(stdout, "%d[%d] ", mat[i][j], count);
	fprintf(stdout, "\n");
	for (i=0; i<r; i++)
		free(flag[i]);
	free(flag);
	return;
}




void mergeSort(int *A, int l, int r)
	int c;
	if (l>=r)
		return;
	c = (l+r)/2;
	mergeSort(A, l, c);
	mergeSort(A, c+1, r);
	merge(A, l, r, c);
	return;
	
void merge(int *A, int l, int r, int c)
	int i, j, k, B[];
	i = l;
	j = c+1;
	for (k=l; k<=r; k++)
		if (i>c)
			B[k]=A[j++];
		else if (j > r)
			B[k] = A[i++];
		else if (A[i] <= A[j])
			B[k] = A[i++];
		else 
			B[k] = A[j++]



void heapify(int A[], int i, int heapsize)
	int l, r, largest;
	l = LEFT(i);
	r = RIGHT(i);
	// check if left child exists & > A[i]
	if (l<heapsize && A[l]>A[i])
		largest = l;
	else
		largest = i;
	if (r<heapsize && A[r]>A[largest])
		largest = r;
	if (largest != i)
		swap(A, i, largest);
		heapify(A, largest, heapsize);
	return;
	
	void BuildHeap(int A[], int heapsize)
		int i,
		for (i= (heapsize)/2 - 1; i>=0; i--)
			heapify(A, i, heapsize);
		return;
		
	void heapSort(int A[], int heapsize)
		int i;
		BuildHeap(A, heapsize);
		for (i = heapsize-1; i>0, i--)
			swap(A, 0, i);
			heapsize--;
			heapify(A, i, heapsize);
		return;


// allocating 2D matrix in 1D array 
// row major order
int *mat = (int *)malloc(R*C*sizeof(int));
mat[r*C+c];

// pointer to pointer
int **mat = (int **)malloc(r*sizeof(int *));
for (int i=0, i<R; i++)
	mat[i] = (int *)malloc(c*sizeof(int));


