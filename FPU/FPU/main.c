//#include <iostream>
#include<stdio.h>
#include<math.h>

/// <summary>
/// 
/// </summary>
/// <param name="n">numero de bits que será implementado o número</param>
/// <param name="i">valor decimal qualquer</param>
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

int main() {

	unionfloat var;
	unionfloat var2;
	int exp;//teste
	int exp2;//teste
	int desloca;//teste
	int mantissa_aux;//teste
	int mantissa_aux2;//teste
	int soma_mantissa;//teste
	printf("Entre com um ponto flutuante 1: ");
	scanf_s("%f", &var.f);//35.75
	//var.f=20.50;//ao inves de ler do teclado o valor ta fixo
	printf("Entre com um ponto flutuante 2: ");
	scanf_s("%f", &var2.f);//20.50
	//var2.f=35.75;//ao inves de ler do teclado o valor ta fixo

	printf("\n\n");
	printf("%d ", var.field.sinal);
	binario(var.field.exponente, 8);
	printf(" ");
	binario(var.field.mantissa, 23);
	printf("\n");
	printf("numero 1 reconstituido  : %f \n", pow(-1, (var.field.sinal)) * (1.0 + var.field.mantissa / pow(2, 23)) * pow(2, (var.field.exponente - 127)));

	printf("\n");
	printf("%d ", var2.field.sinal);
	binario(var2.field.exponente, 8);
	printf(" ");
	binario(var2.field.mantissa, 23);
	printf("\n");
	printf("numero 2 reconstituido  : %f \n", pow(-1, (var2.field.sinal)) * (1.0 + var2.field.mantissa / pow(2, 23)) * pow(2, (var2.field.exponente - 127)));
	printf("\n");

	//soma
	exp = var.field.exponente - 127;// recupera o expoente limpo  (valora armazenado na variavel expoente - bias(127))
	exp2 = var2.field.exponente - 127;//teste

	mantissa_aux = var.field.mantissa + 0x800000;//passando para variavel auxiliar e somando 1.  (1.mantissa implicito que deve ser adicionado
	mantissa_aux2 = var2.field.mantissa + 0x800000;//passando para variavel auxiliar e somando 1.
	if (exp != exp2) {
		if (exp > exp2) {  // iguala o expoente dos numeros para poder somar (so podemos somar as mantissas se tiverem expoentes iguais) nesse caso exp do numero 1 é maior que o do numero 2
			desloca = exp - exp2;
			mantissa_aux2 = mantissa_aux2 >> desloca; // então  deslocamos a virgual do numero menor (2)
			soma_mantissa = mantissa_aux2 + mantissa_aux;
			binario(soma_mantissa, 23);
			printf("\n\n numero reconstituido  : %f \n", pow(-1, (var.field.sinal)) * (soma_mantissa / pow(2, 23)) * pow(2, (var.field.exponente - 127)));
		}
		if (exp < exp2) { // iguala o expoente dos numeros para poder somar (so podemos somar as mantissas se tiverem expoentes iguais) nesse caso exp do numero 2 é maior que o do numero 1
			desloca = exp2 - exp;
			mantissa_aux = mantissa_aux >> desloca;  // então  deslocamos a virgual do numero menor (1)
			soma_mantissa = mantissa_aux + mantissa_aux2; // realizamos a soma
			binario(soma_mantissa, 23);
			printf("\n\n numero reconstituido  : %f \n", pow(-1, (var2.field.sinal)) * (soma_mantissa / pow(2, 23)) * pow(2, (var2.field.exponente - 127)));
		}
	}
	else {
		soma_mantissa = mantissa_aux + mantissa_aux2;
		binario(soma_mantissa, 23);
		printf("\n\n numero reconstituido  : %f \n", pow(-1, (var2.field.sinal)) * (soma_mantissa / pow(2, 23)) * pow(2, (var2.field.exponente - 127)));
	}

	return 0;
}
