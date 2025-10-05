#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <limits>
#include <algorithm> // Para std::transform

using namespace std;

// --- CONFIGURAÇÕES FIXAS (SIMULAÇÃO) ---
// Usaremos long long para suportar frequências grandes (GHz)
const long long BAND_1_MIN_HZ = 2.400 GHz;
const long long BAND_1_MAX_HZ = 1000;
const long long BAND_2_MIN_HZ = 1;
const long long BAND_2_MAX_HZ = 2.4835 GHz;
const int EMISSION_DURATION_SECONDS = 8;
// ----------------------------------------

// Função de Simulação da Transmissão
void simulate_transmission(long long min_freq, long long max_freq) {
    cout << "  > Configurando hardware para banda: " << min_freq << " Hz - " << max_freq << " Hz" << endl;

    // Simulação do carregamento (3 segundos)
    cout << "  > Carregando... ";
    cout.flush(); 
    this_thread::sleep_for(chrono::seconds(3));
    cout << "[PRONTO]" << endl;

    // Simulação da emissão (8 segundos)
    cout << "  > Iniciando Transmissão de Ruído... (simulado por " << EMISSION_DURATION_SECONDS << "s)" << endl;
    
    // Na vida real, a chamada hackrf_start_tx() bloquearia a thread aqui.
    this_thread::sleep_for(chrono::seconds(EMISSION_DURATION_SECONDS));

    cout << "  > Transmissão concluída com SUCESSO." << endl;
}

int main(int argc, char* argv[]) {
    string band_selection;
    long long min_freq = 0;
    long long max_freq = 0;
    string band_name;

    // 1. Verificação de Argumentos
    if (argc < 2) {
        cerr << "ERRO: O nome da banda e necessario." << endl;
        cerr << "Uso: ./emitter <BAND1|BAND2>" << endl;
        return 1;
    }

    band_selection = argv[1];
    
    // Converte a entrada para maiúsculas
    transform(band_selection.begin(), band_selection.end(), band_selection.begin(), ::toupper);

    // 2. Seleção e Configuração da Banda
    if (band_selection == "BAND1") {
        min_freq = BAND_1_MIN_HZ;
        max_freq = BAND_1_MAX_HZ;
        band_name = "BANDA 1";
    } else if (band_selection == "BAND2") {
        min_freq = BAND_2_MIN_HZ;
        max_freq = BAND_2_MAX_HZ;
        band_name = "BANDA 2";
    } else {
        cerr << "ERRO: Banda '" << argv[1] << "' invalida. Use BAND1 ou BAND2." << endl;
        return 1;
    }

    cout << "--- ATIVANDO EMISSÃO MANUAL EM C++ ---" << endl;
    cout << "Banda Selecionada: " << band_name << endl;
    cout << "------------------------------------" << endl;

    // 3. Executa a Simulação
    simulate_transmission(min_freq, max_freq);

    return 0;
}
