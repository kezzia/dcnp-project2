#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

//Type Amount Number1 Number2 … NumberN --> Type Amount Number1, Number2, … , NumberN
//0000 0010 1000111 11111111 --> 0001 002 71,255

// checks to see if the incoming string is of format 1 or format 2
int correct_format(char str[]) {
  char reason[50];
  //printf("String is %s\n", str);

  int i, j, count;
  char splitStrings[10][17];

  j = 0; count = 0;
    for (i = 0; i <= strlen(str); i++) {
      //if space, comma, or null found, assign null to splitStrings[count]
      if ((str[i] == ' ') || (str[i] == ',') || (str[i] == '\0')) {
        splitStrings[count][j] ='\0';
        count++;
        j = 0;
      } else {
        splitStrings[count][j] = str[i];
        j++;
      }/*endif*/
    } /* endfor */

    // for(int k = 0; k < count; k++) {
    //   printf("splitStrings[%d]: %s\n", k, splitStrings[k]);
    // }

    // we cannot have the correct format if there are less than 3 fields
    if (count >= 3) {
      // if the string is type 1
      if (strcmp(splitStrings[0], "1") == 0) {
        //checking for decimals by checking for numbers padded with 0s
        for(int i = 2; i < count; i++) {
          if (strlen(splitStrings[i]) > 1) {
            int first_digit = splitStrings[i][0] - '0';
            if (first_digit == 0) {
              printf("members of type 1 should be decimals\n");
              return 0;
            }
          } else {
            printf("I'm a 0\n");
          }
        }
        // if there is more than one entry
        if(atoi(splitStrings[1]) > 1) {
          // check original string for commas
          char *substring = strstr(str, ",");
          if(!substring) {
            // if there are no commas then the format is wrong
            printf("members of type 1 are separated by commas\n");
            return 0;
          }
        }
        // if there is only one entry, or there are no commas the format is right
        return 1;
      } else if (strcmp(splitStrings[0], "0") == 0) { // if first character is a 0
        // check that every single character is not something other than 0 or 1
        for(int i = 0; i < count; i++) {
          for(int j = 0; j < 17; j++) {
            if (isdigit(splitStrings[i][j])) {
              int char_as_int = splitStrings[i][j] - '0';
              if (char_as_int > 1) {
                printf("type 0 should have binary only. %d is not binary\n", char_as_int);
                return 0;
              }
            }
          }
        }
        // check that splitstrings 2 is 1 byte long
        if( strlen(splitStrings[1]) != 8) {
          // if splitStrings[2] is shorter than 1 byte, it's wrong
          printf("the amount of type 0 should be 1 byte long\n");
          return 0;
        }

        // if there is more than one entry
        if (convert_from_binary(splitStrings[1]) > 1) {
          // check that original string has no commas
          char *substring = strstr(str, ",");
          if(substring) {
            // if there are commas then the format is wrong
            printf("members of type 0 should not be comma separated\n");
            return 0;
          }
        }
        // if we get through all that it must be true
      return 1;
    } else { // error the type is neither 0 nor 1
      printf("invalid type. entries can be type 0 or type 1\n");
      return 0;
    }
  } else { // else for if count < 3
    printf("This line has only %d when it should have at least 3\n", count);
    return 0;
  }

}


// converts ascii codes into binary numbers (unpadded)
long convert_to_binary(long decimal_num) {
    long num, remainder, base = 1, binary = 0, no_of_1s = 0;
    num = decimal_num;
    while (num > 0)
    {
        remainder = num % 2;
        /*  To count no.of 1s */
        if (remainder == 1)
        {
            no_of_1s++;
        }
        binary = binary + remainder * base;
        num = num / 2;
        base = base * 10;
    }
    return binary;
}


int convert_from_binary(char binary[]) {
  int  num, binary_val, decimal_val = 0, base = 1, rem;
  unsigned long long sixteen_digit_integer;
  /*checks to see if the number is has a 1 in the 2^16 space.
    integers and longs can't hold 16 digit numbers*/
  if (binary[0] == '1') {
    //manually convert the 16 digit int to a ull
    if (strcmp("111111111111", binary)) {
      sixteen_digit_integer = 1111111111111111;
    } else {
      sixteen_digit_integer = 1111111111111110;
    }
    while ( sixteen_digit_integer > 0)
    {
        rem = sixteen_digit_integer % 10;
        decimal_val = decimal_val + rem * base;
        sixteen_digit_integer = sixteen_digit_integer / 10 ;
        base = base * 2;
    }
  } else {
    binary_val = atoi(binary);
    num = atoi(binary);

    while (num > 0)
    {
        rem = num % 10;
        decimal_val = decimal_val + rem * base;
        num = num / 10 ;
        base = base * 2;
    }
  }
  return decimal_val;
}


