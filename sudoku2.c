#include <stdio.h>


void sudokuYazdir(int cozulecekSudoku[9][9]){
    for (int satir = 0; satir < 9; satir++){
        for (int sutun  = 0; sutun < 9; sutun++){
            printf("%d",cozulecekSudoku[satir][sutun]);
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


int sudokuKontrol(int cozulecekSudoku[9][9],int satir,int sutun,int sayi){

    // satir kontrol 
    for (int i = 0; i < 9; i++)
    {
        if (cozulecekSudoku[satir][i] == sayi)
        {
            return 0;
        }
    }

    // sutun kontrol

    for (int i = 0; i < 9; i++)
    {
        if (cozulecekSudoku[i][sutun] == sayi)
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
            if (cozulecekSudoku[baslangicSatir + i ][baslangicSutun +j] == sayi){
                return 0;
            }
        }
    }
    return 1;
}



int sudokuCoz(int cozulecekSudoku[9][9]){

    for (int satir = 0; satir < 9; satir++){
        for (int sutun = 0; sutun < 9; sutun++){
            if (cozulecekSudoku[satir][sutun] == 0){ 
                for (int sayi = 1; sayi <= 9; sayi++){
                    if (sudokuKontrol(cozulecekSudoku,satir,sutun,sayi) == 1){
                        cozulecekSudoku[satir][sutun] = sayi;
                        if (sudokuCoz(cozulecekSudoku) == 1){
                            return 1;
                        }
                        cozulecekSudoku[satir][sutun] = 0;
                    }
                } return 0;
                
            }
            
        }
        
    }return 1;
    
}

int main(){

    int cozulecekSudoku[9][9] = {
    {8, 7, 0,0,4,2,9,1,5},
    {1, 3, 0,5,0,8,0,2,0},
    {5, 0, 2,0,0,0,0,8,3},
    {4, 0, 3,0,0,0,8,7,0},
    {0, 6, 7,0,0,1,3,0,0},
    {0, 0, 0,0,0,0,2,5,0},
    {0, 0, 4,6,0,5,0,3,0},
    {6, 0, 1,0,0,4,5,0,8},
    {0, 8, 0,2,0,0,0,0,4}

};

    sudokuYazdir(cozulecekSudoku);

    if (sudokuCoz(cozulecekSudoku)) {
        printf("Sudoku Başariyla Çözüldü:\n\n\n");
        printf("----------------\n");
        sudokuYazdir(cozulecekSudoku);
    }

    return 0;
}