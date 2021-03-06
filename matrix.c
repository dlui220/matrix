#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"

/*-------------- struct matrix *new_matrix() --------------
Inputs:  int rows
         int cols 
Returns: 

Once allocated, access the matrix as follows:
m->m[r][c]=something;
if (m->lastcol)... 
*/
struct matrix *new_matrix(int rows, int cols) {
  double **tmp;
  int i;
  struct matrix *m;

  tmp = (double **)malloc(rows * sizeof(double *));
  for (i=0;i<rows;i++) {
      tmp[i]=(double *)malloc(cols * sizeof(double));
    }

  m=(struct matrix *)malloc(sizeof(struct matrix));
  m->m=tmp;
  m->rows = rows;
  m->cols = cols;
  m->lastcol = 0;

  return m;
}


/*-------------- void free_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

1. free individual rows
2. free array holding row pointers
3. free actual matrix
*/
void free_matrix(struct matrix *m) {

  int i;
  for (i=0;i<m->rows;i++) {
      free(m->m[i]);
    }
  free(m->m);
  free(m);
}


/*======== void grow_matrix() ==========
Inputs:  struct matrix *m
         int newcols 
Returns: 

Reallocates the memory for m->m such that it now has
newcols number of collumns
====================*/
void grow_matrix(struct matrix *m, int newcols) {
  
  int i;
  for (i=0;i<m->rows;i++) {
      m->m[i] = realloc(m->m[i],newcols*sizeof(double));
  }
  m->cols = newcols;
}


/*-------------- void print_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

print the matrix
*/
void print_matrix(struct matrix *m) {
	int rows;
	int cols;
	for ( rows = 0; rows < m->rows; rows++ ){
		for ( cols = 0; cols < m->cols; cols++ ){
			printf("%f ", m->m[rows][cols]);
		}
		printf("\n");
	}
}

/*-------------- void ident() --------------
	Inputs:  struct matrix *m <-- assumes m is a square matrix
	Returns:

	turns m in to an identity matrix
*/
void ident(struct matrix *m) {
	int msize = m->cols;

	int rows;
	int cols;

	for (rows = 0; rows < msize; rows++) {
		for (cols = 0; cols < msize; cols++) {
			if (rows == cols) {
				m -> m[rows][cols] = 1;
			} else {
				m -> m[rows][cols] = 0;
			}
		}
	}
}
/*-------------- void scalar_mult() --------------
	Inputs:  double x
	struct matrix *m
	Returns:

	multiply each element of m by x
*/
void scalar_mult(double x, struct matrix *m) {
	int rows;
	int cols;
	for ( rows = 0; rows < m ->rows; rows++ ){
		for ( cols = 0; cols < m->cols; cols++ ){
			m -> m[rows][cols] = m->m [rows][cols] * x ;
		}
	}
}


/* /\*-------------- void matrix_mult() -------------- */
/* 	Inputs:  struct matrix *a */
/* 	struct matrix *b  */
/* 	Returns:  */

/* 	a*b -> b */
/* *\/ */
void matrix_mult(struct matrix *a, struct matrix *b) {
	int arows;
	int acols;

	int brows;
	int bcols;

	// example
	// 1 2    3 3 3   3+12+21 6+15+24   36 45  
	// 4 5  * 3 3 3 = 3+12+21 6+15+24 = 36 45
	// 7 8    

	struct matrix *result = new_matrix(a->rows,b->cols);

	for (arows = 0; arows < a->rows; arows++){
		double * row = a->m[arows];
		for (brows = 0; brows < b->rows; brows++){
			double temp = 0;
			for (bcols = 0; bcols < b->cols; bcols++){
				temp += row[bcols] * b->m[brows][bcols];
			}
			result->m[arows][brows] = temp;
		}
	}
	copy_matrix(result,b);
}



/*-------------- void copy_matrix() --------------
	Inputs:  struct matrix *a
	struct matrix *b
	Returns:

	copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {

	int r, c;

	for (r=0; r < a->rows; r++)
		for (c=0; c < a->cols; c++)
			b->m[r][c] = a->m[r][c];
}

/*======== struct matrix * make_translate() ==========
	Inputs:  int x
	int y
	int z
	Returns: The translation matrix created using x, y and z
	as the translation offsets.
	====================*/
