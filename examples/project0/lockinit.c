uint64_t *locky;
uint64_t *foo;

int main(){
	locky = lock_init();
	foo = "XXXXXXX\n";
	fork();

	lock(locky);
	while (*foo != 0) {
 	   write(1, foo, 8);
 	   foo = foo + 1;
 	 }
	unlock(locky);
}
