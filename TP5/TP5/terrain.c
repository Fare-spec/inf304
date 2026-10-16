
#include "terrain.h"
#include "robot.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

erreur_terrain gracefully_exit(erreur_terrain code, FILE *f) { return code; }

erreur_terrain lire_terrain(FILE *f, Terrain *t, int *dx, int *dy) {
  int l = 0, h = 0; // Dimensions du terrain
  int rx, ry;       // Coordonnées initiales du robot
  char buffer[DIM_MAX + 4], extra;

  if (f == NULL) {
    return gracefully_exit(ERREUR_OUVERTURE, f);
  }

  // Lecture de la largeur
  if (!fgets(buffer, sizeof(buffer), f) ||
      sscanf(buffer, "%d %c", &l, &extra) != 1)
    return gracefully_exit(ERREUR_LECTURE_LARGEUR, f);

  // Lecture de la hauteur

  if (!fgets(buffer, sizeof(buffer), f) ||
      sscanf(buffer, "%d %c", &h, &extra) != 1)
    return gracefully_exit(ERREUR_LECTURE_HAUTEUR, f);

  t->largeur = l;
  t->hauteur = h;

  // Lecture du terrain
  if (l <= 0 || h <= 0 || l >= DIM_MAX || h >= DIM_MAX)
    return gracefully_exit(ERREUR_MISMATCH,
                           f); // On vérifie que les dimensions respectent les
                               // contraintes de > 0 et < DIM_MAX
  for (int y = 0; y < h; y++) {
    if (!fgets(buffer, sizeof(buffer), f))
      return gracefully_exit(ERREUR_LECTURE, f);

    for (int x = 0; x < l; x++) {
      char c = buffer[x];

      switch (c) {
      case '.':
        t->tab[x][y] = LIBRE;
        break;

      case '~':
        t->tab[x][y] = EAU;
        break;

      case '#':
        t->tab[x][y] = ROCHER;
        break;
      case 'C':
        t->tab[x][y] = LIBRE;
        rx = x, ry = y;
        break;

      default:
        return gracefully_exit(ERREUR_CONTENT, f);
        break;
      }
    }
  }

  *dy = ry;

  *dx = rx;

  return gracefully_exit(OK, f);
}

void afficher_terrain(Terrain *t) {
  int width = t->largeur;
  int height = t->hauteur;

  for (int y = 0; y < height; y++) {

    for (int x = 0; x < width; x++) {

      char c;

      switch (t->tab[x][y]) {
      case LIBRE:
        c = '.';
        break;
      case ROCHER:
        c = '#';
        break;
      case EAU:
        c = '~';
        break;
      default:
        return;
      }

      printf("%c ", c);
    }
    printf("\n");
  }
}
