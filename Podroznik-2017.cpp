//#include "stdafx.h"

#include <iostream>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


using namespace std;

void game(int choice_bot1, int choice_bot2, int *w);
int bot_low(int points_bot1, int points_bot2, int round, int wybory1[], int wybory2[]);
int bot_high(int points_bot1, int points_bot2, int round, int wybory1[], int wybory2[]);

const int R = 25;
const int ilosc_gier = 1000;
int wybory1 [ilosc_gier];
int wybory2 [ilosc_gier];
 
int main()
{
    int j=0;
    int choice1 = 0, choice2 = 0;
    int SCORE[2] = {0, 0};
    int *s;
    s = SCORE;

    srand(time(NULL));
    do{
        cout << "Runda " << j+1 << endl;
        choice1 = bot_low(SCORE[0], SCORE[1], j, wybory1, wybory2);
        choice2 = bot_high(SCORE[1], SCORE[0], j, wybory2, wybory1);
        cout << "Gracz 1  wybral: " << choice1 << "\t";
        cout << "Gracz 2 wybral: " << choice2 << "\t" << endl;
        wybory1[j] = choice1;
        wybory2[j] = choice2;
        game(choice1, choice2, s);
        cout << endl << "Punktacja: \n\t" << SCORE[0] << "\n\t" << SCORE[1] << endl << endl << endl;
        j++;
    }
    while(j<ilosc_gier);
    cout << "Ncisnij ENTER aby kontynuowac...";
    getchar();
    system("CLS");
    cout << "Koniec gry!\n\t Gracz 1 uzyskal: "  << SCORE[0] << "\n\t Gracz 2 uzyskal: " 
    << SCORE[1] << endl;
    getchar();
    return 0;
}

void game(int choice_bot1, int choice_bot2, int *w)
{
    bool flag=0;
    if((choice_bot1 < 180) || (choice_bot1 > 300)){
        if((choice_bot2 >= 180) && (choice_bot2 <= 300))
            w[1] += choice_bot2 + R;
        flag = 1;
    }
    if(!flag && ((choice_bot2 < 180) || (choice_bot2 > 300))){
        if((choice_bot1 >= 180) && (choice_bot1 <= 300))
            w[0] += choice_bot1 + R;
        flag = 1;
    }
   
    if (!flag) {
    if(choice_bot1 == choice_bot2){
           w[0] += choice_bot1;
        w[1] += choice_bot1;
    }
    else{
        if(choice_bot1 > choice_bot2){
            w[0] += choice_bot2 - R;
            w[1] += choice_bot2 + R;
        }           
        else{
            w[0] += choice_bot1 + R;
            w[1] += choice_bot1 - R;
        }           
    }
    }
}


