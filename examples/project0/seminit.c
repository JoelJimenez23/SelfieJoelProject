uint64_t *semini;
uint64_t *foo;
uint64_t *foo1;
uint64_t *foo2;
uint64_t *locky;

void test(){
	sem_wait(semini);
	lock(locky);
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
	unlock(locky);
	sem_pos(semini);
}

int main(){
	semini = sem_init(2);
	locky = lock_init();

	foo = "XXXXXXX\n";
	foo1 ="YYYYYYY\n";
	foo2 ="ZZZZZZZ\n";

	fork();
	if(get_pid() == 1){
		fork();
	}
	
	test();


	return 0;
}