/*quick and dirty function that returns the degree of an integer */
int intlen(long x) {
    if(x>=10000000000000000) return 17;
    if(x>=1000000000000000) return 16; //65535 converts to 1111 1111 1111 1111, which has 16 bits
    if(x>=100000000000000) return 15;
    if(x>=10000000000000) return 14;
    if(x>=1000000000000) return 13;
    if(x>=100000000000) return 12;
    if(x>=10000000000) return 11;
    if(x>=1000000000) return 10;
    if(x>=100000000) return 9;
    if(x>=10000000) return 8;
    if(x>=1000000) return 7;
    if(x>=100000) return 6;
    if(x>=10000) return 5;
    if(x>=1000) return 4;
    if(x>=100) return 3;
    if(x>=10) return 2;
    return 1;
}


//no conversion
int type_0_translation(char message[], char output_file_target[]) {
  printf("RUNNING TYPE 0 TRANSLATION\n");
  FILE * output;
  output = fopen(output_file_target,"a");

  if (output == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }
     /* Print each line */
     printf("\nORIGINAL STRING: %s\n", message);
     printf("OUTPUT: %s\n", message);
     fprintf(output, "%s\n", message);

  fclose(output);
  return 0;
}

//convert type binary to decimal with type decimals unchanged
int type_1_translation(char message[], char output_file_target[]) {
   printf("RUNNING TYPE 1 TRANSLATION\n");
   FILE * output;
   char str[60];
   char super_string[60];
   char splitStrings[10][17]; // we can store 10 words of 17 chars
   int super_string_index = 0;
   int i, j, count;

   /* opening file for writing */
   output = fopen(output_file_target,"w");

      int numbers_in_string;
      j = 0; count = 0;
        for (i = 0; i <= strlen(message); i++) {
          //if space or null found, assign null to splitStrings[count]
          if ((message[i] == ' ') || (message[i] == ',') || (message[i] == '\0')) {
            splitStrings[count][j] ='\0';
            count++;
            j = 0;
          } else {
            splitStrings[count][j] = str[i];
            j++;
          }/*endif*/
        } /* endfor */

        //convert only if type 1
        if (strcmp(splitStrings[0],"1") == 0) {
          printf("\nORIGINAL STRING: %s",str);

          //add the new type to the super_string
          strcat(super_string, "0 ");

          char binary_as_string[17];
          for (int i = 1; i < count; i++) {
            //check for the 16 digit numbers before trying to insert into int
            if (strcmp(splitStrings[i],"65535") == 0) {
              strcat(super_string, "1111111111111111 ");
            } else if (strcmp(splitStrings[i],"65534") == 0) {
              strcat(super_string, "1111111111111110 ");
            } else {
              int binary = convert_to_binary(atol(splitStrings[i]));
              //number of 0's we must add
              int padding_required = 16 - intlen(binary);

              switch (padding_required) {
                case 1:
                  sprintf(binary_as_string, "0%i", binary);
                  break;
                case 2:
                  sprintf(binary_as_string, "00%i", binary);
                  break;
                case 3:
                  sprintf(binary_as_string, "000%i", binary);
                  break;
                case 4:
                  sprintf(binary_as_string, "0000%i", binary);
                  break;
                case 5:
                  sprintf(binary_as_string, "00000%i", binary);
                  break;
                case 6:
                  sprintf(binary_as_string, "000000%i", binary);
                  break;
                case 7:
                  sprintf(binary_as_string, "0000000%i", binary);
                  break;
                case 8:
                  sprintf(binary_as_string, "00000000%i", binary);
                  break;
                case 9:
                  sprintf(binary_as_string, "000000000%i", binary);
                  break;
                case 10:
                  sprintf(binary_as_string, "0000000000%i", binary);
                  break;
                case 11:
                  sprintf(binary_as_string, "00000000000%i", binary);
                  break;
                case 12:
                  sprintf(binary_as_string, "000000000000%i", binary);
                  break;
                case 13:
                  sprintf(binary_as_string, "0000000000000%i", binary);
                  break;
                case 14:
                  sprintf(binary_as_string, "00000000000000%i", binary);
                  break;
                case 15:
                  sprintf(binary_as_string, "000000000000000%i", binary);
                  break;
              }
              strcat(super_string, binary_as_string);
              strcat(super_string, " ");
            }/* endif */
          }/* endfor */
        } else { // if type = 0 just copy the string in
          fprintf(output, "%s\n", str);
        }
        printf("CONVERTED STRING:\n%s\n", super_string);
        fprintf(output, "%s\n", super_string);
        /*clear super string */
        memset(super_string,0,strlen(super_string));


   fclose(output);
   return(0);
}

