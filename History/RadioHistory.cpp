#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// --- ESTRUTURA DE DADOS SIMULADOS ---
struct DeviceHistory {
    // Info de Fabricacao (Simulada, pois nao e lida diretamente do hardware)
    string manufacturing_date = "2023-08-15"; // Exemplo: Ano-Mes-Dia
    string manufacturer_name = "TechRF Solutions Ltda.";

    // Info de Uso (Rastreada pelo software, nao pelo hardware)
    bool has_emitted = true;
    long long first_emitted_freq = 144390000; // 144.390.000 Hz (Exemplo de radioamador)
    string first_emission_date = "2024-10-04"; // Data em que o usuario usou pela primeira vez
};

// Funcao para formatar frequencias (copiada do RadioInfo.cpp)
string format_frequency(long long freq_hz) {
    if (freq_hz >= 1000000000LL) {
        stringstream ss;
        ss << fixed << setprecision(3) << (double)freq_hz / 1000000000.0 << " GHz";
        return ss.str();
    } else if (freq_hz >= 1000000LL) {
        stringstream ss;
        ss << fixed << setprecision(3) << (double)freq_hz / 1000000.0 << " MHz";
        return ss.str();
    } else {
        return to_string(freq_hz) + " Hz";
    }
}

void display_history(const DeviceHistory& history) {
    cout << "---------------------------------------" << endl;
    cout << "      HISTÓRICO E INFO DE FABRICAÇÃO" << endl;
    cout << "---------------------------------------" << endl;

    // 1. Informações de Fabricação (Simuladas)
    cout << "Fabricante:      " << history.manufacturer_name << endl;
    cout << "Data de Fábrica: " << history.manufacturing_date << endl;
    cout << "---------------------------------------" << endl;

    // 2. Informações Históricas de Uso
    cout << "HISTÓRICO DE EMISSÃO:" << endl;
    
    if (history.has_emitted) {
        cout << "  Primeira Emissão (Data): " << history.first_emission_date << endl;
        cout << "  Primeira Frequência:     " << format_frequency(history.first_emitted_freq) << endl;
    } else {
        cout << "  Nenhuma emissão registrada nesta ferramenta." << endl;
    }
    cout << "---------------------------------------" << endl;
}

int main() {
    // Cria um objeto de dados com as informacoes historicas
    DeviceHistory data;
    
    // Altere este valor para 'false' para simular um dispositivo sem historico de emissao
    // data.has_emitted = false; 

    display_history(data);

    return 0;
}
