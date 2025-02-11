COMO EXECUTAR

1-Clone o repositório: git clone

2-Abra o projeto no VS Code utilizando a extensão da Raspberry e compile o arquivo "pio_matrix.c".

3-Compile o projeto, ou carregue o código diretamente na Placa BitDogLab.

4-Execute o código e interaja com as suas funcionalidades disponíveis.

FUNCIONALIDADES:

  - Adicionado caracteres (A-Z) (a-z) (0-9) à biblioteca font.h 

  - Entrada de caracteres disponíveis na biblioteca font.h via PC/Serial Monitor   

  - Cada caractere digitado no Serial Monitor será exibido no display SSD1306. 
Observação: Apenas um caractere será enviado de cada vez, não há suporte para o 
envio de strings completas. 

  - Quando um número entre 0 e 9 for digitado, um símbolo correspondente ao número 
será exibido no display e também na matriz 5x5 WS2812.

  - Interação com o Botão A  

    Ao pressionar o botão A o estado do LED RGB VERDE irá se alterar (ligado/desligado),
    uma mensagem informativa sobre o estado do LED será exibida no display
    e texto descritivo sobre a operação no Serial Monitor.

  - Interação com o Botão B  
    Ao pressionar o botão B o estado do LED RGB AZUL irá se alterar (ligado/desligado), 
    uma mensagem informativa sobre o estado do LED será exibida no display e
    haverá texto descritivo sobre a operação no Serial Monitor.  

5-Certifique-se que esta com todas configurações necessárias para o funcionamento do código.

VÍDEO DA PLACA : https://youtu.be/2sGzBXb6Cpg?si=pRG2ZaaBqgXWX02u
