#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/*
 * Write program usage
 */
void
usage(char *argv[])
{
  fprintf(stderr, " Usage: %s FNAME\n", argv[0]);
  return;
}

/*
 * Expects one command line argument, the file name for which we
 * require the Fletcher 32 checksum
 */
int
main(int argc, char *argv[])
{
  /* Check number of command line arguments */
  if(argc != 2) {
    usage(argv);
    exit(1);
  }

  /* Open file. Fail if it does not exist */
  char *fname = argv[1];
  FILE *fp = fopen(fname, "r");
  if(fp == NULL) {
    fprintf(stderr, " fopen() for %s returned NULL, quitting\n", fname);
    exit(2);
  }

  /* Fletcher 32 checksum */
  uint32_t sum1 = 0;
  uint32_t sum2 = 0;
  for(;;) {
    uint8_t elem;
    size_t n = fread(&elem, sizeof(elem), 1, fp);
    if (n == 0) {
      break;
    }
    sum1 = (sum1 + elem) % 65535;
    sum2 = (sum2 + sum1) % 65535;
  }
  uint32_t f32 = (sum2 << 16) | sum1;
  fclose(fp);

  /* Print file name and checksum as hexadecimal */
  printf(" %s: %08x\n", fname, f32);  
  return 0;
}
