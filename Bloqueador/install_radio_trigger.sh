#!/data/data/com.termux/files/usr/bin/sh
# install_radio_trigger.sh
# Instala um comando 'o-m-d-rf-r-g' que compila e executa RadioEmitter.cpp
# Uso: sh install_radio_trigger.sh

SRC="RadioEmitter.cpp"
BINNAME="RadioEmitter"
CMDNAME="o-m-d-rf-r-g"
USER_BIN="$HOME/bin"

# checa se arquivo fonte existe
if [ ! -f "$SRC" ]; then
  echo "Arquivo $SRC não encontrado no diretório atual."
  echo "Coloque RadioEmitter.cpp aqui e rode este instalador novamente."
  exit 1
fi

# verifica se g++/clang está instalado
if ! command -v g++ >/dev/null 2>&1; then
  echo "g++ não encontrado. Instale com: pkg install clang -y"
  exit 2
fi

# cria ~/bin se não existir e adiciona PATH no .profile se necessário
mkdir -p "$USER_BIN"
case ":$PATH:" in
  *":$USER_BIN:"*) ;;
  *)
    echo "Adicionando $USER_BIN ao PATH no ~/.profile"
    echo 'export PATH="$HOME/bin:$PATH"' >> "$HOME/.profile"
    # não exporta na sessão atual automaticamente; usuário pode source ~/.profile
    ;;
esac

# compila o código
echo "Compilando $SRC ..."
g++ -std=c++17 "$SRC" -O2 -o "$BINNAME"
if [ $? -ne 0 ]; then
  echo "Erro na compilação de $SRC"
  exit 3
fi

# cria wrapper executável em ~/bin
WRAPPER="$USER_BIN/$CMDNAME"
cat > "$WRAPPER" <<'EOF'
#!/data/data/com.termux/files/usr/bin/sh
# wrapper o-m-d-rf-r-g: executa RadioEmitter (simulação)
SCRIPT_DIR="$(cd "$(dirname "$0")" >/dev/null 2>&1 && pwd)"
# Se RadioEmitter estiver no diretório atual, preferimos ele
if [ -x "./RadioEmitter" ]; then
  ./RadioEmitter "$@"
  exit $?
fi
# senão, procura em $HOME (quando instalado)
if [ -x "$HOME/RadioEmitter" ]; then
  "$HOME/RadioEmitter" "$@"
  exit $?
fi
# senão, procura no PATH (padrão: ~/bin)
if command -v RadioEmitter >/dev/null 2>&1; then
  RadioEmitter "$@"
  exit $?
fi
echo "Binary RadioEmitter não encontrado. Coloque RadioEmitter (compilado) no mesmo diretório ou em \$HOME ou no PATH."
exit 4
EOF

chmod +x "$WRAPPER"
echo "Wrapper instalado: $WRAPPER"

# move o binário compilado para $HOME (opcional, mantém cópia local)
mv -f "$BINNAME" "$HOME/" 2>/dev/null || true

echo "Instalação concluída."
echo "Feche e reabra o Termux, ou rode: source ~/.profile"
echo "Depois digite: $CMDNAME"
exit 0
