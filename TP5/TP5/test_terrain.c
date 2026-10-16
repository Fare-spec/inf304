#include "terrain.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  FILE *f;
  Terrain t;
  int x, y;
  erreur_terrain code = ERREUR_OUVERTURE;
  char buffer[PATH_MAX];

  if (argc < 2) {
    printf("Usage : %s <fichier>\n", argv[0]);
    return 1;
  }

  if (strlen(argv[1]) >= sizeof(buffer)) {
    fprintf(stderr, "Path is too big.\n");
    return 1;
  }

  strcpy(buffer, argv[1]);

  while (code == ERREUR_OUVERTURE) {

    f = fopen(buffer, "r");

    if (f == NULL) {
      code = ERREUR_OUVERTURE;
    } else {
      code = lire_terrain(f, &t, &x, &y);
      fclose(f);
    }

    switch (code) {

    case ERREUR_OUVERTURE:
      printf("Couldn't open the file %s\n", buffer);
      printf("Please input the name of a test file: ");

      if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
      }

      buffer[strcspn(buffer, "\n")] = '\0';
      break;

    case OK:
      afficher_terrain(&t);
      printf("Position initiale du robot : (%d, %d)\n", x, y);
      return 0;

    default:
      printf("Generic error: couldn't read or parse the file.\n");
      return 1;
    }
  }

  return 0;
}
