#include <stdio.h>
#include <stdlib.h>

typedef struct {//struktura Date koja sadrzi tri promenljive tipa int za dan, mesec i godinu
    int dd;
    int mm;
    int yy;
}Date;
Date date;

typedef struct {//sturktura Remainder, sazdrzi dve promenljive tipa int(dan i mesec)i pokazivac na note
    int dd;
    int mm;
    char *note;
}Remainder;
Remainder R;

int check_leapYear(int year){ //Proverava da li je godina prestupna, vraca 1 ako jeste ili 0 ako nije
    if(year % 400 == 0 || (year % 100!=0 && year % 4 ==0))
       return 1;
    return 0;
}

void increase_month(int *mm,  int *yy){ //Povecava redni broj meseca, vraca sledeci
    ++*mm;
    if(*mm > 12){
        ++*yy;
        *mm = *mm - 12;
    }
}

void decrease_month(int *mm,  int *yy){ //Smanjuje redni broj meseca i vraca prethodni
    --*mm;
    if(*mm < 1){
        --*yy;
        if(*yy<1600){
            printf("No record available");
            return;
        }
        *mm = *mm + 12;
    }
}


int getNumberOfDays(int month,int year){ //Vraca broj dana u mesecu, a februar proverava da li je prestupna godina
   switch(month){                         
      case 1 : return(31);
      case 2 : if(check_leapYear(year)==1)
		 return(29);
	       else
		 return(28);
      case 3 : return(31);
      case 4 : return(30);
      case 5 : return(31);
      case 6 : return(30);
      case 7 : return(31);
      case 8 : return(31);
      case 9 : return(30);
      case 10: return(31);
      case 11: return(30);
      case 12: return(31);
      default: return(-1);
   }
}

char *getName(int day){ //prima redni broj dana u nedelji i vraca naziv, krece od nedelje, pa ide do subote
   switch(day){
      case 0 :return("Sunday");
      case 1 :return("Monday");
      case 2 :return("Tuesday");
      case 3 :return("Wednesday");
      case 4 :return("Thursday");
      case 5 :return("Friday");
      case 6 :return("Saturday");
      default:return("Error in getName() module.Invalid argument passed");
   }
}

void print_date(int mm, int yy){ //prima mesec i godinu i stampa ime meseca i godinu
    printf("----------------------");
    switch(mm){
        case 1: printf("January"); break;
        case 2: printf("February"); break;
        case 3: printf("March"); break;
        case 4: printf("April"); break;
        case 5: printf("May"); break;
        case 6: printf("June"); break;
        case 7: printf("July"); break;
        case 8: printf("August"); break;
        case 9: printf("September"); break;
        case 10: printf("October"); break;
        case 11: printf("November"); break;
        case 12: printf("December"); break;
    }
    printf(" , %d", yy);
    printf("----------------------");
}
int getDayNumber(int day,int mon,int year){ //vraca redni broj dana, a prima datum(dan, mesec i godinu)
    int res = 0, t1, t2, y = year;
    year = year - 1600;
    while(year >= 100){
        res = res + 5;
        year = year - 100;
    }
    res = (res % 7);
    t1 = ((year - 1) / 4);
    t2 = (year-1)-t1;
    t1 = (t1*2)+t2;
    t1 = (t1%7);
    res = res + t1;
    res = res%7;
    t2 = 0;
    for(t1 = 1;t1 < mon; t1++){
        t2 += getNumberOfDays(t1,y);
    }
    t2 = t2 + day;
    t2 = t2 % 7;
    res = res + t2;
    res = res % 7;
    if(y > 2000)
        res = res + 1;
    res = res % 7;
    return res;
}

char *getDay(int dd,int mm,int yy){ // Vraca naziv dana u odnosu na prosledjeni datum
    int day;
    if(!(mm>=1 && mm<=12)){
        return("Invalid month value");
    }
    if(!(dd>=1 && dd<=getNumberOfDays(mm,yy))){
        return("Invalid date");
    }
    if(yy>=1600){
        day = getDayNumber(dd,mm,yy);
        day = day%7;
        return(getName(day));
    }else{
        return("Please give year more than 1600");
    }
}

