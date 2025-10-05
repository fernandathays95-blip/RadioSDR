#include <SPI.h>       // Biblioteca para comunicação SPI (necessária para NRF24L01)
#include "RF24.h"      // Biblioteca específica do módulo NRF24L01

// 1. Definição dos Pinos de Controle
// CE (Chip Enable) e CSN (Chip Select Not) são os pinos de controle
// Estes pinos precisam ser definidos de acordo com a sua fiação!
#define CE_PIN  9
#define CSN_PIN 10

// 2. Criar Objeto de Rádio
// Passa os pinos de controle para o construtor
RF24 radio(CE_PIN, CSN_PIN); 

// 3. O Setup (Executado uma vez)
void setup() {
  Serial.begin(9600); // Inicia a comunicação serial para enviar a saída ao Termux/PC
  while (!Serial) {
    ; // Espera a porta serial ser aberta.
  }
  
  Serial.println("--- INICIANDO VERIFICACAO DO MODULO DE RADIO ---");
  
  // 4. A VERIFICAÇÃO CHAVE
  // radio.begin() tenta se comunicar com o módulo.
  // Se ele falhar (retornar false), o módulo não está conectado, energizado ou configurado corretamente.
  if (!radio.begin()) {
    Serial.println("\n[ERRO FATAL] O MODULO DE RADIO NRF24L01 NAO FOI ENCONTRADO!");
    Serial.println("Possiveis causas:");
    Serial.println("1. Cabos CSN/CE/GND/VCC desconectados ou trocados.");
    Serial.println("2. O modulo esta queimado ou mal conectado.");
    Serial.println("3. Nao ha alimentacao suficiente (tente um capacitor de 10uF entre VCC e GND).");
    // Trava o programa aqui para indicar falha grave
    while (true) {
      delay(500); 
    } 
  }

  // 5. Se a inicialização for bem-sucedida
  Serial.println("\n[SUCESSO] MODULO DE RADIO NRF24L01 DETECTADO E PRONTO!");
  
  // Imprime detalhes adicionais para confirmar
  Serial.print("Status do Radio: ");
  radio.printDetails(); 
  
  // 6. Preparação para Emissão
  // Define o módulo como transmissor
  radio.stopListening(); 
  
  // Define o endereço de envio (precisa de 5 bytes)
  const byte address[6] = "RADIO";
  radio.openWritingPipe(address);
  
  Serial.println("\n[PRONTO PARA EMITIR] O sistema esta configurado como transmissor.");
}

// 7. O Loop (Apenas simula a emissão)
void loop() {
  const char text[] = "TX_OK"; // Mensagem de teste

  // Envia a mensagem e verifica se a transmissão foi bem-sucedida
  if (radio.write(&text, sizeof(text))) {
    Serial.print("Emissao de teste bem-sucedida: ");
    Serial.println(text);
  } else {
    Serial.println("Falha na emissao de teste (pode ser problema de alcance ou receptor).");
  }

  delay(2000); // Espera 2 segundos antes de tentar novamente
}
