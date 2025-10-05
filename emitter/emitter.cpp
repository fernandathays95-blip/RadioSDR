#include <iostream>
#include <string>
#include <cmath>
#include <unistd.h> // Para sleep (simulação de tempo de emissão)

// A inclusão real para emissão seria:
// #include <hackrf.h> 

using namespace std;

// Funções de simulação para evitar dependência do hardware
void initialize_hackrf_simulation() {
    cout << "  [SIMULAÇÃO] Inicializando o hardware HackRF..." << endl;
}

void transmit_frequency_simulation(long long freq_hz) {
    cout << "  [SIMULAÇÃO] Configurando a frequência para: " << freq_hz << " Hz." << endl;
    cout << "  [SIMULAÇÃO] Gerando e enviando sinal de rádio..." << endl;
    
    // Simula a transmissão por 5 segundos
    sleep(5); 
    
    cout << "  [SIMULAÇÃO] Emissão concluída." << endl;
}

void finalize_hackrf_simulation() {
    cout << "  [SIMULAÇÃO] Desconectando o hardware." << endl;
}

int main(int argc, char* argv[]) {
    // 1. Verificação de Argumentos
    if (argc < 2) {
        cerr << "ERRO: Frequência não especificada." << endl;
        cerr << "Uso: ./emitter <frequencia_em_hz>" << endl;
        return 1;
    }

    long long frequency_hz;
    
    // Converte o argumento para um número
    try {
        frequency_hz = stoll(argv[1]);
    } catch (const invalid_argument& e) {
        cerr << "ERRO: O argumento deve ser um número inteiro válido." << endl;
        return 1;
    } catch (const out_of_range& e) {
        cerr << "ERRO: Frequência muito grande." << endl;
        return 1;
    }

    cout << "\n--- FERRAMENTA DE EMISSÃO RF ---" << endl;
    cout << "Solicitada emissão na frequência: " << frequency_hz << " Hz." << endl;
    
    // 2. Chamadas de Emissão (Simuladas)
    initialize_hackrf_simulation();
    transmit_frequency_simulation(frequency_hz);
    finalize_hackrf_simulation();

    cout << "--- FIM DA TRANSMISSÃO ---" << endl;
    return 0;
}
