#include "robot.h"
void init_robot(Robot *r, int x, int y, Orientation o) {
  r->x = x, r->y = y, r->o = o;
}
void avancer(Robot *r) {
  r->x += ((r->o) & 1) *
          (-(r->o - 2)); // first part get 0 if north or south, second part
                         // becomes 1 if east, -1 if ouest... This took me a
                         // while to come up with.
  r->y -= ((r->o + 1) & 1) * (1 - r->o); // Same here but reversed.
}
void tourner_a_gauche(Robot *r) { r->o = (r->o + 3) & 3; }

void tourner_a_droite(Robot *r) { r->o = (r->o + 1) & 3; }
void position(Robot *r, int *x, int *y) { *x = r->x, *y = r->y; }
int abscisse(Robot *r) { return r->x; }

int ordonnee(Robot *r) { return r->y; }

Orientation orient(Robot *r) { return r->o; }

void position_devant(Robot *r, int *x, int *y) {
  *x = r->x + (r->o & 1) * (2 - r->o);
  *y = r->y - ((r->o + 1) & 1) * (1 - r->o);
}
