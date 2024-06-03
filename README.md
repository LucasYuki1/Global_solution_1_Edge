# Projeto de Monitoramento de pH com Display LCD e Relógio RTC

## Índice

1. [Descrição](#descrição)
2. [Componentes Utilizados](#componentes-utilizados)
3. [Conexões](#conexões)
   - [Conexões do Display LCD I2C](#conexões-do-display-lcd-i2c)
   - [Conexões do Módulo RTC DS1307](#conexões-do-módulo-rtc-ds1307)
   - [Conexões do Sensor de pH](#conexões-do-sensor-de-ph)
4. [Instruções de Uso](#instruções-de-uso)


## Descrição

Este projeto utiliza um sensor de pH conectado a um Arduino Uno para medir o nível de pH de uma solução. Os valores de pH são exibidos em um display LCD I2C (16x2) juntamente com um relógio em tempo real (RTC). O display mostra a média dos valores de pH lidos a cada 5 segundos e atualiza a hora a cada segundo.

## Componentes Utilizados

- Arduino Uno
- Sensor de pH (SKU SEN0161 ou similar)
- Display LCD I2C (16x2)
- Módulo RTC DS1307
- Jumpers e Protoboard

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
| SDA        | A4           |
| SCL        | A5           |

### Conexões do Sensor de pH

| Sensor de pH | Arduino Uno  |
|--------------|--------------|
| VCC          | 5V           |
| GND          | GND          |
| Signal       | A0           |

## Instruções de Uso

1. Conecte os componentes conforme descrito nas conexões.
2. Carregue o código no Arduino Uno usando a IDE do Arduino.
3. Abra o Monitor Serial para verificar as leituras do sensor de pH e o horário do RTC.
4. O display LCD exibirá a média dos valores de pH a cada 5 segundos e o relógio será atualizado a cada segundo.

O código fonte completo pode ser encontrado [aqui](https://github.com/LucasYuki1/Global_solution_1_Edge/blob/main/global.cpp).


