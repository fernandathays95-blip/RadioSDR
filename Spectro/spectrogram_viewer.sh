#!/data/data/com.termux/files/usr/bin/bash

# Este script orquestra a captura de dados e a geracao do espectrograma.

# --- CONFIGURAÇÕES PADRÃO ---
SAMPLE_RATE=2400000       # 2.4 MS/s (Taxa de amostragem padrao do RTL-SDR)
CAPTURE_DURATION=10       # 10 segundos de captura
TEMP_DATA_FILE="temp_iq_data.bin"
PYTHON_SCRIPT="gen_spec.py"
# ----------------------------

# 1. Verifica se os argumentos necessários foram fornecidos
if [ -z "$1" ] || [ -z "$2" ]; then
    echo "Uso: ./spectrogram_viewer.sh <frequencia_central_em_hz> <nome_saida_png>"
    echo "Exemplo: ./spectrogram_viewer.sh 100000000 fm_band.png"
    exit 1
fi

CENTER_FREQ=$1
OUTPUT_NAME=$2
NUM_SAMPLES=$((CAPTURE_DURATION * SAMPLE_RATE)) # Calcula o numero total de amostras

echo "--- FERRAMENTA DE ESPECTROGRAMA ---"
echo "Frequencia Central: $CENTER_FREQ Hz ($((CENTER_FREQ / 1000000)) MHz)"
echo "Taxa de Amostragem: $((SAMPLE_RATE / 1000000)) MS/s"
echo "Tempo de Captura: $CAPTURE_DURATION segundos"
echo "-----------------------------------"


# 2. Verifica o hardware RTL-SDR
if ! command -v rtl_sdr &> /dev/null
then
    echo "[ERRO] O comando 'rtl_sdr' nao foi encontrado. Certifique-se de que o hardware SDR (RTL-SDR) esta conectado e o pacote 'rtl-sdr' esta instalado."
    exit 1
fi

# 3. Captura dos dados brutos com rtl_sdr
echo "[PASSO 1/3] Capturando $CAPTURE_DURATION segundos de dados I/Q..."
rtl_sdr -f $CENTER_FREQ -s $SAMPLE_RATE -n $NUM_SAMPLES $TEMP_DATA_FILE

if [ $? -ne 0 ]; then
    echo "[ERRO] A captura de dados falhou. Verifique a conexao do seu dongle RTL-SDR."
    exit 1
fi

# 4. Geração do Espectrograma Colorido (Chama o Python)
echo "[PASSO 2/3] Dados capturados. Processando espectrograma com Python..."
python $PYTHON_SCRIPT $TEMP_DATA_FILE $CENTER_FREQ $SAMPLE_RATE $OUTPUT_NAME

echo "[PASSO 3/3] Processo concluído."
