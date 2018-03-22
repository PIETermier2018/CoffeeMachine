int Eaubut = 49 ;
int Cafebut = 50 ;
int Sucrebut = 51 ;

void setup() {
  Serial.begin(9600) ;
  
  pinMode(Eaubut, INPUT) ;
  pinMode(Cafebut, INPUT) ;
  pinMode(Sucrebut, INPUT) ;
}

void loop() {
  Serial.print("Eaubut : ") ;
  Serial.print(digitalRead(Eaubut)) ;
  Serial.print(" , Cafebut : ") ;
  Serial.print(digitalRead(Cafebut)) ;
  Serial.print(" , Sucrebut : ") ;
  Serial.println(digitalRead(Sucrebut)) ;
}
