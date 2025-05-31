uint64_t *locky;
uint64_t *foo;
uint64_t *foo1;

int main(){
	locky = lock_init();
	foo = "XXXXXXX\n";
	foo1 = "YYYYYYY\n";
	fork();

	lock(locky);
	if(thread_id() == 0){  
		while (*foo != 0) {
 		  write(1, foo, 8);
 	 		foo = foo + 1;
 	 	}
	} else if (thread_id() == 1){
		while (*foo1 != 0){
			write(1,foo1,8);
			foo1 = foo1 + 1;
		}
	}

	unlock(locky);
}
