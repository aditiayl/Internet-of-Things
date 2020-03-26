/*
  Quick demo of major drawing operations on a single DMD
 */

#include <SPI.h>
#include <DMD2.h>
#include <fonts/SystemFont5x7.h>

SoftDMD dmd(1,1);  // DMD controls the entire display
int a,l=0, score=0, kalah=0; //a= tombol pada app inventor (Start='3', Atas='1', Bawah='0') 
bool atas; //atas untuk penentu jawaban benar/salah
// the setup routine runs once when you press reset:
void setup() {
  dmd.setBrightness(255);
  dmd.selectFont(SystemFont5x7);
  dmd.begin();

  // Circle with a line at a tangent to it
 // dmd.drawLine(14,9,28,15);

  // Outline box containing a filled box

Serial.begin(9600);
while (l!=1){        //jika bluetooth aktif maka akan bernilai 1
 dmd.drawString( 4,1,F("Math")); //mencetak tulisan Math pada posisi x=4 dan y=1 pada p10
 dmd.drawString( 5,9,F("Bowl"));  //mencetak tulisan Bowl pada posisi x=5 dan y=9 pada p10

  if(Serial.available()>0){
    a = Serial.read();} //membaca serial dari bluetooth
    if(a=='3'){  // dimulai, jika di tekan tombol "Start" pada App Inventor("Start" bervariable string 3)
    //  digitalWrite(led,HIGH);
       Serial.println("Led is On");  //mecetak string led is no pada App Inventor
       l=1;}
           else if(a=='0'){  //tidak dimulai, jika tidak ditekan "start"
    //  digitalWrite(led,HIGH);
       Serial.println("Led is Off");
       l=0;}
       }delay(1000);
dmd.clearScreen();  //menghapus tulisan "Math Bowl"
Serial.begin(9600);
} 





// the loop routine runs over and over again forever:
void loop() {
  int s=0;
  int q=0;
  a=3;
s=Soal(q); //manggil fungsi soal dan mengambil hasil return fungsi soal ke int s
  dmd.clearScreen();
Ball(s); //manggil fungsi Ball

}
//fungsi untuk soal dan tampilan soal
int Soal(int x){
  int c= random(1,9);
  int b= random(1,9);
   
  dmd.drawString(7,5,String(c));  //mencetak angka random dari int c
  dmd.drawString(13,5,F("x"));   //mencetak X
  dmd.drawString(19,5,String(b)); // mencetak angka ramdom dari int b
  delay(700);
  dmd.clearScreen();
  return(c*b);  // perkalian c dengan b
  } 
 //fungsi play untuk main ulang jika permainan sudah diketahui menang dan kalah
 // fungsi play sama persis dengan fungsi setup hanya l diubah menjadi po
void play(){  
  int po=0;
  while (po!=1){
 dmd.drawString( 4,1,F("Main"));
 dmd.drawString( 3,9,F("Lagi?"));

  if(Serial.available()>0){
    a = Serial.read();}
    if(a=='3'){
    //  digitalWrite(led,HIGH);
       po=1;}
           else if(a=='0'){
    //  digitalWrite(led,HIGH);
       Serial.println("Led is Off");
       po=0;}
       }delay(1000);
dmd.clearScreen();
  }

  //fungsi ball terdiri dari control ball, algoritma benar/salah, dan scoring
