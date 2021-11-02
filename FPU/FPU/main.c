//#include <iostream>
#include<stdio.h>
#include<math.h>

/// <summary>
/// Fun��o para imprimir na tela os bits de um n�mero
/// </summary>
/// <param name="n">valor decimal qualquer</param>
/// <param name="i">numero de bits que ser� implementado o n�mero</param>
/// <returns></returns>
int binario(int n, int i)
{
	int k;
	for (i--; i >= 0; i--)
	{
		k = n >> i; //valor de n deslocado em i
		if (k & 1) //1 � uma m�scara, n�mero 1 em bin�rio 00000001
			printf("1");
		else
			printf("0");
	}
}

typedef union {
	float f; //f e a struct field ocupam a mesma posi��o da mem�ria
	struct {
		unsigned int mantissa : 23;
		unsigned int exponente : 8;
		unsigned int sinal : 1;
	} field;
} unionfloat;

float reconstruirNumero(unionfloat numero, int soma) {
	return pow(-1, (numero.field.sinal)) * (soma / pow(2, 23)) * pow(2, (numero.field.exponente - 127));
}

unionfloat normalizaNumero(int sinal, int exp, int mantissa) {
	unionfloat n;
	n.field.sinal = sinal;
	int desloc_exp = 0;			      
	for (desloc_exp = 0; (mantissa & 0x800000) != 0; desloc_exp++) {
		mantissa = mantissa << 1;
		printf("\n%d ", desloc_exp);
		binario(mantissa, 30);
	}
	n.field.exponente = - desloc_exp + 127;
	n.field.mantissa = mantissa << 1; //Desloca mais uma vez para abstrair primeiro 1

	printf("\n\n");
	printf("%d ", n.field.sinal);
	binario(n.field.exponente, 8);
	printf(" ");
	binario(n.field.mantissa, 23);

	return n;	
}

void ajustaNegativo(int * mantissa, int * exp) {
	// Faz o complemento de 2 da mantissa e deixar �ltimos 24 bits
	*mantissa = (~(*mantissa) + 1) & 0xFFFFFF;
	// binario(*mantissa, 24);
	// printf("\n");
	// // Se n�mero complementado ficou maior que 23 bits
	// if (*mantissa & 0xF00000) {
	// 	// Desloca uma casa para direita e aumenta expoente (para manter em 23 bits)
	// 	*mantissa = (*mantissa) >> 1;
	// 	*exp = *exp + 1;
	// }
}

/// <summary>
/// Opera��o de soma de dois n�meros com ponto flutuante
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

	// Se for um n�mero negativo
	if (a.field.sinal == 1) {
		ajustaNegativo(&mantissa_aux, &exp);
	}
	// Se for um n�mero negativo
	if (b.field.sinal == 1) {
		ajustaNegativo(&mantissa_aux2, &exp2);
	}

	if (exp != exp2) {
		//se os expoentes forem diferentes, tem que pegar o menor e igualar ao maior
		if (exp > exp2) {  // iguala o expoente dos numeros para poder somar (so podemos somar as mantissas se tiverem expoentes iguais) nesse caso exp do numero 1 � maior que o do numero 2
			binario(soma_mantissa, 23);
			desloca = exp - exp2; //quantas vezes tem que deslocar essa mantissa
			mantissa_aux2 = mantissa_aux2 >> desloca; // ent�o  deslocamos a virgual do numero menor (2)
			soma_mantissa = mantissa_aux2 + mantissa_aux;
			binario(soma_mantissa, 23);
			printf("\n\n numero reconstituido  : %f \n", reconstruirNumero(a, soma_mantissa));

			//TODO verificar se precisa normalizar o n�mero: deslocar a v�rgula e aumentar o expoente
		}
		if (exp < exp2) { // iguala o expoente dos numeros para poder somar (so podemos somar as mantissas se tiverem expoentes iguais) nesse caso exp do numero 2 � maior que o do numero 1
			desloca = exp2 - exp;
			mantissa_aux = mantissa_aux >> desloca;  // ent�o  deslocamos a virgual do numero menor (1)
			soma_mantissa = mantissa_aux + mantissa_aux2; // realizamos a soma
			binario(soma_mantissa, 23);
			printf("\n\n numero reconstituido  : %f \n", reconstruirNumero(b, soma_mantissa));
		}
	}
	else {
		printf("\n\nMantissas somadas:\n");
		printf("\n1:");
		binario(mantissa_aux, 30);
		printf("\n2:");
		binario(mantissa_aux2, 30);
		printf("\nsoma:");
		soma_mantissa = mantissa_aux + mantissa_aux2;
		binario(soma_mantissa, 30);
		//printf("\n\n numero reconstituido  : %f \n", reconstruirNumero(b, soma_mantissa));
		printf("\n\n numero reconstituido  : %f \n", reconstruirNumero(normalizaNumero(a.field.sinal, exp, soma_mantissa), soma_mantissa));
	}
}

int main() {

	unionfloat numero1;
	unionfloat numero2;

	unionfloat numeroResultadoOperacao;

	printf("Entre com um ponto flutuante 1: ");
	//scanf("%f", &numero1.f);//35.75
	//var.f=20.50;//ao inves de ler do teclado o valor ta fixo
	numero1.f = 4.78;
	printf("Entre com um ponto flutuante 2: ");
	//scanf("%f", &numero2.f);//20.50
	//var2.f=35.75;//ao inves de ler do teclado o valor ta fixo
	numero2.f = -5.23;
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
	
	numeroResultadoOperacao = add(numero1, numero2);


	return 0;
}
