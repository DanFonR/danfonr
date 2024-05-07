/*
Este programa cifra frases em 6 diferentes cifras de substituicao/transposicao,
armazena o resultado em uma struct,
e loga o resultado em um arquivo de texto
Codigo produzido para trabalho de Algoritmos e Programacao de Computadores I
*/

/*
Codigo por Dannyel Fontenele Ribeiro
Testagem por Victor Cardozo Pedrosa
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
#define sys_clr() (void) system("cls")
#else
#define sys_clr() (void) system("clear")
#endif
#define PLAINSIZ BUFSIZ / 2

char *cesar(char frase[]) {
/*
Sendo A = 1 e Z = 26, some 3 ao valor da letra
Se maior que 26, tire 26. (Ex.: A -> D, Z -> C, M -> P)
*/
  for (int i = 0; i < strlen(frase); i++) {
    char letter = frase[i];

    if (isupper(letter))
      frase[i] = (letter + 3 - 'A') % 26 + 'A';
    else if (islower(letter))
      frase[i] = (letter + 3 - 'a') % 26 + 'a';
    else continue;
  }
  return frase;
}

char *atbash(char frase[]) {
/*
Troca das posicoes das letras
(Ex.: A -> Z, Z -> A, M -> N, N -> M)
*/
  for (int i = 0; i < strlen(frase); i++) {
    char letter = frase[i];

    if (isupper(letter))
      frase[i] = 'A' + 'Z' - letter;
    else if (islower(letter))
      frase[i] = 'a' + 'z' - letter;
    else continue;
  }
  return frase;
}

char *affine(char frase[], int chave_a, int chave_b) {
/*
Posicao das letras comecando em 0, cifra-se frase usando a formula
(chave_a * letra + chave_b) MOD 26
*/
  for (int i = 0; i < strlen(frase); i++) {
    char letter = frase[i];

    if (isupper(letter))
      frase[i] = ((chave_a * (letter % 'A') + chave_b) % 26) + 'A';
    else if (97 <= letter && letter <= 122)
      frase[i] = ((chave_a * (letter % 'a') + chave_b) % 26) + 'a';
    else continue;
  }
  return frase;
}

char *morse(char frase[]) {
  char morse[36][6] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....",
                       "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.",
                       "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",
                       "-.--", "--..", "-----", ".----", "..---", "...--",
                       "....-", ".....", "-....", "--...", "---..", "----."};
  static char ciphertxt[BUFSIZ] = "";

  for (int i = 0; i < strlen(frase); i++) {
    char letter = tolower(frase[i]);
    
    if (strlen(ciphertxt) >= BUFSIZ - 100)
      break;
    if (islower(letter)) {
      strcat(ciphertxt, morse[letter % 97]);
      strcat(ciphertxt, " ");
    }
    else if (isdigit(letter)) {
      strcat(ciphertxt, morse[letter - 22]);
      strcat(ciphertxt, " ");
    }
    else if (letter == ' ') {
      strcat(ciphertxt, "/ ");
    }
  }

  ciphertxt[strlen(ciphertxt) - 1] = '\0';

  return ciphertxt;
}

char *vigenere(char frase[], char *chave) {
/*
Parear frase com chave (repetir chave se necessario)
Soma da posicao das letras - 1, tirar 26 se maior que 26
*/
  int delta = 0; /*offset para parear letras corretamente*/
  int len_chave = strlen(chave);

  for (int i = 0; i < strlen(frase); i++) {
    unsigned char cripto = (frase[i] + chave[(i - delta) % len_chave] - 1);

    if (islower(frase[i])) {
      if (cripto > 218)
        cripto -= 122;
      else
        cripto -= 96;

      frase[i] = cripto;
    }
    else if (isupper(frase[i])) {
      if (cripto >= 187)
        cripto -= 122;
      else
        cripto -= 96;

      frase[i] = cripto;
    }
    else delta++;
  }
  return frase;
}

char *polibio(char frase[]) {
/*
Uma das versoes que se baseia em uma matriz 5x5 do alfabeto, tal que I == J
*/
  char polybius[26][3] = {"11", "12", "13", "14", "15", "21", "22", "23",
                          "24", "24", "25", "31", "32", "33",
                          "34", "35", "41", "42", "43", "44", "45", "51",
                          "52", "53", "54", "55"};
  static char poly_ciphertxt[250] = "";

  for (int i = 0; i < strlen(frase); i++) {
    char letter = tolower(frase[i]);

    if (isalpha(letter)) {
      strcat(poly_ciphertxt, polybius[letter % 'a']);
      strcat(poly_ciphertxt, " ");
    }
    else if (letter == 32)
      strcat(poly_ciphertxt, "/ ");
  }

  poly_ciphertxt[strlen(poly_ciphertxt) - 1] = '\0';

  return poly_ciphertxt;
}

