#include "matrix.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXCHAR 100

Matrix* matrix_create(int row, int col) {
	Matrix *matrix = malloc(sizeof(Matrix));
	matrix->rows = row;
	matrix->cols = col;
	matrix->entries = malloc(row * sizeof(double*));
	for (int i = 0; i < row; i++) {
		matrix->entries[i] = malloc(col * sizeof(double));
	}
	return matrix;
}

void matrix_fill(Matrix *m, int n) {
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			m->entries[i][j] = n;
		}
	}
}

void matrix_free(Matrix *m) {
	for (int i = 0; i < m->rows; i++) {
		free(m->entries[i]);
	}
	free(m);
	m = NULL;
}

void matrix_print(Matrix* m) {
	printf("Rows: %d Columns: %d\n", m->rows, m->cols);
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			if (m->entries[i][j] == 0)
			{
				printf(" ");
			}
			else
			{
				printf("%1.3f ", m->entries[i][j]);
			}
		}
		printf("\n");
	}
}

Matrix* matrix_copy(Matrix* m) {
	Matrix* mat = matrix_create(m->rows, m->cols);
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			mat->entries[i][j] = m->entries[i][j];
		}
	}
	return mat;
}

void matrix_save(Matrix* m, char* file_string) {
	FILE* file = fopen(file_string, "w");
	fprintf(file, "%d\n", m->rows);
	fprintf(file, "%d\n", m->cols);
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			fprintf(file, "%.6f\n", m->entries[i][j]);
		}
	}
	printf("Successfully saved matrix to %s\n", file_string);
	fclose(file);
}

Matrix* matrix_load(char* file_string) {
	FILE* file = fopen(file_string, "r");
	char entry[MAXCHAR]; 
	fgets(entry, MAXCHAR, file);
	int rows = atoi(entry);
	fgets(entry, MAXCHAR, file);
	int cols = atoi(entry);
	Matrix* m = matrix_create(rows, cols);
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			fgets(entry, MAXCHAR, file);
			m->entries[i][j] = strtod(entry, NULL);
		}
	}
	printf("Sucessfully loaded matrix from %s\n", file_string);
	fclose(file);
	return m;
}

double uniform_distribution(double low, double high) {
	double difference = high - low; // The difference between the two
	int scale = 10000;
	int scaled_difference = (int)(difference * scale);
	return low + (1.0 * (rand() % scaled_difference) / scale);
}

void matrix_randomize(Matrix* m, int n) {
	// Pulling from a random distribution of 
	// Min: -1 / sqrt(n)
	// Max: 1 / sqrt(n)
	double min = -1.0 / sqrt(n);
	double max = 1.0 / sqrt(n);
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			m->entries[i][j] = uniform_distribution(min, max);
		}
	}
}

int matrix_argmax(Matrix* m) {
	// Expects a Mx1 matrix
	double max_score = 0;
	int max_idx = 0;
	for (int i = 0; i < m->rows; i++) {
		if (m->entries[i][0] > max_score) {
			max_score = m->entries[i][0];
			max_idx = i;
		}
	}
	return max_idx;
}

Matrix* matrix_flatten(Matrix* m, int axis) {
	// Axis = 0 -> Column Vector, Axis = 1 -> Row Vector
	Matrix* mat;
	if (axis == 0) {
		mat = matrix_create(m->rows * m->cols, 1);
	} else if (axis == 1) {
		mat = matrix_create(1, m->rows * m->cols);
	} else {
		printf("Argument to matrix_flatten must be 0 or 1");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			if (axis == 0) mat->entries[i * m->cols + j][0] = m->entries[i][j];
			else if (axis == 1) mat->entries[0][i * m->cols + j] = m->entries[i][j];
		}
	}
	return mat;
}

//OPERATION


int check_dimensions(Matrix *m1, Matrix *m2) {
	if (m1->rows == m2->rows && m1->cols == m2->cols) return 1;
	return 0;
}

Matrix* multiply(Matrix *m1, Matrix *m2) {
	if (check_dimensions(m1, m2)) {
		Matrix *m = matrix_create(m1->rows, m1->cols);
		for (int i = 0; i < m1->rows; i++) {
			for (int j = 0; j < m2->cols; j++) {
				m->entries[i][j] = m1->entries[i][j] * m2->entries[i][j];
			}
		}
		return m;
	} else {
		printf("Dimension mistmatch multiply: %dx%d %dx%d\n", m1->rows, m1->cols, m2->rows, m2->cols);
		exit(1);
	}
}

Matrix* add(Matrix *m1, Matrix *m2) {
	if (check_dimensions(m1, m2)) {
		Matrix *m = matrix_create(m1->rows, m1->cols);
		for (int i = 0; i < m1->rows; i++) {
			for (int j = 0; j < m2->cols; j++) {
				m->entries[i][j] = m1->entries[i][j] + m2->entries[i][j];
			}
		}
		return m;
	} else {
		printf("Dimension mistmatch add: %dx%d %dx%d\n", m1->rows, m1->cols, m2->rows, m2->cols);
		exit(1);
	}
}

Matrix* subtract(Matrix *m1, Matrix *m2) {
	if (check_dimensions(m1, m2)) {
		Matrix *m = matrix_create(m1->rows, m1->cols);
		for (int i = 0; i < m1->rows; i++) {
			for (int j = 0; j < m2->cols; j++) {
				m->entries[i][j] = m1->entries[i][j] - m2->entries[i][j];
			}
		}
		return m;
	} else {
		printf("Dimension mistmatch subtract: %dx%d %dx%d\n", m1->rows, m1->cols, m2->rows, m2->cols);
		exit(1);
	}
}

Matrix* apply(double (*func)(double), Matrix* m) {
	Matrix *mat = matrix_copy(m);
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			mat->entries[i][j] = (*func)(m->entries[i][j]);
		}
	}
	return mat;
}

Matrix* dot(Matrix *m1, Matrix *m2) {
	if (m1->cols == m2->rows) {
		Matrix *m = matrix_create(m1->rows, m2->cols);
		for (int i = 0; i < m1->rows; i++) {
			for (int j = 0; j < m2->cols; j++) {
				double sum = 0;
				for (int k = 0; k < m2->rows; k++) {
					sum += m1->entries[i][k] * m2->entries[k][j];
				}
				m->entries[i][j] = sum;
			}
		}
		return m;
	} else {
		printf("Dimension mistmatch dot: %dx%d %dx%d\n", m1->rows, m1->cols, m2->rows, m2->cols);
		exit(1);
	}
}

Matrix* scale(double n, Matrix* m) {
	Matrix* mat = matrix_copy(m);
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			mat->entries[i][j] *= n;
		}
	}
	return mat;
}

Matrix* addScalar(double n, Matrix* m) {
	Matrix* mat = matrix_copy(m);
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			mat->entries[i][j] += n;
		}
	}
	return mat;
}

Matrix* transpose(Matrix* m) {
	Matrix* mat = matrix_create(m->cols, m->rows);
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			mat->entries[j][i] = m->entries[i][j];
		}
	}
	return mat;
}

int main()
{
	Matrix* matrice= matrix_create(5,5);
	matrix_fill(matrice,1);
	matrice->entries[0][0]=544;
	matrix_print(matrice);
}
