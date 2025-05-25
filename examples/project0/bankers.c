uint64_t *array;
uint64_t *bankers;
uint64_t *sem;
uint64_t *lockcito;

uint64_t *array_1;
uint64_t *array_2;
uint64_t *array_3;
uint64_t *array_4;
uint64_t *array_5;
uint64_t contador;

void test(){
	while(contador < 10){ 
	sem_wait(sem);
	//pensar();
	if(get_pid() == 1){
		array_1 = create_array(5);
		insert_array(array_1,0,1);
		insert_array(array_1,1,1);
		if(request_bankers(bankers,0,array_1)){
			release_bankers(bankers,0);
		}

	}else if (get_pid() == 2){
		array_2 = create_array(5);
		insert_array(array_2,1,1);
		insert_array(array_2,2,1);
		if(request_bankers(bankers,1,array_2)){
			release_bankers(bankers,1);
		}
	} else if (get_pid() == 3){
		array_3 = create_array(5);
		insert_array(array_3,2,1);
		insert_array(array_3,3,1);
		if(request_bankers(bankers,2,array_3)){
			release_bankers(bankers,2);
		}
	} else if (get_pid() == 4){
		array_4 = create_array(5);
		insert_array(array_4,3,1);
		insert_array(array_4,4,1);
		if(request_bankers(bankers,3,array_4)){
			release_bankers(bankers,3);
		}
	} else if (get_pid() == 5){
		array_5 = create_array(5);
		insert_array(array_5,4,1);
		insert_array(array_5,0,1);
		if(request_bankers(bankers,4,array_5)){
			release_bankers(bankers,4);
		}
	}

	sem_pos(sem);
	contador = contador + 1;
	}
}


int main(){
	sem = sem_init(4);
	lockcito = lock_init();
	array = create_array(5);
	insert_array(array,0,1);
	insert_array(array,1,1);
	insert_array(array,2,1);
	insert_array(array,3,1);
	insert_array(array,4,1);
	bankers = create_bankers(5,5,array);
	contador = 0;

	fork();
	if(get_pid() == 1){
		fork();
	}
	if(get_pid() == 1){
		fork();
	}
	if(get_pid() == 1){
		fork();
	}

	test();
	
	return 0;
}
