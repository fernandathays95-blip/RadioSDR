#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

// Esta função simula a comunicação com o hardware e retorna seus dados.
// No código real, usariamos hackrf_open() ou rtlsdr_open() aqui.
struct RadioModuleInfo {
    bool connected = true;
    string model = "HackRF One (Simulacao)";
    string serial_number = "00000000-A1B2C3D4-E5F6G7H8";
    string firmware_version = "1.2.3";
    long long min_freq = 100000; // 100 kHz
    long long max_freq = 6000000000LL; // 6 GHz
    double max_sample_rate = 20.0; // 20 MHz
    string status_message = "Pronto para Transmitir/Receber";
};

// Função para formatar frequências grandes (Hz) para MHz/GHz
string format_frequency(long long freq_hz) {
    if (freq_hz >= 1000000000LL) {
        stringstream ss;
        ss << fixed << setprecision(2) << (double)freq_hz / 1000000000.0 << " GHz";
        return ss.str();
    } else if (freq_hz >= 1000000LL) {
        stringstream ss;
        ss << fixed << setprecision(2) << (double)freq_hz / 1000000.0 << " MHz";
        return ss.str();
    } else {
        return to_string(freq_hz) + " Hz";
    }
}

void display_info(const RadioModuleInfo& info) {
    cout << "---------------------------------------" << endl;
    cout << "        INFORMAÇÕES DO MÓDULO SDR" << endl;
    cout << "---------------------------------------" << endl;

    if (!info.connected) {
        cout << "[ERRO] Módulo Desconectado ou Não Encontrado!" << endl;
        cout << "Verifique a conexão USB (OTG) e a alimentação do módulo." << endl;
        cout << "---------------------------------------" << endl;
        return;
    }

    cout << "Modelo:          " << info.model << endl;
    cout << "N° de Série:     " << info.serial_number << endl;
    cout << "Firmware:        " << info.firmware_version << endl;
    cout << "---------------------------------------" << endl;
    cout << "Capacidade de RF:" << endl;
    cout << "  Frequência Mín: " << format_frequency(info.min_freq) << endl;
    cout << "  Frequência Máx: " << format_frequency(info.max_freq) << endl;
    cout << "  Taxa de Amostra: " << info.max_sample_rate << " MS/s" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Status Atual:    " << info.status_message << endl;
    cout << "---------------------------------------" << endl;
}

int main() {
    // 1. Simulação da Checagem do Módulo
    RadioModuleInfo module_data;
    
    // Você pode modificar 'module_data.connected = false;' para simular um erro de conexão.
    
    // 2. Exibir as Informações
    display_info(module_data);

    return 0;
}
