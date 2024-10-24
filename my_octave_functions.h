//Copyright Giurgiu Andrei-Stefan 315CA 2023-2024
#include <stdio.h>
#include <stdlib.h>
#ifndef MY_OCTAVE_FUNCTIONS_H_
#define MY_OCTAVE_FUNCTIONS_H_
#define modulo 10007
typedef struct{
	int linii, coloane, suma;
	int **matrix;
} matrice;

void array_memory_alloc(matrice **v, int idx, int *idx_maxim)
{
	int max = *idx_maxim;
	if (idx == max) {
		max *= 2;
	} else {
		if (idx < max / 2)
			max /= 2;
	}
	if (max != *idx_maxim) {
		*v = (matrice *)realloc(*v, max * sizeof(matrice));
		if (!*v) {
			fprintf(stderr, "Skill issue 1\n");
			return;
		}
	}
	*idx_maxim = max;
}

void element_memory_alloc(matrice *v, int idx, int lin, int col)
{
	v[idx].linii = lin;
	v[idx].coloane = col;
	v[idx].matrix = (int **)malloc(v[idx].linii * sizeof(int *));
	if (!v[idx].matrix) {
		fprintf(stderr, "Skill issue 2\n");
		free(v[idx].matrix);
		return;
	}
	for (int i = 0 ; i < v[idx].linii ; i++) {
		v[idx].matrix[i] = (int *)malloc(v[idx].coloane * sizeof(int));
		if (!v[idx].matrix[i]) {
			fprintf(stderr, "Skill issue 3\n");
			for (int j = 0 ; j < i ; j++)
				free(v[idx].matrix[j]);
			free(v[idx].matrix);
			return;
		}
	}
}

void input_matrix(matrice *v, int idx, int *c_sz)
{
	int i, j;
	for (i = 0; i < v[idx].linii; i++)
		for (j = 0; j < v[idx].coloane; j++)
			scanf("%d", &v[idx].matrix[i][j]);
	*c_sz += 1;
}

