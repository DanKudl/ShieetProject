#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "functions.h"
#include "functions.c"
#include <stdlib.h>

int v(int n, int* opened, FILE** origin_file, int* lines_count)
{
    FILE* local_subor;
    if (*opened == 0) {
        local_subor = fopen("konferencny_zoznam.txt", "r");
        if (local_subor == NULL)
        {
            printf("Neotvoreny subor(ne otkrilos)\n");
            return 1;
        }
        else if (local_subor != NULL)
        {
            *opened = 1;
            *origin_file = local_subor;

            if (n == 0)
            {
                int ryad = 1;
                //check all the stuffffff
                int i = 1, errors = 0, counter = 0, plus = 0;
                int number2chet = 0, number2nechet = 0;
                char symb6;
                int hours = 0, minutes = 0;
                int year = 0, month = 0, day = 0;
                char chn = getc(local_subor);
                while (chn != EOF ) { //&& errors == 0
                    if (chn == '\n') {
                        ryad++;
                        //errors check esli malo symvolov
                        if (i == 2) {
                            if (counter < 10) {
                                errors = 2;
                                printf("Error line %d, < 10 symbols\n", ryad);
                                
                            }
                        }
                        else if (i == 3) {
                            if (counter < 3) {
                                errors = 3;
                                printf("Error line %d, < 3 symbols\n", ryad);
                                
                            }
                        }
                        else if (i == 6) {
                            if (counter < 2) {
                                errors = 6;
                                printf("Error line %d, < 2 symbols\n", ryad);
                                
                            }
                        }
                        else if (i == 7) {
                            if (counter < 3) {
                                errors = 7;
                                printf("Error line %d, < 4 symbols\n", ryad);
                                
                            }
                        }
                        else if (i == 8) {
                            if (counter < 7) {
                                errors = 8;
                                printf("Error line %d, < 8 symbols\n", ryad);
                                
                            }
                        }

                        //obnulenie
                        counter = 0;
                        number2chet = 0; number2nechet = 0;
                        hours = 0; minutes = 0;
                        year = 0; month = 0; day = 0;

                        //sleduyushii ryad
                        i++; if (i == 9) {
                            i = 1;
                            chn = getc(local_subor);
                            ryad++;
                        }
                    }
                    else {
                        if (i == 1) {
                            
                            if ((!isalpha(chn) && chn != ' ')) {
                                errors = 1;
                                printf("Error line %d, spec simvol v imeni\n", ryad);
                                
                            }
                            if (counter >= 50) {
                                errors = 1;
                                printf("Error line %d, name > 50 symbols\n", ryad);
                                
                            }
                        }
                        else if (i == 2) {
                            if (!isdigit(chn) && chn != '\n') {
                                errors = 2;
                                printf("Error line %d, bad symbol %c\n", ryad, chn);
                                
                            }
                            else {
                                if (counter != 9) {
                                    if (counter % 2 == 0) {
                                        number2chet += chn - '0';
                                    }
                                    else {
                                        number2nechet += chn - '0';
                                    }
                                }
                                if (counter == 9) {
                                    if (counter % 2 == 0) {
                                        number2chet += chn - '0';
                                    }
                                    else {
                                        number2nechet += chn - '0';
                                    }

                                    if (number2chet != number2nechet && abs(number2chet - number2nechet) != 11) {
                                        errors = 2;
                                        printf("Error line %d, numb%11!=0\n", ryad);
                                        
                                    }
                                }
                            }
                            if (counter > 9) {
                                errors = 2;
                                printf("Error line %d, > 10 numbers\n", ryad);
                                
                            }
                        }
                        else if (i == 3) {
                            if (counter < 3) {
                                if (isalpha(chn)) {
                                    if (!isupper(chn)) {
                                        errors = 3;
                                        printf("Error line %d, symbol %c isnt upper\n", ryad, chn);
                                        
                                    }
                                }
                            }
                            else {
                                errors = 3;
                                printf("Error line %d, > 3 symbols\n", ryad);
                               
                            }
                        }
                        else if (i == 4) {
                            if (counter > 149) {
                                errors = 4;
                                printf("Error line %d, > 150 symbols\n",ryad);
                                
                            }
                        }
                        else if (i == 5) {
                            if (counter > 199) {
                                errors = 5;
                                printf("Error line %d, > 200 symbols\n", ryad);
                                
                            }
                            if (!isalpha(chn) && chn != ' ' && chn != '#') {
                                errors = 5;
                                printf("Error line %d, unexpected symbol %c\n", ryad, chn);
                                
                            }
                        }
                        else if (i == 6) {
                            //PD, PP, UD, UP
                            if (counter == 0) {
                                symb6 = chn;
                            }
                            else if(counter == 1) {
                                if ((symb6 == 'P' && chn == 'D') || (symb6 == 'P' && chn == 'P') || (symb6 == 'U' && chn == 'D') || (symb6 == 'U' && chn == 'P')) {
                                     //idk   
                                }
                                else {
                                    errors = 6;
                                    printf("Error line %d, wrong code (%c%c)\n", ryad, symb6, chn);
                                }
                            }
                            else if (counter > 1) {
                                errors = 6;
                                printf("Error line %d, > 2 symbols\n", ryad);
                               
                            }
                        }
                        else if (i == 7) {
                            if (counter > 3) {
                                errors = 7;
                                printf("Error line %d, > 4 symbols\n", ryad);
                                
                            }
                            else {
                                if (counter == 0) {
                                    hours += (chn - '0') * 10;
                                }
                                else if (counter == 1) {
                                    hours += (chn - '0');
                                }

                                if (counter == 2) {
                                    minutes += (chn - '0') * 10;
                                }
                                else if (counter == 3) {
                                    minutes += (chn - '0');

                                    //checks
                                    if (hours > 23 || minutes > 59) {
                                        errors = 7;
                                        printf("Error line %d, wrong time format\n", ryad);
                                        
                                    }

                                }
                            }
                        }
                        else if (i == 8) {
                            if (counter > 7) {
                                errors = 8;
                                printf("Error line %d, > 8 symbols\n", ryad);
                                
                            }
                            else {
                                if (counter == 0) {
                                    year += (chn - '0') * 1000;
                                }
                                else if (counter == 1) {
                                    year += (chn - '0') * 100;
                                }
                                else if (counter == 2) {
                                    year += (chn - '0') * 10;
                                }
                                else if (counter == 3) {
                                    year += (chn - '0');
                                }
                                else if (counter == 4) {
                                    month += (chn - '0') * 10;
                                }
                                else if (counter == 5) {
                                    month += (chn - '0');
                                }
                                else if (counter == 6) {
                                    day += (chn - '0') * 10;
                                }
                                else if (counter == 7) {
                                    day += (chn - '0');

                                    if (day > 31 || month > 12) {
                                        errors = 8;
                                        printf("Error line %d, wrong data format\n", ryad);
                                        
                                    }
                                }
                            }
                        }
                        counter++;
                    }
                    chn = getc(local_subor);
                }

               
                
                //output
                if (errors == 0) {
                    *lines_count = ryad;
                    if ((ryad + 1) % 9 == 0) {
                        //output from file
                        printf("Prezenter:                   ");
                        i = 1;
                        rewind(local_subor);
                        char ch = getc(local_subor);
                        while (ch != EOF) {
                            if (ch == '\n') {
                                i++; if (i == 9) {
                                    i = 1;
                                    ch = getc(local_subor);
                                    printf("\n");
                                }
                                printf("\n");
                                if (i == 1 && !feof(local_subor)) printf("Prezenter:                   ");
                                else if (i == 2) printf("Rodne cislo:                 ");
                                else if (i == 3) printf("Kod prezentacnej miestnosti: ");
                                else if (i == 4) printf("Nazov prispevku:             ");
                                else if (i == 5) printf("Mena autorov:                ");
                                else if (i == 6) printf("Typ prezentovania:           ");
                                else if (i == 7) printf("Cas prezentovania:           ");
                                else if (i == 8) printf("Datum:                       ");
                            }
                            else {
                                printf("%c", ch);
                            }
                            ch = getc(local_subor);
                        }
                        printf("\n\n\nOpened successfuly, %d lines readed\n\n", *lines_count);
                    }
                }
                else {
                    printf("Error, not enough lines\n");
                }
                
            }
            else if (n == 1)
            {
                //output from dynamic arrays   
            }

        }
        return 0;
    }
    else {
        printf("v alreay used!\n");
        //output from dynamic arrays
    }
}

    int o()
    {
        
    }
    int n(char*** lines, FILE** file)
    {
        //write lines to array there


    }
    int s()
    {

    }
    int h()
    {

    }
    int p()
    {

    }
    int z()
    {

    }
    int k()
    {

}



int main()
{
    FILE* subor;
    char command;
    int _n = 0, opened = 0;
    int lines_counter = 0;


    char** lines;

    do
    {
        scanf("%c", &command);
        if (command == 'v')
        {
            v(_n, &opened, &subor, &lines_counter);
            printf("\n");
        }
        if (command == 'o')
        {
            o();
            printf("\n");
        }
        if (command == 'n') {
            if (opened) {
                n(&lines, &subor);
            }
            else {
                printf("No file opened yet, write v to open file");
            }
            printf("\n");
        }
        if (command == 'c')//DELETETHEN
        {
            opened = 0;
        }
        if (command == 'k')
        {
            return 0;
        }
    } while (1);
    fclose(subor);
    return 0;
}

