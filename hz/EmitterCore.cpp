#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cmath> // Para conversão de Hz para formatos amigáveis

using namespace std;

// Duração da simulação de emissão
const int EMISSION_DURATION_SECONDS = 10;

// Função para converter Hz para MHz ou GHz para exibição
string format_frequency(long long freq_hz) {
    if (freq_hz >= 1000000000LL) {
        return to_string(freq_hz / 1000000000.0) + " GHz";
    } else if (freq_hz >= 1000000LL) {
        return to_string(freq_hz / 1000000.0) + " MHz";
    } else if (freq_hz >= 1000LL) {
        return to_string(freq_hz / 1000.0) + " kHz";
    } else {
        return to_string(freq_hz) + " Hz";
    }
}

void simulate_transmission(long long freq_hz) {
    string freq_formatted = format_frequency(freq_hz);
    
    cout << "  > Frequência de Emissão: " << freq_formatted << endl;
    
    // Simulação do carregamento
    cout << "  > Configurando Modulador... ";
    cout.flush(); 
    this_thread::sleep_for(chrono::seconds(2));
    cout << "[PRONTO]" << endl;

    // Simulação da emissão
    cout << "  > Iniciando Transmissão de Ruído... (por " << EMISSION_DURATION_SECONDS << "s)" << endl;
    
    this_thread::sleep_for(chrono::seconds(EMISSION_DURATION_SECONDS));

    cout << "  > Transmissão concluída com SUCESSO na frequência: " << freq_formatted << endl;
}

int main(int argc, char* argv[]) {
    // 1. Verificação de Argumentos
    if (argc < 2) {
        cerr << "ERRO: Frequencia deve ser fornecida em Hertz (Hz)." << endl;
        cerr << "Uso: ./emitter_core <frequencia_hz>" << endl;
        return 1;
    }

    long long frequency_hz;
    
    // Tenta converter o argumento para long long
    try {
        frequency_hz = stoll(argv[1]);
        if (frequency_hz < 0) throw std::invalid_argument("Negativo");
    } catch (const exception& e) {
        cerr << "ERRO: O argumento deve ser um numero inteiro positivo valido (Hz)." << endl;
        return 1;
    }

    cout << "--- FERRAMENTA DE EMISSÃO CUSTOMIZADA ---" << endl;
    
    // 2. Executa a Simulação
    simulate_transmission(frequency_hz);

    return 0;
}
