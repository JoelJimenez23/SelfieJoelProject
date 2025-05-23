uint64_t *foo;
uint64_t *foo1;
uint64_t *foo2;
uint64_t contador;

int main(){
	foo =  "XXXXXXX\n";
	foo1 = "YYYYYYY\n";
	foo2 = "ZZZZZZZ\n";
	contador = thread();
	contador = thread();

	if(contador == 0){
		while (*foo) {
			write(1,foo,8);
			foo = foo + 1;
		}
	} else if(contador == 1){
		while (*foo1) {
			write(1,foo1,8);
			foo1 = foo1 + 1;
		}
	} else if(contador == 2){
		while (*foo2) {
			write(1,foo2,8);
			foo2 = foo2 + 1;
		}
	}
	
	return 0;

}
