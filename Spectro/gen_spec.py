import numpy as np
import matplotlib.pyplot as plt
import sys
import os

if len(sys.argv) < 5:
    print("Uso: python gen_spec.py <caminho_dados> <freq_center> <sample_rate> <nome_saida>")
    sys.exit(1)

# 1. Receber argumentos do script shell
data_file = sys.argv[1]
center_freq = float(sys.argv[2])
sample_rate = float(sys.argv[3])
output_name = sys.argv[4]

try:
    # 2. Carregar e processar os dados I/Q
    # Dados brutos são uint8 (I, Q)
    iq_data = np.fromfile(data_file, dtype=np.uint8) - 127.5
    
    # Converte os bytes em números complexos (I + jQ)
    iq_data = iq_data[::2] + 1j * iq_data[1::2] 
    
    # 3. Geração do Espectrograma Colorido
    
    plt.figure(figsize=(10, 8)) # Define o tamanho da imagem
    
    # A função specgram faz o trabalho pesado de FFT e plota
    # cmap='viridis' ou 'inferno' fornece o efeito colorido de mapa de calor
    plt.specgram(
        iq_data,
        Fs=sample_rate,
        NFFT=1024,
        cmap='viridis',  # Mapa de cores para o efeito "calor"
        scale='dB'
    ) 

    # 4. Configuração da Visualização
    plt.title(f'Espectrograma de Radio: {center_freq/1e6:.2f} MHz')
    plt.xlabel('Tempo (segundos)')
    plt.ylabel('Frequência (Hz)')
    
    # Define as legendas de frequência (Y-axis) para serem legíveis
    # O centro do eixo Y deve ser a frequência central
    num_ticks = 5
    ticks = np.linspace(-sample_rate/2, sample_rate/2, num_ticks)
    tick_labels = [f'{center_freq/1e6 + t/1e6:.2f} MHz' for t in ticks]
    plt.yticks(ticks, tick_labels)
    
    # Adiciona a barra lateral que explica as cores (Intensidade do Sinal)
    plt.colorbar(label='Intensidade do Sinal (dB)')
    
    # 5. Salvar a Imagem
    plt.savefig(output_name, bbox_inches='tight')
    
    print(f"\n[SUCESSO] Espectrograma colorido gerado: {output_name}")
    print("Você pode visualizar esta imagem na sua galeria.")
    
except Exception as e:
    print(f"\n[ERRO] Falha ao gerar o espectrograma: {e}")
    sys.exit(1)
finally:
    # 6. Limpeza
    os.remove(data_file)
    print(f"Dados brutos temporários ({data_file}) removidos.")