int checkNote(int dd, int mm){   // Proverava da li postoji poruka(podsetnik) u mesecu, vraca 1 ukoliko postoji, u suprotnom 0
    FILE *fp;
    fp = fopen("note2.txt","r");
    if(fp == NULL){
        printf("Error in Opening the file");
    }
    char line[300];
    while(fscanf(fp, "%d %d|%[^\n]", &R.dd, &R.mm, line) != EOF){ 
        if(R.dd == dd && R.mm == mm){
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void printMonth(int mon,int year){ //prima mesec i godinu, stampa sve dane za prosledjeni mesec
    int nod, day, cnt, d = 1, isNote = 0;
    system("cls");
    if(!(mon>=1 && mon<=12)){
        printf("INVALID MONTH");
        getch();
        return;
    }
    if(!(year>=1600)){
        printf("INVALID YEAR");
        getch();
        return;
    }
    print_date(mon,year);
    printf("\nS   M   T   W   T   F   S   \n");
    nod = getNumberOfDays(mon,year);
    day = getDayNumber(d,mon,year);
    switch(day){ //pocetna pozicija dana za odredjeni mesec
        case 0 :
            printf("");
            cnt = 0;
            break;
        case 1 :
            printf("    ");
            cnt = 1;
            break;
        case 2 :
            printf("        ");
            cnt = 2;
            break;
        case 3 :
            printf("            ");
            cnt = 3;
            break;
        case 4 :
            printf("                ");
            cnt = 4;
            break;
        case 5 :
            printf("                    ");
            cnt = 5;
            break;
        case 6 :
            printf("                        ");
            cnt = 6;
            break;
        default :
            printf("INVALID DATA FROM THE getOddNumber()MODULE");
            return;
    }
    for(d=1;d<=nod;d++){
        if(cnt%7==0){
            printf("\n");
        }

        cnt++;
        if(checkNote(d,mon)==1){//proverava da li postoji podsetnik za odredjeni dan u mesecu, ako ima dodaje zvezdicu pored dana
          printf("%02d* ",d);
        }else{
          printf("%02d  ",d);      
        }
        
    }
    printf("\nPress 'n'  to Next, Press 'p' to Previous and 'q' to Quit\n");
    printf("Sign * indicates the NOTE, Press 's' to see note: ");

    
}

void AddNote(){//funkcija za dodavanje podsetnika(poruke), cuva poruku u fajlu
    FILE *fp;
    fp = fopen("note2.txt","a");
    system("cls");
    printf("Enter the date(DD/MM): ");
    scanf("%d/%d",&R.dd, &R.mm);
    
    printf("Enter the Note(300 character max): ");
    R.note = malloc(1);
    fflush(stdin);
    int c;
    int i = 0;
    int size = 1;
    while((c = fgetc(stdin)) != '\n'){
             char *tmp;
             size++;
             tmp = realloc(R.note, size);
             if(!tmp){
                      free(R.note);
                      exit(0);         
             }else{
                   R.note = tmp;      
             }
             R.note[i] = c;
             i++;
    }
    R.note[i] = '\0';
    
    if(fprintf(fp, "%d %d|%s", R.dd, R.mm, R.note)){
                 fprintf(fp, "\n");
        puts("Note is saved sucessfully\n");
        fclose(fp);
    }else{
        puts("\aFail to save!!\a");
    }
    printf("Press any key............");
    getch();
    fclose(fp);
}

void showNote(int mm){//funkcija za citanje svih poruka za odredjeni mesec iz fajla, ako nema vraca odgovarajucu poruku
    FILE *fp;
    int i = 0, isFound = 0;
    system("cls");
    fp = fopen("note2.txt","r");
    if(fp == NULL){
        printf("Error in opening the file\n");
    }

    int n;
    char line[300];
    while(fscanf(fp, "%d %d|%[^\n]", &R.dd, &R.mm, line) != EOF){
                     R.note = malloc(strlen(line));
                     R.note = line;
        if(R.mm == mm){
            printf("Note %d Day = %d: %s\n", i+1, R.dd,  R.note);
            isFound = 1;
            i++;
        }
    }
    if(isFound == 0){
        printf("This Month contains no note\n");
    }
    printf("Press any key to back.......");
    
    getch();
    
}

int main(){
    int choice;
    char ch = 'a';
    while(1){
        system("cls");
        printf("1. Find Out the Day\n");
        printf("2. Print all the day of month\n");
        printf("3. Add Note\n");
        printf("4. EXIT\n");
        printf("ENTER YOUR CHOICE : ");
        scanf("%d",&choice);

        system("cls");
        switch(choice){
            case 1:
                printf("Enter date (DD.MM.YYYY) : ");
                scanf("%d.%d.%d",&date.dd,&date.mm,&date.yy);
                printf("Day is : %s",getDay(date.dd,date.mm,date.yy));
                printf("\nPress any key to continue......");
                getch();
                break;
            case 2 :
                printf("Enter month and year (MM/YYYY) : ");
                scanf("%d/%d",&date.mm,&date.yy);
                system("cls");
                ch = 'a';
                while(ch!='q'){
                    printMonth(date.mm,date.yy);
                    ch = getch();
                    if(ch == 'n'){
                        increase_month(&date.mm,&date.yy);
                        system("cls");
                        printMonth(date.mm,date.yy);
                    }else if(ch == 'p'){
                        decrease_month(&date.mm,&date.yy);
                        system("cls");
                        printMonth(date.mm,date.yy);
                    }else if(ch == 's'){
                        showNote(date.mm);
                        system("cls");
                    }
                }
                break;
            case 3:
                AddNote();
                break;
            case 4 :
                 free(R.note);
                exit(0);
        }
    }
    return 0;
}
