#include <string.h>
#include <stdio.h>

int main() {
  // correct formatting. Should be TRUE.
  char str1[] = "1 100 3,2,1";
  char str2[] = "0 00000010 01011001 00000001";
  //correct formatting, single entry. Should be TRUE.
  char str3[] = "1 1 3";
  char str4[] = "0 00000001 01011001";
  // amount and body does not match type. Should be FALSE.
  char str5[] = "1 00000010 01011001 00000001";
  char str6[] = "0 100 3,2,1";
  // amount and body does not match type, single entry. FALSE.
  char str7[] = "1 00000001 01011001";
  char str8[] = "0 1 3";
  // body separated by spaces instead of commas. FALSE.
  char str9[] = "1 100 3 2 1";
  // body separated by commas instead of faces. FALSE.
  char str10[] = "0 00000010 01011001,00000001";
  // type 1 but contains a 0
  char str11[] = "1 1 0";

  printf("\nTEST 1:\n");
  int a = correct_format(str1);
  printf("\nTEST 2:\n");
  int b = correct_format(str2);
  printf("\nTEST 3:\n");
  int c = correct_format(str3);
  printf("\nTEST 4:\n");
  int d = correct_format(str4);
  printf("\nTEST 5:\n");
  int e = correct_format(str5);
  printf("\nTEST 6:\n");
  int f = correct_format(str6);
  printf("\nTEST 7:\n");
  int g = correct_format(str7);
  printf("\nTEST 8:\n");
  int h = correct_format(str8);
  printf("\nTEST 9:\n");
  int i = correct_format(str9);
  printf("\nTEST 10:\n");
  int j = correct_format(str10);
  printf("\nTEST 11:\n");
  int k = correct_format(str11);


  printf("Test 1: ");
  if (a == 1) {
    printf("TRUE\n");
  } else {
    printf("FALSE\n");
  }

  printf("Test 2: ");
  if (b == 1) {
    printf("TRUE\n");
  } else {
    printf("FALSE\n");
  }

  printf("Test 3: ");
  if (c == 1) {
    printf("TRUE\n");
  } else {
    printf("FALSE\n");
  }

  printf("Test 4: ");
  if (d == 1) {
    printf("TRUE\n");
  } else {
    printf("FALSE\n");
  }

  printf("Test 5: ");
  if (e == 0) {
    printf("TRUE\n");
  } else {
    printf("FALSE\n");
  }

  printf("Test 6: ");
  if (f == 0) {
    printf("TRUE\n");
  } else {
    printf("FALSE\n");
  }

  printf("Test 7: ");
  if (g == 0) {
    printf("TRUE\n");
  } else {
    printf("FALSE\n");
  }

  printf("Test 8: ");
  if (h == 0) {
    printf("TRUE\n");
  } else {
    printf("FALSE\n");
  }

  printf("Test 9: ");
  if (i == 0) {
    printf("TRUE\n");
  } else {
    printf("FALSE\n");
  }

  printf("Test 10: ");
  if (j == 0) {
    printf("TRUE\n");
  } else {
    printf("FALSE\n");
  }

  printf("Test 11: ");
  if (k == 1) {
    printf("TRUE\n");
  } else {
    printf("FALSE\n");
  }

  if ((a == 1) && (b == 1) && (c == 1) && (d == 1) && (e == 0) && (f == 0) &&
    (g == 0) && (h == 0) && (i == 0) && (j == 0) && (k == 1)) {
    printf("TRUE\n");
  } else {
    printf("FALSE\n");
  }

  return 0;
}
