#pragma once

typedef struct {
	double** entries;
	int rows;
	int cols;
} Matrix;

Matrix* matrix_create(int row, int col);
void matrix_fill(Matrix *m, int n);
void matrix_free(Matrix *m);
void matrix_print(Matrix *m);
Matrix* matrix_copy(Matrix *m);
void matrix_save(Matrix* m, char* file_string);
Matrix* matrix_load(char* file_string);
void matrix_randomize(Matrix* m, int n);
int matrix_argmax(Matrix* m);
Matrix* matrix_flatten(Matrix* m, int axis);

//OPERATION

Matrix* multiply(Matrix* m1, Matrix* m2);
Matrix* add(Matrix* m1, Matrix* m2);
Matrix* subtract(Matrix* m1, Matrix* m2);
Matrix* dot(Matrix* m1, Matrix* m2);
Matrix* apply(double (*func)(double), Matrix* m);
Matrix* scale(double n, Matrix* m);
Matrix* addScalar(double n, Matrix* m);
Matrix* transpose(Matrix* m);
