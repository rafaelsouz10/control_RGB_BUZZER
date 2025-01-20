# Controle de LEDs e Buzzer com Raspberry Pi Pico

Este projeto implementa um sistema simples de controle de LEDs e um buzzer usando a Raspberry Pi Pico. Comandos enviados pela interface serial ativam LEDs e produzem sinais sonoros através do buzzer.

## Funcionalidades

1. **Controle de LEDs**:
   - Ativa LEDs vermelho, verde ou azul com base no comando recebido.
   - Possibilidade de desligar todos os LEDs com o comando `OFF`.

2. **Controle do Buzzer**:
   - O buzzer emite sinais sonoros associados ao LED ativado. O tempo de ativação varia dependendo do comando:
     - `RED`: 500 ms
     - `GREEN`: 800 ms
     - `BLUE`: 1000 ms

3. **Interface Serial**:
   - Comandos são enviados via UART.

## Configuração de Hardware

### GPIOs Utilizados:
- **LEDs**:
  - Vermelho: GPIO 13
  - Verde: GPIO 11
  - Azul: GPIO 12

- **Buzzer**:
  - Buzzer A: GPIO 21

## Funcionamento

### Fluxo do Programa:
1. Inicializa todos os pinos GPIO configurando-os como saídas.
2. Aguarda a recepção de comandos pela interface serial.
3. Ao receber um comando:
   - Identifica o comando (exemplo: `RED`, `GREEN`, `BLUE`, `OFF`).
   - Realiza a ação correspondente (ativa LEDs e/ou buzzer).
4. Repete o processo continuamente.

### Comandos Disponíveis:
| Comando  | Ação                     |
|----------|--------------------------|
| `RED`    | Liga o LED vermelho e aciona o buzzer por 500 ms. |
| `GREEN`  | Liga o LED verde e aciona o buzzer por 800 ms.    |
| `BLUE`   | Liga o LED azul e aciona o buzzer por 1000 ms.    |
| `OFF`    | Desliga todos os LEDs.                            |

Os comandos devem ser enviados via UART.

### Exemplo de Envio de Comando:
- Para ligar o LED vermelho: `RED`
- Para desligar todos os LEDs: `OFF`

