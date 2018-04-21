#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "practice_project.h"

int main(int argc, char *argv[]) {

  int conversion_type = atoi(argv[1]);
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


/* 0 means no translation, 1 means to only translate type 0 units to type
1 with type 1 units unchanged, 2 means to only translate type 1 units to type 0
with type 0 units unchanged, and 3 means to translate type 0 to 1 and type 1 to 0. */

//0 means no translation
  if (conversion_type == 0) {
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
  } else if (conversion_type == 1) {
    // 1 means to only translate binary units to decimal with decimal units unchanged
    printf("TYPE 1 TRANSLATION:\n");
    printf("TEST 1:\n");
    type_1_translation(str1, output_file_target);
    printf("EXPECTED: %s\n", str2);

    printf("TEST 2:\n");
    type_1_translation(str3, output_file_target);
    printf("EXPECTED: %s\n", str4);

    printf("TEST 3:\n");
    type_1_translation(str5, output_file_target);
    printf("EXPECTED: %s\n", str6);

    printf("TEST 4:\n");
    type_1_translation(str7, output_file_target);
    printf("EXPECTED: %s\n", str8);

    printf("TEST 5:\n");
    type_1_translation(str9, output_file_target);
    printf("EXPECTED: %s\n", str10);
  } else if (conversion_type == 2) {
    // 2 means to only translate decimal units to binary with type binary unchanged
    printf("TYPE 2 TRANSLATION:\n");
    printf("\nTEST 1:\n");
    type_2_translation(str2, output_file_target);
    printf("\nEXPECTED: %s\n", str1);

    printf("\nTEST 2:\n");
    type_2_translation(str4, output_file_target);
    printf("\nEXPECTED: %s\n", str3);

    printf("\nTEST 3:\n");
    type_2_translation(str6, output_file_target);
    printf("\nEXPECTED: %s\n", str5);

    printf("\nTEST 4:\n");
    type_2_translation(str8, output_file_target);
    printf("\nEXPECTED: %s\n", str7);

    printf("\nTEST 5:\n");
    type_2_translation(str10, output_file_target);
    printf("\nEXPECTED: %s\n", str9);
  } else if (conversion_type == 3) {
    // translate everything
    printf("TYPE 3 TRANSLATION:\n");
    printf("TEST 1:\n");
    type_3_translation(str1, output_file_target);
    printf("EXPECTED: %s\n", str2);

    printf("TEST 2:\n");
    type_3_translation(str3, output_file_target);
    printf("EXPECTED: %s\n", str4);

    printf("TEST 3:\n");
    type_3_translation(str5, output_file_target);
    printf("EXPECTED: %s\n", str6);

    printf("TEST 4:\n");
    type_3_translation(str7, output_file_target);
    printf("EXPECTED: %s\n", str8);

    printf("TEST 5:\n");
    type_3_translation(str9, output_file_target);
    printf("EXPECTED: %s\n", str10);
  }

  return 0;
}
