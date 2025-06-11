uint64_t *array;
uint64_t *foo;

int main(){
	foo = "XXXXXXX\n";
	array = malloc(4 * sizeof(uint64_t));
	*(array+2) = 3;
	if(*(array + 2) == 3){

	  while (*foo != 0) {
	    // 1 means that we print to the console
	    // foo points to a chunk of 8 characters
	    // 8 means that we print 8 characters
	    write(1, foo, 8);
	
  	  // go to the next chunk of 8 characters
  	  foo = foo + 1;
  	}

	}

	return 0;
}
