#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Sudoku'yu ekrana yazdıran fonksiyon
void sudokuYazdir(int sudokuUretilen[9][9]){
    for (int satir = 0; satir < 9; satir++){
        for (int sutun  = 0; sutun < 9; sutun++){
            printf("%d",sudokuUretilen[satir][sutun]); 
            if ((sutun + 1 )% 3 == 0){ // 3 sütunluk blokları ayırır.
                printf(" | ");
            }
        }
        printf("\n");
            if ((satir + 1) % 3 == 0){
            printf("----------------\n"); // 3 satırlık blokları ayırır.
        }
    }
}

int islemSayisi = 0;
int sudokuKontrol(int sudokuUretilen[9][9],int satir,int sutun,int denenenSayi){
    
    //Her kontrol işleminde islemSayisi sayacini bir artırıyoruz.Bu sayede toplam kaç işlem yapıldığını biliyoruz.
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
    
    // 3x3 karelerin başlangıç satır ve sütun başlangıç noktlarının indekslerini belirleme
    if (satir < 3)
    {
        baslangicSatir = 0;
    }else if (satir < 6)
    {
        baslangicSatir = 3;
    }else baslangicSatir = 6;
    

    // 3x3 karelerin başlangıç satır ve sütun başlangıç noktlarının indekslerini belirleme
    if (sutun < 3)
    {
        baslangicSutun = 0;
    }else if (sutun <6)
    {
        baslangicSutun = 3;
    }else baslangicSutun = 6;

    // 3x3 kare içindeki hücreleri kontrol etme
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            
            // Eğer denenen sayı 3x3 kare içinde bulunuyorsa 0 döndürür ve bu sayının o hücreye konulamayacağını söyler.
            if (sudokuUretilen[baslangicSatir + i ][baslangicSutun +j] == denenenSayi){
                return 0;
            }
        }
    }
    return 1; // Eğer sayı satırda, sütunda ve 3x3 karede yoksa 1 döndürür yani bu sayı o hücreye yerleşebilir.
}



int sudokuCoz(int sudokuUretilen[9][9]){


    //Burada for döngüleri ile sudokunun her bir elemanını geziyoruz.
    for (int satir = 0; satir < 9; satir++){
        for (int sutun = 0; sutun < 9; sutun++){

            //Eğer o eleman 0 ise yani boş ise buraya sayı denicez.
            if (sudokuUretilen[satir][sutun] == 0){
                
                //1 den 9 a kadar olan sayıları deniyoruz.
                for (int denenenSayi = 1; denenenSayi <= 9; denenenSayi++){
                    
                    //Eğer denenen sayı o satır,sütun ve 3x3 karede yoksa sudokuKontrol fonksiyonu 1 döndürüyor ve if bloğunun içine giriyiyoruz
                    if (sudokuKontrol(sudokuUretilen,satir,sutun,denenenSayi) == 1){
                        sudokuUretilen[satir][sutun] = denenenSayi;  //Denenen sayıyı o boşluğa yerleştiriyoruz.
                        
                        //Tekrar sudokuCoz fonksiyonunu çağırıyoruz.
                        if (sudokuCoz(sudokuUretilen) == 1){            
                            return 1;
                        }
                        sudokuUretilen[satir][sutun] = 0; //Eğer yerleştirilen sayı sonrasında sudoku çözülemediyse o sayıyı geri alıyoruz.
                                                          //ve diğer sayıyı deniyoruz.
                    }
                } return 0; //Eğer 1 den 9 a kadar olan sayılar denendiyse ve hiçbiri uymadıysa 0 döndürür yani sudoku çözülemez.
                
            }
            
        }
        
    }return 1; //Eğer sudoku tamamen dolduysa 1 döndürür yani sudoku çözüldü demektir.
    
}

