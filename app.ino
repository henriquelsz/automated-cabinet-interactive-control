#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN  9
#define RST_PIN 8
char st[20];
// Inicializa o LCD
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
void LCD();

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup()
{
  // Define o LCD com 20 colunas e 4 linhas
  lcd.begin(20, 4);
  // Inicia a serial
  Serial.begin(9600);
  // Inicia  SPI bus 
  SPI.begin();
  // Inicia MFRC522    
  mfrc522.PCD_Init();
  Serial.println("Aproxime o seu cartao/TAG do leitor");
  Serial.println();
  LCD();

  //Pinos ligados aos pinos 1, 2, 3 e 4 do teclado - Linhas
  pinMode(43, OUTPUT); //Linha 1
  pinMode(45, OUTPUT); //Linha 2
  pinMode(47, OUTPUT); //Linha 3
  pinMode(49, OUTPUT); //Linha 4
  
  //Pinos ligados aos pinos 5, 6, 7 e 8 do teclado - Colunas
  pinMode(42, INPUT); //Coluna 5
  pinMode(44, INPUT); //Coluna 6
  pinMode(46, INPUT); //Coluna 7
  pinMode(48, INPUT); //Coluna 8
  
  Serial.println("Aguardando acionamento das teclas...");
  Serial.println();

  //Define saida do motor
  pinMode(12, OUTPUT); //Motor
  pinMode(10, OUTPUT); //Porta de verificacão do cartao 1
  pinMode(11, OUTPUT); //Porta de verificacão do cartao 2
  
} 

void LCD(){
  // Mostra informacoes no display
  lcd.setCursor(2,1);
  lcd.clear();
  delay(10);
  lcd.setCursor(1,0);
  lcd.print("Selecione a gaveta:");
  lcd.setCursor(2,1);
  lcd.print("2 - Camisa");
  lcd.setCursor(2,2);
  lcd.print("3 - Shorts");
  lcd.setCursor(2,3);
  lcd.print("0 - RESET");

  
}

 
void loop()
{

  
 
  for (int ti = 43; ti<50; ti++)
    {
    //Alterna o estado dos pinos das linhas
    digitalWrite(43, LOW);
    digitalWrite(45, LOW);
    digitalWrite(47, LOW);
    digitalWrite(49, LOW);
    digitalWrite(ti, HIGH);

    if (digitalRead(44) == HIGH && digitalRead(49) == HIGH)
         {
          digitalWrite(12, LOW);
          digitalWrite(10, LOW);
          digitalWrite(11, LOW);
          digitalWrite(13, LOW);
          LCD();
         }
    //Verifica se alguma tecla da coluna 5 foi pressionada

 
    //Verifica se alguma tecla da coluna 6 foi pressionada = "2"   
    if (digitalRead(44) == HIGH && digitalRead(43)== HIGH && digitalRead(12) == LOW)
    {
      
      if(digitalRead(44) == HIGH && digitalRead(43)== HIGH && digitalRead(12) == LOW)
      {
         delay(100);
         lcd.setCursor(1,0);
         lcd.clear();
         lcd.setCursor(2,2);
         lcd.clear();
         lcd.setCursor(2,3);
         lcd.clear();
         delay(100);
         lcd.setCursor(2,1);
         lcd.print("Aguarde a camisa");
         lcd.setCursor(1,2);
         lcd.print("Resetar - aperte 0");
         digitalWrite(10, HIGH);
         digitalWrite(12, HIGH);
         //Verifica se o botão "0" foi acionado
         if (digitalRead(44) == HIGH && digitalRead(49) == HIGH)
         {
          digitalWrite(12, LOW);
          digitalWrite(10, LOW);
          LCD();
         }
         else{
         goto pontoA;
       }
      }
    }
    
    //Verifica se alguma tecla da coluna 7 foi pressionada = "3"
    if (digitalRead(46) == HIGH && digitalRead(43)== HIGH && digitalRead(12) == LOW)
    {
      
      if(digitalRead(46) == HIGH && digitalRead(43)== HIGH  && digitalRead(12) == LOW)
      {
        delay(100);
        lcd.setCursor(1,0);
        lcd.clear();
        lcd.setCursor(2,2);
        lcd.clear();
        lcd.setCursor(2,3);
        lcd.clear();
        delay(100);
        lcd.setCursor(2,1);
        lcd.print("Aguarde o shorts");
        lcd.setCursor(1,2);
        lcd.print("Resetar - aperte 0");
        digitalWrite(11, HIGH);
        digitalWrite(12, HIGH);
        //Verifica se o botão "0" foi acionado
         if (digitalRead(44) == HIGH && digitalRead(49) == HIGH)
         {
          digitalWrite(12, LOW);
          digitalWrite(10, LOW);
          LCD();
         }
         else{
         goto pontoA;
       }
      }
    }
    
  
    
   }
   delay(10);

  //Ponto da leitura do cartão 1
  pontoA:
  delay(10);
  // Busca novos cartões 
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Seleciona um catão a ser lido
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Mostra ID na serial
  Serial.print("ID da tag:");
  String conteudo = "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  conteudo.toUpperCase();
 
  if(digitalRead(10) == HIGH && digitalRead(11) == LOW && digitalRead(12) == HIGH){
    if (conteudo.substring(1) == "3C 2C 47 C9") //ID CARTÃO
     {
         delay(1);
         digitalWrite(12, LOW);
         lcd.setCursor(1,0);
         lcd.clear();
         lcd.setCursor(2,2);
         lcd.clear();
         lcd.setCursor(2,3);
         lcd.clear();
         delay(10);
         lcd.setCursor(2,1);
         lcd.print("Retire a camisa");
         delay(3000);
         digitalWrite(10, LOW);
         LCD();
     }
  }

  if(digitalRead(11) == HIGH && digitalRead(10) == LOW && digitalRead(12) == HIGH){
    if (conteudo.substring(1) == "6C 8F 47 C9") //ID CARTÃO
     {
         delay(1);
         digitalWrite(12, LOW);
         lcd.setCursor(1,0);
         lcd.clear();
         lcd.setCursor(2,2);
         lcd.clear();
         lcd.setCursor(2,3);
         lcd.clear();
         delay(10);
         lcd.setCursor(2,1);
         lcd.print("Retire o shorts");
         delay(3000);
         digitalWrite(11, LOW);
         LCD();
     }
  }  

         
}
 

void imprime_linha_coluna(int x, int y)
{
       Serial.print("Linha : ");
       Serial.print(x);
       Serial.print(" x Coluna : ");
       Serial.print(y);
       delay(10);
       Serial.println();
}
