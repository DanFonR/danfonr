#include <stdio.h>
int main(int argc, char *argv[]){
  int operr;
  char oper[4][5] = {"add", "sub", "mult", "div"};
  int ok = scanf("%d", &operr);
  
  switch (operr) {
    case 0:
      int sum = (int)argv[2]+(int)argv[3];
      printf("%d", sum);
      break;
    case 1:
      int sub = (int)argv[2]-(int)argv[3];
      printf("%d", sub);
      break;
    case 2:
      int mult = (int)argv[2] * (int)argv[3];
      printf("%d", mult);
      break;
    case 3:
      float div = (float)argv[2] / (float)argv[3];
      printf("%.3f", div);
      break;
  }
  return 0;
}