struct matrix * make_translate(double x, double y, double z) {
	struct matrix * temp;
  temp = new_matrix(4,4);
	ident(temp);

	// from notes
	/*  1 0 0 a     x     a+x */
	/* 	0 1 0 b     y     b+y */
	/* 	0 0 1 c  *  z  =  c+z */
	/* 	0 0 0 1     1     1 */

	temp->m[0][3] = x;
	temp->m[1][3] = y;
	temp->m[2][3] = z;
	return temp;
}

/*======== struct matrix * make_scale() ==========
	Inputs:  int x
	int y
	int z
	Returns: The translation matrix creates using x, y and z
	as the scale factors
	====================*/
struct matrix * make_scale(double x, double y, double z) {
	struct matrix *temp;
	temp = new_matrix(4,4);

	// From notes
	/*  a 0 0 0     x     ax */
	/* 	0 b 0 0     y     by */
	/* 	0 0 c 0  *  z  =  cz */
	/* 	0 0 0 1     1     1 */

	temp->m[0][0] = x;
	temp->m[1][1] = y;
	temp->m[2][2] = z;
	temp->m[3][3] = 1;
	return temp;
}


/*======== struct matrix * make_rotX() ==========
	Inputs:  double theta

	Returns: The rotation matrix created using theta as the
	angle of rotation and X as the axis of rotation.
	====================*/
struct matrix * make_rotX(double theta) {
	struct matrix * temp;
	temp = new_matrix(4, 4);
  theta *= M_PI/180;

	// From notes
	/*  x     y             z       1 */
	/* 	1     0             0       0 */
	/* 	0  cos(theta)  -sin(theta)  0 */
	/* 	0  sin(theta)   cos(theta)  0 */
	/* 	0     0             0       1 */

  temp->m[0][0] = 1;
  temp->m[1][1] = cos(theta);
  temp->m[2][1] = sin(theta);
  temp->m[1][2] = -sin(theta);
  temp->m[2][2] = cos(theta);
  temp->m[3][3] = 1;
  return temp;
}

/*======== struct matrix * make_rotY() ==========
	Inputs:  double theta

	Returns: The rotation matrix created using theta as the
	angle of rotation and Y as the axis of rotation.
	====================*/
struct matrix * make_rotY(double theta) {
	struct matrix * temp;
	temp = new_matrix(4, 4);
  theta *= M_PI/180;
	
	// From notes
	/*  cos(theta)  0  -sin(theta)  0  */
	/* 	0           1       0       0  */
	/* 	sin(theta)  0   cos(theta)  0  */
	/* 	0           0       0       1  */

  temp->m[0][0] = cos(theta);
	temp->m[0][2] = -sin(theta);
	temp->m[1][1] = 1;
	temp->m[2][0] = sin(theta);
	temp->m[2][2] = cos(theta);
	temp->m[3][3] = 1;
	return temp;

}

/*======== struct matrix * make_rotZ() ==========
	Inputs:  double theta

	Returns: The rotation matrix created using theta as the
	angle of rotation and Z as the axis of rotation.
	====================*/
struct matrix * make_rotZ(double theta) {
	struct matrix * temp; 
	temp = new_matrix(4, 4);
  theta *= M_PI/180;

	// From notes
	/*  cos(theta)  -sin(theta)  0  0     x     xcos(theta) - ysin(theta) */
	/* 	sin(theta)   cos(theta)  0  0  *  y  =  ycos(theta) + xsin(theta) */
	/* 	0            0           1  0     z                 z             */
	/* 	0            0           0  1     1                 1             */


  temp->m[0][0] = cos(theta);
  temp->m[0][1] = -sin(theta);
  temp->m[1][0] = sin(theta);
  temp->m[1][1] = cos(theta);
  temp->m[2][2] = 1;
  temp->m[3][3] = 1;
  return temp;
}
