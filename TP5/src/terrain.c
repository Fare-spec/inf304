
#include "terrain.h"
#include "robot.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

erreur_terrain gracefully_exit(erreur_terrain code) { return code; }

erreur_terrain lire_terrain(FILE *f, Terrain *t, int *dx, int *dy) {
  int l = 0, h = 0;     // Dimensions du terrain
  int rx = -1, ry = -1; // Coordonnées initiales du robot
  char buffer[DIM_MAX + 4], extra;
  int bc = 0; // to check if there is only one bot.

  if (f == NULL) {
    return gracefully_exit(ERROR_OPENING);
  }

  // Lecture de la largeur
  if (!fgets(buffer, sizeof(buffer), f) ||
      sscanf(buffer, "%d %c", &l, &extra) != 1)
    return gracefully_exit(ERROR_READING_WIDTH);

  // Lecture de la hauteur

  if (!fgets(buffer, sizeof(buffer), f) ||
      sscanf(buffer, "%d %c", &h, &extra) != 1)
    return gracefully_exit(ERROR_READING_HEIGH);

  t->largeur = l;
  t->hauteur = h;

  // Lecture du terrain
  if (l <= 0 || h <= 0 || l >= DIM_MAX || h >= DIM_MAX)
    return gracefully_exit(
        ERROR_MISMATCH); // On vérifie que les dimensions respectent les
                         // contraintes de > 0 et < DIM_MAX
  for (int y = 0; y < h; y++) {
    if (!fgets(buffer, sizeof(buffer), f)) {
      return gracefully_exit(ERROR_DIMS);
    }

    size_t longueur = strcspn(buffer, "\r\n");

    if (longueur != (size_t)l ||
        (buffer[longueur] != '\0' && buffer[longueur] != '\n' &&
         !(buffer[longueur] == '\r' && buffer[longueur + 1] == '\n'))) {
      return gracefully_exit(ERROR_DIMS);
    }

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
        bc++;
        if (bc > 1) {
          return gracefully_exit(ERROR_TOO_MANY_RB);
        }
        t->tab[x][y] = LIBRE;
        rx = x, ry = y;
        break;

      default:
        return gracefully_exit(ERROR_CONTENT);
        break;
      }
    }
  }
  if (fgets(buffer, sizeof(buffer), f)) {
    return gracefully_exit(ERROR_DIMS);
  }
  if (bc < 1) {
    return gracefully_exit(ERROR_MISSING_RB);
  }

  *dy = ry;

  *dx = rx;

  return gracefully_exit(OK);
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