int type_2_translation(char input_file_path[], char output_file_target[]) {
  printf("RUNNING TYPE 2 TRANSLATION\n");
  FILE * fp;
  FILE * output;
  char str[60];
  char splitStrings[10][17]; // we can store 10 words of 17 chars
  char super_string[60];
  char dec_as_string[10];
  fp = fopen(input_file_path , "r");
  output = fopen(output_file_target,"w");
  int i, j, count;

  if(fp == NULL) {
     perror("Error opening file");
     return(-1);
  }

  char temp_dec_as_string[4];
  int space_number = 1;
  while( fgets (str, 60, fp)!=NULL ) {
    printf("\nORIGINAL STRING: %s",str);
  int numbers_in_string;
  j = 0; count = 0;
    for (i = 0; i <= strlen(str); i++) {
      //if space or null found, assign null to splitStrings[count]
      if ((str[i] == ' ') || (str[i] == '\0')) {
        splitStrings[count][j] ='\0';
        count++;
        j = 0;
      } else {
        splitStrings[count][j] = str[i];
        j++;
      }/*endif*/
    } /* endfor */

    //convert only if it's type 0
    if (strcmp(splitStrings[0],"0") == 0) {
        strcat(super_string, "1 ");
        //the number of numbers in the string will be equal to this first one
        numbers_in_string = convert_from_binary(splitStrings[1]);
        //printf("There are %i numbers in the string and %i commas to place\n", numbers_in_string, (numbers_in_string-1));
        int number_of_commas_placed = 0;
        for(i=1; i < count; i++) {
          int dec = convert_from_binary(splitStrings[i]);

          if (i == 1) {
            int padding_required = 3 - intlen(dec);
            if (padding_required == 1) {
              sprintf(dec_as_string, "0%i", dec);
              strcat(super_string, dec_as_string);
            } else if (padding_required == 2) {
              sprintf(dec_as_string, "00%i", dec);
              strcat(super_string, dec_as_string);
            }
          } else {
            sprintf(dec_as_string, "%i", dec);
            strcat(super_string, dec_as_string);
          }
          if (space_number == 1) {
            strcat(super_string, " ");
          } else if ((space_number > 1)
            && (number_of_commas_placed < (numbers_in_string-1))) {
            strcat(super_string, ",");
            number_of_commas_placed++;
          }
          space_number++;
        }/* endfor*/
        fprintf(output, "%s\n", super_string);
        printf("CONVERTED STRING: %s\n", super_string);
        // clear super_string for the next numbers
        memset(super_string,0,strlen(super_string));
        space_number = 1;
      } /*endif*/
      else { //if type = 1 just copy it in
        fprintf(output, "%s\n", str);
      }
    } /*endwhile*/
  fclose(fp);
  fclose(output);
  return 0;
}


