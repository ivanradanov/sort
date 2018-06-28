#include <stdio.h>

// フェルマー素数
#define N ((1<<16)+1)

int A[N];

/*
A[0], A[1], ..., A[n-1] の中でk+1番目に小さい値を返す関数
ただし、Aの中身は書き換えてしまう。
*/
#define SWAP(a, b) do {int c = a; a = b; b = c;} while(0)
int quick_select(int A[], int n, int p)
{
	SWAP(A[0], A[n/2]);
	int pivot = A[0], j = 0, k = 0;
	for (int i = 1; i < n; i++) {
		if (A[i] < pivot) {
			k++;
			j++;
			SWAP(A[k], A[j]);
			SWAP(A[i], A[j]);
		} else if (A[i] == pivot) {
			k++;
			SWAP(A[i], A[k]);
		}
	}
	SWAP(A[0], A[j]);
	if (j <= p && p <= k) return pivot;
	else if (p < j) return quick_select(A, j, p);
	else return quick_select(A + k + 1, n - k - 1, p - k - 1);
}

int main(){
  int i;
  A[0] = 0;
  A[1] = 3; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }

// すべての要素が同じ場合でも計算が早く終わるか確認する

  for(i=0;i<N;i++){
    if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
//    printf("%d th element is %d\n", i, quick_select(A, N, i));
  }
}
