//hw3_Problem3
//21500706_Áö¼º¹Î
#include <stdio.h>
#include <time.h>

int subset[51][51];
//recursive algorithm
int reC(int n, int k) {
    if(n>=0 && k==0) return 1;
    else if(n==0 && k>0) return 0;
    else if(n==k) return 1;
    else if(n>0 && k>0) return reC(n-1, k-1)+reC(n-1,k);
}

// dynamic programming approach
int dyC(int n, int k) {
    if(subset[n][k] != 0) return subset[n][k];

    else if(n>=0 && k==0) {
        subset[n][k] = 1; 
        return 1;
    }
    else if(n==0 && k>0) {
        subset[n][k]=0;
        return 0;
    }
    else if(n==k){
        subset[n][k]=1;
        return 1;
    }
    else {
        subset[n][k] =dyC(n-1, k-1)+dyC(n-1,k);
        return subset[n][k];
    }
}



int main() {
    time_t start=0, end=0;
    double result;
    int n, k;
    char check = 'y';
    while(check == 'y' || check == 'Y') {
        printf("Enter a integer n : ");
        scanf("%d",&n);
        printf("Enter a integer k : ");
        scanf("%d", &k);
        printf("------------------------\n");
        printf("First : DP solution\n");
        start=clock();
        printf("%d\n", dyC(n,k));
        end = clock();
        result = (double)(end - start);
        printf("DP time : %fs\n\n", result/CLOCKS_PER_SEC);
        printf("Second : recursive solution\n");
        start=clock();
        printf("%d\n",reC(n,k));
        end= clock();
        result = (double)(end - start);
        printf("recursive time : %fs\n\n", result/CLOCKS_PER_SEC);

        getchar();
        printf("One more time? (y/n) : ");
        scanf("%c", &check);
    }
    printf("Ok, Bye!\n");
    return 0;
}