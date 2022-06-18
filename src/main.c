#include <png.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * Add value to the specified pixel. Will not overflow an unsigned char.
 */
void addPixel(unsigned char *pixels, int x, int y, int value, int width) {
  int index = x + y * width;
  if (pixels[index * 3 + 2] + value < 255) {
    pixels[index * 3 + 2] += value;
    pixels[index * 3 + 1] += value;
    pixels[index * 3 + 0] += value;
  } else {
    pixels[index * 3 + 2] = 255;
    pixels[index * 3 + 1] = 255;
    pixels[index * 3 + 0] = 255;
  }
}

/*
 * Run the logistic function for "n" iterations using a random starting point
 * and report the result.
 */
double getEquilibrium(double r, int n) {
  double x = (double)random() / RAND_MAX;
  for (int i = 0; i < n; i++) {
    x = r * x * (1 - x);
  }
  if (x < 0) {
    x = 0;
  }
  if (x > 1) {
    x = 1;
  }
  return x;
}

void usage(char *argv[]) {
  fprintf(stderr,
          "Usage: %s [-n iterations] [-x width] [-y height] [-o outFile]\n"
          " -n\tNumber of iterations (Default 100).\n"
          " -x\tImage width (Default 1920).\n"
          " -y\tImage height (Default 1080).\n"
          " -o\tOutput file (Default standard output).\n"
          " -a\tThe r1 boundary (Default 3.5).\n"
          " -b\tThe r2 boundary (Default 4).\n"
          " -h\tPrint this usage message.\n"
          "",
          argv[0]);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {

  /*
   * Default values.
   */
  int iterations = 100;
  int width = 1920;
  int height = 1080;
  double r1 = 3.5;
  double r2 = 4;

  char *outFile = NULL;

  /*
   * Handle program arguments.
   */
  int opt;
  char *optstring = "n:x:y:o:ha:b:";
  while ((opt = getopt(argc, argv, optstring)) != -1) {
    if (opt == 'n') {
      iterations = atoi(optarg);
    }
    if (opt == 'x') {
      width = atoi(optarg);
    }
    if (opt == 'y') {
      height = atoi(optarg);
    }
    if (opt == 'a') {
      r1 = strtod(optarg, NULL);
    }
    if (opt == 'b') {
      r2 = strtod(optarg, NULL);
    }
    if (opt == 'h') {
      usage(argv);
    }
    if (opt == 'o') {
      outFile = malloc(strlen(optarg) + 1);
      strcpy(outFile, optarg);
    }
  }

  /*
   * Input validation.
   */
  if (optind != argc) {
    fprintf(stderr, "Wrong number of arguments.\n\n");
    usage(argv);
  }

  if (!outFile) {
    fprintf(stderr, "Please specify and output file with -o.\n\n");
    usage(argv);
  }

  if (r1 > r2) {
    fprintf(stderr, "r1 should be less than r2.\n\n");
    usage(argv);
  }

  unsigned char pixels[width * height * 3];
  bzero(pixels, width * height * 3);

  /*
   * Run calculations for every pixel.
   */
  static int percent = 0;
  for (double r = r1; r < r2; r += (r2 - r1) / (width * 10000)) {

    /*
     * Print out progress.
     */
    int p = 100. * (r - r1) / (r2 - r1);
    if (percent != p) {
      fprintf(stderr, "Progress: %d\r", p);
      percent = p;
    }
    double equilibrium = getEquilibrium(r, iterations);
    addPixel(pixels, (r - r1) * width / (r2 - r1), equilibrium * height, 1,
             width);
  }
  fprintf(stderr, "Progress: 100\n");

  /*
   * Use libpng to write the image to a file.
   */
  png_image image = {0};

  image.width = width;
  image.height = height;
  image.format = PNG_FORMAT_RGB;
  image.version = PNG_IMAGE_VERSION;

  if (!png_image_write_to_file(&image, outFile, 0, pixels, 0, NULL)) {
    fprintf(stderr, "libpng: Failed to write to file.\n");
    exit(EXIT_FAILURE);
  }
}
