#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define DIM_MAX 256

typedef enum { LIBRE, EAU, ROCHER } Case;

typedef struct {
  int largeur, hauteur;
  Case tab[DIM_MAX][DIM_MAX];
} Terrain;

int graceful_exit(int code, FILE *f) {
  if (fclose(f) == EOF)
    return -1;
  return code;
}

int lire_terrain(const char *nom, Terrain *t) {
  if (nom == NULL || t == NULL)
    return -1;

  FILE *f = fopen(nom, "r");
  if (f == NULL)
    return -1;

  char ligne[DIM_MAX + 4], extra;
  int L, H, nbC = 0;
  int valide = 1; // On utilise cet int afin d'éviter l'utilisation de goto qui
                  // est interdite.

  if (!fgets(ligne, sizeof(ligne), f) ||
      sscanf(ligne, "%d %c", &L, &extra) != 1)
    valide = 0;

  if (valide) {
    if (!fgets(ligne, sizeof(ligne), f) ||
        sscanf(ligne, "%d %c", &H, &extra) != 1)
      valide = 0;
  }

  if (valide && (L <= 0 || H <= 0 || L >= DIM_MAX || H >= DIM_MAX))
    valide = 0;

  if (valide) {
    for (int y = 0; y < H && valide; y++) {
      if (!fgets(ligne, sizeof(ligne), f)) {
        valide = 0;
      } else {
        size_t n = strlen(ligne);

        while (n > 0 && (ligne[n - 1] == '\n' || ligne[n - 1] == '\r'))
          n--;

        if (n != (size_t)L) {
          valide = 0;
        } else {
          for (int x = 0; x < L && valide; x++) {
            char c = ligne[x];

            if (c == '.' || c == 'C') {
              t->tab[x][y] = LIBRE;
              nbC += (c == 'C');
            } else if (c == '~') {
              t->tab[x][y] = EAU;
            } else if (c == '#') {
              t->tab[x][y] = ROCHER;
            } else {
              valide = 0;
            }
          }
        }
      }
    }
  }

  if (valide && nbC != 1)
    valide = 0;

  if (valide) {
    int c;

    while (valide && (c = fgetc(f)) != EOF) {
      if (!isspace((unsigned char)c))
        valide = 0;
    }

    if (ferror(f))
      valide = 0;
  }

  if (valide) {
    t->largeur = L;
    t->hauteur = H;
  }

  return graceful_exit(valide ? 0 : -1, f);
}
