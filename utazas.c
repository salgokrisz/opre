
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 512

void run();
void new();
void edit();
void delete();
void list();
void fullList();
void filteredBy_place();

int main(int argc,char *argv[])
{
    run();
    return 0;
}

void run()
{
    char pressed[MAX_SIZE];

    while(strcmp(pressed,"x") != 0)
    {
        if( strcmp(pressed,"1") == 0 )
        {
            new();
        }
        else if( strcmp(pressed,"2") == 0 )
        {
            edit();
        }
        else if( strcmp(pressed,"3") == 0 )
        {
            delete();
        }
        else if( strcmp(pressed,"4") == 0 )
        {
            fullList();
        }

        printf("\n******************\n");
        printf("[1] Bejelentes\n");
        printf("[2] Adatmodositas\n");
        printf("[3] Adat torlese\n");
        printf("[4] Listazas\n");
        printf("[x] Kilepes\n");
        printf("\nValassz egy menupontot majd nyomj ENTER-t: ");

        scanf("%s",pressed);
    }
}

void new()
{
    FILE *data;
    data = fopen("data.txt","a+");
    char name[MAX_SIZE] = "";
    char place[MAX_SIZE] = "";
    char phone[MAX_SIZE] = "";
    char vehicle[MAX_SIZE] = "";
	int correctPlace = 0;

    printf("\n******************\n");
    printf("\nUtas neve: ");
    scanf(" %s", name);
    printf("\nHelyszin: ");
	scanf(" %s", place);
	while (correctPlace == 0){
		if (strcmp(place, "Bali") == 0 || strcmp(place, "Mali") == 0 || strcmp(place, "Cook_szigetek") == 0 || strcmp(place, "Bahamak") == 0 || strcmp(place, "Izland") == 0){
			correctPlace = 1;
		}else{
			printf("Ervenytelen helyszin\nValasszon az alabbiak kozul:\nBali\nMali\nCook_szigetek\nBahamak\nIzland\nAdja meg ujra: ");
			scanf("%s", place);
			//scanf(" %s", place);
		}
	}
    printf("\nTelefonszam: ");
    scanf(" %s", phone);
    printf("\nUtazas modja: ");
    scanf(" %s", vehicle);

/*
    time_t current_time;
    struct tm * time_info;
    char timeS[MAX_SIZE];
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(timeS, sizeof(timeS)-1, "%Y-%m-%d %H:%M:%S", time_info);
*/
    fprintf(data, "%s\t%s\t%s\t%s\t\n", name, place, phone, vehicle);
    fclose(data);

    printf("\n##### A bejegyzes sikeresen megtortent. #####\n");
}

