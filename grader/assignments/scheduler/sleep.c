void* malloc(unsigned long);

uint64_t pthread_create();
uint64_t pthread_join(uint64_t* status);
void     pthread_exit(uint64_t status);

uint64_t global_variable = 0;

int main(int argc, char** argv) {
  uint64_t  tid;
  uint64_t* status;

  status = malloc(sizeof(uint64_t));

  tid = pthread_create();
  
  if (tid) {
    sleep(40);
    global_variable = 16;
  }
  else {
    sleep(60);
    global_variable = 32;
  }

  if (tid) {
    pthread_join(status);
  } else {
    pthread_exit(0);
  }

  return global_variable;
}