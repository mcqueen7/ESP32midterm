#include "pitches.h"
#include<Servo.h>
Servo rightservo;
Servo leftservo;
int rightang=0;
int leftang=0;
int lbn;
int rbn;
int mbn;
int mbp=1;
int nowmode; //0:prepare 1:play 2:lose
//設定各接腳
int latchPin = 25;
int clockPin = 33;
int dataPin = 32;
int pausetime=200;
int x=4;
int y=2;  //coordinates
int xs=0; 
int ys=1; //directions

int countdown=0;
int ntime=0;
int ptime=0;

int freq = 2000;
int hitchannel = 4;
int resolution = 8;
int tonePin = 13;

int losemi=0;
byte scan[8] = {
   B11111110,
   B11111101,
   B11111011,
   B11110111,
   B11101111,
   B11011111,
   B10111111,
   B01111111
}; //掃描

byte heart[8] = {
   B01100110,
   B10011001,
   B10000001,
   B10000001,
   B10000001,
   B01000010,
   B00100100,
   B00011000
}; //heart圖案

byte lose[8] = {
   B00000000,
   B10100101,
   B01000010,
   B10100101,
   B00000000,
   B00111100,
   B01000010,
   B10000001
};//lose圖案

byte show[8] = {
   B00000000,
   B00000000,
   B00011000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000
};

byte three[8] = {
B00111110,
B01100001,
B01100000,
B00111100,
B00111100,
B01100000,
B01100011,
B00111110


};
byte two[8] = {
B00111110,
B01100011,
B01110001,
B00111000,
B00001100,
B00000110,
B01111111,
B01111111

};

byte one[8] = {
B00011000,
B00011100,
B00011110,
B00011000,
B00011000,
B00011000,
B01111111,
B01111111

};
byte nmap[8] = {
B00000000,
B00000000,
B00011000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000
};
int melody[] = {

 NOTE_E4, NOTE_DS4, NOTE_E4,0 , NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_A4, NOTE_E4, NOTE_D4, NOTE_CS4,
 NOTE_E4, NOTE_E4, NOTE_E4,NOTE_E4, NOTE_D4, NOTE_D4, NOTE_D4,NOTE_C4, NOTE_C4, NOTE_C4,NOTE_B3, NOTE_B3, NOTE_B3,
NOTE_A3, NOTE_A3, NOTE_A3, NOTE_A3, NOTE_B3, NOTE_A3, NOTE_G3, NOTE_A3, 

};
int noteDurations[] = {
       8,8,8,8,8,8,8,4,4,4,4,
    8,16,16, 8,16,16,8,16,16,8,16,16,8,
    16,16,8,16,16,8,8,2,
    
};

