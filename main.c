#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>


int v(int n, int* opened, FILE** origin_file, int* lines_count, int* symbol_count, char line[], int symbols) {

    FILE* local_subor;                                                                          //zavedieme FILE pre konferencny zoznam
    if (n == 0) {                                                                               //ak n este ne bolo stlacene d'alej bude overenie udajov a vypis s suboru
        local_subor = fopen("konferencny_zoznam.txt", "r");
        if (local_subor == NULL)                                                                //ak subor nepodari otvorit vipise spravu,odriadkuje a ukonci funkciu
        {
            printf("Neotvoreny subor\n");
            return 1;
        }
        else if (local_subor != NULL)
        {
            *opened = 1;
            *origin_file = local_subor;

            int ryad = 1;
            //overime kazdy ret'azec, zavedieme premmenny pre overenie
            int i = 1, errors = 0, counter = 0, plus = 0;
            int number2chet = 0, number2nechet = 0;
            char symb6;
            int hours = 0, minutes = 0;
            int year = 0, month = 0, day = 0;
            char chn = getc(local_subor);

            while (chn != EOF) {                                                        //&& errors == 0
                if (chn == '\n') {
                    ryad++;
                    //overenie udajov na chybu symbolov, kde i - cislo ret'azca kazdeho bloku(i = 1 - prezentor; i=2 - rodne cislo a tak dalej)
                    if (i == 2) {
                        if (counter < 9) {
                            errors = 2;
                            printf("%d. Nekorektne zadany vstup: rodne cislo\n", ryad);

                        }
                    }
                    else if (i == 3) {
                        if (counter < 3) {
                            errors = 3;
                            printf("%d. Nekorektne zadany vstup: kod prezentacnej miestmosti\n", ryad);

                        }
                    }
                    else if (i == 6) {
                        if (counter < 2) {
                            errors = 6;
                            printf("%d. Nekorektne zadany vstup: typ prezentovania\n", ryad);

                        }
                    }
                    else if (i == 7) {
                        if (counter < 3) {
                            errors = 7;
                            printf("%d. Nekorektne zadany vstup: cas\n", ryad);

                        }
                    }
                    else if (i == 8) {
                        if (counter < 7) {
                            errors = 8;
                            printf("%d. Nekorektne zadany vstup: datum\n", ryad);

                        }
                    }

                    //nulovanie premmenych 
                    counter = 0;
                    number2chet = 0; number2nechet = 0;
                    hours = 0; minutes = 0;
                    year = 0; month = 0; day = 0;

                    //nasledujuci blok udajov(ryad = cislo riadka)
                    i++;
                    if (i == 9) {
                        i = 1;
                        chn = getc(local_subor);
                        ryad++;
                    }
                }
                else {
                    if (i == 1) {

                        if ((!isalpha(chn) && chn != ' ')) {                            //pouzijeme isalpha, isdigit pre overenie na cislo alebo na list 
                            errors = 1;
                            printf("%d. Nekorektne zadany vstup: meno\n", ryad);

                        }
                        if (counter >= 50) {                                            //counter zvazuje kolko bolo charov v riadku
                            errors = 1;
                            printf("%d. Nekorektne zadany vstup: rodne meno\n", ryad);

                        }
                    }
                    else if (i == 2) {
                        if (!isdigit(chn) && chn != '\n') {
                            errors = 2;
                            printf("%d. Nekorektne zadany vstup: rodne cislo\n", ryad);

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

                                if (number2chet != number2nechet && abs(number2chet - number2nechet) % 11 != 0) {
                                    errors = 2;
                                    printf("%d. Nekorektne zadany vstup: rodne cislo(%d - %d)\n", ryad, number2chet, number2nechet);

                                }
                            }
                        }
                        if (counter > 9) {
                            errors = 2;
                            printf("%d. Nekorektne zadany vstup: rodne cislo\n", ryad);

                        }
                    }
                    else if (i == 3) {
                        if (counter < 3) {
                            if (isalpha(chn)) {
                                if (!isupper(chn)) {
                                    errors = 3;
                                    printf("%d. Nekorektne zadany vstup: kod prezentacnej miestnosti\n", ryad);

                                }
                            }
                        }
                        else {
                            errors = 3;
                            printf("%d. Nekorektne zadany vstup: kod prezentacnej miestnosti\n", ryad);

                        }
                    }
                    else if (i == 4) {
                        if (counter > 149) {
                            errors = 4;
                            printf("%d. Nekorektne zadany vstup: nazov prispevku\n", ryad);

                        }
                    }
                    else if (i == 5) {
                        if (counter > 199) {
                            errors = 5;
                            printf("%d. Nekorektne zadany vstup: mena autorov\n", ryad);

                        }
                        if (!isalpha(chn) && chn != ' ' && chn != '#') {
                            errors = 5;
                            printf("%d. Nekorektne zadany vstup: mena autorov\n", ryad);

                        }
                    }
                    else if (i == 6) {
                        //overenie na patrenie do typov PD, PP, UD, UP
                        if (counter == 0) {
                            symb6 = chn;
                        }
                        else if (counter == 1) {
                            if ((symb6 == 'P' && chn == 'D') || (symb6 == 'P' && chn == 'P') || (symb6 == 'U' && chn == 'D') || (symb6 == 'U' && chn == 'P')) {
                                //skip
                            }
                            else {
                                errors = 6;
                                printf("%d. Nekorektne zadany vstup: typ prezentovania\n", ryad);
                            }
                        }
                        else if (counter > 1) {
                            errors = 6;
                            printf("%d. Nekorektne zadany vstup: typ prezentovania\n", ryad);

                        }
                    }
                    //overenie spravnosti casu
                    else if (i == 7) {
                        if (counter > 3) {
                            errors = 7;
                            printf("%d. Nekorektne zadany vstup: cas", ryad);

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
                                if (hours > 23 || minutes > 59) {
                                    errors = 7;
                                    printf("%d. Nekorektne zadany vstup: cas\n", ryad);

                                }

                            }
                        }
                    }
                    //overenie spravnosti datuma
                    else if (i == 8) {
                        if (counter > 7) {
                            errors = 8;
                            printf("%d. Nekorektne zadany vstup: datum\n", ryad);

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
                                    printf("%d. Nekorektne zadany vstup: datum\n", ryad);

                                }
                            }
                        }
                    }
                    counter++;
                }
                chn = getc(local_subor);
            }



            //vypis
            if (errors == 0) {   //ak nemame chyb tak zacneme vypis, inak - vypiseme spravy o chybach
                int symbols = 0;
                *lines_count = ryad;
                if ((ryad + 1) % 9 == 0) {
                    //vypis z subora
                    printf("Prezenter:                   ");    //vypiseme najprv prezenter a d'alej cez cyclus vypiseme ret'azec a kazdy raz ak bude \n - odriadkujeme a vypiseme nasledujuci nazov udajov a udaj
                    i = 1;
                    rewind(local_subor);
                    char ch = getc(local_subor);
                    while (ch != EOF) {
                        if (ch == '\n') {
                            if (i != 8) {
                                symbols++;
                            }
                            i++;
                            if (i == 9) {
                                i = 1;
                                ch = getc(local_subor);
                                printf("\n");
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
                        }
                        ch = getc(local_subor);
                    }
                    *symbol_count = symbols;
                }
            }
            else {
                printf("Error, not enough lines\n");
            }

        }
        return 0;
    }
    else {                                          //vypiseme udaje z dynamickych poli
        int nazov = 1;
        if (line != NULL) {
            printf("Prezenter:                   ");
            //zavedieme premennu nazov ktora bude znamenat nazov typu udajov 
            for (int i = 0; i < symbols; i++) {                     //cyclus pre nacitanie kazdeho chara a vypis udajov z poloziek ktory oddeleny bodkami a bloky budu oddeleni "/"
                if (line[i] != '&') {
                    if (line[i] == '/' && line[i+1] != '&') {
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
        }
        return 0;
    }
}

char* n(int symbol_count, int* n_used)
{
    FILE* subor = fopen("konferencny_zoznam.txt", "r");                  //otvorime subor pre citanie 
    char* local_line = (char*)calloc(symbol_count, sizeof(char));        //allokujeme panat cez calloc na velkost charov ktora zodpoveda poctu znakov precitanych zo suboru  
    int i = 1, first = 1, j = 0;
    char ch = getc(subor);

    while (ch != EOF && j < symbol_count) {
        if (ch == '\n') {                                                //ak znak sa rovna "\n" tak zmenime ho na bodku a ak sa rovna "\n\n" zmenime na "/"
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
    return local_line;
}

void o(int n, int opened, char line[], FILE* file, int lines_count) {


    if (opened == 1) {
        int date;
        char kod[4];

        scanf("%d %s", &date, kod);

        //nacitame do premennych datum a kod miestnosti 
        int blocks = (lines_count + 1) / 9;
        int* times = (int*)calloc(blocks, sizeof(int));         //zavedieme dynamicky poli v ktorych bude udaje o datume a kodoch
        int* dates = (int*)calloc(blocks, sizeof(int));
        char** kodes = (char**)calloc(blocks, sizeof(char*));
        for (int i = 0; i < blocks; i++) {
            kodes[i] = (char*)calloc(3, sizeof(char));
        }
        char** vars = (char**)calloc(blocks, sizeof(char*));
        for (int i = 0; i < blocks; i++) {
            vars[i] = (char*)calloc(2, sizeof(char));           //cyclus pre allokaciu pamati pre typ prezentovania
        }
        char** names = (char**)calloc(blocks, sizeof(char*));
        for (int i = 0; i < blocks; i++) {
            names[i] = (char*)calloc(50, sizeof(char));         //cyclus pre allokaciu pamati pre mena
        }
        char** jobs = (char**)calloc(blocks, sizeof(char*));
        for (int i = 0; i < blocks; i++) {                      //cyclus pre allokaciu pamati pre nazov prispevku
            jobs[i] = (char*)calloc(200, sizeof(char));
        }


        //vypis z suboru
        if (file == NULL) {
            printf("Neotvoreny subor\n");
        }
        else {
            rewind(file);
            char current_line[200];
            fgets(current_line, 200, file);
            int line_number = 0, block_number = 0;
            //nacitanie udajov do poli

            do {
                if (line_number == 9) {                         //cyclus pre nacitanie udajov, v ktorom nevhodne ret'azce budeme preskakovat 
                    line_number = 0;
                    block_number++;
                }

                if (line_number == 0) {
                    //prvy retazec vypiseme ako meno
                    current_line[strlen(current_line) - 1] = NULL;          //nacitame z suboru a kopirujeme do nasej premennej s menami
                    strcpy(names[block_number], current_line);
                }
                else if (line_number == 2) {
                    //treti retazec vypiseme ako kod prezentacnej miestnosti
                    current_line[3] = NULL;
                    strcpy(kodes[block_number], current_line);
                }
                else if (line_number == 3) {
                    //stvrty vypiseme ako nazov prispevku
                    current_line[strlen(current_line) - 1] = NULL;
                    strcpy(jobs[block_number], current_line);
                }
                else if (line_number == 5) {
                    //siesty ako typ prezentovania 
                    current_line[2] = NULL;
                    strcpy(vars[block_number], current_line);
                }
                else if (line_number == 6) {
                    //siedmy ako cas a prelozme ho do int
                    times[block_number] = atoi(current_line);
                }
                else if (line_number == 7) {
                    //a osmy ako datum
                    dates[block_number] = atoi(current_line);//prelozme chary datumov  do integerov 
                }

                fgets(current_line, 200, file);
                line_number++;
            } while (!feof(file));
            //posledny ret'azec vzdy bude datumom
            dates[blocks - 1] = atoi(current_line);

            //filtering
            int finded = 0;
            int temp1, temp2;
            for (int i = 0; i < blocks; i++) {
                if (dates[i] == date && (strcmp(kodes[i], kod) == 0)) {             //zavedeme cyclus a podmienku a budeme prepisovat udaje z tych co sme nasli
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

            if (finded != 0) {                                                  //triedime podla casu sposobom swap
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
                        temp1 = dates[i], temp2 = times[i];         //menime premenny 
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



                //vystup
                //najprv pre U typy prezentovania
                for (int i = 0; i < finded; i++) {
                    if (vars[i][0] == 'U') {                                    //
                        if (times[i] < 1000) {
                            printf("0");
                        }

                        printf("%d %s\t%s\t %s\n", times[i], vars[i], names[i], jobs[i]);
                        if (i == finded - 1) printf("\n");
                    }
                }
                //ak sme nasli P
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
                printf("Nic sa nenaslo\n");
            }
        }


    }
    else {
        printf("Neotvoreny subor!\n");
    }
}

void s(int opened, int n, char line[], int symbols)
{
    if (opened == 0) {
        printf("Neotvoreny subor!\n");         //zavedieme podmienky. ak este neotvorili subor alebo ne stlacili n tak funkcia vypise spravu a skonci
        return;
    }
    else {
        if (n == 0) {
            printf("Polia nie su vytvorene\n");
            return;
        }
        else {
            char datum[9];                                      //zavedieme polia pre premenny pre datum a typ prezentovania ktore budu na vstupe a nacitame do nych udaje
            char typ[3];
            scanf("%s %s", datum, typ);
            //hladame vhodne bloky v dynamickych poli

            char date[8]; int date_l = 8;
            char kod[2]; int kod_l = 2;                     //zavedieme premenny pre udaje ktore bedeme nacitat z dynamickych poli
            char time[4]; int time_l = 4;
            char name[50]; int name_l = 0;
            char job[150]; int job_l = 0;

            int dot_num = 1, j = 0, date_finded = 0, kod_finded = 0;   //a zavedieme premenny ktory ukazuju na status (ci sme nasli nieco alebo nie)
            int nothing_finded = 1;

            for (int i = 0; i < symbols; i++) {                 //zavedieme cyclus ktory bude nacitat kazdy znak z dynamickych poli
                if (line[i] == '/' || i == symbols - 1) {       //a ked cyclus najde bodku tak zvacsi premennu dot_num(ktora obsahuje nazov polozky)
                    j = 0;                                      //a ked najde "/" tak obnuli dot_num(to bude znamenat ze sme presli prvy alebo nieaky vacsi blok udajov
                    dot_num = 1;

                    if (date_finded == 0 && kod_finded == 0) {
                        nothing_finded = 0;
                        for (int k = 0; k < time_l; k++) {
                            printf("%c", time[k]);
                        }
                        printf("  ");                               //v tejto casti bude vypis udajov z premennych ak sme nasli iba jeden vhodny variant 
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
                        job[j] = line[i];                       //ked dot nam bude ukazovat na vhodnu nam polozky tak budeme vypisovat z nej udaje do premennej
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
                printf("Pre dany vstup neexistuju zaznamy\n");                 //ak nic sa nenaslo - vypise spravu
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

            char chislo[10];                        //zavedieme premennu pre rodne cislo a nacitame ho zo vstupu
            scanf("%s", chislo);
            //dalej budeme hladat na bloky ktory patria vstupnemu rodnemu cislu

            int blocks = (lines_count + 1) / 9;                             //premenna blocks znamena cislo blokov v dinamickych poli
            char** names = (char**)calloc(blocks, sizeof(char*));
            for (int i = 0; i < blocks; i++) {
                names[i] = (char*)calloc(50, sizeof(char));                 //alokujeme pamat pre dynamicke polia(vsetkyrosne udaje: mena, rodne cisla a tak dalej) pre kazdy blok 
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
                    current_block++;                //ak najdeme v dynamickych poli "/" tak presuneme sa na nasledujuci blok udajov
                    j = 0;
                    dot_pos = 1;
                }
                else if (line[i] == '.') {         //a ak najdeme bodku tak presuneme sa na nasledujucu polozku
                    dot_pos++;
                    j = 0;
                }
                else {
                    if (dot_pos == 1) {
                        names[current_block][j] = line[i]; j++;     //pri nacitani znaka z dynamickych poli line[] budeme venovat cislo polozky(premenna dot_pos)
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
                if (strcmp(rodni[i], chislo) == 0) {                            //ak nacitane na vstupe rodne cislo a rodne cislo ktore nacitali z nieakoho bloku su rovnaky 
                    printf("%d\t%s\t %s\n", counter, names[i], jobs[i]);        //tak vypiseme seriove cislo meno a naazov pripevku
                    counter++;
                }
            }
            if (counter == 1) {
                printf("Pre dany vstup neexistuju zaznamy\n");
                return line;
            }

            char* result_line = (char*)calloc(symbols, sizeof(char));       //zavedieme nove dynamicke pole na prepisanie udajov 
            int choise;
            char kod[3];
            char var[2];
            char time[4];
            char date[8];
            char ch[10];
            strcpy(ch, chislo);                                     //zavedieme premenny pre nacitanie a editovanie 
            scanf("%d %s %s %s %s", &choise, kod, var, time, date);


            int error = 0;
            int h1 = (time[0] - '0');
            int h2 = (time[1] - '0');
            int mi1 = (time[2] - '0');
            int mi2 = (time[3] - '0');
            int mo1 = (dates[4] - '0');
            int mo2 = (dates[5] - '0');
            int d1 = (time[6] - '0');
            int d2 = (time[7] - '0');
            int _hours = h1 * 10 + h2, _minutes = mi1 * 10 + mi2, _month = mo1 * 10 + mo2, _day = d1 * 10 + d2;
            if (choise > counter - 1) {
                error = 1;
                printf("Zadane udaje nie su korektne, zadaj novy retazec: \n");  //skontrolujeme udaje ktory nacitali a ak nieco zadane nekorektne tak vypiseme spravu
            }
            else if (!isupper(kod[0])) {
                error = 1;
                printf("Zadane udaje nie su korektne, zadaj novy retazec: \n");
            }
            else if (!isdigit(kod[1])) {
                error = 1;
                printf("Zadane udaje nie su korektne, zadaj novy retazec: \n");
            }
            else if (!isdigit(kod[2])) {
                error = 1;
                printf("Zadane udaje nie su korektne, zadaj novy retazec: \n");
            }
            else if (strcmp(var, "UP") != 0) {
                if (strcmp(var, "PP") != 0) {
                    if (strcmp(var, "UD") != 0) {
                        if (strcmp(var, "PD") != 0) {
                            error = 1;
                            printf("Zadane udaje nie su korektne, zadaj novy retazec:\n");
                        }
                    }
                }
            }
            else if (_hours > 23 || _minutes > 59) {
                error = 1;
                printf("Zadane udaje nie su korektne, zadaj novy retazec:\n");
            }
            else if (_month > 12 || _day > 31) {
                error = 1;
                printf("Zadane udaje nie su korektne, zadaj novy retazec:\n");
            }

            if (error == 0) {                               //ak nie bolo chyb tak vypiseme udaje do noveho dynamickeho polia(result_line)
                int current_symbol = 0; int xd = 0;         //zavedieme premennu xd pre pocet serioveho cisla a ak seriove cislo rovna sa resiovomu cislu ktore sme nacitali vo scanf(premenna choice) tak budeme menit udaje v tychto blokach
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
                        result_line[current_symbol] = '.';
                        current_symbol++;
                        if (xd != choise) {

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
                printf("Aktualizacia udajov prebehla v poriadku\n");
                return result_line;
            }
            else {
                printf("Zadane udaje nie su korektne, zadaj novy retazec:\n");
                return line;
            }
        }
    }
}

void h(int _n, int symbols, char line[], int lines_count) {
    int blocks = (lines_count + 1) / 9;
    char** years = (char**)calloc(blocks, sizeof(char*));
    for (int i = 0; i < blocks; i++) {
        years[i] = (char*)calloc(2, sizeof(char));                 //alokujeme pamat pre dynamicke polia(vsetkyrosne udaje: mena, rodne cisla a tak dalej) pre kazdy blok 
    }
    char** sex = (char**)calloc(blocks, sizeof(char*));
    for (int i = 0; i < blocks; i++) {
        sex[i] = (char*)calloc(1, sizeof(char));
    }
    char** kodes = (char**)calloc(blocks, sizeof(char*));
    for (int i = 0; i < blocks; i++) {
        kodes[i] = (char*)calloc(2, sizeof(char));
    }

    int current_block = 0, j = 0, dot_pos = 1;
    for (int i = 0; i < symbols; i++) {
        if (line[i] == '/') {
            current_block++;                //ak najdeme v dynamickych poli "/" tak presuneme sa na nasledujuci blok udajov
            j = 0;
            dot_pos = 1;
        }
        else if (line[i] == '.') {         //a ak najdeme bodku tak presuneme sa na nasledujucu polozku
            dot_pos++;
            j = 0;
        }
        else {
            if (dot_pos == 2 && j < 2) {
                years[current_block][j] = line[i]; j++;     //pri nacitani znaka z dynamickych poli line[] budeme venovat cislo polozky(premenna dot_pos)
            }
            else if (dot_pos == 2 && j == 2) {
                sex[current_block][0] = line[i]; j++;
            }
            else if (dot_pos == 6) {
                kodes[current_block][j] = line[i]; j++;
            }
        }
    }


    printf("Muzi\t\tUP\tUD\tPP\tPD\n");
    int count = 0; int age1 = 0, age2 = 9;
    int age=0;
    for (int i = 0; i < 10; i++) {
        age1 = i * 10;
        age2 = age1 + 9;
        printf("%dr - %dr\t",age1, age2);
        if (age1 == 0) printf("\t");
        for (int j = 0; j < blocks; j++) {
            if (strcmp(kodes[j], "UP") == 0 && (sex[j][0] - '0') < 2) {
                age = (years[j][0] - '0') * 10 + (years[j][1] - '0');
                if (age < 22) {
                    age = 21 - age;
                }
                else {
                    age = 121 - age;
                }

                if (age >= age1 && age <= age2) {
                    count++;
                }
            }
        }
        printf("%d\t", count);
        count = 0;
        for (int j = 0; j < blocks; j++) {
            if (strcmp(kodes[j], "UD") == 0 && (sex[j][0] - '0') < 2) {
                age = (years[j][0] - '0') * 10 + (years[j][1] - '0');
                if (age < 22) {
                    age = 21 - age;
                }
                else {
                    age = 121 - age;
                }

                if (age >= age1 && age <= age2) {
                    count++;
                }
            }
        }
        printf("%d\t", count);
        count = 0;
        for (int j = 0; j < blocks; j++) {
            if (strcmp(kodes[j], "PP") == 0 && (sex[j][0] - '0') < 2) {
                age = (years[j][0] - '0') * 10 + (years[j][1] - '0');
                if (age < 22) {
                    age = 21 - age;
                }
                else {
                    age = 121 - age;
                }

                if (age >= age1 && age <= age2) {
                    count++;
                }
            }
        }
        printf("%d\t", count);
        count = 0;
        for (int j = 0; j < blocks; j++) {
            if (strcmp(kodes[j], "PD") == 0 && (sex[j][0] - '0') < 2) {
                age = (years[j][0] - '0') * 10 + (years[j][1] - '0');
                if (age < 22) {
                    age = 21 - age;
                }
                else {
                    age = 121 - age;
                }

                if (age >= age1 && age <= age2) {
                    count++;
                }
            }
        }
        printf("%d\n", count);
        count = 0;
    }
    printf("\nJeni\t\tUP\tUD\tPP\tPD\n");
    count = 0; age1 = 0; age2 = 9;
    age = 0;
    for (int i = 0; i < 10; i++) {
        age1 = i * 10;
        age2 = age1 + 9;
        printf("%dr - %dr\t", age1, age2);
        if (age1 == 0) printf("\t");
        for (int j = 0; j < blocks; j++) {
            if (strcmp(kodes[j], "UP") == 0 && (sex[j][0] - '0') > 3) {
                age = (years[j][0] - '0') * 10 + (years[j][1] - '0');
                if (age < 22) {
                    age = 21 - age;
                }
                else {
                    age = 121 - age;
                }

                if (age >= age1 && age <= age2) {
                    count++;
                }
            }
        }
        printf("%d\t", count);
        count = 0;
        for (int j = 0; j < blocks; j++) {
            if (strcmp(kodes[j], "UD") == 0 && (sex[j][0] - '0') > 3) {
                age = (years[j][0] - '0') * 10 + (years[j][1] - '0');
                if (age < 22) {
                    age = 21 - age;
                }
                else {
                    age = 121 - age;
                }

                if (age >= age1 && age <= age2) {
                    count++;
                }
            }
        }
        printf("%d\t", count);
        count = 0;
        for (int j = 0; j < blocks; j++) {
            if (strcmp(kodes[j], "PP") == 0 && (sex[j][0] - '0') > 3) {
                age = (years[j][0] - '0') * 10 + (years[j][1] - '0');
                if (age < 22) {
                    age = 21 - age;
                }
                else {
                    age = 121 - age;
                }

                if (age >= age1 && age <= age2) {
                    count++;
                }
            }
        }
        printf("%d\t", count);
        count = 0;
        for (int j = 0; j < blocks; j++) {
            
            if (strcmp(kodes[j], "PD") == 0 && (sex[j][0] - '0') > 3) {
                age = (years[j][0] - '0') * 10 + (years[j][1] - '0');
                if (age < 22) {
                    age = 21 - age;
                }
                else {
                    age = 121 - age;
                }

                if (age >= age1 && age <= age2) {
                    count++;
                }
            }
        }
        printf("%d\n", count);
        count = 0;
    }
}

char* z(int _n, char line[], int symbols) {
    if (_n == 1) {
        FILE* file = fopen("arrayViewFile.txt", "w");

        char chislo[10];
        scanf("%s", chislo);

        int start_pos = 0;
        int dot_pos = 1; int j = 0; int to_delete = 1;
        int changes = 0;

        for (int symb = 0; symb < symbols; symb++) {
            if (line[symb] == '.') {
                dot_pos++;
            } 
            if (line[symb] == '/' ) {
                printf("\n"); ///delete then gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg
                if (to_delete == 1) {
                    changes++;
                    for (int i = start_pos; i < symb; i++) {
                        line[i] = '&';
                    }
                }
                start_pos = symb + 1; j = 0; to_delete = 1;dot_pos = 1;
            }

            if (dot_pos == 2 && line[symb] != '.') {
                printf("%c - %c   ", line[symb], chislo[j]);
                if (line[symb] != chislo[j]) {
                    to_delete = 0;
                    
                }
                j++;
            }

            if (symb == symbols - 1 && to_delete == 1) {
                changes++;
                for (int i = start_pos; i <= symb; i++) {
                    line[i] = '&';
                }
            }
        }
        if (changes == 0) {
            printf("Nothing found\n");
        }
        else {
            printf("Vymazalo sa : %d zaznamov!\n", changes);
        }
        fprintf(file, "%s", line);
        fclose(file);
        return line;
    }
    else {
        printf("Polia nie su vytvorene\n");
        return line;
    }
}

int main()
{
    FILE* subor = fopen("konferencny_zoznam.txt", "r");
    FILE* arrayViewFile = fopen("arrayViewFile.txt", "w");                                      //zavedieme a otvorime FILE pre zapis udajov dinamickych polia 
    char command = ' ';
    int _n = 0, opened = 0;
    int lines_counter = 0, symbol_counter = 0, symbols = 0;

    char* line = (char*)calloc(10000, sizeof(char));

    do
    {
        if (symbol_counter != 0) { symbols = symbol_counter; }                  //zavedieme cyclus v ktorom budeme nacitat komandy 
        
        command = _fgetchar();
        

        if (command == 'v')
        {
            v(_n, &opened, &subor, &lines_counter, &symbol_counter, line, symbols);
            printf("\n");
        }
        else if (command == 'n') {
            if (opened == 1) {
                line = (char*)realloc(line, symbol_counter);
                line = n(symbol_counter, &_n);
                fprintf(arrayViewFile, "%s", line);
            }
            else {
                printf("Neotvoreny subor!\n");
            }
        }
        else if (command == 'k')
        {
            free(line);
            if (opened == 1) {
                fclose(subor);
            }
            exit(0);
        }
        else if (command == 'o') {
            o(_n, opened, line, subor, lines_counter);
        }
        else if (command == 's') {
            s(opened, _n, line, symbols);
        }
        else if (command == 'p') {
            line = p(opened, _n, symbols, line, lines_counter);
            fprintf(arrayViewFile, "%s", line);
        }
        else if (command == 'h') {
            h(_n, symbols, line, lines_counter);
        }
        else if (command == 'z') {
            line = z(_n, line, symbols);
            fprintf(arrayViewFile, "%s", line);
        }
    } while (1);

    fclose(subor);

    return 0;
}