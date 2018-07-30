#include <stdio.h>

// フェルマー素数
#define N ((1<<16)+1)

int A[N];

/*
A[0], A[1], ..., A[n-1] の中でk+1番目に小さい値を返す関数
ただし、Aの中身は書き換えてしまう。
*/

#define SWAP(a, b) do {int c = a; a = b; b = c;} while(0)

void pretty_print(int A[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d\t", A[i]);
	printf("\n");
}

int median(int A[], int n)
{
	for (int i = 1; i < n; i++)
		for (int j = i; j > 0 && A[j] < A[j - 1]; j--)
			SWAP(A[j], A[j-1]);
	return A[n / 2];
}

int quick_select(int A[], int n, int k);

int select_pivot(int A[], int n)
{
	if (n <= 5)
		return median(A, n);
	int B[N/5 + 1], i, j;
	for (i = 0, j = 0; j < n; i++, j += 5)
		if (j + 5 < n) {
			B[i] = median(A + j, 5);
		} else {
			B[i] = median(A + j, n - j);
			break;
		}
	int sn = i + 1;
	return quick_select(B, sn, sn / 2);
}

int quick_select(int A[], int n, int p)
{
	int pivot = select_pivot(A, n), j = 0, k = 0;
	for (int i = 0; i < n; i++) {
		if (A[i] < pivot) {
			j++;
			SWAP(A[i], A[j]);
		}
	}
	int k = j;
	for (int i = k + 1; i < n; i++) {
		if (A[i] == pivot) {
			k++;
			SWAP(A[i], A[k]);
		}
	}
	if (j <= p && p < k) return pivot;
	else if (p < j) return quick_select(A, j, p);
	else return quick_select(A + k, n - k, p - k);
}

int main(){
  int i;
  A[0] = 0;
  A[1] = 3; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }
  for(i=0;i<N;i++){
    if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
//    printf("%d th element is %d\n", i, quick_select(A, N, i));
  }
}
