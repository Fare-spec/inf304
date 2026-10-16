#include "robot.h"
void init_robot(Robot *r, int x, int y, Orientation o) {
  r->x = x, r->y = y, r->o = 0;
}
void avancer(Robot *r) {
  r->x += ((r->o) & 1) *
          (-(r->o - 2)); // first part get 0 if north or south, second part
                         // becomes 1 if east, -1 if ouest... This took me a
                         // while to come up with.
  r->y += ((r->o + 1) & 1) * (1 - r->o); // Same here but reversed.
}
void tourner_a_gauche(Robot *r) { r->o = r->o ^ 1; }
