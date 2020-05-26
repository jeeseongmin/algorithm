#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define FREE(ptr) if(ptr) {free(ptr); ptr = NULL; }

// �������� ���ڸ� ����.
// ���Դ� 1 ~ 100
// ��ġ�� ������ 1�޷� ~ 300 �޷� ����
// �ִ� �뷮�� ��ǰ �� * 40 
// ����� ��ǰ�� ���� ����ڰ� �Է�.
// 15���� �ʰ��ϸ� ���α׷� ������ ����.

//int weight[10000], benefit[10000]; // ������ ���Կ� ��ġ
//int num, max_weight; //�ʿ��� ������ ������ ��ƿ �� �ִ� ����

typedef struct {
    float time;
    float benefit;
} Result;

// weight�� ��ƿ �� �ִ� �ִ� ���Ը� ���Ϸ��� ����
void createState(int *pweight, int *pbenefit, int *grd_weight, int *grd_benefit, int num) {
    srand(time(NULL));
    for(int i = 0; i<num; i++) {
        int random = (rand() % 100) + 1;
        pweight[i] = random;
        grd_weight[i] = random;
    }
    // weight random (max 100)
    for(int i = 0; i<num; i++) {
        int random = (rand() % 300) + 1;
        pbenefit[i] = random;
        grd_benefit[i] = random;
    }
}

void deleteState(int *pweight, int *pbenefit, int *grd_weight, int *grd_benefit, int num) {
    FREE(pweight);
    FREE(pbenefit);
    FREE(grd_weight);
    FREE(grd_benefit);
}

// max_weight �� �ִ� / weight�� ���� ����
int DP(int *pweight, int *pbenefit, int **dp, int num_dp, int weight, int num, int max_weight) {
    
    for(int i =0; i<=num; i++) {
        for(int w =0; w<=max_weight; w++) {
            if(i==0 || w== 0)
                dp[i][w] = 0;
            else if(pweight[i-1] <= w) {
                int n1 = pbenefit[i-1]+dp[i-1][w-pweight[i-1]];
                int n2 = dp[i-1][w];
                if(n1>n2) dp[i][w]=n1;
                else dp[i][w]=n2;
            }
            else dp[i][w] = dp[i-1][w];
            //printf("dp[%d][%d] : %d\n",i, w, dp[i][w]);
        }
    }
    return dp[num][max_weight];
}

float DP_before(int *pweight, int *pbenefit, int num) {
    /* DEBUG
    for(int i =0; i<num; i++) {
        printf("dp[%d] : %d(b), %d(w)\n",i, p[i].benefit, p[i].weight);
    } */
    int max_weight = num * 40;
    float result;
    int **dp = malloc (sizeof(int*) * num+1);
    for(int i =0; i<num+1; i++) {
        dp[i] = (int *)malloc (sizeof(int) * max_weight+1);
    }
    result = DP(pweight, pbenefit, dp, 0, 0, num, max_weight);
    // dp �迭 free
    for(int i=0; i<num+1; ++i) {
        FREE(dp[i]);
    }
    FREE (dp);
    return result;
}

float Greedy(int *weight, int *benefit, int num) {
    int max_weight = num * 40;

    int min_idx=0;
    int max_weight_grd = 0;
    float max_benefit_grd = 0;
    // �ڸ� benefit
    float fraction=0;
    float temp_weight =0;
    float temp_benefit =0;
    float standard = 0;
    //for(int i =0; i<num; i++) {
    //    printf("p_grd[%d] : %d(b), %d(w)\n",i, p_grd[i].benefit, p_grd[i].weight);
    //}
    // ����
    for(int i=0; i<num-1; i++) {
        temp_weight = i;
        temp_benefit = i;
        for(int j = i; j<num; j++) {
            if(benefit[j]/weight[j] > benefit[min_idx]/weight[min_idx]) {
                min_idx = j;
            }
        }
        temp_weight = weight[min_idx];
        temp_benefit = benefit[min_idx];
        weight[min_idx] = weight[i];
        benefit[min_idx] = benefit[i];
        weight[i]=temp_weight;
        benefit[i]=temp_weight;
    }
    /* DEBUG
    for(int i =0; i<num; i++) {
       printf("grd[%d] : %d(b), %d(w)\n",i, grd[i].benefit, grd[i].weight);
    }
    */
    for(int i =0; i<num; i++) {
        // �������� ������ ���� �־��� ���� ���Ժ��� �۴ٸ� ����
        if(weight[i]+max_weight_grd < max_weight) {
            max_benefit_grd += benefit[i];
            max_weight_grd += weight[i];
        }
        // �������� ������ ���� �־��� ���� ���Ժ��� ũ�ٸ� �ڸ��� ��
        else if(weight[i] + max_weight_grd > max_weight) {
            int rest = max_weight-max_weight_grd;            
            fraction = (double)benefit[i]/(double)weight[i] * (double)rest;
            max_benefit_grd += fraction;
            return max_benefit_grd;
        }
        // �������� ������ ���� �־��� ���� ���Կ� ���ٸ� ��
        if(weight[i]+max_weight_grd == max_weight) {
            return max_benefit_grd;            
        }
    }
    printf("Error: grd\n");
    return 0;
}

