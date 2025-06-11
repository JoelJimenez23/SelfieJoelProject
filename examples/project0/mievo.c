uint64_t *test;
uint64_t *locky;
uint64_t *aja;

uint64_t main(){
	locky = lock_init();
	test = malloc(sizeof(uint64_t));
	*test = 1;
	printf(1,test);
	printf(0,*test);
	thread();
	thread();
	thread_join();
	
	

	if(get_pid() == 1){
		lock(locky);
		printf(0,111);
		printf(1,test);
		printf(0,*test);
		printf(0,111);
		*test = 2;
		unlock(locky);
	}
	if(get_pid() == 2){
		lock(locky);
		printf(0,222);
		printf(1,test);
		printf(0,*test);
		printf(0,222);
		*test = 3;
		unlock(locky);
	}
	if(get_pid() == 3){
		lock(locky);
		printf(0,333);
		printf(1,test);
		printf(0,*test);
		printf(0,333);
		*test = 4;
		unlock(locky);
	}


	return 0;
}
