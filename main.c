#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;

  color c;
  c.red = 100;
  c.green = MAX_COLOR;
  c.blue = 0;

	clear_screen(s);

  struct matrix *edges;
  struct matrix *transform;

  edges = new_matrix(4, 1);
  
  add_edge(edges, 80, 80, 0, 80, 120, 0);
  add_edge(edges, 80, 120, 0, 120, 120, 0);
  add_edge(edges, 120, 120, 0, 120, 80, 0);
  add_edge(edges, 120, 80, 0, 80, 80, 0);
  
  draw_lines(edges, s, c);
  
  int i;

  for(i=0; i<50; i++){
    scalar_mult(0.75, edges);
    draw_lines(edges,s,c);
		scalar_mult(1.55,edges);
		draw_lines(edges,s,c);
	}

	display(s);
	save_extension(s, "matrix.png");

  
	free_matrix( transform );
	free_matrix( edges );
}  