void edit()
{
    printf("\n******************\n");
    fullList();
    int n;
    int k=0;
	int correctPlace = 0;

    printf("\nAdja meg melyik bejegyzest szeretned modositani: ");
    scanf("%d",&n);

    FILE *data;
    FILE *helpfile;
    data = fopen("data.txt","r");
    helpfile = fopen("helpfile.txt","w");
    char line[MAX_SIZE];
    char input[MAX_SIZE];

    while(fgets(line,sizeof(line),data))
    {
        if(strlen(line) > 10)
        {
            k = k + 1;
            if(k == n)
            {
                char *p = strtok (line, "\t");
                char *array[4];
                int i = 0;
                while (p != NULL)
                {
                    array[i++] = p;
                    p = strtok (NULL, "\t");
                }
                char pressed[MAX_SIZE];

                do
                {
                    printf("\n[1] Utas neve\n");
                    printf("[2] Helyszin\n");
                    printf("[3] Telefonszam\n");
                    printf("[4] Utazas modja\n");
                    printf("[s] Mentes\n");

                    printf("\nAdja meg melyik adatot szeretned modositani: ");
                    scanf("%s",pressed);

                    char edit[MAX_SIZE];
                    char edit1[MAX_SIZE];
                    char edit2[MAX_SIZE];
                    char edit3[MAX_SIZE];

                    if( strcmp(pressed,"1") == 0 )
                    {
                        printf("%s => ", array[0]);
                        scanf("%s",edit);
                        array[0] = edit;
                    }
                    if( strcmp(pressed,"2") == 0 )
                    {
                        printf("%s => ", array[1]);
                        scanf("%s",edit1);
						while (correctPlace == 0){
							if (strcmp(edit1, "Bali") == 0 || strcmp(edit1, "Mali") == 0 || strcmp(edit1, "Cook_szigetek") == 0 || strcmp(edit1, "Bahamak") == 0 || strcmp(edit1, "Izland") == 0){
								correctPlace = 1;
							}else{
								printf("Ervenytelen helyszin\nValasszon az alabbiak kozul:\nBali\nMali\nCook_szigetek\nBahamak\nIzland\nAdja meg ujra: ");
								scanf("%s", edit1);
							}
						}
                        array[1] = edit1;
                    }
                    if( strcmp(pressed,"3") == 0 )
                    {
                        printf("%s => ", array[2]);
                        scanf("%s",edit2);
                        array[2] = edit2;
                    }
                    if( strcmp(pressed,"4") == 0 )
                    {
                        printf("%s => ", array[3]);
                        scanf("%s",edit3);
                        array[3] = edit3;
                    }
                }
                while (strcmp(pressed,"s") != 0);
/*
				time_t current_time;
				struct tm * time_info;
				char timeS[MAX_SIZE];
				time(&current_time);
				time_info = localtime(&current_time);
				strftime(timeS, sizeof(timeS)-1, "%Y-%m-%d %H:%M:%S", time_info);
*/
                fprintf(helpfile, "%s\t%s\t%s\t%s\t\n", array[0], array[1], array[2], array[3]);
            }
            else
            {
                fputs(line,helpfile);
            }
        }
    }

    fclose(data);
    fclose(helpfile);

    FILE *fr;
    FILE *t;
    fr = fopen("helpfile.txt","r");
    t = fopen("data.txt","w");

    char line2[MAX_SIZE];
    while(fgets(line2,sizeof(line2),fr))
    {
        fputs(line2,t);
    }

    fclose(fr);
    fclose(t);

    //remove("helpfile.txt");
    printf("\n##### A bejegyzes modositasa sikeresen megtortent #####\n");
}

void delete()
{
    printf("\n******************\n");
    fullList();
    int n;
    int i=0;
    printf("\nAdja meg melyik bejegyzést szeretnéd törölni: ");
    scanf("%d",&n);

    FILE *data;
    FILE *helpfile;
    data = fopen("data.txt","r");
    helpfile = fopen("helpfile.txt","w");
    char line[MAX_SIZE];

    while(fgets(line,sizeof(line),data))
    {
        i=i+1;
        if(i != n)
        {
            fputs(line,helpfile);
        }
    }

    fclose(data);
    fclose(helpfile);

    FILE *fr;
    FILE *t;
    fr = fopen("helpfile.txt","r");
    t = fopen("data.txt","w");

    char line2[MAX_SIZE];
    while(fgets(line2,sizeof(line2),fr))
    {
        fputs(line2,t);
    }

    fclose(fr);
    fclose(t);

    remove("helpfile.txt");

    printf("\n##### A bejegyzes torlese sikeresen megtortent #####\n");
}

void fullList()
{
    int j = 0;
    FILE *data;
    data = fopen("data.txt","r");

    char line[MAX_SIZE];

    printf("\n");
    while (fgets(line, sizeof(line), data))
    {
        if(strlen(line) > 10)
        {
            j = j + 1;
            int i = 0;
            char *p = strtok (line, "\t"); //spliting the line by \t
            char *array[10];

            while (p != NULL)
            {
                array[i++] = p;
                p = strtok (NULL, "\t");
            }
            printf("[");
            printf("%d", j);
            printf("] ");

            for (i = 0; i < 5; i=i+1)
            {
                printf("%s\t", array[i]);
            }
            printf("\n");
        }
    }

    fclose(data);
}
