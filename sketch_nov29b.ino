#define D1 A0
#define D2 A1
#define D3 A2
#define D4 A3
#define IN1 2
#define IN2 4
#define IN3 5
#define IN4 7
#define ENA 3
#define ENB 6

#define RUNSPEED 65
#define TURNSPEED 100
//10顺时针，01逆时针
int Read(void);
void Move(int speed_l, int speed_r);
int i=1;
int temp = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  temp = Read();
  switch (temp) {
    case 0000:
     Move(RUNSPEED, RUNSPEED);
      break;//直行或者断点
   /* {switch(temp)
    {case 0000:
     Move(RUNSPEED, RUNSPEED);
      break;
      case 0001:
    Move(-TURNSPEED, -TURNSPEED);
      delay(20);
      Move(0,0);
      delay(80);
       Move(TURNSPEED, -TURNSPEED);
       while (Read() == 0010 || Read() == 0011 ||01110);
      break;
      case 1000:
       Move(-TURNSPEED, -TURNSPEED);
      delay(20);
      Move(0,0);
      delay(80);
       Move(TURNSPEED, -TURNSPEED);
       while (Read() == 1100 || Read() == 0100||Read() ==0110 );
      break;
     }
    }*/
     
     
    case 111://右直角
    case 11:
    case 1:
      Move(-TURNSPEED, -TURNSPEED);
      delay(20);
      Move(0,0);
      delay(80);
      Move(TURNSPEED, -TURNSPEED);
      while (Read() == 1 || Read() == 11 || Read() == 0);
      break;
    case 10:  
     Move(TURNSPEED, 30);
      delay(10);
      break;//右偏
     
      
    case 1110://左直角
    case 1100:
    case 1000:
      Move(-100, -100);
      delay(20);
      Move(0,0);
      delay(80);
      Move(-TURNSPEED, TURNSPEED);
      while (Read() == 1000 || Read() == 1100 || Read() == 1110 || Read() == 0);
      break;
    case 100://左偏
      Move(60, TURNSPEED);
      delay(10);
      break;
      case 0110:
      {switch(temp)
        {case 0100://左v
//      case 1000:
      Move(- RUNSPEED,- RUNSPEED);
      delay(20);
      Move(0,0);
      delay(80);
      Move( RUNSPEED,TURNSPEED);
      while(Read()==0110||Read()==0100||Read()==1000||Read()==0)
      break;
      case 0010://右v
      case 0001:
    
       Move(- RUNSPEED,- RUNSPEED);
      delay(10);
      Move(0,0);
      delay(80);
      Move(TURNSPEED, RUNSPEED);
      while(Read()==0110||Read()==0010||Read()==0001||Read()==0)
      break;
      case 1111:
      case 1001://十字路左转
      
      Move(-RUNSPEED,-RUNSPEED);
      delay(20);
      Move(0,0);
      delay(80);
      if (i==1){
      Move(70, TURNSPEED);//第一次左转
      i++;}
      else
      Move(TURNSPEED, TURNSPEED);//第二次直行
      while (Read() == 1000 || Read() == 1100 || Read() == 1110 || Read() == 0);
      break;
      
      case 0000:
      
       Move(RUNSPEED,RUNSPEED);
      break;
     }
      }
     break;
      
     
      
    case 1111:
      for (int i = 0; i++; i < 500) {
        if (Read() != 1111)
          break;
        delay(1);
      }
      if (Read() == 1111)
        Move(0, 0);
      break;


  }
}

int Read(void) {
  return (digitalRead(D1) + digitalRead(D2) * 10 + digitalRead(D3) * 100 + digitalRead(D4) * 1000);
}

void Move(int L, int R) {
  //    Serial.print("L=");
  //    Serial.println(L);
  //    Serial.print("R=");
  //    Serial.println(R);
  if (L > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  else if (L == 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }
  else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    L = -L;
  }
  if (R > 0) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else if (R == 0) {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    R = -R;
  }
  if (L > 0xff) L = 0xff;
  if (R > 0xff) R = 0xff;
  analogWrite(ENA, L);
  analogWrite(ENB, R);
}
