#ifndef B_H_
#define B_H_

struct B {};
struct D : public B {};

void func(B *);
void func(void *);
void test(D *);

#endif
