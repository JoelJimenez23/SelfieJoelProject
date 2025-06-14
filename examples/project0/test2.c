uint64_t *semaphore;
uint64_t *sem_lock;
uint64_t num_iter;
uint64_t counter;


uint64_t *create_sem(uint64_t size){
	uint64_t *sem;
	uint64_t *queue;
	sem = malloc(2 * sizeof(uint64_t));
	queue = (uint64_t*)0;	
	*sem = size;
	*(sem+1) = (uint64_t)queue;
	return sem;
}

void sem_wait_t(uint64_t * sem){
	uint64_t *new_node;
	uint64_t *new_node1;
	uint64_t *tmp;
	uint64_t *test;
	uint64_t *test1;
	lock(sem_lock);
	if(*sem == 0){
		if(*(sem+1) == (uint64_t*)0){
			new_node = malloc(2 * sizeof(uint64_t));
			*(new_node) = get_context(); 
			*(new_node+1) = (uint64_t*)0;
			*(sem+1) = new_node;
		} 
		else {
			tmp = (uint64_t*)(*(sem+1));
			while(*(tmp+1) != (uint64_t)0){
				tmp = *(tmp+1);
			}
			new_node1 = malloc(2 * sizeof(uint64_t));
			*new_node1 = get_context();
			*(new_node1+1) = (uint64_t*)0;
			*(tmp+1) = new_node1;
		}
		unlock(sem_lock);
		sleep();
	} else {
		*sem = *sem - 1;
		unlock(sem_lock);
	}
}

void sem_post(uint64_t * sem){
	uint64_t *head;
	uint64_t *test;
	lock(sem_lock);
	*sem = *sem + 1; 
	head = *(sem+1);
	if(head != (uint64_t*)0){
		*(sem+1) = *(head+1);
		awake(*head);
	}
	unlock(sem_lock);
}

void test(){
	uint64_t i;
	uint64_t tmp;
	i = 0;
	while(i<num_iter){
		sem_wait_t(semaphore);
		tmp = counter;
		tmp = tmp + 1;
		counter = tmp;
		sem_post(semaphore);
		i = i + 1;
	}
}

uint64_t main(){
	semaphore = create_sem(1);
	sem_lock = lock_init();
	num_iter = 10;
	counter = 0;
	
	thread();
	thread();
	thread();
	thread();
	thread();
	thread_join();
	
	test();

	printf(0,counter);

	return 0;
}

