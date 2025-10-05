#!/data/data/com.termux/files/usr/bin/bash

# --- CONFIGURAÇÕES ---
EMITTER_CORE="./emitter_core"
# --------------------

# 1. Verifica se a frequência foi fornecida
if [ -z "$1" ]; then
    echo "ERRO: Voce deve fornecer a frequencia em Hertz (Hz)."
    echo "Uso: ./emit.sh <frequencia_em_hz>"
    echo "Exemplo: ./emit.sh 107900000"
    exit 1
fi

FREQUENCY_HZ=$1

# 2. Validação simples para garantir que o input é um número
if ! [[ "$FREQUENCY_HZ" =~ ^[0-9]+$ ]]; then
    echo "ERRO: A frequencia '$FREQUENCY_HZ' deve ser um numero inteiro positivo."
    exit 1
fi

# 3. Verifica se o executável C++ existe
if [ ! -f "$EMITTER_CORE" ]; then
    echo "ERRO: O programa C++ ($EMITTER_CORE) nao foi encontrado."
    echo "Por favor, compile 'EmitterCore.cpp' primeiro."
    exit 1
fi

# 4. Chama o programa C++ passando a frequência como argumento
$EMITTER_CORE $FREQUENCY_HZ
