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
uint64_t *cs_counter;

void test(){
	while(contador < 40){ 
	sem_wait(sem);
	//pensar();
	if(get_pid() == 1){
		
		lock(lockcito);
		if(request_bankers(bankers,0,array_1)){
			increment_critical_section_counter(cs_counter,0);
			unlock(lockcito);
			//comer();
			release_bankers(bankers,0);
		}else{
			unlock(lockcito);
		}

	}else if (get_pid() == 2){

		lock(lockcito);
		if(request_bankers(bankers,1,array_2)){
			increment_critical_section_counter(cs_counter,1);
			unlock(lockcito);
			//comer()
			release_bankers(bankers,1);
		} else {  
		unlock(lockcito);
		}

	} else if (get_pid() == 3){

		lock(lockcito);
		if(request_bankers(bankers,2,array_3)){
			increment_critical_section_counter(cs_counter,2);
			unlock(lockcito);
			//comer()
			release_bankers(bankers,2);
		} else {
			unlock(lockcito);
		}
	} else if (get_pid() == 4){

		lock(lockcito);
		if(request_bankers(bankers,3,array_4)){
			increment_critical_section_counter(cs_counter,3);
			unlock(lockcito);
			//comer()
			release_bankers(bankers,3);
		} else {
				unlock(lockcito);
		}
	} else if (get_pid() == 5){
		lock(lockcito);
		if(request_bankers(bankers,4,array_5)){
			increment_critical_section_counter(cs_counter,4);
			unlock(lockcito);
			//comer()
			release_bankers(bankers,4);
		} else {  
		unlock(lockcito);
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
	array_1 = create_array(5);
	insert_array(array_1,0,1);
	insert_array(array_1,1,1);
	array_2 = create_array(5);
	insert_array(array_2,1,1);
	insert_array(array_2,2,1);
	array_3 = create_array(5);
	insert_array(array_3,2,1);
	insert_array(array_3,3,1);
	array_4 = create_array(5);
	insert_array(array_4,3,1);
	insert_array(array_4,4,1);
	array_5 = create_array(5);
	insert_array(array_5,4,1);
	insert_array(array_5,0,1);



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

	cs_counter = critical_section_counter(5);	

	test();
	
	get_critical_section_counter(cs_counter,5);

	return 0;
}
