#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;
  struct matrix *test;
	test = new_matrix(4, 4);
	ident(test);
	scalar_mult(5,test);


	print_matrix(test);
}
