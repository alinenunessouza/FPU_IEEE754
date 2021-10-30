# Projeto de unidade de aritmética em ponto flutuante (FPU) com padrão IEE754

![image](https://user-images.githubusercontent.com/72985725/139558295-c3476c6f-81bd-4ad3-94d3-a25780b0b5fb.png)

#### Estrutura da FPU
![image](https://user-images.githubusercontent.com/72985725/139558387-ee6f5c6a-76ff-41a7-8ed2-3128a9c70fb0.png)

- op[1:0]: seleciona qual operação será utilizada (soma ou subtração)
- out[31:0]: número equivalente a saída da operação no padrão 754
- sinalização de overflow: quando não tem bits suficientes para representar o número
- sinalização de underflow: quando não tem precisão suficiente para mostrar o número (caso do número ser muito pequeno)

##### Código das operações
- 00 -> soma
- 01 -> subtração

