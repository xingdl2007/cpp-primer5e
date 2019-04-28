#include <iostream>
#include <semaphore.h>
#include <thread>

int r1, r2;
int x = 0, y = 0;
sem_t begin_sem1, begin_sem2, end_sem;

uint64_t cnt = 1000000;

void func1() {
  uint32_t loop = 0;
  while (true) {
    sem_wait(&begin_sem1);
    y = 1;
    asm volatile("mfence" : : : "memory");
    r1 = x;
    sem_post(&end_sem);

    if (++loop == cnt)
      break;
  }
};

void func2() {
  uint32_t loop = 0;
  while (true) {
    sem_wait(&begin_sem2);
    x = 1;
    asm volatile("mfence" : : : "memory");
    r2 = y;
    sem_post(&end_sem);

    if (++loop == cnt)
      break;
  }
};

int main(int argc, char *argv[]) {
  uint64_t loop = 0, counter = 0;
  sem_init(&begin_sem1, 0, 0);
  sem_init(&begin_sem2, 0, 0);
  sem_init(&end_sem, 0, 0);

  std::thread t1(func1);
  std::thread t2(func2);

  while (true) {
    x = 0;
    y = 0;
    ++loop;
    sem_post(&begin_sem1);
    sem_post(&begin_sem2);

    sem_wait(&end_sem);
    sem_wait(&end_sem);

    if (r1 == 0 && r2 == 0) {
      ++counter;
      std::cout << "caught " << counter << " after " << loop << " time"
                << std::endl;
    }

    if (loop == cnt) {
      break;
    }
  }
  t1.join();
  t2.join();
}