void output_matrix(matrice *v, int idx, int c_sz)
{
	if (idx >= c_sz || idx < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	int i, j;
	for (i = 0; i < v[idx].linii; i++) {
		for (j = 0; j < v[idx].coloane; j++)
			printf("%d ", v[idx].matrix[i][j]);
		printf("\n");
	}
}

void matrix_param(matrice *v, int idx, int c_sz)
{
	if (idx >= c_sz || idx < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	printf("%d %d\n", v[idx].linii, v[idx].coloane);
}

void change_element(matrice *v, int idx, int **mat, int n_lines, int n_columns)
{
	v[idx].linii = n_lines;
	v[idx].coloane = n_columns;
	v[idx].matrix = mat;
}

void clean_matrix(int **mat, int n)
{
	for (int i = 0 ; i < n ; i++)
		free(mat[i]);
	free(mat);
}

int suma_elementelor(matrice *v, int idx)
{
	int s = 0;
	for (int i = 0 ; i < v[idx].linii; i++)
		for (int j = 0; j < v[idx].coloane; j++) {
			int tmp = (s + v[idx].matrix[i][j]) % modulo;
			if (tmp < 0)
				tmp += modulo;
			s = tmp;
		}
	return s;
}

void assign_sum(matrice *v, int current_size)
{
	for (int i = 0 ; i < current_size; i++)
		v[i].suma = suma_elementelor(v, i);
}

void matrix_redimension(matrice *v, int idx, int c_sz)
{
	if (idx >= c_sz || idx < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	int new_lines;
	scanf("%d", &new_lines);
	int *tablou_linii = (int *)malloc(new_lines * sizeof(int));
	if (!tablou_linii) {
		fprintf(stderr, "Skill issue 4\n");
		return;
	}
	for (int i = 0 ; i < new_lines ; i++) {
		scanf("%d", &tablou_linii[i]);
		if (tablou_linii[i] > v[idx].linii) {
			printf("No matrix with the given index");
			return;
		}
	}
	int new_columns;
	scanf("%d", &new_columns);
	int *tablou_coloane = (int *)malloc(new_columns * sizeof(int));
	if (!tablou_coloane) {
		fprintf(stderr, "Skill issue 5\n");
		return;
	}
	for (int i = 0 ; i < new_columns; i++) {
		scanf("%d", &tablou_coloane[i]);
		if (tablou_coloane[i] > v[idx].coloane) {
			printf("No matrix with the given index");
			return;
		}
	}
	int **mat = (int **)malloc(new_lines * sizeof(int *));
	if (!mat) {
		fprintf(stderr, "Skill issue 6\n");
		return;
	}
	for (int i = 0 ; i < new_lines; i++) {
		mat[i] = (int *)malloc(new_columns * sizeof(int));
		if (!mat[i]) {
			fprintf(stderr, "Skill issue 7\n");
			return;
		}
	}
	for (int i = 0; i < new_lines; i++)
		for (int j = 0 ; j < new_columns; j++)
			mat[i][j] = v[idx].matrix[tablou_linii[i]][tablou_coloane[j]];
	clean_matrix(v[idx].matrix, v[idx].linii);
	change_element(v, idx, mat, new_lines, new_columns);
	v[idx].suma = suma_elementelor(v, idx);
	free(tablou_coloane);
	free(tablou_linii);
}

int check(matrice *v, int i1, int i2, int c_sz)
{
	if (i1 >= c_sz || i2 >= c_sz || i1 < 0 || i2 < 0) {
		printf("No matrix with the given index\n");
		return -1;
	}
	if (v[i1].coloane != v[i2].linii) {
		printf("Cannot perform matrix multiplication\n");
		return -1;
	}
	return 1;
}

void multiplication(matrice *v, int idx, int idx1, int idx2)
{
	v[idx].linii = v[idx1].linii;
	v[idx].coloane = v[idx2].coloane;
	element_memory_alloc(v, idx, v[idx].linii, v[idx].coloane);
	for (int i = 0 ; i < v[idx].linii; i++)
		for (int j = 0 ; j < v[idx].coloane; j++) {
			v[idx].matrix[i][j] = 0;
			for (int k = 0 ; k < v[idx1].coloane ; k++) {
				int tmp = (v[idx].matrix[i][j] + v[idx1].matrix[i][k] *
				v[idx2].matrix[k][j]) % modulo;
				if (tmp < 0)
					tmp += modulo;
				v[idx].matrix[i][j] = tmp;
			}
		}
	v[idx].suma = suma_elementelor(v, idx);
}

void sorting_array(matrice *v, int current_size)
{
	assign_sum(v, current_size);
	for (int i = 0 ; i < current_size - 1; i++)
		for (int j = i + 1 ; j < current_size; j++)
			if (v[i].suma > v[j].suma) {
				matrice tmp = v[i];
				v[i] = v[j];
				v[j] = tmp;
			}
}

void transpunere(matrice *v, int idx, int c_sz)
{
	if (idx >= c_sz || idx < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	int nr_linii = v[idx].coloane;
	int nr_coloane = v[idx].linii;
	int **mat = (int **)malloc(nr_linii * sizeof(int *));
	if (!mat) {
		fprintf(stderr, "Skill issue 8\n");
		return;
	}
	for (int i = 0 ; i < nr_linii; i++) {
		mat[i] = (int *)malloc(nr_coloane * sizeof(int));
		if (!mat[i]) {
			fprintf(stderr, "Skill issue 9\n");
			return;
		}
	}
	for (int i = 0; i < v[idx].linii; i++)
		for (int j = 0; j < v[idx].coloane; j++)
			mat[j][i] = v[idx].matrix[i][j];
	for (int i = 0 ; i < v[idx].linii; i++)
		free(v[idx].matrix[i]);
	free(v[idx].matrix);
	change_element(v, idx, mat, nr_linii, nr_coloane);
}

void multiplication_out_of_array(int **a, int **b, int n)
{
	int **c;
	c = (int **)calloc(n, sizeof(int *));
	for (int i = 0 ; i < n; i++)
		c[i] = (int *)calloc(n, sizeof(int));
	for (int i = 0 ; i < n; i++)
		for (int j = 0 ; j < n; j++)
			for (int k = 0 ; k < n ; k++) {
				int tmp = (c[i][j] + a[i][k] * b[k][j]) % modulo;
				if (tmp < 0)
					tmp += modulo;
				c[i][j] = tmp;
			}
	for (int i = 0 ; i < n ; i++)
		for (int j = 0; j < n; j++)
			a[i][j] = c[i][j];
	for (int i = 0 ; i < n; i++)
		free(c[i]);
	free(c);
}

int **expo(int **mat, int n, int power)
{
	int **identity;
	identity = (int **)malloc(n * sizeof(int *));
	for (int i = 0 ; i < n ; i++)
		identity[i] = (int *)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			if (i == j)
				identity[i][j] = 1;
			else
				identity[i][j] = 0;
	}
	while (power > 0) {
		if (power % 2 == 1)
			multiplication_out_of_array(identity, mat, n);
		multiplication_out_of_array(mat, mat, n);
		power /= 2;
	}
	for (int i = 0; i < n; i++)
		for (int j = 0 ; j < n; j++)
			mat[i][j] = identity[i][j];
	for (int i = 0 ; i < n; i++)
		free(identity[i]);
	free(identity);
	return mat;
}

void expo_task(matrice *v, int id, int c_sz, int putere)
{
	if (id >= c_sz || id < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	if (putere < 0) {
		printf("Power should be positive\n");
		return;
	}
	if (v[id].linii != v[id].coloane) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}
	v[id].matrix = expo(v[id].matrix, v[id].linii, putere);
	v[id].suma = suma_elementelor(v, id);
}

void kill_matrix(matrice *v, int idx, int *c_sz)
{
	if (idx >= *c_sz || idx < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	for (int i = idx; i < *c_sz - 1; i++) {
		matrice tmp = v[i];
		v[i] = v[i + 1];
		v[i + 1] = tmp;
	}
	clean_matrix(v[*c_sz - 1].matrix, v[*c_sz - 1].linii);
	*c_sz = *c_sz - 1;
}

int **allocate_matrix(int n)
{
	int **grid = (int **)calloc(n, sizeof(int *));
	if (!grid) {
		fprintf(stderr, "Strassen e dezamagit\n");
		return NULL;
	}
	for (int i = 0 ; i < n; i++) {
		grid[i] = (int *)calloc(n, sizeof(int));
		if (!grid[i]) {
			fprintf(stderr, "Strassen e pe jumatate dezamagit\n");
			return NULL;
		}
	}
	return grid;
}

int **adunare(int **m1, int **m2, int n)
{
	int **result;
	result = allocate_matrix(n);
	for (int i = 0 ; i < n; i++)
		for (int j = 0 ; j < n; j++) {
			int tmp = m1[i][j] + m2[i][j];
			if (tmp < 0)
				tmp += modulo;
			result[i][j] = tmp % modulo;
		}
	return result;
}

int **scadere(int **m1, int **m2, int n)
{
	int **result;
	result = allocate_matrix(n);
	for (int i = 0 ; i < n; i++)
		for (int j = 0 ; j < n; j++) {
			int tmp = m1[i][j] - m2[i][j];
			if (tmp < 0)
				tmp += modulo;
			result[i][j] = tmp % modulo;
		}
	return result;
}

void print_block(int **a, int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			printf("%d ", a[i][j]);
		printf("\n");
	}
}

void mk(int **a1, int **a2, int **a3, int **a4, int **a5, int **a6, int dim)
{
	clean_matrix(a1, dim);
	clean_matrix(a2, dim);
	clean_matrix(a3, dim);
	clean_matrix(a4, dim);
	clean_matrix(a5, dim);
	clean_matrix(a6, dim);
}

void only_doublekill_block(int **a1, int **a2, int dim)
{
	clean_matrix(a1, dim);
	clean_matrix(a2, dim);
}

void S(int **m1, int **m2, int **result, int n)
{
	if (n == 1) {
		result[0][0] = m1[0][0] * m2[0][0];
		return;
	}
	int **a1, **a2, **a3, **a4, **b1, **b2, **b3, **b4, dim = n / 2;
	a1 = allocate_matrix(dim);
	a2 = allocate_matrix(dim);
	a3 = allocate_matrix(dim);
	a4 = allocate_matrix(dim);
	b1 = allocate_matrix(dim);
	b2 = allocate_matrix(dim);
	b3 = allocate_matrix(dim);
	b4 = allocate_matrix(dim);
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++) {
			a1[i][j] = m1[i][j];
			b1[i][j] = m2[i][j];
			a2[i][j] = m1[i][j + dim];
			b2[i][j] = m2[i][j + dim];
			a3[i][j] = m1[i + dim][j];
			b3[i][j] = m2[i + dim][j];
			a4[i][j] = m1[i + dim][j + dim];
			b4[i][j] = m2[i + dim][j + dim];
		}
	int **c1, **c2, **c3, **c4, **M1, **M2, **M3, **M4, **M5, **M6, **M7;
	int **tmp1, **tmp2;
	M1 = allocate_matrix(dim);
	M2 = allocate_matrix(dim);
	M3 = allocate_matrix(dim);
	M4 = allocate_matrix(dim);
	M5 = allocate_matrix(dim);
	M6 = allocate_matrix(dim);
	M7 = allocate_matrix(dim);
	tmp1 = adunare(a1, a4, dim);
	tmp2 = adunare(b1, b4, dim);
	S(tmp1, tmp2, M1, dim);
	only_doublekill_block(tmp1, tmp2, dim);
	tmp1 = adunare(a3, a4, dim);
	S(tmp1, b1, M2, dim);
	clean_matrix(tmp1, dim);
	tmp1 = scadere(b2, b4, dim);
	S(a1, tmp1, M3, dim);
	clean_matrix(tmp1, dim);
	tmp1 = scadere(b3, b1, dim);
	S(a4, tmp1, M4, dim);
	clean_matrix(tmp1, dim);
	tmp1 = adunare(a1, a2, dim);
	S(tmp1, b4, M5, dim);
	clean_matrix(tmp1, dim);
	tmp1 = scadere(a3, a1, dim);
	tmp2 = adunare(b1, b2, dim);
	S(tmp1, tmp2, M6, dim);
	only_doublekill_block(tmp1, tmp2, dim);
	tmp1 = scadere(a2, a4, dim);
	tmp2 = adunare(b3, b4, dim);
	S(tmp1, tmp2, M7, dim);
	only_doublekill_block(tmp1, tmp2, dim);
	tmp1 = adunare(M1, M4, dim);
	tmp2 = scadere(M5, M7, dim);
	c1 = scadere(tmp1, tmp2, dim);
	only_doublekill_block(tmp1, tmp2, dim);
	c2 = adunare(M3, M5, dim);
	c3 = adunare(M2, M4, dim);
	tmp1 = scadere(M1, M2, dim);
	tmp2 = adunare(M3, M6, dim);
	c4 = adunare(tmp1, tmp2, dim);
	clean_matrix(tmp1, dim);
	clean_matrix(tmp2, dim);
	for (int i = 0 ; i < dim; i++)
		for (int j = 0; j < dim; j++) {
			result[i][j] = c1[i][j];
			result[i][j + dim] = c2[i][j];
			result[i + dim][j] = c3[i][j];
			result[i + dim][j + dim] = c4[i][j];
		}
	mk(a1, a2, a3, a4, b1, b2, dim);
	mk(b3, b4, M1, M2, M3, M4, dim);
	mk(M5, M6, M7, c1, c2, c3, dim);
	clean_matrix(c4, dim);
}

void headshot_the_array(matrice *v, int idx)
{
	for (int i = 0 ; i < idx ; i++) {
		clean_matrix(v[i].matrix, v[i].linii);
		v[i].linii = 0;
		v[i].coloane = 0;
		v[i].suma = 0;
	}
	free(v);
}

#endif
