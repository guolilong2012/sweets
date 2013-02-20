#include <stdio.h>

void quicksort(int a[], int l, int h)
{
	if (l >= h) return;
	int i, j, key;
	i = l; j = h; key = a[i];
	while (i < j) {
		while (i<j && a[j]>key) j--;
		if (i < j) a[i++] = a[j];
		while (i<j && a[i]<key) i++;
		if (i < j) a[j--] = a[i];
	}
	a[i] = key;
	if (l < i-1)
		quicksort(a, l, i-1);
	if (i+1 < h)
		quicksort(a, i+1, h);
}

int main(void)
{
	int i;
	int a[] = {3, 5, 1, 4, 6, 2};

	printf("Befort sort: ");
	for (i = 0; i < sizeof(a)/4; i++) {
		printf("%d ", a[i]);
	}
	quicksort(a, 0, sizeof(a)/4);
	printf("\nAfter sort: ");
	for (i = 0; i < sizeof(a)/4; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");

	return 0;
}

