# Projeto de Monitoramento de pH com Display LCD e Relógio RTC

## Índice

1. [Descrição](#descrição)
2. [Componentes Utilizados](#componentes-utilizados)
3. [Conexões](#conexões)
   - [Conexões do Display LCD I2C](#conexões-do-display-lcd-i2c)
   - [Conexões do Módulo RTC DS1307](#conexões-do-módulo-rtc-ds1307)
4. [Acesso ao projeto e código fonte](#acesso-ao-projeto-e-código-fonte)
5. [Bibliotecas Utilizadas](#bibliotecas-utilizadas)
6. [Manual de Montagem](#manual-de-montagem)
   - [Cuidados na Montagem](#cuidados-na-montagem)
   - [Instruções para Dispositivos Externos](#instruções-para-dispositivos-externos)
     - [Display LCD I2C](#display-lcd-i2c)
     - [Módulo RTC DS1307](#módulo-rtc-ds1307)
     - [Buzzer](#buzzer)
   - [Instruções para Montagem de LEDs](#instruções-para-montagem-de-leds)
   - [Instruções de Compilação do Código na IDE](#instruções-de-compilação-do-código-na-ide)
7. [Instruções de Uso](#instruções-de-uso)

## Descrição

<h3>Introdução</h3>
<p>
Olá, nós da BluepH faremos uma breve descrição de nosso projeto. Ele consiste em um medidor de pH feito com Arduino. O intuito do produto é medir valores armazenados de um sensor de pH e mostrar a média dos valores, de maneira formatada no display.

Além disso, se o dispositivo detectar uma grande variação do pH, ele marcará na memória EEPROM do Arduino o horário exato e a magnitude da variação. O display também mostrará a porcentagem em relação ao pH, indicando se o pH está no nível ideal com um símbolo de check, e o LED verde ficará aceso.

Caso o pH não esteja no valor ideal, existem dois outros símbolos que aparecerão:

1- Um sinal de exclamação indicará um pH baixo. Além disso, o buzzer emitirá um alerta e um LED vermelho se acenderá, indicando que é preciso tomar atenção ao risco.
<br><br>2- Um símbolo de interrogação aparecerá se o valor estiver acima do ideal, indicando que os níveis de pH da água no momento estão mais elevados do que o normal e é preciso estar atento a isso. Um LED amarelo também se acenderá.
</p>

## Componentes Utilizados

| Componentes     | Quantidade |
|-----------------|------------|
| Arduino Uno R3  | 1          |
| Breadboard      | 1          |
| Buzzer (Piezzo) | 1          |
| Cabo USB        | 1          |
| Display LCD I2C | 1          |
| DS1307 RTC      | 1          |
| Jumpers/Wires   | 21~23      |
| LED Amarelo     | 1          |
| LED Verde       | 1          |
| LED Vermelho    | 1          |
| Potenciômetro   | 1          |
| Resistores 220Ω | 3          |
| SKU SEN0161     | 1          |

## Conexões

### Conexões do Display LCD I2C

| LCD I2C | Arduino Uno  |
|---------|--------------|
| VCC     | 5V           |
| GND     | GND          |
| SDA     | A4           |
| SCL     | A5           |

### Conexões do Módulo RTC DS1307

| RTC DS1307 | Arduino Uno  |
|------------|--------------|
| VCC        | 5V           |
| GND        | GND          |
| SDA        | A4.2         |
| SCL        | A5.2         |

<h2>Segue a imagem de exemplo para a montagem:</h2>

<p></p>

![Captura de tela 2024-06-03 192436](https://github.com/LucasYuki1/Global_solution_1_Edge/assets/148162404/cc59deef-defa-498a-b50f-a71d10e112e0)

<h3>OBS: Não é necessário conectar os dois lados com o VCC e GND, porém ao fazer isso suas opções podem aumentar</h3>

## Acesso ao projeto e código fonte

O código fonte completo pode ser encontrado em [código fonte](https://github.com/LucasYuki1/Global_solution_1_Edge/blob/main/global.cpp) e a simulação feita no Wokwi pode ser encontrada [aqui](https://wokwi.com/projects/399338846464022529).

## Bibliotecas Utilizadas

- ``LiquidCrystal_I2C``
- ``RTClib``
- ``Wire``

## Manual de Montagem

### Cuidados na Montagem

- **Polaridade:** Certifique-se de conectar os polos positivos e negativos corretamente. O GND da placa Arduino deve ser conectado ao GND da breadboard (indicativo de negativo "-"). Nos componentes, o GND será conectado ao GND e o VCC será conectado ao sinal positivo "+" (5V).
- **Resistores:** Preste atenção ao valor dos resistores e à posição deles na placa. Conectar um LED sem o resistor apropriado pode danificá-lo.

### Instruções para Dispositivos Externos

#### Display LCD I2C
- Conectar o pino SDA do display ao pino A4 do Arduino.
- Conectar o pino SCL do display ao pino A5 do Arduino.

#### Módulo RTC DS1307
- Conectar o pino SDA do módulo RTC ao pino A4.2 do Arduino (localizado 3 pinos acima do pino 13).
- Conectar o pino SCL do módulo RTC ao pino A5.2 do Arduino (localizado 1 pino acima do A4.2).

#### Buzzer
- Conectar o pino positivo do buzzer ao pino 8 do Arduino.
- Conectar o pino negativo do buzzer a qualquer pino GND da breadboard.

### Instruções para Montagem de LEDs

- **Conexão dos Resistores:** Os resistores devem ser conectados entre o polo negativo da breadboard e os pinos internos. Alternativamente, pode-se conectar o polo negativo com a linha da breadboard via jumper.
- **Conexão dos LEDs:** Na mesma linha do resistor, insira o pino menor (cátodo) do LED. Conecte o pino maior (ânodo) aos seguintes pinos do Arduino:
  - ``LED Vermelho: pino 12``
  - ``LED Verde: pino 7``
  - ``LED Amarelo: pino 6``

  *A ordem dos LEDs pode ser alterada conforme a necessidade do usuário.*

### Instruções de Compilação do Código na IDE

1. **Configuração da Placa:** No software do Arduino, configure a placa Arduino Uno.
2. **Instalação das Bibliotecas:** Instale as bibliotecas necessárias: `LiquidCrystal I2C` e `RTClib`.
3. **Inserção do Código:** Insira o código no programa da IDE do Arduino.
4. **Conexão:** Conecte o cabo USB ao seu dispositivo e ao Arduino.
5. **Compilação:** Compile o código na IDE do Arduino.
6. **Resolução de Erros:** Se ocorrer algum erro, verifique se a porta serial está correta.


## Instruções de Uso

1. Conecte os componentes conforme descrito nas conexões.
2. Carregue o código no Arduino Uno usando a IDE do Arduino, recomendamos a versão 1.8.19 que pode ser encontrada no site do arduino ou no [link](https://www.arduino.cc/en/software).
3. Abra o Monitor Serial para verificar as leituras do sensor de pH e o horário do RTC.
4. O display LCD exibirá a média dos valores de pH a cada 5 segundos e o relógio será atualizado a cada segundo.

## Desenvolvedores do Projeto

| Nome                          | RM      |
|-------------------------------|---------|
| Leonardo Rocha Scarpitta      | 555460  |
| Lucas Henzo Ide Yuki          | 554865  |
| Nicolas Haubricht Heinfellner | 556259  |


