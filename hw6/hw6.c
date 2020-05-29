#include <stdio.h>
#include <stdio.h>
#include <string.h>

// 0과 1인지 체크해주는 함수
// 만약 0과 1이 아니라 공백, 탭 등이라면 0을 반환한다.
int isNum(char ch) {
  // 만약 0과 1이 아니라면,
  if(ch != 48 && ch != 49) {
    return 0;
  }
}

int main() {
  FILE *fp;
  // 노드의 알파벳 순서대로 저장
  char alphabet[30];
  // 파일 포인터를 가리키는 char
  char ch;
  int i=0, j=0;
  // 초기 matrix
  int arr[21][21];
  // adjacent list에서 저장한 transpose matrix
  int newarr[21][21] ={0,};
  // node의 개수
  int length = 0;
  // row count
  int row=0;
  // column count
  int col=0;
  char str[20] = "hw6_data1.txt";
  fp = fopen(str, "rt");
  printf("file_name : %s\n\n",str);
  if(fp == NULL) {
    printf("==> 파일이 없습니다.\n");
    return 0;
  }
  printf("input file\n");
  printf("---------------\n");
  printf("  ");
  // 한줄 읽기 : 노드의 갯수와 알파벳 종류를 파악한다.
  while((ch=fgetc(fp)) != '\n') {
    if(65<=ch && ch<=90) {
      alphabet[col] = ch;
      printf("%c ",alphabet[col]);
      col++;
    }
    // 소문자일 경우
    else if(97<=ch && ch<=122) {
      alphabet[col] = ch-32;
      printf("%c ",alphabet[col]);
      col++;
    }
  }
  // 노드의 갯수를 length에 저장. 
  length = col;
  printf("\n");
  /* 디버그용_1
  for(int i =0; i<col; i++) {
    printf("alphabet[%d] : %c\n",i, alphabet[i]);
  }
*/
  col = 0;
  row++;
  // 파일이 끝날때까지 파일포인터를 돌린다.
  while((ch=fgetc(fp)) != EOF) {
    // 밑에 엔터가 더 있다고 할지라도, 노드 갯수만큼만 체크한다.
    if(row>length) break;
    // 한줄의 끝에 도달했다면, col 초기화 후, row 증가
    if(ch == '\n') {
      col = 0;
      row++;
      printf("\n");
    }
    else {
      // 세로 첫 줄 문자인 경우 제외하기 위해,
      // 그리고 첫줄은 무조건 1부터 시작하기 때문에 row-1부터 센다.
      if(col == 0) {
        printf("%c ", alphabet[row-1]);
        col++;
        continue;
      }
      // 0과 1이 아니라면 공백이므로 고려하지 않고 continue
      if(!isNum(ch)) {
        continue;
      }
      // 0과 1이라면 배열에 저장하고 col 값 1 증가.
      else {
        arr[row-1][col-1] = ch%48;
        printf("%d ", arr[row-1][col-1]);
        // 디버그용_1 : printf("arr[%d][%d] : %d\n", row-1, col-1, arr[row-1][col-1]);
        col ++;
      }
    }
  }
  fclose(fp);
  printf("---------------\n");
  // 기존 matrix의 adjacency list 출력
  printf("Array of adjacency list of above graph\n");
  for(int i=0; i<length; i++) {
    printf("[%c] -> ", alphabet[i]);
    for(int j =0; j<length; j++) {
      // 만약 matrix 값이 1로 유효할 경우
      if(arr[i][j] == 1) {
        // transpose matrix로 1 저장.
        newarr[j][i] = 1;
        // 기존 matrix 내용을 출력해주는 함수.
        printf("%c ", alphabet[j]);
      }
    }
    printf("\n");
  }
  printf("---------------\n");
  //  adjacency list를 통해 transpose adjacency list를 생성.
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

