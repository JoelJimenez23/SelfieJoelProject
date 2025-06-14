uint64_t *semaphore;
uint64_t *sem_lock;
uint64_t *foo;
uint64_t *foo1;
uint64_t *foo2;

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
	request(1);
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
	release(1);
}

void sem_post(uint64_t * sem){
	uint64_t *head;
	uint64_t *test;
	request(1);
	lock(sem_lock);
	*sem = *sem + 1; 
	head = *(sem+1);
	if(head != (uint64_t*)0){
		*(sem+1) = *(head+1);
		awake(*head);
	}
	unlock(sem_lock);
	release(1);
}


void write_w(uint64_t* cadena,uint64_t size){
	request(0);
	while(*cadena != 0){
		write(1,cadena,size);
		cadena = cadena + 1;
	}
	release(0);
}


void test(){
	sem_wait_t(semaphore);
	if(get_pid() == 1){
 		write_w(foo,8);	 
	}else if(get_pid() == 2){
		write_w(foo1,8);
	} else if(get_pid() == 3){
		write_w(foo2,8);
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

