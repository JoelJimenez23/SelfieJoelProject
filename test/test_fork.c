uint64_t *foo1;
uint64_t *foo2;
uint64_t test;

int main(){
	foo1 = "XXXXXXX\n";
	foo2 = "YYYYYYY\n";
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
	
	return 0;
}
