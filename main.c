#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>


int v(int n, int* opened, FILE** origin_file, int* lines_count, int* symbol_count, char line[], int symbols) {

    FILE* arrayViewFile = fopen("arrayViewFile.txt", "w");
    FILE* local_subor;
    if (n == 0) {
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

            int ryad = 1;
            //check all the stuffffff
            int i = 1, errors = 0, counter = 0, plus = 0;
            int number2chet = 0, number2nechet = 0;
            char symb6;
            int hours = 0, minutes = 0;
            int year = 0, month = 0, day = 0;
            char chn = getc(local_subor);
            while (chn != EOF) { //&& errors == 0
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
                    i++;
                    if (i == 9) {
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
                            printf("Error line %d, > 150 symbols\n", ryad);

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
                        else if (counter == 1) {
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
                int symbols = 0;
                *lines_count = ryad;
                if ((ryad + 1) % 9 == 0) {
                    //output from file
                    printf("Prezenter:                   ");
                    i = 1;
                    rewind(local_subor);
                    char ch = getc(local_subor);
                    while (ch != EOF) {
                        if (ch == '\n') {
                            if (i != 8) {
                                fprintf(arrayViewFile, ".");
                                symbols++;
                            }
                            i++;
                            if (i == 9) {
                                i = 1;
                                ch = getc(local_subor);
                                printf("\n");
                                fprintf(arrayViewFile, "/");
                                symbols++;
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
                            symbols++;
                            fprintf(arrayViewFile, "%c", ch);
                        }
                        ch = getc(local_subor);
                    }
                    printf("\n\n\nOpened successfuly, %d lines readed\n\n", *lines_count);
                    *symbol_count = symbols;
                }
            }
            else {
                printf("Error, not enough lines\n");
            }
        }
        return 0;
    }
    else {
        int nazov = 1;
        if (line != NULL) {
            printf("Prezenter:                   ");
            //printf("Output from dyynamic array\n");
            for (int i = 0; i < symbols; i++) {
                if (line[i] == '/') {
                    printf("\n\n");
                    nazov = 1;
                    printf("Prezenter:                   ");
                }
                else if (line[i] == '.') {
                    printf("\n");
                    nazov++;
                    if (nazov == 2) printf("Rodne cislo:                 ");
                    else if (nazov == 3) printf("Kod prezentacnej miestnosti: ");
                    else if (nazov == 4) printf("Nazov prispevku:             ");
                    else if (nazov == 5) printf("Mena autorov:                ");
                    else if (nazov == 6) printf("Typ prezentovania:           ");
                    else if (nazov == 7) printf("Cas prezentovania:           ");
                    else if (nazov == 8) printf("Datum:                       ");
                }
                else printf("%c", line[i]);
            }
        }
        return 0;
    }
}

char* n(int symbol_count, int* n_used)
{
    FILE* subor = fopen("konferencny_zoznam.txt", "r");
    char* local_line = (char*)calloc(symbol_count, sizeof(char));
    int i = 1, first = 1, j = 0;
    char ch = getc(subor);

    while (ch != EOF && j < symbol_count) {
        if (ch == '\n') {
            if (i != 8) {
                char point = '.';
                local_line[j] = point;
                j++;
            }
            i++;
            if (i == 9) {
                i = 1;
                ch = getc(subor);
                char slesh = '/';
                local_line[j] = slesh;
                j++;
            }
        }
        else {
            local_line[j] = ch;
            j++;
        }
        ch = getc(subor);
    }
    *n_used = 1;
    printf("%d symbols writed to dynamic array\n", symbol_count);
    return local_line;
}

void o(int n, int opened, char line[], FILE* file, int lines_count) {


    if (opened == 1) {
        int date;
        char kod[4];

        scanf("%d %s", &date, kod);

        //choto delaem
        int blocks = (lines_count + 1) / 9;
        int* times = (int*)calloc(blocks, sizeof(int));
        int* dates = (int*)calloc(blocks, sizeof(int));
        char** kodes = (char**)calloc(blocks, sizeof(char*));
        for (int i = 0; i < blocks; i++) {
            kodes[i] = (char*)calloc(3, sizeof(char));
        }
        char** vars = (char**)calloc(blocks, sizeof(char*));
        for (int i = 0; i < blocks; i++) {
            vars[i] = (char*)calloc(2, sizeof(char));
        }
        char** names = (char**)calloc(blocks, sizeof(char*));
        for (int i = 0; i < blocks; i++) {
            names[i] = (char*)calloc(50, sizeof(char));
        }
        char** jobs = (char**)calloc(blocks, sizeof(char*));
        for (int i = 0; i < blocks; i++) {
            jobs[i] = (char*)calloc(200, sizeof(char));
        }


        //vivod s faila
        if (file == NULL) {
            printf("Neotvoreny subor\n");
        }
        else {
            rewind(file);
            char current_line[200];
            fgets(current_line, 200, file);
            int line_number = 0, block_number = 0;
            //filling arrays

            do {
                if (line_number == 9) {
                    line_number = 0;
                    block_number++;
                }

                if (line_number == 0) {
                    //name
                    current_line[strlen(current_line) - 1] = NULL;
                    strcpy(names[block_number], current_line);
                }
                else if (line_number == 2) {
                    //kod
                    current_line[3] = NULL;
                    strcpy(kodes[block_number], current_line);
                }
                else if (line_number == 3) {
                    //job
                    current_line[strlen(current_line) - 1] = NULL;
                    strcpy(jobs[block_number], current_line);
                }
                else if (line_number == 5) {
                    //tam gde 4 varianta
                    current_line[2] = NULL;
                    strcpy(vars[block_number], current_line);
                }
                else if (line_number == 6) {
                    //time
                    times[block_number] = atoi(current_line);
                }
                else if (line_number == 7) {
                    //date
                    dates[block_number] = atoi(current_line);//filtering
                }

                fgets(current_line, 200, file);
                line_number++;
            } while (!feof(file));
            //last line as date
            dates[blocks - 1] = atoi(current_line);

            //filtering
            int finded = 0;
            int temp1, temp2;
            for (int i = 0; i < blocks; i++) {
                if (dates[i] == date && (strcmp(kodes[i], kod) == 0)) {
                    temp1 = dates[i], temp2 = times[i];
                    char* temmp1 = kodes[i];
                    char* temmp2 = vars[i];
                    char* temmp3 = names[i];
                    char* temmp4 = jobs[i];
                    dates[i] = dates[finded];
                    times[i] = times[finded];
                    kodes[i] = kodes[finded];
                    vars[i] = vars[finded];
                    names[i] = names[finded];
                    jobs[i] = jobs[finded];
                    dates[finded] = temp1;
                    times[finded] = temp2;
                    kodes[finded] = temmp1;
                    vars[finded] = temmp2;
                    names[finded] = temmp3;
                    jobs[finded] = temmp4;

                    finded++;
                }
            }

            if (finded != 0) {
                int min = times[0], min_j = 0;
                for (int i = 0; i < finded - 1; i++) {
                    min = times[i], min_j = i;
                    for (int j = i; j < finded; j++) {
                        if (times[j] < min) {
                            min_j = j;
                            min = times[j];
                        }
                    }

                    if (i != min_j) {
                        //swap
                        temp1 = dates[i], temp2 = times[i];
                        char* temmp1 = kodes[i];
                        char* temmp2 = vars[i];
                        char* temmp3 = names[i];
                        char* temmp4 = jobs[i];
                        dates[i] = dates[min_j];
                        times[i] = times[min_j];
                        kodes[i] = kodes[min_j];
                        vars[i] = vars[min_j];
                        names[i] = names[min_j];
                        jobs[i] = jobs[min_j];
                        dates[min_j] = temp1;
                        times[min_j] = temp2;
                        kodes[min_j] = temmp1;
                        vars[min_j] = temmp2;
                        names[min_j] = temmp3;
                        jobs[min_j] = temmp4;
                    }
                }



                //output
                //for U first
                for (int i = 0; i < finded; i++) {
                    if (vars[i][0] == 'U') {
                        if (times[i] < 1000) {
                            printf("0");
                        }

                        printf("%d %s\t%s\t %s\n", times[i], vars[i], names[i], jobs[i]);
                        if (i == finded - 1) printf("\n");
                    }
                }
                //for P first
                for (int i = 0; i < finded; i++) {
                    if (vars[i][0] == 'P') {
                        if (times[i] < 1000) {
                            printf("0");
                        }

                        printf("%d %s\t%s\t %s\n", times[i], vars[i], names[i], jobs[i]);
                    }
                }
            }
            else {
                printf("No elements finded\n");
            }
        }


    }
    else {
        printf("No file opened yet, write v to open file\n");
    }
}

void s(int opened, int n, char line[], int symbols)
{
    if (opened == 0) {
        printf("Neotvoreny subor!\n");
        return;
    }
    else {
        if (n == 0) {
            printf("Polia nie su vytvorene\n");
            return;
        }
        else {
            char datum[9];
            char typ[2];
            scanf("%s %s", datum, typ);
            //searching for right blocks

            char date[8]; int date_l = 8;
            char kod[2]; int kod_l = 2;
            char time[4]; int time_l = 4;
            char name[50]; int name_l = 0;
            char job[150]; int job_l = 0;

            int dot_num = 1, j = 0, date_finded = 0, kod_finded = 0;
            int nothing_finded = 1;

            for (int i = 0; i < symbols; i++) {
                if (line[i] == '/' || i == symbols - 1) {
                    j = 0;
                    dot_num = 1;

                    if (date_finded == 0 && kod_finded == 0) {
                        nothing_finded = 0;
                        for (int k = 0; k < time_l; k++) {
                            printf("%c", time[k]);
                        }
                        printf("  ");
                        for (int k = 0; k < name_l; k++) {
                            printf("%c", name[k]);
                        }
                        printf("  ");
                        for (int k = 0; k < job_l; k++) {
                            printf("%c", job[k]);
                        }
                        printf("\n");
                    }
                    date_finded = 0; kod_finded = 0;
                }
                else if (line[i] == '.') {
                    if (dot_num == 1) {
                        name_l = j;
                    }
                    else if (dot_num == 4) {
                        job_l = j;
                    }

                    j = 0;
                    dot_num++;
                }
                else {
                    if (dot_num == 1) {
                        name[j] = line[i];
                        j++;
                    }
                    else if (dot_num == 4) {
                        job[j] = line[i];
                        j++;
                    }
                    else if (dot_num == 6) {
                        kod[j] = line[i];
                        if (typ[j] != kod[j]) kod_finded = -1;
                        j++;
                    }
                    else if (dot_num == 7) {

                        time[j] = line[i];
                        j++;
                    }
                    else if (dot_num == 8) {
                        date[j] = line[i];
                        if (datum[j] != date[j]) date_finded = -1;
                        j++;
                    }
                }


            }
            if (nothing_finded == 1) {
                printf("Nothing found\n");
            }

        }
    }
}

char* p(int opened, int n, int symbols, char line[], int lines_count) {

    if (opened == 0) {
        printf("Neotvoreny subor!\n");
        return;
    }
    else {
        if (n == 0) {
            printf("Polia nie su vytvorene\n");
            return;
        }
        else {

            char chislo[10];
            scanf("%s", chislo);
            //searching for right blocks

            int blocks = (lines_count + 1) / 9;
            char** names = (char**)calloc(blocks, sizeof(char*));
            for (int i = 0; i < blocks; i++) {
                names[i] = (char*)calloc(50, sizeof(char));
            }
            char** rodni = (char**)calloc(blocks, sizeof(char*));
            for (int i = 0; i < blocks; i++) {
                rodni[i] = (char*)calloc(10, sizeof(char));
            }
            char** kodes = (char**)calloc(blocks, sizeof(char*));
            for (int i = 0; i < blocks; i++) {
                kodes[i] = (char*)calloc(3, sizeof(char));
            }
            char** jobs = (char**)calloc(blocks, sizeof(char*));
            for (int i = 0; i < blocks; i++) {
                jobs[i] = (char*)calloc(200, sizeof(char));
            }
            char** stuff = (char**)calloc(blocks, sizeof(char*));
            for (int i = 0; i < blocks; i++) {
                stuff[i] = (char*)calloc(200, sizeof(char));
            }
            char** vars = (char**)calloc(blocks, sizeof(char*));
            for (int i = 0; i < blocks; i++) {
                vars[i] = (char*)calloc(2, sizeof(char));
            }
            char** times = (char**)calloc(blocks, sizeof(char*));
            for (int i = 0; i < blocks; i++) {
                times[i] = (char*)calloc(4, sizeof(char));
            }
            char** dates = (char**)calloc(blocks, sizeof(char*));
            for (int i = 0; i < blocks; i++) {
                dates[i] = (char*)calloc(8, sizeof(char));
            }
            
            int current_block = 0, j = 0, dot_pos = 1;
            for (int i = 0; i < symbols; i++) {
                if (line[i] == '/') {
                    current_block++;
                    j = 0;
                    dot_pos = 1;
                }
                else if(line[i] == '.') {
                    dot_pos++;
                    j = 0;
                }
                else {
                    if (dot_pos == 1) {
                        names[current_block][j] = line[i]; j++;
                    }
                    else if (dot_pos == 2) {
                        rodni[current_block][j] = line[i]; j++;
                    }
                    else if (dot_pos == 3) {
                        kodes[current_block][j] = line[i]; j++;
                    }
                    else if (dot_pos == 4) {
                        jobs[current_block][j] = line[i]; j++;
                    }
                    else if (dot_pos == 5) {
                        stuff[current_block][j] = line[i]; j++;
                    }
                    else if (dot_pos == 6) {
                        vars[current_block][j] = line[i]; j++;
                    }
                    else if (dot_pos == 7) {
                        times[current_block][j] = line[i]; j++;
                    }
                    else if (dot_pos == 8) {
                        dates[current_block][j] = line[i]; j++;
                    }
                }
            }
            int counter = 1;
            for (int i = 0; i < blocks; i++) {
                if (strcmp(rodni[i], chislo) == 0) {
                    printf("%d\t%s\t %s\n", counter, names[i], jobs[i]);
                    counter++;
                }
            }
            if (counter == 1) {
                printf("Nothing found\n");
                return line;
            }

            char* result_line = (char*)calloc(symbols, sizeof(char));
            int choise; char kod[3]; char var[2]; char time[4]; char date[8]; char ch[10];strcpy(ch, chislo);
            scanf("%d %s %s %s %s", &choise, kod, var, time, date);
            

            int error = 0;
            int h1 = (time[0] - '0'); int h2 = (time[1] - '0'); int mi1 = (time[2] - '0'); int mi2 = (time[3] - '0'); int mo1 = (dates[4] - '0'); int mo2 = (dates[5] - '0'); int d1 = (time[6] - '0');int d2 = (time[7] - '0');
            int _hours = h1 * 10 + h2, _minutes = mi1 * 10 + mi2, _month = mo1 * 10 + mo2, _day = d1 * 10 + d2;
            if (choise > counter - 1) {
                error = 1;
                printf("Wrong number of participant\n");
            }
            else if (!isupper(kod[0])) {
                error = 1;
                printf("first code letter not upper\n");
            }
            else if (!isdigit(kod[1])) {
                error = 1;
                printf("second code character not digit\n");
            }
            else if (!isdigit(kod[2])) {
                error = 1;
                printf("third code charcater not digit\n");
            }
            else if (strcmp(var, "UP") != 0) {
                if (strcmp(var, "PP") != 0) {
                    if (strcmp(var, "UD") != 0) {
                        if (strcmp(var, "PD") != 0) {
                            error = 1;
                            printf("wrong presentation type\n");
                        }
                    }
                }
            }
            else if (_hours > 23 || _minutes > 59) {
                error = 1;
                printf("wrong time format\n");
            }
            else if (_month > 12 || _day > 31) {
                error = 1;
                printf("wrong date format\n");
            }

            if(error == 0) {
                int current_symbol = 0; int xd = 0;
                for (int i = 0; i < blocks; i++) {
                    if (current_symbol < symbols) {
                        if (strcmp(rodni[i], ch) == 0) {
                            xd++;
                        }
                        for (int l = 0; l < strlen(names[i]); l++) {
                            result_line[current_symbol] = names[i][l];
                            current_symbol++;
                        }
                        result_line[current_symbol] = '.'; current_symbol++;
                        for (int l = 0; l < strlen(rodni[i]); l++) {
                            result_line[current_symbol] = rodni[i][l];
                            current_symbol++;
                        }
                        result_line[current_symbol] = '.'; current_symbol++;
                        if (xd!= choise) {
                            
                            for (int l = 0; l < 3; l++) {
                                result_line[current_symbol] = kodes[i][l];
                                current_symbol++;
                            }
                        }
                        else {
                            for (int l = 0; l < 3; l++) {
                                result_line[current_symbol] = kod[l];
                                current_symbol++;
                            }
                        }
                        result_line[current_symbol] = '.'; current_symbol++;
                        for (int l = 0; l < strlen(jobs[i]); l++) {
                            result_line[current_symbol] = jobs[i][l];
                            current_symbol++;
                        }
                        result_line[current_symbol] = '.'; current_symbol++;
                        for (int l = 0; l < strlen(stuff[i]); l++) {
                            result_line[current_symbol] = stuff[i][l];
                            current_symbol++;
                        }
                        result_line[current_symbol] = '.'; current_symbol++;
                        if (xd != choise) {
                            for (int l = 0; l < 2; l++) {
                                result_line[current_symbol] = vars[i][l];
                                current_symbol++;
                            }
                        }
                        else {
                            for (int l = 0; l < 2; l++) {
                                result_line[current_symbol] = var[l];
                                current_symbol++;
                            }
                        }
                        result_line[current_symbol] = '.'; current_symbol++;
                        if (xd != choise) {
                            for (int l = 0; l < 4; l++) {
                                result_line[current_symbol] = times[i][l];
                                current_symbol++;
                            }
                        }
                        else {
                            for (int l = 0; l < 4; l++) {
                                result_line[current_symbol] = time[l];
                                current_symbol++;
                            }
                        }
                        result_line[current_symbol] = '.'; current_symbol++;
                        if (xd != choise) {
                            for (int l = 0; l < 8; l++) {
                                result_line[current_symbol] = dates[i][l];
                                current_symbol++;
                            }
                        }
                        else {
                            for (int l = 0; l < 8; l++) {
                                result_line[current_symbol] = date[l];
                                current_symbol++;
                            }
                        }
                        if (symbols - current_symbol > 5) {
                            result_line[current_symbol] = '/'; current_symbol++;
                        }
                        
                    }
                    
                }
                printf("Modified successfuly\n");
                return result_line;
            }
            else {
                printf("Wrong input\n");
                return line;
            }
        }
    }
}

void h(int _n, int symbols, char line[])
{
    if (_n == 0) {
        printf("Polia nie su vytvorene!\n");
        return;
    }
    else {
        int rcislo[4];
        rcislo[3] ='\0';
        char group[3];
        group[2] = '\0';
        int daname = 1, j = 0;
        int age1;
        int age2;
        int groupUP = 0, groupUD = 0, groupPP = 0, groupPD = 0;
        printf("GAY \t\tUP\tUD\tPP\tPD\n");
        for (int t = 0; t < 10; t++)
        {
            age1 = 1;
            age2 = 4;
            for (int i = 0; i < symbols; i++) {
                if (line[i] == '/') daname = 1;
                else if (line[i] == '.') daname++;
                else {

                    if (daname == 2) {
                        rcislo[j] = line[i];
                        j++;
                    }
                    if (rcislo[2] > '1') {
                        if (daname == 6) {
                            group[j] = line[i];
                            j++;
                        }if (strcmp(group, "UP") == 0) groupUP++;
                        else if (strcmp(group, "UD") == 0) groupUD++;
                        else if (strcmp(group, "PP") == 0) groupPP++;
                        else if (strcmp(group, "PD") == 0) groupPD++;

                    }
                }
            }
            printf("%dr - %dr:\t%d\t%d\t%d\t%d\n", age1, age2, groupUP, groupUD, groupPP, groupPD);
            groupUP = 0; groupUD = 0; groupPP = 0; groupPD = 0;
        }
        printf("Muzi\t\tUP\tUD\tPP\tPD\n");

        for (int t = 0; t < 10; t++) {
            age1 = t * 10;
            age2 = age1 + 9;
            for (int i = 0; i < symbols; i++) {
                if (line[i] == '/') daname = 1;
                else if (line[i] == '.') daname++;
                else {

                    if (daname == 2) {
                        rcislo[j] = line[i];
                        j++;
                    }
                    if (rcislo[2] > '1') {
                        if (daname == 6) {
                            group[j] = line[i];
                            j++;
                        }if (strcmp(group, "UP") == 0) groupUP++;
                        else if (strcmp(group, "UD") == 0) groupUD++;
                        else if (strcmp(group, "PP") == 0) groupPP++;
                        else if (strcmp(group, "PD") == 0) groupPD++;

                    }
                }
            }
            printf("%dr - %dr:\t%d\t%d\t%d\t%d\n", age1, age2, groupUP, groupUD, groupPP, groupPD);
            groupUP = 0; groupUD = 0; groupPP = 0; groupPD = 0;
        }
        printf("\nZeni\t\tUP\tUD\tPP\tPD\n");
        for (int t = 0; t < 10; t++) {
            age1 = t * 10;
            age2 = age1 + 9;
            for (int i = 0; i < symbols; i++) {
                if (line[i] == '/') daname = 1;
                else if (line[i] == '.') daname++;
                else {

                    if (daname == 2) {
                        rcislo[j] = line[i];
                        j++;
                    }
                    if (rcislo[2] > '1') {
                        if (daname == 6) {
                            group[j] = line[i];
                            j++;
                        }if (strcmp(group, "UP") == 0) groupUP++;
                        else if (strcmp(group, "UD") == 0) groupUD++;
                        else if (strcmp(group, "PP") == 0) groupPP++;
                        else if (strcmp(group, "PD") == 0) groupPD++;

                    }
                }
            }
            printf("%dr - %dr:\t%d\t%d\t%d\t%d\n", age1, age2, groupUP, groupUD, groupPP, groupPD);
            groupUP = 0; groupUD = 0; groupPP = 0; groupPD = 0;
        }
    }
}

int main()
{
    FILE* subor = fopen("konferencny_zoznam.txt", "r");
    char command;
    int _n = 0, opened = 0;
    int lines_counter = 0, symbol_counter = 0, symbols = 0;


    char* line = (char*)calloc(10000, sizeof(char));



    do
    {
        if (symbol_counter != 0) { symbols = symbol_counter; }
        scanf("%c", &command);

        if (command == 'v')
        {
           // system("cls");
            v(_n, &opened, &subor, &lines_counter, &symbol_counter, line, symbols);
            printf("\n");
        }
        else if (command == 'n') {
            if (opened == 1) {
                line = (char*)realloc(line, symbol_counter);
                line = n(symbol_counter, &_n);

            }
            else {
                printf("No file opened yet, write v to open file\n");
            }
        }
        else if (command == 'k')
        {
            free(line);
            return 0;
        }
        else if (command == 'o') {
            o(_n, opened, line, subor, lines_counter);
        }
        else if (command == 's') {
            s(opened, _n, line, symbols);
        }
        else if (command == 'p') {
            line = p(opened, _n, symbols, line, lines_counter);
        }
        else if (command == 'h') {
            h(_n, symbols, line);
        }
    } while (1);
    fclose(subor);
    return 0;
}