int main() {
  struct {
    char plaintext[PLAINSIZ];
    char ciphertxt[BUFSIZ];
  } par_plain_cipher;
  char cifras[6][21] = {"Cesar", "Atbash", "Affine",
                        "Morse", "Vigenere", "Quadrado de Polibio"};
  FILE *fptr = fopen("cifras.txt", "a");

  if (!fptr) {
    perror("Um erro ocorreu ao criar/acessar logs de frases");
    exit(EXIT_FAILURE);
  }

  while (1) {
    sys_clr();
    puts("Selecione uma opcao para cifrar sua frase:\n\
1. Cesar;\n\
2. Atbash;\n\
3. Affine;\n\
4. Morse;\n\
5. Vigenere;\n\
6. Quadrado de Polibio;\n\
9. Limpar logs de frases;\n\
0. Sair do programa");

    int choice = 0;

    while (1) {
      int input_test = scanf("%2d", &choice);

      getchar();

      if (choice == 9) {
        freopen(NULL, "w", fptr);
        puts("Log limpo");
        printf("Proxima opcao: ");
      }
      else if (!(input_test) || ((choice < 0) || (choice > 6)))
        printf("Opcao invalida. Tente novamente.\n");
      else if (choice == 0) {
        sys_clr();
        puts("Ok. Ate mais.");
        fclose(fptr);
        exit(EXIT_SUCCESS);
      }
      else break;
    }

    sys_clr();
    puts(cifras[choice - 1]);

    char frase[PLAINSIZ];
    printf("digite a frase: ");
    fgets(frase, PLAINSIZ, stdin);
    frase[strlen(frase) - 1] = '\0';
    strcpy(par_plain_cipher.plaintext, frase);

    switch (choice) {
      case 1:
        printf("A frase \"%s\" em Cesar se torna: ", frase);
        cesar(frase);
        puts(frase);
        strcpy(par_plain_cipher.ciphertxt, frase);

        break;

      case 2:
        printf("A frase \"%s\" em Atbash se torna: ", frase);
        atbash(frase);
        puts(frase);
        strcpy(par_plain_cipher.ciphertxt, frase);

        break;

      case 3:
        sys_clr();
        puts("Affine");
        printf("Insira valores inteiros para as chaves A e B: ");

        int chave_a, chave_b;
        int teste_scan = scanf("%20d %20d", &chave_a, &chave_b);

        getchar();

        if (teste_scan != 2) {
          puts("Insira valores validos.");

          break;
        }

        if (!(chave_a % 2 && chave_a % 13)) {
          puts("Chave A invalida. O MDC entre ela e 26 deve ser 1.");

          break;
        }

        printf("A frase \"%s\" em Affine se torna: ", frase);
        affine(frase, chave_a, chave_b);
        puts(frase);
        strcpy(par_plain_cipher.ciphertxt, frase);

        break;

      case 4:
        char *em_morse = morse(frase);

        printf("A frase \"%s\" em Morse se torna: ", frase);
        puts(em_morse);
        strcpy(par_plain_cipher.ciphertxt, em_morse);

        break;

      case 5:
        sys_clr();
        puts("Vigenere");
        printf("Digite uma palavra-chave: ");

        char chave[51]; /*Palavras de ate 50 letras, sem acentos ou ce-cedilha*/
        int teste_vig = scanf("%50s", chave);

        getchar();

        if (!teste_vig) {
          erro:
            puts("Digite uma chave valida.");

            break;
        }

        for (int i = 0; i < strlen(chave); i++) {
          if (!isalpha(chave[i]))
            goto erro;

          chave[i] = tolower(chave[i]);

        }

        printf("A frase \"%s\" em Vigenere cifrada com \"%s\" se torna: ",
              frase, chave);
        vigenere(frase, chave);
        puts(frase);
        strcpy(par_plain_cipher.ciphertxt, frase);

        break;

      case 6: 
        char *em_polibio = polibio(frase);

        printf("A frase \"%s\" em Quadrado de Polibio se torna: ", frase);
        puts(em_polibio);
        strcpy(par_plain_cipher.ciphertxt, em_polibio);

        break;
    }

    if (strlen(par_plain_cipher.ciphertxt))
      fprintf(fptr, "%s: plaintext: \"%s\"; ciphertext: \"%s\"\n",
              cifras[choice - 1], par_plain_cipher.plaintext,
              par_plain_cipher.ciphertxt);
    printf("Continuar?(Y/n) ");

    char continuar = getchar();
    continuar = tolower(continuar);

    if (continuar == 'n') {
      printf("Ok. Ate mais!\n");
      fclose(fptr);
      break;
    }

  }

  return 0;
}
