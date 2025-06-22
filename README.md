ADXL357 STM32 HAL Driver

C driver library para o sensor acelerômetro ADXL357 de 3 eixos, baixo ruído e baixa deriva.
Desenvolvido para microcontroladores STM32 utilizando a biblioteca STM32 HAL e interface SPI.

---

Features

- Verificação do ID do dispositivo
- Configuração da taxa de saída de dados (output data rate) e faixa de medição
- Habilitação do modo de medição contínua
- Leitura dos dados de aceleração nos eixos X, Y e Z
- Comunicação SPI com controle do Chip Select (CS)
- Tratamento básico de erros

---

Requisitos

- Microcontrolador STM32 com biblioteca STM32 HAL
- Interface SPI conectada ao sensor ADXL357
- Conhecimento básico em C embarcado e uso do STM32CubeIDE ou similar

---

Quick Start

1. Adicione os arquivos do driver ao seu projeto

Inclua ADXL357.c e ADXL357.h na pasta de código-fonte do seu projeto STM32.

2. Configure seu hardware

Configure o periférico SPI e os pinos GPIO do SPI e do Chip Select (CS) conforme o esquema da sua placa.

3. Inicialize a estrutura de handle do driver

ADXL357_HW_InitTypeDef ADXL357_Handle = {
    .SPIhandler = &hspi1,             // Handle SPI configurado no seu projeto
    .CS_GPIOport = GPIOA,             // Porta GPIO do pino CS
    .CS_GPIOpin = GPIO_PIN_4,         // Pino GPIO do CS
    .SPI_Timeout = 100                // Timeout SPI em milissegundos
};

4. Verifique a conexão com o sensor

if (ADXL357_ID_Verify(&ADXL357_Handle) != ADXL_NO_ERROR) {
    // Trate erro: sensor não detectado
}

5. Configure as configurações do sensor

ADXL357_Set_Output_DataRate(&ADXL357_Handle, ADXL_RATE_100HZ);
ADXL357_Set_Range(&ADXL357_Handle, ADXL_RANGE_40G);
ADXL357_Set_Continuous_Measurement(&ADXL357_Handle);

6. Leia os dados de aceleração

ADXL357_Data_TypeDef accel_data;
if (ADXL357_Data_Read(&ADXL357_Handle, &accel_data) == ADXL_NO_ERROR) {
    int32_t x = accel_data.DX;
    int32_t y = accel_data.DY;
    int32_t z = accel_data.DZ;
    // Processar dados de aceleração
}

---

API Overview

Função                         - Descrição
------------------------------|-----------------------------------
ADXL357_ID_Verify()            - Verifica presença do sensor
ADXL357_Set_Output_DataRate()  - Define taxa de saída de dados
ADXL357_Set_Range()            - Define faixa de medição
ADXL357_Set_Continuous_Measurement() - Ativa medição contínua
ADXL357_Data_Read()            - Lê dados de aceleração X, Y, Z
ADXL357_SingleRegister_Read() e Write() - Acesso baixo nível a registradores

---

License

Este projeto está licenciado sob a licença MIT. Veja o arquivo LICENSE para mais detalhes.

---

Autor

Nathan Netzel
Estudante de Engenharia Elétrica - Universidade Estadual de Londrina
