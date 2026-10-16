#include <stdio.h>
#include <time.h>

#define N 100000000

typedef enum { Nord, Est, Sud, Ouest } Orientation;

typedef struct {
  int x, y;
  Orientation o;
} Robot;

__attribute__((noinline)) void gauche1(Robot *r) {
  if (r->o == Nord)
    r->o = Ouest;
  else if (r->o == Ouest)
    r->o = Sud;
  else if (r->o == Sud)
    r->o = Est;
  else
    r->o = Nord;
}

__attribute__((noinline)) void gauche2(Robot *r) { r->o = (r->o + 3) & 3; }

int main(void) {
  Robot r = {0, 0, Nord};

  clock_t debut = clock();

  for (int i = 0; i < N; i++)
    gauche1(&r);

  double t1 = (double)(clock() - debut) / CLOCKS_PER_SEC;

  printf("Version 1 : %.6f s\n", t1);

  r.o = Nord;
  debut = clock();

  for (int i = 0; i < N; i++)
    gauche2(&r);

  double t2 = (double)(clock() - debut) / CLOCKS_PER_SEC;

  printf("Version 2 : %.6f s\n", t2);
  printf("Rapport : %.2fx\n", t1 / t2);
  printf("Resultat : %d\n", r.o);
}