void Ball(int w){
  a='\n';
; //mencetak garis tengah pemisah lintasan
  dmd.drawLine(0,8,26,8);  //mencetak garis tengah pemisah lintasan
  int ew=random(0,2); //randoom penempatan jawaban
  if(ew==0){ //bernilai 0 jika berada diatas
  dmd.drawString(20,0,String(w)); //mecetak jawaban yang benar di atas
  dmd.drawString(20,9,String(random(w-3,w+3))); //mencetak jawaban yang salah (random) di bawah
  atas=true; //atas true jika jawaban ada di atas
  }
  else {  // bernilai 1 jika jawaban benar ada di bawah
  dmd.drawString(20,0,String(random(w-3,w+3)));  //mencetak jawaban yang salah (random) di atas
  dmd.drawString(20,9,String(w)); //mencetak jawaban yang benar di bawah
  atas=false; //atas false jika jawaban ada di bawah
  }
  

//  n = n -1;
  //if(n<0){n=9;}
  delay(100);
  dmd.drawCircle(5,3,3); //mencetak sebuah ingkaran
  dmd.drawFilledBox(5-1,2,5+1,6); //mencetak isi bola (kotak)
    int y=0;int z=0;
    while(1){  if(Serial.available()>0){  //komdisi apabila sudah konek
    a = Serial.read();}
    if(a=='1'){
       break;}
     else if(a=='0'){;
       break;};
       }
  delay(900);
 dmd.drawCircle(5,3,3, GRAPHICS_OFF); //menghapus jejak pergerakan bola
    dmd.drawFilledBox(5-1,2,5+1,6, GRAPHICS_OFF); //menghapus jejak pergerakan isi bola
  
     if(a=='1'){ //jika '1' (Atas) maka bola bergerak dilintasan atas
  for(int a=3;a<=30;a++){ //loop pergerakan bola
  dmd.drawCircle(a,3,3);
  dmd.drawFilledBox(a-1,2,a+1,6);
  delay(90);
  dmd.drawCircle(a,3,3, GRAPHICS_OFF);
    dmd.drawFilledBox(a-1,2,a+1,6, GRAPHICS_OFF);
  } 
 }
    else if(a=='0'){  ////jika '0' (Bawah) maka bola bergerak dilintasan bawah
  
   for(int a=3;a<=30;a++){ //loop pergerakan bola
  dmd.drawCircle(a,12,3);
  dmd.drawFilledBox(a-1,11,a+1,15);
  delay(90);
  dmd.drawCircle(a,12,3, GRAPHICS_OFF);
    dmd.drawFilledBox(a-1,11,a+1,15, GRAPHICS_OFF);}
    }
  delay(100);
   dmd.clearScreen();
    
    if(a=='0' && atas){ //salah, a=0 maka memilih jawaban di bawah dan jawaban yang benar diatas (atas true)
    kalah += 1; //mengitung point yang salah
    dmd.drawString(1,4,F("SALAH"));
    delay(500);
    dmd.clearScreen();
    dmd.drawString(0,4,F("Skor"));
    dmd.drawString(25,4, String(score));//mecetak poin score
    delay(700);
    dmd.clearScreen();
    
  }else if(a=='0' && !atas ){ //benar, a=0 maka memilih jawaban di bawah dan jawaban yang benar dibawah (atas flase)
      score +=1; //menghitung pint yang benar
      dmd.drawString(1,4,F("BENAR"));
      delay(500);
      dmd.clearScreen();
      dmd.drawString(0,4,F("Skor"));
      dmd.drawString(25,4, String(score));//mecetak poin score
      delay(700);
      dmd.clearScreen();
  }
  if(a=='1' && atas){ //benar, a=1 maka memilih jawaban di atas dan jawaban yang benar diatas (atas true)
    score +=1;  //menghitung point yang benar
    dmd.drawString(1,4,F("BENAR"));
    delay(500);
    dmd.clearScreen();
    dmd.drawString(0,4,F("Skor"));
    dmd.drawString(25,4, String(score)); //mecetak poin score
    delay(700);
    dmd.clearScreen();
    
  }else if(a=='1' && !atas ){  //salah, a=1 maka memilih jawaban di atas dan jawaban yang benar dibawah (atas false)
      kalah += 1;   //menghitung point yang salah
      dmd.drawString(1,4,F("SALAH"));
      delay(500);
      dmd.clearScreen();
      dmd.drawString(0,4,F("Skor"));
      dmd.drawString(25,4, String(score)); //mecetak poin score
      delay(700);
      dmd.clearScreen();

  }

  if(kalah+score==5){ //soal akan looping 5 kali
    if(score>=3){ //akan menang jika point score >=3
      dmd.drawString(8,4,F("WIN"));
      delay(900);
      dmd.clearScreen();
      score=0; //reset point
      kalah=0;//reset point
      play(); //memanggil fungsi play
    }else //akan kalh jika poin score kurang dari 3
     dmd.drawString(3,4,F("LOSE"));
     delay(900);
     dmd.clearScreen();
      score=0;//reset point
      kalah=0;//reset point
      play(); //memanggil fungsi play
  }

    
   delay(700);
   dmd.clearScreen();
    
}

  
