#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long int mulcnt = 0;
long long int addcnt = 0;
long long int nmulcnt = 0;
long long int naddcnt = 0;
clock_t start, finish;
double duration[20];
double nduration[20];

void normal(int n, int** a, int**b, int** c) {		//일반곱셈법
	int i, j, k;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			c[i][j] = 0;
			for (k = 0; k < n; k++) {
				c[i][j] += a[i][k] * b[k][j];
				nmulcnt++;
			}
			naddcnt++;
		}
	}
}

void strassen(int m, int** a, int** b, int** c) {
	int i, j, k;
	if (m <= 16) {				//treshold
		/*	int m1, m2, m3, m4, m5, m6, m7;
			m1 = (a[0][0] + a[1][1])*(b[0][0] + b[1][1]);
			m2 = (a[1][0] + a[1][1])*b[0][0];
			m3 = a[0][0] * (b[0][1] - b[1][1]);
			m4 = a[1][1] * (b[1][0] - b[0][0]);
			m5 = (a[0][0] + a[0][1])*b[1][1];
			m6 = (a[1][0] - a[0][0])*(b[0][0] + b[0][1]);
			m7 = (a[0][1] - a[1][1])*(b[1][0] + b[1][1]);
			c[0][0] = m1 + m4 - m5 + m7;
			c[0][1] = m3 + m5;
			c[1][0] = m2 + m4;
			c[1][1] = m1 + m3 - m2 + m6;
			addcnt += 18;
			mulcnt += 7;*/
		for (i = 0; i < m; i++) {
			for (j = 0; j < m; j++) {
				c[i][j] = 0;
				for (k = 0; k < m; k++) {
					c[i][j] += a[i][k] * b[k][j];
					mulcnt++;
				}
				addcnt++;
			}
		}
	}
	else {
		int n = m / 2;										//4분할용
		int** m1 = (int**)malloc(sizeof(int*)*n);			//m1~m7과 계산용임시로 t1,t2 동적할당
		for (i = 0; i < n; i++)
			m1[i] = (int*)malloc(sizeof(int)*n);
		int** m2 = (int**)malloc(sizeof(int*)*n);
		for (i = 0; i < n; i++)
			m2[i] = (int*)malloc(sizeof(int)*n);
		int** m3 = (int**)malloc(sizeof(int*)*n);
		for (i = 0; i < n; i++)
			m3[i] = (int*)malloc(sizeof(int)*n);
		int** m4 = (int**)malloc(sizeof(int*)*n);
		for (i = 0; i < n; i++)
			m4[i] = (int*)malloc(sizeof(int)*n);
		int** m5 = (int**)malloc(sizeof(int*)*n);
		for (i = 0; i < n; i++)
			m5[i] = (int*)malloc(sizeof(int)*n);
		int** m6 = (int**)malloc(sizeof(int*)*n);
		for (i = 0; i < n; i++)
			m6[i] = (int*)malloc(sizeof(int)*n);
		int** m7 = (int**)malloc(sizeof(int*)*n);
		for (i = 0; i < n; i++)
			m7[i] = (int*)malloc(sizeof(int)*n);
		int** t1 = (int**)malloc(sizeof(int*)*n);
		for (i = 0; i < n; i++)
			t1[i] = (int*)malloc(sizeof(int)*n);
		int** t2 = (int**)malloc(sizeof(int*)*n);
		for (i = 0; i < n; i++)
			t2[i] = (int*)malloc(sizeof(int)*n);

		for (i = 0; i < n; i++)	//m1
			for (j = 0; j < n; j++) {
				t1[i][j] = 0;
				t1[i][j] = a[i][j] + a[i + n][j + n];	//a11+a22
				t2[i][j] = b[i][j] + b[i + n][j + n];	//b11+b22
				addcnt += 2;
			}
		strassen(n, t1, t2, m1);

		for (i = 0; i < n; i++)	//m2
			for (j = 0; j < n; j++) {
				t1[i][j] = a[i + n][j] + a[i + n][j + n];	//a21+a22
				t2[i][j] = b[i][j];	//b11
				addcnt += 1;
			}
		strassen(n, t1, t2, m2);

		for (i = 0; i < n; i++)	//m3
			for (j = 0; j < n; j++) {
				t1[i][j] = a[i][j];	//a11
				t2[i][j] = b[i][j + n] - b[i + n][j + n];	//b12-b22
				addcnt += 1;
			}
		strassen(n, t1, t2, m3);

		for (i = 0; i < n; i++)	//m4
			for (j = 0; j < n; j++) {
				t1[i][j] = a[i + n][j + n];	//a22
				t2[i][j] = b[i + n][j] - b[i][j];	//b21-b11
				addcnt += 1;
			}
		strassen(n, t1, t2, m4);

		for (i = 0; i < n; i++)	//m5
			for (j = 0; j < n; j++) {
				t1[i][j] = a[i][j] + a[i][j + n];	//a11+a12
				t2[i][j] = b[i + n][j + n];	//b22
				addcnt += 1;
			}
		strassen(n, t1, t2, m5);

		for (i = 0; i < n; i++)	//m6
			for (j = 0; j < n; j++) {
				t1[i][j] = a[i + n][j] - a[i][j];	//a21-a11
				t2[i][j] = b[i][j] + b[i][j + n];	//b11+b12
				addcnt += 2;
			}
		strassen(n, t1, t2, m6);

		for (i = 0; i < n; i++)	//m7
			for (j = 0; j < n; j++) {
				t1[i][j] = a[i][j + n] - a[i + n][j + n];	//a12-a22
				t2[i][j] = b[i + n][j] + b[i + n][j + n];	//b21+b22
				addcnt += 2;
			}
		strassen(n, t1, t2, m7);

		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++) {
				c[i][j] = m1[i][j] + m4[i][j];	//c11
				c[i][j + n] = m3[i][j] + m5[i][j];	//c12
				c[i + n][j] = m2[i][j] + m4[i][j];	//c21
				c[i + n][j + n] = m1[i][j] + m3[i][j] - m2[i][j] + m6[i][j];	//c22
				addcnt += 8;
			}
		for (i = 0; i < n; i++) {			//동적할당 해제
			free(m1[i]);
			free(m2[i]);
			free(m3[i]);
			free(m4[i]);
			free(m5[i]);
			free(m6[i]);
			free(m7[i]);
			free(t1[i]);
			free(t2[i]);
		}
		free(m1);
		free(m2);
		free(m3);
		free(m4);
		free(m5);
		free(m6);
		free(m7);
		free(t1);
		free(t2);
	}
}


