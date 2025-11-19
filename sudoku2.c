#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int islemSayisi = 0;

void sudokuYazdir(int sudokuUretilen[9][9]){
    for (int satir = 0; satir < 9; satir++){
        for (int sutun  = 0; sutun < 9; sutun++){
            printf("%d",sudokuUretilen[satir][sutun]);
            if ((sutun + 1 )% 3 == 0){
                printf(" | ");
            }
        }
        printf("\n");
            if ((satir + 1) % 3 == 0){
            printf("----------------\n");
        }
    }
}


int sudokuKontrol(int sudokuUretilen[9][9],int satir,int sutun,int denenenSayi){
    islemSayisi++;
    // satir kontrol 
    for (int i = 0; i < 9; i++)
    {
        if (sudokuUretilen[satir][i] == denenenSayi)
        {
            return 0;
        }
    }

    // sutun kontrol

    for (int i = 0; i < 9; i++)
    {
        if (sudokuUretilen[i][sutun] == denenenSayi)
        {
            return 0;
        }
    }

    // 3*3 luk karelerin kontrolu 

    int baslangicSatir,baslangicSutun;
    if (satir < 3)
    {
        baslangicSatir = 0;
    }else if (satir < 6)
    {
        baslangicSatir = 3;
    }else baslangicSatir = 6;
    

    if (sutun < 3)
    {
        baslangicSutun = 0;
    }else if (sutun <6)
    {
        baslangicSutun = 3;
    }else baslangicSutun = 6;

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (sudokuUretilen[baslangicSatir + i ][baslangicSutun +j] == denenenSayi){
                return 0;
            }
        }
    }
    return 1;
}



int sudokuCoz(int sudokuUretilen[9][9]){

    for (int satir = 0; satir < 9; satir++){
        for (int sutun = 0; sutun < 9; sutun++){
            if (sudokuUretilen[satir][sutun] == 0){ 
                for (int denenenSayi = 1; denenenSayi <= 9; denenenSayi++){
                    if (sudokuKontrol(sudokuUretilen,satir,sutun,denenenSayi) == 1){
                        sudokuUretilen[satir][sutun] = denenenSayi;
                        if (sudokuCoz(sudokuUretilen) == 1){
                            return 1;
                        }
                        sudokuUretilen[satir][sutun] = 0;
                    }
                } return 0;
                
            }
            
        }
        
    }return 1;
    
}

int tekcozumsayac = 0;
int tekCozum(int sudokuUretilen[9][9]){

    if (tekcozumsayac == 2)
    {
        return 1;
    }
    

    for (int satir = 0; satir < 9; satir++){
        for (int sutun = 0; sutun < 9; sutun++){
            if (sudokuUretilen[satir][sutun] == 0){ 
                for (int denenenSayi = 1; denenenSayi <= 9; denenenSayi++){
                    if (sudokuKontrol(sudokuUretilen,satir,sutun,denenenSayi) == 1){
                        sudokuUretilen[satir][sutun] = denenenSayi;
                        tekCozum(sudokuUretilen);
                        sudokuUretilen[satir][sutun] = 0;

                    }
                } return 0;
                
            }
            
        }
    tekcozumsayac++;    
    }return 1;
    
}

void sudokuUret(int sudokuUretilen[9][9]){
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            sudokuUretilen[i][j] = 0;
        }
        
    }

    int sayilar[9] = {1,2,3,4,5,6,7,8,9};

    for (int i = 0; i < 25; i++)
    {
        int a = rand() % 9;
        int b = rand() % 9;
        int gecicia = sayilar[a];
        sayilar[a] = sayilar[b];
        sayilar[b] = gecicia;
    }
    
    for (int i = 0; i < 9; i++)
    {
        sudokuUretilen[0][i] = sayilar[i];
    }
    

    if(sudokuCoz(sudokuUretilen) == 1){
        int silinecekSayi = 45;
        int silinenSayi = 0;

        while (silinenSayi < silinecekSayi)
        {
        int satir = rand() % 9;
        int sutun = rand() % 9;

        if (sudokuUretilen[satir][sutun] != 0)
        {
            sudokuUretilen[satir][sutun] = 0;
            silinenSayi++;
        }
        
        }
    }else {
        printf("Uretilen sudoku cozulemedi. \n");
    }


    
}

int main(){

/*    int cozulecekSudoku[9][9] = {
    {8, 7, 0,0,4,2,9,1,5},
    {1, 3, 0,5,0,8,0,2,0},
    {5, 0, 2,0,0,0,0,8,3},
    {4, 0, 3,0,0,0,8,7,0},
    {0, 6, 7,0,0,1,3,0,0},
    {0, 0, 0,0,0,0,2,5,0},
    {0, 0, 4,6,0,5,0,3,0},
    {6, 0, 1,0,0,4,5,0,8},
    {0, 8, 0,2,0,0,0,0,4}

}; */  // eskiden sudokuyu hazır verirdik şimdi kod kendisi üretiyor artık o yüzden bu diziyi yoruma aldım.

    srand(time(NULL));
    int sudokuUretilen[9][9];

    sudokuUret(sudokuUretilen);
    islemSayisi = 0;
    sudokuYazdir(sudokuUretilen);

    if (sudokuCoz(sudokuUretilen) == 1) {
        printf("Sudoku Başariyla Çözüldü:\n\n\n");
        sudokuYazdir(sudokuUretilen);
        printf("Toplam işlem sayisi: %d\n", islemSayisi);
    }else {
        printf("Cozum bulunamadi. \n\n");
    }

    tekCozum(sudokuUretilen);

    if (tekcozumsayac == 2)
    {
        printf("\n\nSudokunun birden fazla çözümü vardir.\n");
    }else {
        printf("\n\nSudokunun tek çözümü vardir.\n");
    }
    

    return 0;
}