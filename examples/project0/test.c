uint64_t *semaphore;
uint64_t *foo;
uint64_t *foo1;
uint64_t *foo2;
uint64_t *sem_lock;


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
	uint64_t *tmp;
	if(*sem == 0){
		lock(sem_lock);
		if(*(sem+1) == (uint64_t*)0){
			new_node = malloc(2*sizeof(uint64_t));
			//printf(1,new_node);
			*(new_node) = get_context(); 
			//printf(1,*(new_node));
			*(new_node+1) = ((uint64_t*)0);
			*(sem+1) = new_node;
			/*
			printf(1, sem);           // dirección del semáforo
			printf(1, *(sem+1));      // dirección del head
			printf(0, *sem);            // contador del semáforo
			printf(1, new_node);        // debería ser igual que *(sem+1)
			printf(1, *new_node);
			*/
		} 
		else {
			new_node = malloc(2*sizeof(uint64_t));
			tmp = (uint64_t*)(*(sem+1));
			while(*(tmp + 1) != (uint64_t)0){
				tmp = (uint64_t*)*(tmp+1);
			}
			*new_node = (uint64_t)get_context(); 
			*(new_node+1) = (uint64_t)0;
			*(tmp+1) = new_node;
		}
		unlock(sem_lock);
		sleep();
	} else {
		lock(sem_lock);
		*sem = *sem - 1;
		unlock(sem_lock);
	}
}

void sem_post(uint64_t * sem){
	uint64_t *head;
	lock(sem_lock);
	*sem = *sem + 1; //count++
	head = *(sem+1);

	if(head != (uint64_t*)0){
		*(*(sem+1)) = *(*(head+1));
		printf(0,222);
		printf(1,*(sem+1));
		printf(1,*(*(sem+1)));
		printf(0,222);
		awake(*(*(sem+1)));// despertar 
	}
	unlock(sem_lock);
}


void test(){
	sem_wait_t(semaphore);
	if(get_pid() == 1){
		while (*foo != 0) {
 	   write(1, foo, 8);
 	   foo = foo + 1;
 	 } 
	}else if(get_pid() == 2){
		while (*foo1 != 0) {
 	   write(1, foo1, 8);
 	   foo1 = foo1 + 1;
 	 	}
	} else if(get_pid() == 3){
		while (*foo2 != 0) {
 	   write(1, foo2, 8);
 	   foo2 = foo2 + 1;
 	 	}
	}
	sem_post(semaphore);
}


uint64_t main(){
	semaphore = create_sem(1);
	sem_lock = lock_init();
	foo  = "XXXXXXX\n";
	foo1 = "YYYYYYY\n";
	foo2 = "ZZZZZZZ\n";

	thread();
	thread();
	thread_join();

	test();

	return 0;
}
