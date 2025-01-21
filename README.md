# Controle de LEDs e Buzzer com Raspberry Pi Pico

Este projeto implementa um sistema simples de controle de LEDs e um buzzer usando a Raspberry Pi Pico. Comandos enviados pela interface serial ativam LEDs e produzem sinais sonoros através do buzzer.

## Funcionalidades

1. **Controle de LEDs**:
   - Ativa LEDs vermelho, verde, azul ou branco com base no comando recebido.
   - Possibilidade de desligar todos os LEDs com o comando `OFF`.

2. **Controle do Buzzer**:
   - O buzzer emite sinais sonoros associados ao LED ativado. O tempo de ativação varia dependendo do comando:
     - `RED`: 500 ms
     - `GREEN`: 800 ms
     - `BLUE`: 1000 ms
     - `BRANCO`: 250 ms

3. **Interface Serial**:
   - Comandos são enviados via UART.

## Configuração de Hardware

### GPIOs Utilizados:
- **LEDs**:
  - **Vermelho**: GPIO 13
  - **Verde**: GPIO 11
  - **Azul**: GPIO 12
  - **Branco**: GPIO 15 (adicionado)

- **Buzzer**:
  - **Buzzer A**: GPIO 21

- **Botão (para reset em modo BOOTSEL)**:
  - **Botão A**: GPIO 5

## Funcionamento

### Fluxo do Programa:
1. Inicializa todos os pinos GPIO configurando-os como saídas.
2. Aguarda a recepção de comandos pela interface serial.
3. Ao receber um comando:
   - Identifica o comando (exemplo: `RED`, `GREEN`, `BLUE`, `BRANCO`, `OFF`).
   - Realiza a ação correspondente (ativa LEDs e/ou buzzer).
4. Repete o processo continuamente.

### Comandos Disponíveis:
| Comando  | Ação                     |
|----------|--------------------------|
| `RED`    | Liga o LED vermelho e aciona o buzzer por 500 ms. |
| `GREEN`  | Liga o LED verde e aciona o buzzer por 800 ms.    |
| `BLUE`   | Liga o LED azul e aciona o buzzer por 1000 ms.    |
| `BRANCO` | Liga o LED branco e aciona o buzzer por 250 ms.    |
| `OFF`    | Desliga todos os LEDs.                            |

Os comandos devem ser enviados via UART.

### Exemplo de Envio de Comando:
- Para ligar o LED vermelho: `RED`
- Para ligar o LED branco: `BRANCO`
- Para desligar todos os LEDs: `OFF`

### Interrupção do Botão A:
- O botão A, conectado ao GPIO 5, é utilizado para colocar a Raspberry Pi Pico no modo de gravação USB (BOOTSEL) quando pressionado. Isso permite que você grave um novo firmware na placa.

## Como Compilar e Carregar o Código

1. Clone este repositório ou baixe os arquivos do projeto.
2. Abra o arquivo no seu ambiente de desenvolvimento (como o Visual Studio Code).
3. Compile o código e carregue na sua Raspberry Pi Pico W usando o ambiente de desenvolvimento da Raspberry Pi (por exemplo, `minicom` para terminal serial ou o método direto de carregamento de código).
4. Use um terminal serial (como o Serial Monitor do VSCode ou PuTTY) para enviar comandos à placa.
   4.1. Caso utilizar o serial monitor do VSCode, fique atento a mudar a opção "Line Ending" para "LF".

## Conclusão

Este projeto, desenvolvido para aprendizado do processo seletivo EmbarcaTech, oferece uma maneira simples e eficiente de controlar LEDs e um buzzer com a Raspberry Pi Pico W, usando comandos via UART, além de incluir a funcionalidade de interrupção para reset no modo BOOTSEL com um botão. Ideal para iniciantes que desejam aprender a programar e interagir com hardware.
