#include <iostream>
#include <pthread.h>
using namespace std;

long cnt = 0;

void* add1 (void* threadId) {
  long Id = (long) threadId;

  for (int i = 0; i < 10000; i++){
    cnt = cnt + 1;
    cout << "Thread #" << Id << " finished No." << cnt << " job" << endl;
  }

  pthread_exit(NULL);
}

int main (int argc, char* argv[]) {
  pthread_t threads[2];
  int ret_val = 0;

  for (long i = 0; i < 2; i++) {
    ret_val = pthread_create(&threads[i], NULL, add1, (void*) i);
    if (ret_val) {
      cout << "ERROR!! return code of pthread_create(): " << ret_val << endl;
      exit(-1);
    }
  }

  void* status;
  pthread_join(threads[0], &status);
  pthread_join(threads[1], &status);
  cout << "The result value of cnt: " << cnt << endl;
  pthread_exit(NULL);
}
