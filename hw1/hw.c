#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// 무작위로 숫자를 생성.
// 무게는 1 ~ 100
// 가치의 범위는 1달러 ~ 300 달러 사이
// 최대 용량은 물품 수 * 40 
// 참고로 물품의 수는 사용자가 입력.
// 15분을 초과하면 프로그램 실행을 중지.

//int weight[10000], benefit[10000]; // 물건의 무게와 가치
//int num, max_weight; //필요한 물건의 개수와 버틸 수 있는 무게

typedef struct {
    float time;
    float benefit;
} Result;

typedef struct {
    int weight;
    int benefit;
} Item, *PItem;

// weight은 버틸 수 있는 최대 무게를 비교하려는 변수
PItem createState(int num) {
    PItem item = (PItem)malloc(sizeof(Item) * num);
    srand(time(NULL));
    for(int i = 0; i<num; i++) {
        int random = (rand() % 300) + 1;
        item[i].weight = random;
        //weight[i] = random;
    }
    // weight random (max 100)
    for(int i = 0; i<num; i++) {
        int random = (rand() % 100) + 1;
        item[i].benefit = random;
    }
    return item;
}

void deleteState(PItem item) {
    free(item);
}
int DP(PItem p, int **dp, int num_dp, int weight, int num, int max_weight) {
    //if(num==50) printf("check!\n");
    // 이미 값이 존재한다면 그 값을 그냥 return
    if(dp[num_dp][weight] > 0) return dp[num_dp][weight];
    if(num_dp == num) return 0;
    int n1 = 0;

    if(weight + p[num_dp].weight <= max_weight) {
        n1 = p[num_dp].benefit + DP(p, dp, num_dp+1, weight+p[num_dp].weight, num, max_weight); 
    } // 포함
    int n2 = DP(p, dp, num_dp+1, weight, num, max_weight);
    // 미포함
    if(n1>=n2) return dp[num_dp][weight] = n1;
    else return dp[num_dp][weight] = n2;
}

float DP_before(PItem p, int num) {
    /* DEBUG
    for(int i =0; i<num; i++) {
        printf("dp[%d] : %d(b), %d(w)\n",i, p[i].benefit, p[i].weight);
    } */
    int max_weight = num * 40;
    float result;
    int **dp;
    dp = (int**) malloc (sizeof(int*) * num+1);
    for(int i =0; i<num+1; i++) {
        dp[i] = (int *) malloc (sizeof(int) * max_weight+1);
    }
    result = DP(p, dp, 0, 0, num, max_weight);
    // dp 배열 free
    for(int i=0; i<num+1; i++) {
        free(dp[i]);
    }
    free (dp);
    return result;
}

float Greedy(PItem p_grd, int num) {
    int max_weight = num * 40;

    int min_idx=0;
    int max_weight_grd = 0;
    float max_benefit_grd = 0;
    // 자른 benefit
    float fraction=0;
    Item temp;
    temp.weight =0;
    temp.benefit =0;
    float standard = 0;
    //for(int i =0; i<num; i++) {
    //    printf("p_grd[%d] : %d(b), %d(w)\n",i, p_grd[i].benefit, p_grd[i].weight);
    //}
    // 정렬
    for(int i=0; i<num-1; i++) {
        temp.weight = i;
        temp.benefit = i;
        for(int j = i; j<num; j++) {
            if(p_grd[j].benefit/p_grd[j].weight > p_grd[min_idx].benefit/p_grd[min_idx].weight) {
                min_idx = j;
            }
        }
        temp = p_grd[min_idx];
        p_grd[min_idx] = p_grd[i];
        p_grd[i] = temp;
    }
    /* DEBUG
    for(int i =0; i<num; i++) {
       printf("grd[%d] : %d(b), %d(w)\n",i, grd[i].benefit, grd[i].weight);
    }
    */
    for(int i =0; i<num; i++) {
        // 넣으려는 물건이 만약 넣었을 때의 무게보다 작다면 성공
        if(p_grd[i].weight+max_weight_grd < max_weight) {
            max_benefit_grd += p_grd[i].benefit;
            max_weight_grd += p_grd[i].weight;
        }
        // 넣으려는 물건이 만약 넣었을 때의 무게보다 크다면 자르고 끝
        else if(p_grd[i].weight + max_weight_grd > max_weight) {
            int rest = max_weight-max_weight_grd;            
            fraction = (double)p_grd[i].benefit/(double)p_grd[i].weight * (double)rest;
            max_benefit_grd += fraction;
            free(p_grd);
            return max_benefit_grd;
        }
        // 넣으려는 물건이 만약 넣었을 때의 무게와 같다면 끝
        if(p_grd[i].weight+max_weight_grd == max_weight) {
            free(p_grd);
            return max_benefit_grd;            
        }
    }
    printf("Error: grd\n");
    return 0;
}

int main() {
    // 각 알고리즘의 결과를 담는 구조체
    Result grd[9];
    Result dp[9];
    Result bnb[9];
    time_t start, end;
    int arr[9] = {10, 100, 500, 1000, 3000, 5000, 7000, 9000, 10000};
    //int arr[3] = {10, 20, 50};
    for(int i=0; i< 9; i++) {
        PItem p = createState(arr[i]); 
        PItem p_grd = p;

        start=clock();
        grd[i].benefit = Greedy(p_grd, arr[i]);
        end=clock();
        grd[i].time = (double)(end - start)/1000;
        printf("Greedy time(%ds) : %.3fs\n", arr[i], grd[i].time);
        printf("Greedy benefit(%ds) : %.2f\n\n", arr[i], grd[i].benefit);

        // Dynamic Programming mehtod
        start=clock();
        dp[i].benefit = DP_before(p, arr[i]);
        end=clock();
        dp[i].time = (double)(end - start)/1000;
        printf("Dp time(%ds) : %.3fs\n", arr[i], dp[i].time);
        printf("Dp benefit(%ds) : %.2f\n\n", arr[i], dp[i].benefit);
        deleteState(p);
        deleteState(p_grd);
    }

    //BnB();

    printf("end\n");
    return 0;
}
