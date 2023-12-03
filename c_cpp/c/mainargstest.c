// argc = 1: std; argc = 2: which nums?; argc = 3: which num?; argc = 4: result; else: error
#include <stdio.h>
#include <stdlib.h>

void opt_test(int *option) {
  while (1){
    int test = scanf("%d", option);

    getchar();

    if (test == 1){
      break;
    }

    printf("invalid option\n");
  }
}

int main(int argc, char *argv[]){
  switch (argc) {
    case 1:
      printf("choose between:\n\
1. add 2 numbers\n\
2. subtract one number from another\n\
3. multiply 2 numbers\n\
4. divide one number by another\n\
0. quit\n");
      
      int option, num1, num2;;
      
      opt_test(&option);

      if (option != 0) {
        printf("insert first num: ");
        opt_test(&num1);
        printf("insert second num: ");
        opt_test(&num2);
      }
      
      switch (option) {
        case 1:
          int sum = num1 + num2;
          
          printf("the sum of %d and %d is %d\n", num1, num2, sum);

          break;

        case 2:
          int minus = num1 - num2;

          printf("%d minus %d is %d\n", num1, num2, minus);

          break;

        case 3:
          int mult = num1 * num2;

          printf("%d times %d is %d\n", num1, num2, mult);

          break;

        case 4:
          float div = (float)num1 / num2;

          printf("%d divided %d is approximately %.2f\n", num1, num2, div);

          break;
      }      
      
      break;

    case 2:
      char options[4][5] = {"add", "sub", "mult", "div"};
      int among;
      
      for (int i = 0; i < 4; i++) {
        if (argv[1] == options[i]) {
          among = 1;
          break;
        }
      }
  }
  
  return 0;
}