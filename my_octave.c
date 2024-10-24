//Copyright Giurgiu Andrei-Stefan 315CA 2023-2024
#include <stdio.h>
#include <stdlib.h>
#include "my_octave_functions.h"

int main(void)
{
	matrice *v;
	v = (matrice *)malloc(2 * sizeof(matrice));
	int size_max = 2, c_sz = 0, i1 = 0, i2 = 0, id = 0, putere = 0;
	char c;
	scanf("%c", &c);
	while (c != 'Q') {
		if (c >= 'A' && c <= 'Z')
			switch (c) {
				case 'L': {
					array_memory_alloc(&v, c_sz, &size_max);
					scanf("%d%d", &i1, &i2);
					element_memory_alloc(v, c_sz, i1, i2);
					input_matrix(v, c_sz, &c_sz);
					break;
				}
				case 'D': {
					scanf("%d", &id);
					matrix_param(v, id, c_sz);
					break;
				}
				case 'P': {
					scanf("%d", &id);
					output_matrix(v, id, c_sz);
					break;
				}
				case 'C': {
					scanf("%d", &id);
					matrix_redimension(v, id, c_sz);
					break;
				}
				case 'M': {
					scanf("%d%d", &i1, &i2);
					if (check(v, i1, i2, c_sz) == 1) {
						array_memory_alloc(&v, c_sz, &size_max);
						multiplication(v, c_sz, i1, i2);
						c_sz++;
					}
					break;
				}
				case 'O': {
					sorting_array(v, c_sz);
					break;
				}
				case 'T': {
					scanf("%d", &id);
					transpunere(v, id, c_sz);
					break;
				}
				case 'R': {
					scanf("%d%d", &id, &putere);
					expo_task(v, id, c_sz, putere);
					break;
				}
				case 'F': {
					scanf("%d", &id);
					kill_matrix(v, id, &c_sz);
					array_memory_alloc(&v, c_sz, &size_max);
					break;
				}
				case 'S': {
					scanf("%d%d", &i1, &i2);
					if (check(v, i1, i2, c_sz) < 0)
						break;
					array_memory_alloc(&v, c_sz, &size_max);
					element_memory_alloc(v, c_sz, v[i1].linii, v[i1].coloane);
					S(v[i1].matrix, v[i2].matrix, v[c_sz].matrix, v[i1].linii);
					v[c_sz].suma = suma_elementelor(v, c_sz);
					c_sz += 1;
					break;
				}
				default: {
					printf("Unrecognized command\n");
					break;
				}
			}
		scanf("%c", &c);
	}
	headshot_the_array(v, c_sz);
	return 0;
}
