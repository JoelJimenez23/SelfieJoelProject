uint64_t contador;
uint64_t bolt;
uint64_t starter;
uint64_t* foo;

// Variables "locales" por hilo simuladas como globales
uint64_t i_thread1;
uint64_t i_thread2;

void P() {
  if (starter == 1) i_thread1 = 0;
  if (starter == 2) i_thread2 = 0;

  while ((starter == 1 && i_thread1 < 2) || (starter == 2 && i_thread2 < 2)) {
    while (compare_and_swap(&bolt, 0, 1) == 1) {}

    contador = contador + 1;

    bolt = 0;

    if (starter == 1) i_thread1 = i_thread1 + 1;
    if (starter == 2) i_thread2 = i_thread2 + 1;
  }
}

int main() {
  foo = "XXX\n";
  contador = 0;
  bolt = 0;

  starter = thread();
  thread_join();

  if (starter == 1) {
    P();
  }

  starter = thread();
  if (starter == 2) {
    P();
  }

  if (contador == 4) {
    while (*foo) {
      write(1, foo, 1); // corregido: escribir de a 1 byte
      foo = foo + 1;
    }
  }

  return 0;
}

