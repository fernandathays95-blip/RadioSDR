#!/data/data/com.termux/files/usr/bin/bash

# --- CONFIGURAÇÃO ---
# Nome do executável compilado em C++
EXECUTABLE_NAME="./emitter" 

# O comando que o usuário deve digitar
REQUIRED_COMMAND="rf-g-o-k-h-"
# --------------------

# Verifica se o executável C++ existe
if [ ! -f $EXECUTABLE_NAME ]; then
    echo "ERRO: O programa de emissão ($EXECUTABLE_NAME) não foi encontrado."
    echo "Por favor, compile o emitter.cpp primeiro."
    exit 1
fi

# Verifica se o primeiro argumento é o comando RF correto
if [ "$1" != "$REQUIRED_COMMAND" ]; then
    echo "Uso incorreto."
    echo "Sintaxe correta: $REQUIRED_COMMAND <frequencia_em_hz>"
    echo "Exemplo: $REQUIRED_COMMAND 102500000"
    exit 1
fi

# Verifica se a frequência foi passada como segundo argumento
if [ -z "$2" ]; then
    echo "ERRO: A frequência (em Hz) deve ser fornecida."
    echo "Sintaxe correta: $REQUIRED_COMMAND <frequencia_em_hz>"
    exit 1
fi

FREQUENCY_HZ=$2

# Executa o programa C++ com a frequência fornecida
$EXECUTABLE_NAME $FREQUENCY_HZ