int bot_low(int points_bot1, int points_bot2, int round, int wybory1[], int wybory2[])
{
    if(round == 0){
        return 180;
    }

    int liczba_krokow = 10;
    
    if(round < liczba_krokow){
        liczba_krokow = round;
    }
    int poprzednie = round -1;

    int obnizona_liczba = 1;
    int wygranych = 0;
    int przegranych = 0;
    int rozmiar_tabeli = 0;
    int analiza [liczba_krokow]; // zapis wynikow wraz z informacja czy wygral gre czy przegral(minusowa wartosc)
    int historia [liczba_krokow]; // zapis 10 ostatnich wyborow
    bool czy_wygral;
    int max_wartosc = 0; 

    // sprawdzenie wyniku poprzedniej rozgrywki

    if(wybory1[poprzednie] > wybory2[poprzednie]){
        czy_wygral = true;
    }else{
        czy_wygral = false;
    }

    // liczba wygranych i przegranych ostatnich gier przeciwnika
    
    for(int i=liczba_krokow; i > 0; i--){
        if(wybory2[poprzednie - i] > max_wartosc){
            max_wartosc = wybory2[poprzednie - i];
        }
        if(wybory1[poprzednie - i] > wybory2[poprzednie - i]){
            wygranych += 1;
        }else{
            przegranych += 1;
        }
    }

    // sprawdzenie jaki rozmiar powinna miec tablica dla danego przypadku
    if(wygranych > przegranych){
        rozmiar_tabeli = wygranych;
    }else{
        rozmiar_tabeli = przegranych;
    }

    
    int analiza_krokow [rozmiar_tabeli];
    int historia_krokow [rozmiar_tabeli][3];
    int step = 0;
    int wybor = 0;
    int taka_sama = 0;
    int mniejsza = 0;
    int wieksza = 0;
    int skok_mini = 0;
    int skok_max = 0;

    if(czy_wygral){
        for(int i = liczba_krokow; i >= 0; i--){
            if(wybory1[poprzednie - i] > wybory2[poprzednie - i]){

                historia_krokow[step][0] = wybory2[poprzednie - i];
                historia_krokow[step][1] = wybory2[poprzednie - i - 1];
                historia_krokow[step][2] = wybory1[poprzednie - i - 1];

                step += 1;
            }
        }
        int skok[step] = {-1};
        for(int i = 0; i < step; i++){
            if(historia_krokow[i][0] == historia_krokow[i][2] || historia_krokow[i][0] == historia_krokow[i][1]){
                taka_sama += 1;
            }
            if(historia_krokow[i][0] > historia_krokow[i][2]){
                wieksza += 1;
                skok[i] = historia_krokow[i][0] - historia_krokow[i][2];
            }
            if(historia_krokow[i][0] < historia_krokow[i][2]){
                mniejsza += 1;
                skok[i] = historia_krokow[i][2] - historia_krokow[i][0];
            }
        }
        skok_mini = skok[0];
        for(int i = 0; i < step; i++){
            if(skok_mini > skok[i] && skok[i] >= 0){
                skok_mini = skok[i];
            }
        }

        if(taka_sama >= wieksza && taka_sama >= mniejsza){
            wybor = wybory2[poprzednie] - obnizona_liczba;
        }
        if(wieksza >= taka_sama && wieksza >= mniejsza){
            wybor = wybory2[poprzednie] + skok_mini - obnizona_liczba;
        }
        if(mniejsza >= wieksza && mniejsza >= taka_sama){
            wybor = wybory2[poprzednie] - skok_mini - obnizona_liczba;
        }

        if(wybor>=max_wartosc){
            wybor = max_wartosc - obnizona_liczba;
        }

        if(wybor >= 180){
            return wybor;
        }else{
            return 180;
        }

    }
    else{
        for(int i = liczba_krokow; i >= 0; i--){
            if(wybory1[poprzednie - i] <= wybory2[poprzednie - i]){

                historia_krokow[step][0] = wybory2[poprzednie - i];
                historia_krokow[step][1] = wybory2[poprzednie - i - 1];
                historia_krokow[step][2] = wybory1[poprzednie - i - 1];

                step += 1;
            }
        }
        int skok[step] = {-1};
        for(int i = 0; i < step; i++){
            if(historia_krokow[i][0] == historia_krokow[i][2] || historia_krokow[i][0] == historia_krokow[i][1]){
                taka_sama += 1;
            }
            if(historia_krokow[i][0] > historia_krokow[i][2]){
                wieksza += 1;
                skok[i] = historia_krokow[i][0] - historia_krokow[i][2];
            }
            if(historia_krokow[i][0] < historia_krokow[i][2]){
                mniejsza += 1;
                skok[i] = historia_krokow[i][2] - historia_krokow[i][0];
            }
        }
        // cout << "\nTaka sama: " << taka_sama << endl;
        // cout <<   "Wieksza:   " << wieksza << endl;
        // cout <<   "Mniejsza:  " << mniejsza << endl;
        skok_max = skok[0];
        for(int i = 0; i < step; i++){
            if(skok_max > skok[i] && skok[i] >= 0){
                skok_max = skok[i];
            }
        }

        if(taka_sama >= wieksza && taka_sama >= mniejsza){
            wybor = wybory2[poprzednie] - obnizona_liczba;
        }
        if(wieksza >= taka_sama && wieksza >= mniejsza){
            wybor = wybory2[poprzednie] + skok_max - obnizona_liczba;
        }
        if(mniejsza >= wieksza && mniejsza >= taka_sama){
            wybor = wybory2[poprzednie] - skok_max - obnizona_liczba;
        }
        
        if(wybor>=max_wartosc){
            wybor = max_wartosc - obnizona_liczba;
        }

        if(wybor >= 180){
            return wybor;
        }else{
            return 180;
        }

    }
}

int bot_high(int points_bot1, int points_bot2, int round, int wybory1[], int wybory2[])
{
    int wybor = 0;

    if(wybory1[round -1]<wybory2[round -1]){
        wybor = wybory1[round -1] - 10;
    }else{
        wybor = wybory2[round -1] - 10;
    }
    if(wybor >= 180){
        return wybor;
    }else{
        return 250;
    }
}

