#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count = 0;

void merge(int s[], int left, int mid, int right) {
	int i = left; int j = mid + 1; int k = left;
	int u[3001];
	while (i <= mid && j <= right) {
		if (s[i] <= s[j]) {
			u[k++] = s[i++];
			count++;
		}
		else {
			u[k++] = s[j++];
			count++;
		}
	}

	while (i <= mid) {
		u[k++] = s[i++];
	}
	while (j <= right) {
		u[k++] = s[j++];
	}
	int l;
	for (l = left; l <= right; l++) {
		s[l] = u[l];
	}
}

void mergesort(int s[], int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		mergesort(s, left, mid);
		mergesort(s, mid + 1, right);
		merge(s, left, mid, right);
	}
}

void swap(int arr[], int x, int y) {
	int t = arr[x];
	arr[x] = arr[y];
	arr[y] = t;
}

int part(int s[], int left, int right) {
	int pivot = s[left];
	int low = left + 1;
	int high = right;
	while (low <= high) {
		while (low <= right && pivot >= s[low]) {
			low++;
			count++;
		}
		while (high >= (left + 1) && pivot <= s[high]) {
			high--;
			count++;
		 }
		if (low <= high) {
			swap(s, low, high);
		}
	}
	swap(s, left, high);
	return high;
}

void quicksort(int s[], int left, int right) {
	if (left < right) {
		int pivot = part(s, left, right);
		quicksort(s, left, pivot - 1);
		quicksort(s, pivot + 1, right);
	}
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	int i, j;
	int r_m = 0;
	int w_m = 0;
	int r_q = 0;
	int w_q = 0;
	char rum[10];
	int run = 0;
	FILE *fp = fopen("input1.txt", "r");
	FILE *fp2 = fopen("output1.txt", "w");
	fprintf(fp2, "	rand_Merge	worst_Merge	rand_Quick	worst_Quick\n");
	fprintf(fp2, "------------------------------------------------------------------\n");
	fscanf(fp, "%s", rum);
	int a = 0;
	while (rum[a] != 0) {
		run *= 10;
		run += rum[a] - 48;
		a++;
	}
	for (a = 0; a < 6; a++) {
		int b = 0;
		char dat[10];
		int data = 0;
		fscanf(fp, "%s", dat);
		while (dat[b] != 0) {
			data *= 10;
			data += dat[b] - 48;
			b++;
		}

		for (j = 0; j < run; j++) {
			int *arr = malloc(sizeof(int)*data);
			int *arr2 = malloc(sizeof(int)*data);
			for (i = 0; i < data; i++) {
				int random = rand();
				arr[i] = random;
				arr2[i] = arr[i];
			}
			mergesort(arr, 0, data - 1);
			r_m += count;
			if (w_m < count)w_m = count;
			count = 0;
			quicksort(arr2, 0, data - 1);
			r_q += count;
			if (w_q < count)w_q = count;
			count = 0;
		}
		r_m /= 10; r_q /= 10;
		fprintf(fp2, "%d:		%d		%d		%d		%d\n", data, r_m, w_m, r_q, w_q);
		r_m = 0; w_m = 0; r_q = 0; w_q = 0;
	}
	fclose(fp);
	fclose(fp2);
}