// max_benefit�� global variable
// local�� benefit, weight, bound
// max_benefit=0 ���� ����.
// ���� �� �� : max profit, total_weight

// children�� ����� ������ : expand�� �Ѵٰ� ���� �� �Ƹ��� �츮�� ���� �� �ִ� profit�� ���Ѽ�
// ��� ������ �� ������, �̰� �̻��� ���� �� ����!!

float bound(int *grd_weight, int *grd_benefit, int max_benefit, int total_weight, int max_weight, int max_num, int index, int flag) {
    int bnd = 0;
    int total =0;
    for(int i=index+1; i<max_num; i++) {
        if(total_weight+grd_weight[i] > max_weight) {
            total += (max_weight-total_weight)*grd_benefit[i]/grd_weight[i];
            break;
        }
        else {
            total += grd_benefit[i];
            total_weight+=grd_weight[i];
        }
    }
    bnd = max_benefit+total;
    return bnd;
}
// total_weight ó���� 0, max_benefit �� ó���� 0
int Bnb(int *grd_weight, int *grd_benefit, int max_benefit, int total_weight, int max_weight, int max_num, int index) {

    int weight = 0;
    int benefit = 0;
    if(index>max_num) return 0;
    if(index != 0) {
        if(grd_weight[index-1] > max_weight)  ; // ���� ����ֱ�.
        else {
            weight = grd_weight[index-1];
            benefit = grd_benefit[index-1];
        }
    }
    total_weight += total_weight_f(grd_weight, grd_benefit, total_weight, max_weight, max_num, index);
    
    int bound_left, bound_right;
    if(index == max_num) {

    }
    else {
        bound_left = bound(grd_weight, grd_benefit, max_benefit+benefit, total_weight, max_weight, max_num, index);
        bound_right = bound(grd_weight, grd_benefit, max_benefit, total_weight, max_weight, max_num, index);
    }
    for(int i =0; i< what; i++) {
        //�̹� knapsack�� ������� weight
        int total_weight = weight;

    }
}

int main() {
    // �� �˰����� ����� ��� ����ü
    // Result grd[10];
    // Result dp[10];
    // Result bnb[10];
    Result grd;
    Result dpr;
    FILE* fp = fopen("output.txt","w");
    time_t start, end;
    int arr[9] = {10, 100, 500, 1000, 3000, 5000, 7000, 9000, 10000};
    int bnb_weight = 0;
    
    fprintf(fp, "Number of Items        Processing time in miliseconds / Maximum benefit value\n");
    fprintf(fp, "                         Greedy                  D.P                 B & B\n");
    for(int i =0; i<9; i++) {
        int *pweight = (int *)malloc(sizeof(int) * arr[i]+1);
        int *pbenefit = (int *)malloc(sizeof(int) * arr[i]+1);
        int *grd_weight = (int *)malloc(sizeof(int) * arr[i]+1);
        int *grd_benefit = (int *)malloc(sizeof(int) * arr[i]+1);

        createState(pweight, pbenefit, grd_weight, grd_benefit, arr[i]);
        start=clock();
        grd.benefit = Greedy(grd_weight, grd_benefit, arr[i]);
        end=clock();
        grd.time = (double)(end - start)/1000;
        printf("Greedy time(%ds) : %.3fs\n", arr[i], grd.time);
        printf("Greedy benefit(%ds) : %.2f\n\n", arr[i], grd.benefit);

        if(i<5) {
            // Dynamic Programming mehtod
            start=clock();
            dpr.benefit = DP_before(pweight, pbenefit, arr[i]);
            end=clock();
            dpr.time = (double)(end - start)/1000;
            printf("Dp time(%ds) : %.3fs\n", arr[i], dpr.time);
            printf("Dp benefit(%ds) : %.2f\n\n", arr[i], dpr.benefit);
            fprintf(fp, "%-5d\t\t\t\t  %.3f/%.2f \t\t%.3f/%.2f\n",arr[i],grd.time, grd.benefit, dpr.time, dpr.benefit);
        }
        if(i>=5){
            fprintf(fp, "%-5d\t\t\t\t  %.3f/%.2f \t\t\n",arr[i],grd.time, grd.benefit);
        }
        deleteState(pweight, pbenefit, grd_weight, grd_benefit, arr[i]);

    }
    fclose(fp);

    //BnB();
    printf("end\n");
    return 0;
}