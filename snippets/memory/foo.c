int A, B;

// very interesting, compiler barrier
// often, for x86/64, a compiler barrier is enough
void foo() {
  A = B + 1;
  asm volatile("" ::: "memory");
  B = 0;
}