void play(){
  if(y==2)show[y]=24;
  else show[y]=0;
      if(y==5&&(x==1)&&lbn==0){
        xs=1;
        ys=-1; 
        y=y+ys;
        x=x*pow(2,xs);
        ledcWriteTone(4,NOTE_C5);
      }
      else if(y==5&&(x==128)&&rbn==0){
        xs=-1;
        ys=-1; 
        y=y+ys;
        x=x*pow(2,xs);
        ledcWriteTone(4,NOTE_C5);
      }
      else if(y==5&&(x==2||x==4||x==8)&&lbn==0){
        xs=-1;
        ys=-1;
       y=y+ys;
       x=x*pow(2,xs);
       ledcWriteTone(4,NOTE_C5);
      }
      else if(y==5&&(x==16||x==32||x==64)&&rbn==0){
        xs=1;
        ys=-1;
      y=y+ys;
      x=x*pow(2,xs);
      ledcWriteTone(4,NOTE_C5);
      }
      else if(y==6&&(x==1||x==2||x==4||x==8)&&lbn==0){
       xs=0;
       ys=-1;
       y=y+ys;
       x=x*pow(2,xs);
       ledcWriteTone(4,NOTE_E5);
      }
      else if(y==6&&(x==16||x==32||x==64||x==128)&&rbn==0){
        xs=0;
        ys=-1;
       y=y+ys;
       x=x*pow(2,xs);
       ledcWriteTone(4,NOTE_E5);
      }
      else if(y==7&&(x==1||x==2||x==4||x==8)&&lbn==0){
       xs=1;
       ys=-1;
       y=y+ys;
       x=x*pow(2,xs);
       ledcWriteTone(4,NOTE_G5);
      }
      else if(y==7&&(x==16||x==32||x==64||x==128)&&rbn==0){
       xs=-1;
       ys=-1;
       y=y+ys;
       x=x*pow(2,xs);
       ledcWriteTone(4,NOTE_G5);
      }
    if(y==0&&ys==-1){
       y=1;ys=1;
    }
    else if(y==7&&ys==1){
     memcpy(show, lose, sizeof(lose));
     nowmode=2;
     losemi=0;
     return;
    }
    else if(((x==4&&xs==1)||x==8||x==16||(x==32&&xs==-1))&&y==3&&ys==-1){
      y=4;ys=1;
    }
    else if(((x==4&&xs==1)||x==8||x==16||(x==32&&xs==-1))&&y==1&&ys==1){
      y=0;ys=-1;    
    }
    else y=y+ys;
    if((x==1||x==1+24)&&xs==-1){
     xs=1;x=2;
    }
    else if((x==128||x==128+24)&&xs==1){
      xs=-1;x=64;
    }
    else if(y==3&&xs==1&&x==4){
      xs=-1;x=2;
    }
    else if(y==3&&xs==-1&&x==32){
      xs=1;x=64;
    }
    else x=x*pow(2,xs);
  if(y==2)show[y]=x+24;
  else show[y]=x; 
}
void button(){
      lbn=digitalRead(27);
      rbn=digitalRead(26);
    if(lbn==0){
        leftservo.write(180);
      }
      else  leftservo.write(0);
    if(rbn==0){
        rightservo.write(0);
      }
      else  rightservo.write(180);

      
  }
  
void startprepare(){
  pausetime=1000;
  if(countdown==0){memcpy(show, three, sizeof(three));
  ledcWriteTone(4,NOTE_C4);
  }
  else if(countdown==1){ memcpy(show, two, sizeof(two));
  ledcWriteTone(4,NOTE_C4);
  }
  else if(countdown==2){ memcpy(show, one, sizeof(one));
  ledcWriteTone(4,NOTE_C5);
  }
 
  if(countdown==3){
    nowmode++;
    pausetime=100;
    x=4;
    y=0;  //coordinates
    xs=0; 
    ys=1; //directions
     memcpy(show, nmap, sizeof(nmap));
    }
  countdown++;

  }
 void showlose(){
      if(losemi==32)losemi=0;
      ledcWriteTone(hitchannel, melody[losemi]);
     pausetime=2000/noteDurations[losemi];
    
    losemi++;
    }
void check(){

   mbn = digitalRead(4);
  if(mbn==0&&mbp==1){    //模式按鈕
   nowmode=0;
    mbp=0;
    countdown=0;   
  }
  if(mbn==1)mbp=1;
    button();
   
    ntime=millis();
    if(ntime-ptime>=pausetime){
      ledcWriteTone(4,0);
      switch(nowmode){
        case 0: startprepare(); break;
        case 1: play(); break;   
        case 2: showlose();break;  
      } 
      ptime=millis();
     }
     
  
  }
void setup() {
 
  rightservo.attach(14);
  leftservo.attach(12);
  Serial.begin(115200);
  pinMode(27,INPUT_PULLUP);
  pinMode(26,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT); 
  ledcSetup(hitchannel, freq, resolution);
  ledcAttachPin(tonePin, hitchannel);
 
}
void loop() {
       
   
       for(int i = 0; i < 8 ; i++){
        check();
        digitalWrite(latchPin,LOW);
        shiftOut(dataPin, clockPin, MSBFIRST, scan[i]);
        shiftOut(dataPin, clockPin, MSBFIRST, show[i]);
        digitalWrite(latchPin,HIGH);
        delay(1);
  }
   
     Serial.print(countdown);
    Serial.print(" ");
    Serial.print(mbn);
    Serial.print(" ");
    Serial.print(mbp);
    Serial.print(" ");
   
    Serial.println(nowmode);
    
   
}
