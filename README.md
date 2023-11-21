# GS_EDGE

# Projeto ESP32 - Sensor DHT22, Display OLED, MQTT

Projeto desenvolvido por Lucas Feijó (RM 99727) e Ana Beatriz (RM 97865). 🛠️

**Dificuldade na Estocagem de Medicamentos Sensíveis à Umidade:**

A armazenagem de medicamentos sensíveis à umidade representa um grande desafio para os hospitais. A manutenção das condições ideais de umidade é crucial para preservar a eficácia e a segurança desses medicamentos. No entanto, a falta de sistemas automatizados de monitoramento dificulta o controle preciso e constante das condições de armazenamento. Funcionários hospitalares muitas vezes precisam realizar verificações manuais periódicas, o que pode ser suscetível a erros humanos e não garantir a detecção imediata de desvios nas condições ideais.

## Solução Proposta

Este projeto visa oferecer uma solução prática e automatizada para monitoramento da umidade em ambientes de armazenamento hospitalar. Utilizando o ESP32, sensores DHT22 e tecnologia MQTT, o sistema possibilita o monitoramento contínuo das condições de umidade dos locais de estocagem. Com a coleta de dados em tempo real, é possível garantir que a umidade permaneça dentro dos parâmetros aceitáveis, evitando a deterioração dos medicamentos. O display OLED integrado fornece informações visuais imediatas sobre as condições de umidade, enquanto os dados são enviados para um servidor MQTT, permitindo o acompanhamento remoto e notificações automáticas em caso de desvios.

Essa solução não apenas reduz a carga de trabalho dos funcionários, permitindo-lhes focar em outras áreas críticas da assistência ao paciente, mas também contribui para a preservação da qualidade dos medicamentos, garantindo tratamentos mais eficazes e seguros para os pacientes.

## Informações do Projeto

- **Data do Projeto:** 21/11/2023 📅
- **Status do Projeto:** Concluído ✅

Este projeto consiste na leitura de dados de um sensor DHT22 (umidade e temperatura), exibição dos dados em um display OLED, controle de um LED e um buzzer com base na umidade lida, além de enviar os dados para um servidor MQTT.

## Componentes Utilizados

- ESP32
- Sensor DHT22
- Display OLED
- LED
- Buzzer
- Conexão Wi-Fi para comunicação
- Servidor MQTT (neste exemplo: mqtt.tago.io)

## Configuração

1. **Configuração do Hardware:**
   - Conectar o sensor DHT22 ao pino especificado no código.
   - Conectar o display OLED e definir os pinos corretamente conforme a conexão.

2. **Configuração do Software:**
   - Certifique-se de ter as bibliotecas necessárias instaladas para o ESP32, DHT22, OLED, MQTT, etc.

3. **Configuração do Wi-Fi e MQTT:**
   - No código, configure as credenciais da sua rede Wi-Fi e as informações do servidor MQTT (como SSID, senha, endereço do servidor, porta e token do dispositivo).

## Como Usar

1. Carregue o código para o ESP32 após realizar todas as conexões físicas corretamente.

2. O ESP32 lerá os dados do sensor DHT22, exibirá os valores no display OLED e controlará o LED e o buzzer com base na umidade lida.

3. Os dados (umidade e temperatura) serão publicados em um tópico MQTT especificado no código para que possam ser consumidos ou processados por outros dispositivos ou aplicativos.

## Link do projeto
https://wokwi.com/projects/382039485790694401

## Notas Adicionais

- Certifique-se de ter as bibliotecas corretas instaladas no Arduino IDE para todas as funcionalidades utilizadas neste projeto.
- Se necessário, ajuste as configurações do servidor MQTT, como endereço, porta e tópico, de acordo com a sua configuração específica.