int main() {
	srand(time(NULL));
	int i, j;
	int limit = 0;										//하한값 발견시 그 값+3까지만 반복용도
	int n = 2;											//n=2^k, 시작은 k=1
	int k = 1;
	int count = 0;										//밑의 stan,stra배열 index용도
	long long int stan[20][2];							//각각 standard, strassen이 k일때 수행횟수 저장용
	long long int stra[20][2];							//2차원배열의 0:mul, 1:add/sub
	FILE *fp = fopen("output2.txt", "w");
	
	while (limit <= 3) {
		int** a = (int**)malloc(sizeof(int*)*n);		//행렬a,b,c,d 동적할당
		for (i = 0; i < n; i++)
			a[i] = (int*)malloc(sizeof(int)*n);
		int** b = (int**)malloc(sizeof(int*)*n);
		for (i = 0; i < n; i++)
			b[i] = (int*)malloc(sizeof(int)*n);
		int** c = (int**)malloc(sizeof(int*)*n);
		for (i = 0; i < n; i++)
			c[i] = (int*)malloc(sizeof(int)*n);
		int** d = (int**)malloc(sizeof(int*)*n);
		for (i = 0; i < n; i++)
			d[i] = (int*)malloc(sizeof(int)*n);

		for (i = 0; i < n; i++)								//행렬 a,b에 랜덤난수 입력
			for (j = 0; j < n; j++) {
				int random = rand();
				a[i][j] = random;
				b[i][j] = a[i][j];
			}
		start = clock();
		normal(n, a, b, c);
		finish = clock();
		nduration[count] = (double)(finish - start) / CLOCKS_PER_SEC;
		
		start = clock();
		strassen(n, a, b, d);
		finish = clock();
		duration[count] = (double)(finish - start) / CLOCKS_PER_SEC;
		stan[count][0] = nmulcnt;
		stan[count][1] = naddcnt;
		stra[count][0] = mulcnt;
		stra[count][1] = addcnt;
		
		for (i = 0; i < n; i++) {
			free(a[i]);
			free(b[i]);
			free(c[i]);
			free(d[i]);
		}
		free(a);
		free(b);
		free(c);
		free(d);

		if (nduration[count]>duration[count]) {//하한 도달시부터 limit++,더이상 k는안바뀜
			limit++;
			n *= 2;
			count++;
		}
		else {
			k++;
			n *= 2;
			count++;
		}

	}
	for (i = 0; i < 7; i++) {
		fprintf(fp, "==================================\n");
		fprintf(fp, "2^%d	Standard	Straasen\n", k - 3 + i);
		fprintf(fp, "----------------------------------\n");
		fprintf(fp, "mul	 %lld	       %lld\n", stan[k - 4 + i][0], stra[k - 4 + i][0]);
		fprintf(fp, "add/sub  %lld             %lld\n", stan[k - 4 + i][1], stra[k - 4 + i][1]);
		fprintf(fp, "time    %f         %f\n", nduration[k - 4 + i], duration[k - 4 + i]);
		fprintf(fp, "==================================\n");
	}
}