int tekcozumsayac = 0;
int tekCozum(int sudokuUretilen[9][9]){

    if (tekcozumsayac == 2) //Eğer çözümlerden 2 tane bulduysa fonksiyondan çıkıyoruz.
    {
        return 1;
    }
    

    for (int satir = 0; satir < 9; satir++){  //sudokuCoz fonksiyonu ile aynı işlevi yapıyor.
        for (int sutun = 0; sutun < 9; sutun++){
            if (sudokuUretilen[satir][sutun] == 0){ 
                for (int denenenSayi = 1; denenenSayi <= 9; denenenSayi++){
                    if (sudokuKontrol(sudokuUretilen,satir,sutun,denenenSayi) == 1){
                        sudokuUretilen[satir][sutun] = denenenSayi; 
                        
                        //Burada fark olarak çözümlerden bir tane bulduğunda tekcozumsayac sayacını bir artırıyoruz.
                        tekCozum(sudokuUretilen);   
                        sudokuUretilen[satir][sutun] = 0;

                    }
                } return 0;
                
            }
            
        }
    tekcozumsayac++;  
    //Eğer sudoku tamamen dolduysa çözümlerden bir tane daha bulduk demektir ve sayacı bir artırıyoruz.  
    }return 1;
    
}

void sudokuUret(int sudokuUretilen[9][9]){
    
    // Öncelikle tüm hücreleri 0 ile dolduruyoruz.
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            sudokuUretilen[i][j] = 0;
        }
        
    }

    int sayilar[9] = {1,2,3,4,5,6,7,8,9};

    // sayilar dizisini karistiriyoruz.
    for (int i = 0; i < 25; i++)
    {
        int a = rand() % 9;  
        int b = rand() % 9;
        int gecicia = sayilar[a];
        sayilar[a] = sayilar[b];
        sayilar[b] = gecicia;
    }
    
    // Ilk satira karistirilmis sayilari yerlestiriyoruz.
    for (int i = 0; i < 9; i++)
    {
        sudokuUretilen[0][i] = sayilar[i];
    }
    

    // Sudokuyu cozmeye calisiyoruz ve eger cozulurse belirli sayida sayiyi siliyoruz.
    if(sudokuCoz(sudokuUretilen) == 1){
        int silinecekSayi = 45;
        int silinenSayi = 0;

        while (silinenSayi < silinecekSayi)
        {
        int satir = rand() % 9; 
        int sutun = rand() % 9;

        // Eğer seçilen hücre boş değilse (0 değilse) o hücreyi 0 yapıyoruz ve silinen sayi sayacini artiriyoruz.
        if (sudokuUretilen[satir][sutun] != 0)
        {
            sudokuUretilen[satir][sutun] = 0;
            silinenSayi++;
        }
        
        }
    }else {   // Eğer sudoku çözülemediyse bir hata mesajı yazdırıyoruz.
        printf("Uretilen sudoku cozulemedi. \n");
    }


    
}

int main(){

    srand(time(NULL));  // Rastgele sayı üretimi için tohumlama
    int sudokuUretilen[9][9];  // Sudoku dizisi

    sudokuUret(sudokuUretilen); 
    
    // Üretilen sudokunun bir kopyasını alıyoruz.Çünkü sudokuCoz fonksiyonu orijinal diziyi değiştiriyor.
    // Bu yüzden orijinal diziyi saklamak için bir kopyasını oluşturuyoruz.
    //Eğer sudokuyu çözdükten sonra tekCozum fonksiyonunu çağırmak istersek uretilenSudoku artık çözülmüş olur ve doğru sonuç vermez.
    int sudokuKopyasi[9][9];
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            sudokuKopyasi[i][j] = sudokuUretilen[i][j]; 
        }
        
    }
    
    // Sudoku üretimi
    islemSayisi = 0;
    sudokuYazdir(sudokuUretilen);  // Üretilen Sudoku'yu yazdırma

    
    // Üretilen sudokuyu bu kısımda çözüyoruz.
    if (sudokuCoz(sudokuUretilen) == 1) {
        printf("Sudoku Başariyla Çözüldü:\n\n\n");
        sudokuYazdir(sudokuUretilen);
        printf("Toplam işlem sayisi: %d\n", islemSayisi);
    }else {
        printf("Cozum bulunamadi. \n\n");
    }

    // Tek çözüm kontrolü
    tekCozum(sudokuKopyasi);
    if (tekcozumsayac == 2){
    printf("\n\nSudokunun birden fazla çözümü vardir.\n");
    }else {
    printf("\n\nSudokunun tek çözümü vardir.\n");
    }
    

    return 0;
}