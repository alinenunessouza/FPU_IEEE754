# Projeto de unidade de aritmética em ponto flutuante (FPU) com padrão IEE754

- A FPU implementada leva em consideração a estrutura de numeros de precisão simples (32 bits) conforme o padrão IEEE 754:

![image](https://user-images.githubusercontent.com/72985725/139558295-c3476c6f-81bd-4ad3-94d3-a25780b0b5fb.png)
- 1 bit para sinal (bit 31): 0 - positivo; 1 - negativo
- 8 bits são para expoente (bits 30 à 23): o valor do expoente é acrescido de 127 para não ter informações negativas no expoente e considerar possíveis números fracionários negativos como inteiros para fins de comparacão, sendo assim, o valor do expoente está entre -127 e +127
- 23 bits para representar a parte fracionária do número, também chamada de mantissa (bits 22 à 0)

#### Estrutura da FPU
![image](https://user-images.githubusercontent.com/72985725/139558387-ee6f5c6a-76ff-41a7-8ed2-3128a9c70fb0.png)

- op[1:0]: seleciona qual operação será utilizada (soma ou subtração)
- out[31:0]: número equivalente a saída da operação no padrão 754
- sinalização de overflow: quando não tem bits suficientes para representar o número
- sinalização de underflow: quando não tem precisão suficiente para mostrar o número (caso do número ser muito pequeno)

#### Operações
- Soma: TODO explicação
- Subtração: TODO explicação

#### Implementacão da FPU no Logisim
- Na entrada do circuito, foi colocada uma entrada de 1 bit para o seletor, que indica qual operação será realizada (soma ou subtração)
- Na entrada e saída do circuito, há registradores que para armazenar as entradas e o resultado da operação
- Registradores de entrada ativos na borda de subida do clock
- Registradores de saída ativos na borda de descida do clock

##### Código das operações
- 00 -> soma
- 01 -> subtração

