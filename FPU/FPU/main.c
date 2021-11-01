//#include <iostream>
#include<stdio.h>
#include<math.h>

/// <summary>
/// Função para imprimir na tela os bits de um número
/// </summary>
/// <param name="n">valor decimal qualquer</param>
/// <param name="i">numero de bits que será implementado o número</param>
/// <returns></returns>
int binario(int n, int i)
{
	int k;
	for (i--; i >= 0; i--)
	{
		k = n >> i; //valor de n deslocado em i
		if (k & 1) //1 é uma máscara, número 1 em binário 00000001
			printf("1");
		else
			printf("0");
	}
}

typedef union {
	float f; //f e a struct field ocupam a mesma posição da memória
	struct {
		unsigned int mantissa : 23;
		unsigned int exponente : 8;
		unsigned int sinal : 1;
	} field;
} unionfloat;

/// <summary>
/// Operação de soma de dois números com ponto flutuante
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
unionfloat add(unionfloat a, unionfloat b) {

	int exp;
	int exp2;
	int desloca;
	int mantissa_aux;
	int mantissa_aux2;
	int soma_mantissa;

	exp = a.field.exponente - 127;// recupera o expoente limpo  (valora armazenado na variavel expoente - bias(127))
	exp2 = b.field.exponente - 127;//teste

	mantissa_aux = a.field.mantissa + 0x800000;//passando para variavel auxiliar e somando 1.  (1.mantissa implicito que deve ser adicionado
	mantissa_aux2 = b.field.mantissa + 0x800000;//passando para variavel auxiliar e somando 1.

	if (exp != exp2) {
		//se os expoentes forem diferentes, tem que pegar o menor e igualar ao maior
		if (exp > exp2) {  // iguala o expoente dos numeros para poder somar (so podemos somar as mantissas se tiverem expoentes iguais) nesse caso exp do numero 1 é maior que o do numero 2
			desloca = exp - exp2; //quantas vezes tem que deslocar essa mantissa
			mantissa_aux2 = mantissa_aux2 >> desloca; // então  deslocamos a virgual do numero menor (2)
			soma_mantissa = mantissa_aux2 + mantissa_aux;
			binario(soma_mantissa, 23);
			printf("\n\n numero reconstituido  : %f \n", pow(-1, (a.field.sinal)) * (soma_mantissa / pow(2, 23)) * pow(2, (a.field.exponente - 127)));

			//TODO verificar se precisa normalizar o número
		}
		if (exp < exp2) { // iguala o expoente dos numeros para poder somar (so podemos somar as mantissas se tiverem expoentes iguais) nesse caso exp do numero 2 é maior que o do numero 1
			desloca = exp2 - exp;
			mantissa_aux = mantissa_aux >> desloca;  // então  deslocamos a virgual do numero menor (1)
			soma_mantissa = mantissa_aux + mantissa_aux2; // realizamos a soma
			binario(soma_mantissa, 23);
			printf("\n\n numero reconstituido  : %f \n", pow(-1, (b.field.sinal)) * (soma_mantissa / pow(2, 23)) * pow(2, (b.field.exponente - 127)));
		}
	}
	else {
		soma_mantissa = mantissa_aux + mantissa_aux2;
		binario(soma_mantissa, 23);
		printf("\n\n numero reconstituido  : %f \n", pow(-1, (b.field.sinal)) * (soma_mantissa / pow(2, 23)) * pow(2, (b.field.exponente - 127)));
	}
}

/// <summary>
/// Operação de subtração de dois números com ponto flutuante
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
unionfloat subtraction(unionfloat a, unionfloat b) {

}

float reconstruirNumero(unionfloat numero) {
	return pow(-1, (numero.field.sinal)) * (1.0 + numero.field.mantissa / pow(2, 23)) * pow(2, (numero.field.exponente - 127));
}

int main() {

	unionfloat numero1;
	unionfloat numero2;

	unionfloat numeroResultadoOperacao;

	printf("Entre com um ponto flutuante 1: ");
	scanf_s("%f", &numero1.f);//35.75
	//var.f=20.50;//ao inves de ler do teclado o valor ta fixo
	printf("Entre com um ponto flutuante 2: ");
	scanf_s("%f", &numero2.f);//20.50
	//var2.f=35.75;//ao inves de ler do teclado o valor ta fixo

	if (numero1.field.exponente > numero2.field.exponente || (numero1.field.exponente == numero2.field.exponente && numero1.field.mantissa > numero2.field.mantissa))
		numeroResultadoOperacao = add(numero1, numero2);
	else
		numeroResultadoOperacao = add(numero2, numero1);

	printf("\n\n");
	printf("%d ", numero1.field.sinal);
	binario(numero1.field.exponente, 8);
	printf(" ");
	binario(numero1.field.mantissa, 23);
	printf("\n");
	printf("numero 1 reconstituido  : %f \n", pow(-1, (numero1.field.sinal)) * (1.0 + numero1.field.mantissa / pow(2, 23)) * pow(2, (numero1.field.exponente - 127)));
	//printf("numero 1 reconstituido  : %f \n", reconstruirNumero(numero1));

	printf("\n");
	printf("%d ", numero2.field.sinal);
	binario(numero2.field.exponente, 8);
	printf(" ");
	binario(numero2.field.mantissa, 23);
	printf("\n");
	printf("numero 2 reconstituido  : %f \n", pow(-1, (numero2.field.sinal)) * (1.0 + numero2.field.mantissa / pow(2, 23)) * pow(2, (numero2.field.exponente - 127)));
	//printf("numero 2 reconstituido  : %f \n", reconstruirNumero(numero2));
	printf("\n");

	return 0;
}
