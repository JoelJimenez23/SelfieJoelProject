uint64_t *sem;
uint64_t *bankers;
uint64_t *resources;

uint64_t *array1;
uint64_t *array2;
uint64_t *array3;

uint64_t contador1;
uint64_t contador2;
uint64_t contador3;

uint64_t contador_tmp;

void test(){
	if(get_pid() == 1){
		while(contador1 < 10){
			array1 = create_array(3);
			insert_array(array1,0,1);
			insert_array(array1,1,1);
			
			if(request_bankers(bankers,0,array1))
				release_bankers(bankers,0);

			contador1 = contador1 + 1;
		}
	}
	else if(get_pid() == 2){
		while(contador2 < 3){
			array2 = create_array(3);
			insert_array(array2,1,1);
			insert_array(array2,2,1);

			if(request_bankers(bankers,1,array2))
				release_bankers(bankers,1);


			contador2 = contador2  + 1;
		}
	}
	else if(get_pid() == 3){
		while(contador3 < 3){
			array3 = create_array(3);
			insert_array(array3,0,1);
			insert_array(array3,2,1);

			if(request_bankers(bankers,2,array3))
				release_bankers(bankers,2);


			contador3 =  contador3 + 1;
		}
	}


}



int main(){
	sem = sem_init(2);
	resources = create_array(3);
	insert_array(resources,0,1);
	insert_array(resources,1,1);
	insert_array(resources,2,1);
	bankers = create_bankers(3,3,resources);
	contador1 = 0;
	contador2 = 0;
	contador3 = 0;
	contador_tmp = 0;
	fork();
	if(get_pid() == 1){fork();}
	
	test();

}