int type_3_translation(char input_file_path[], char output_file_target[]) {
  FILE * fp;
  FILE * output;
  char str[60];
  char splitStrings[10][17]; // we can store 10 words of 17 chars
  char super_string[60];
  char dec_as_string[10];
  fp = fopen(input_file_path , "r");
  output = fopen(output_file_target,"w");
  int i, j, count;

  if(fp == NULL) {
     perror("Error opening file");
     return(-1);
  }



  char temp_dec_as_string[4];
  int space_number = 1;
  while( fgets (str, 60, fp)!=NULL ) {
    int numbers_in_string;
    j = 0; count = 0;
    printf("ORIGINAL STRING: %s\n", str);

    // Removing all commas from the string

    //check for the presence of a comma to start
    char *ptr = strchr(str, ',');
    //while there is a Comma
    while(ptr) {
      //printf("\n%s\n", "There are still commas in the string");
      // find its index
      int index = ptr - str;
      //printf("Comma at index %i\n", index);
      // replace the comma with a space
      str[index] = ' ';
      //printf("New string: %s", str);

      //check for commas again
      ptr = strchr(str, ',');
    }

      for (i = 0; i <= strlen(str); i++) {
        //if space or null found, assign null to splitStrings[count]
        if ((str[i] == ' ') || (str[i] == '\0')) {
          splitStrings[count][j] ='\0';
          count++;
          j = 0;
        } else {
          splitStrings[count][j] = str[i];
          j++;
        }/*endif*/
      } /* endfor */

    if (strcmp(splitStrings[0],"0") == 0) {
      printf("\n\nConverting type 0 to type 1\n");
      strcat(super_string, "1 ");
      //the number of numbers in the string will be equal to this first one
      numbers_in_string = convert_from_binary(splitStrings[1]);
      //printf("There are %i numbers in the string and %i commas to place\n", numbers_in_string, (numbers_in_string-1));
      int number_of_commas_placed = 0;
      for(i=1; i < count; i++) {
        int dec = convert_from_binary(splitStrings[i]);

        if (i == 1) {
          int padding_required = 3 - intlen(dec);
          if (padding_required == 1) {
            sprintf(dec_as_string, "0%i", dec);
            strcat(super_string, dec_as_string);
          } else if (padding_required == 2) {
            sprintf(dec_as_string, "00%i", dec);
            strcat(super_string, dec_as_string);
          }
        } else {
          sprintf(dec_as_string, "%i", dec);
          strcat(super_string, dec_as_string);
        }
        if (space_number == 1) {
          strcat(super_string, " ");
        } else if ((space_number > 1)
          && (number_of_commas_placed < (numbers_in_string-1))) {
          strcat(super_string, ",");
          number_of_commas_placed++;
        }
        space_number++;
      }/* endfor*/
      fprintf(output, "%s\n", super_string);
      printf("CONVERTED STRING: %s\n", super_string);
      // clear super_string for the next numbers
      memset(super_string,0,strlen(super_string));
      space_number = 1;
    } else if (strcmp(splitStrings[0],"1") == 0) {
      printf("\n\nConverting type 1 to type 0\n");
      //add the new type to the super_string
      strcat(super_string, "0 ");

      char binary_as_string[17];
      for (int i = 1; i < count; i++) {
        //check for the 16 digit numbers before trying to insert into int
        if (strcmp(splitStrings[i],"65535") == 0) {
          strcat(super_string, "1111111111111111 ");
        } else if (strcmp(splitStrings[i],"65534") == 0) {
          strcat(super_string, "1111111111111110 ");
        } else {
          int binary = convert_to_binary(atol(splitStrings[i]));
          //number of 0's we must add
          int padding_required = 16 - intlen(binary);

          switch (padding_required) {
            case 1:
              sprintf(binary_as_string, "0%i", binary);
              break;
            case 2:
              sprintf(binary_as_string, "00%i", binary);
              break;
            case 3:
              sprintf(binary_as_string, "000%i", binary);
              break;
            case 4:
              sprintf(binary_as_string, "0000%i", binary);
              break;
            case 5:
              sprintf(binary_as_string, "00000%i", binary);
              break;
            case 6:
              sprintf(binary_as_string, "000000%i", binary);
              break;
            case 7:
              sprintf(binary_as_string, "0000000%i", binary);
              break;
            case 8:
              sprintf(binary_as_string, "00000000%i", binary);
              break;
            case 9:
              sprintf(binary_as_string, "000000000%i", binary);
              break;
            case 10:
              sprintf(binary_as_string, "0000000000%i", binary);
              break;
            case 11:
              sprintf(binary_as_string, "00000000000%i", binary);
              break;
            case 12:
              sprintf(binary_as_string, "000000000000%i", binary);
              break;
            case 13:
              sprintf(binary_as_string, "0000000000000%i", binary);
              break;
            case 14:
              sprintf(binary_as_string, "00000000000000%i", binary);
              break;
            case 15:
              sprintf(binary_as_string, "000000000000000%i", binary);
              break;
          }
          strcat(super_string, binary_as_string);
          strcat(super_string, " ");
        }/* endif */
      }/* endfor */
      printf("CONVERTED STRING:\n%s\n", super_string);
      fprintf(output, "%s\n", super_string);
      /*clear super string */
      memset(super_string,0,strlen(super_string));
    }
  } /*endwhile*/
  fclose(fp);
  fclose(output);
  return 0;
}
