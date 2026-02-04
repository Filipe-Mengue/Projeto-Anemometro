#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Configuração do LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

// --- Variáveis para a INTERRUPÇÃO e DEBOUNCE --- Ignorar frequências de ripple
volatile unsigned long pulsoCount = 0;
volatile unsigned long ultimoPulso = 0; 
const unsigned long INTERVALO_DEBOUNCE_US = 6000; 


const int NUM_AMOSTRAS = 140;            // NÃO ALTERAR. Calibragem do anemômetro         
const unsigned long INTERVALO_MS = 70;           
unsigned long contagensPulsos[NUM_AMOSTRAS]; 
int indiceAmostra = 0; 
unsigned long ultimoCalculo = 0;
float frequenciaMedia = 0.0;
float Velocidade = 0.0;
const float a = 1.65;                     
const float b = -2.976;                     
float velocidade_ms = 0.0;
float velocidade_kmh = 0.0;


// Função da Interrupção com Debounce para desconsiderar frequências de ripple
void contadorPulso() {
  unsigned long agora_us = micros();
  if (agora_us - ultimoPulso > INTERVALO_DEBOUNCE_US) {
    pulsoCount++; 
    ultimoPulso = agora_us; // atualiza o tempo do último pulso.
  }
}

void setup() {
  Serial.begin(9600);

  // Zera o array de amostras 
  for (int i = 0; i < NUM_AMOSTRAS; i++) {
    contagensPulsos[i] = 0;
  }

  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), contadorPulso, RISING); // Pega somente a borda de subida do sinal do anemômetro

  pinMode(4, INPUT); //botao das unidades de medida

  bool mostrar_kmh = digitalRead(4); 


  lcd.init();
  lcd.backlight();
  lcd.setCursor((16 - 10) / 2, 0);
  lcd.print("Anemometro");
}

void loop() {
  unsigned long agora = millis();

  // Verifica se já passou o tempo do intervalo (DE)
  if (agora - ultimoCalculo >= INTERVALO_MS) {
    
    unsigned long contagemAtual;
    // Seção crítica para ler e zerar o contador de pulsos
    noInterrupts();
    contagemAtual = pulsoCount;
    pulsoCount = 0;
    interrupts();

    contagensPulsos[indiceAmostra] = contagemAtual;

    indiceAmostra++;
    if (indiceAmostra >= NUM_AMOSTRAS) {
      indiceAmostra = 0; // Volta para o início se chegar ao fim
    }
    
    unsigned long somaPulsos = 0;
    for (int i = 0; i < NUM_AMOSTRAS; i++) {
      somaPulsos += contagensPulsos[i];
    }
    float mediaPulsos = (float)somaPulsos / NUM_AMOSTRAS;

    frequenciaMedia = mediaPulsos / (INTERVALO_MS / 1000.0);

    Velocidade = (a*frequenciaMedia) + b; //Velocidade em ft/min
    if ( Velocidade <= 0) 
    {
      Velocidade = 0;
    }
    velocidade_ms = Velocidade * 0.05065;
    velocidade_kmh = velocidade_ms * 3.6;

    Serial.print("Velocidade: ");
    Serial.print(velocidade_ms, 2);
    Serial.print(" m/s | ");
    Serial.print(velocidade_kmh, 2);
    Serial.println(" km/h");

    lcd.setCursor(0, 1);
    lcd.print("Vel:           "); // Limpa a linha
    lcd.setCursor(5, 1);

    if (digitalRead(3) == HIGH) {
      lcd.print(velocidade_kmh, 1);
      lcd.print(" Km/h");
    } else {
      lcd.print(velocidade_ms, 1);
      lcd.print(" m/s");
    }

    // Atualiza o tempo do último cálculo
    ultimoCalculo = agora;
  }
}
