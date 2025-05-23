uint64_t *foo1;
uint64_t *foo2;
uint64_t test;
uint64_t test1;
uint64_t *foo3;
uint64_t *foo4;

int main(){
	foo1 = "XXXXXXX\n";
	foo2 = "YYYYYYY\n"; 
	foo3 = "ZZZZZZZ\n";
	foo4 = "CCCCCCC\n";
	test = fork();

	if(test != 0){
		while(*foo1 != 0){
			write(1,foo1,8);
			foo1 = foo1 + 1;
		}
	}
	else if(test == 0){
		while(*foo2 != 0){
			write(1,foo2,8);
			foo2 = foo2 + 1;
		}
	}
	
	test1 = fork();
	if(test1 != 0){
		while(*foo3 != 0){
			write(1,foo3,8);
			foo3 = foo3 + 1;
		}
	}
	else if(test1 == 0){
		while(*foo4 != 0){
			write(1,foo4,8);
			foo4 = foo4 + 1;
		}
	}
	return 0;
}
