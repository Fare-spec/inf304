#include "terrain.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int graceful_exit(int code) {
  printf("\n");
  return code;
}

int main(int argc, char **argv) {
  FILE *f;
  Terrain t;
  int x, y;
  erreur_terrain code = ERROR_OPENING;
  char buffer[PATH_MAX];

  if (argc < 2) {
    printf("Usage : %s <fichier>", argv[0]);
    return graceful_exit(1);
  }

  if (strlen(argv[1]) >= sizeof(buffer)) {
    fprintf(stderr, "Path is too big.");
    return graceful_exit(1);
  }

  strcpy(buffer, argv[1]);

  while (code == ERROR_OPENING) {

    f = fopen(buffer, "r");

    if (f == NULL) {
      code = ERROR_OPENING;
    } else {
      code = lire_terrain(f, &t, &x, &y);
      fclose(f);
    }

    switch (code) {

    case ERROR_OPENING:
      printf("Couldn't open the file %s\n", buffer);
      printf("Please input the name of a test file: ");

      if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return graceful_exit(1);
      }

      buffer[strcspn(buffer, "\n")] = '\0';
      break;
    case ERROR_CONTENT:
      printf("Some character doesn't match the vocabulary of this program");
      return graceful_exit(1);
    case ERROR_MISMATCH:
      printf("Dimensions are either too big or too small.");
      return graceful_exit(1);
    case ERROR_READING:
      printf("Error when reading the file.");
      return graceful_exit(1);
    case ERROR_READING_HEIGH:
      printf("The submitted heigh in the file is wrong. You may use digit for "
             "the first two lines of the files declaring the dimensions of the "
             "terrain.");
      return graceful_exit(1);

    case ERROR_READING_WIDTH:
      printf("The submitted width in the file is wrong. You may use digit for "
             "the first two lines of the files declaring the dimensions of the "
             "terrain.");
      return graceful_exit(1);

    case ERROR_DIMS:
      printf("The submitted width/heigh in the file doesn't match the real "
             "width/heigh of the terrain.");
      return graceful_exit(1);
    case ERROR_MISSING_RB:
      printf("You forgot to add that little cute robot D:");
      return graceful_exit(1);

    case ERROR_TOO_MANY_RB:
      printf("You put too many cute little robots :D, however you need to "
             "remove all of them except one ;( ");
      return graceful_exit(1);

    case OK:
      afficher_terrain(&t);
      printf("Position initiale du robot : (%d, %d)", x, y);
      return graceful_exit(0);

    default:
      printf("Error when executing the program, however this error hasn't been "
             "implemented... yet.");
      return graceful_exit(1);
    }
  }

  return graceful_exit(0);
}
