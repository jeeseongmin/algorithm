#include <stdio.h>
#include <stdio.h>
#include <string.h>

// 0�� 1���� üũ���ִ� �Լ�
// ���� 0�� 1�� �ƴ϶� ����, �� ���̶�� 0�� ��ȯ�Ѵ�.
int isNum(char ch) {
  // ���� 0�� 1�� �ƴ϶��,
  if(ch != 48 && ch != 49) {
    return 0;
  }
}

int main() {
  FILE *fp;
  // ����� ���ĺ� ������� ����
  char alphabet[30];
  // ���� �����͸� ����Ű�� char
  char ch;
  int i=0, j=0;
  // �ʱ� matrix
  int arr[21][21];
  // adjacent list���� ������ transpose matrix
  int newarr[21][21] ={0,};
  // node�� ����
  int length = 0;
  // row count
  int row=0;
  // column count
  int col=0;
  char str[20] = "hw6_data1.txt";
  fp = fopen(str, "rt");
  printf("file_name : %s\n\n",str);
  if(fp == NULL) {
    printf("==> ������ �����ϴ�.\n");
    return 0;
  }
  printf("input file\n");
  printf("---------------\n");
  printf("  ");
  // ���� �б� : ����� ������ ���ĺ� ������ �ľ��Ѵ�.
  while((ch=fgetc(fp)) != '\n') {
    if(65<=ch && ch<=90) {
      alphabet[col] = ch;
      printf("%c ",alphabet[col]);
      col++;
    }
    // �ҹ����� ���
    else if(97<=ch && ch<=122) {
      alphabet[col] = ch-32;
      printf("%c ",alphabet[col]);
      col++;
    }
  }
  // ����� ������ length�� ����. 
  length = col;
  printf("\n");
  /* ����׿�_1
  for(int i =0; i<col; i++) {
    printf("alphabet[%d] : %c\n",i, alphabet[i]);
  }
*/
  col = 0;
  row++;
  // ������ ���������� ���������͸� ������.
  while((ch=fgetc(fp)) != EOF) {
    // �ؿ� ���Ͱ� �� �ִٰ� ������, ��� ������ŭ�� üũ�Ѵ�.
    if(row>length) break;
    // ������ ���� �����ߴٸ�, col �ʱ�ȭ ��, row ����
    if(ch == '\n') {
      col = 0;
      row++;
      printf("\n");
    }
    else {
      // ���� ù �� ������ ��� �����ϱ� ����,
      // �׸��� ù���� ������ 1���� �����ϱ� ������ row-1���� ����.
      if(col == 0) {
        printf("%c ", alphabet[row-1]);
        col++;
        continue;
      }
      // 0�� 1�� �ƴ϶�� �����̹Ƿ� ������� �ʰ� continue
      if(!isNum(ch)) {
        continue;
      }
      // 0�� 1�̶�� �迭�� �����ϰ� col �� 1 ����.
      else {
        arr[row-1][col-1] = ch%48;
        printf("%d ", arr[row-1][col-1]);
        // ����׿�_1 : printf("arr[%d][%d] : %d\n", row-1, col-1, arr[row-1][col-1]);
        col ++;
      }
    }
  }
  fclose(fp);
  printf("---------------\n");
  // ���� matrix�� adjacency list ���
  printf("Array of adjacency list of above graph\n");
  for(int i=0; i<length; i++) {
    printf("[%c] -> ", alphabet[i]);
    for(int j =0; j<length; j++) {
      // ���� matrix ���� 1�� ��ȿ�� ���
      if(arr[i][j] == 1) {
        // transpose matrix�� 1 ����.
        newarr[j][i] = 1;
        // ���� matrix ������ ������ִ� �Լ�.
        printf("%c ", alphabet[j]);
      }
    }
    printf("\n");
  }
  printf("---------------\n");
  //  adjacency list�� ���� transpose adjacency list�� ����.
  printf("Array of adjacency list of transpose graph\n");
  for(int i=0; i<length; i++) {
    printf("[%c] -> ", alphabet[i]);
    for(int j=0; j<length; j++) {
      if(newarr[i][j] == 1) {
        printf("%c ", alphabet[j]);
      }
    }
    printf("\n");
  }
  printf("end!");
}

