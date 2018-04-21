#include <string.h>
#include <stdio.h>

int main() {
  char output_file_target[] = "output.txt";
  char str1[] = "1 2 200,72";
  char str2[] = "0 00000010 11001000 01001000";
  char str3[] = "1 2 59,111";
  char str4[] = "0 00000010 00111011 01101111";
  char str5[] = "1 1 900";
  char str6[] = "0 00000001 00000001 1110000100";
  char str7[] = "1 3 89,77,1";
  char str8[] = "0 00000011 1011001 01011001 00000001";
  char str9[] = "1 1 65535";
  char str10[] = "0 00000001 11111111";


  printf("TYPE 0 TRANSLATION:\n");
  printf("TEST 1:\n");
  type_0_translation(str1, output_file_target);
  printf("EXPECTED: %s\n", str1);

  printf("\nTEST 2:\n");
  type_0_translation(str3, output_file_target);
  printf("EXPECTED: %s\n", str3);

  printf("\nTEST 3:\n");
  type_0_translation(str5, output_file_target);
  printf("EXPECTED: %s\n", str5);

  printf("\nTEST 4:\n");
  type_0_translation(str7, output_file_target);
  printf("EXPECTED: %s\n", str7);

  printf("\nTEST 5:\n");
  type_0_translation(str9, output_file_target);
  printf("EXPECTED: %s\n", str9);




  // printf("TYPE 1 TRANSLATION:\n");
  // printf("TEST 1:\n");
  // type_1_translation(str1, output_file_target);
  // printf("EXPECTED: %s\n", str2);
  //
  // printf("TEST 2:\n");
  // type_1_translation(str3, output_file_target);
  // printf("EXPECTED: %s\n", str4);
  //
  // printf("TEST 3:\n");
  // type_1_translation(str5, output_file_target);
  // printf("EXPECTED: %s\n", str6);
  //
  // printf("TEST 4:\n");
  // type_1_translation(str7, output_file_target);
  // printf("EXPECTED: %s\n", str8);
  //
  // printf("TEST 5:\n");
  // type_1_translation(str9, output_file_target);
  // printf("EXPECTED: %s\n", str10);

  return 0;
}
