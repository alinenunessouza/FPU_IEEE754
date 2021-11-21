#include<stdio.h>
#include<math.h>
#include<locale.h>

typedef union {
	float f; //f e a struct field ocupam a mesma posição da memória
	struct {
		unsigned int mantissa : 23;
		unsigned int exponente : 8;
		unsigned int sinal : 1;
	} field;
} unionfloat;


/// <summary>
/// Normalizar o número a partir do sinal, expoente e mantissa, colocando o primeiro bit como 1
/// </summary>
/// <returns></returns>
unionfloat normalizaNumero(int sinal, int exp, int mantissa) {
	unionfloat n;
	n.field.sinal = sinal;
	int desloc_exp = 0;
	
	// Se não for zero (não faz sentido procurar)
	if (mantissa != 0) {
		// Procura pelo primeiro 1 da mantissa, da esquerda (MSB) para direita (LSB)
		int mascara = 0x80000000;
		for (int i = 31; i >= 0; i--) {
			if ((mantissa & mascara) != 0) {
				desloc_exp = i;
				break;
			}
			mascara = mascara >> 1;
		}
		// Calcula deslocamento em relação à posição padrão (23)
		desloc_exp = desloc_exp - 23;
		if (desloc_exp < 0)
			mantissa = mantissa << abs(desloc_exp);
		else 
			mantissa = mantissa >> desloc_exp;
		n.field.exponente = exp + desloc_exp + 127;
	} else {
		n.field.exponente = 0;
	}

	n.field.mantissa = mantissa;

	return n;
}

/// <summary>
/// Realiza o complemento
/// </summary>
/// <returns></returns>
void ajustaNegativo(int * mantissa, int * exp) {
	*mantissa = ~(*mantissa) + 1;
}

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
	exp2 = b.field.exponente - 127;

	mantissa_aux = a.field.mantissa + 0x800000;//passando para variavel auxiliar e somando 1.  (1.mantissa implicito que deve ser adicionado
	mantissa_aux2 = b.field.mantissa + 0x800000;//passando para variavel auxiliar e somando 1.

	// Se for um número negativo
	if (a.field.sinal == 1) {
		ajustaNegativo(&mantissa_aux, &exp);
	}
	// Se for um número negativo
	if (b.field.sinal == 1) {
		ajustaNegativo(&mantissa_aux2, &exp2);
	}

	if (exp != exp2) {
		//se os expoentes forem diferentes, tem que pegar o menor e igualar ao maior
		if (exp > exp2) {  // iguala o expoente dos numeros para poder somar (so podemos somar as mantissas se tiverem expoentes iguais) nesse caso exp do numero 1 é maior que o do numero 2
			desloca = exp - exp2; //quantas vezes tem que deslocar essa mantissa
			exp2 = exp;
			mantissa_aux2 = mantissa_aux2 >> desloca; // então deslocamos a vírgula do numero menor (2)
		}
		if (exp < exp2) { // iguala o expoente dos numeros para poder somar (so podemos somar as mantissas se tiverem expoentes iguais) nesse caso exp do numero 2 é maior que o do numero 1
			desloca = exp2 - exp; //quantas vezes tem que deslocar essa mantissa
			exp = exp2;
			mantissa_aux = mantissa_aux >> desloca;  // então deslocamos a vírgula do numero menor (1)
		}
	} 

	soma_mantissa = mantissa_aux + mantissa_aux2;

	int sinal = 0;
	// Só faz o complemento se o número for negativo
	if (soma_mantissa < 0) {
		soma_mantissa = ~soma_mantissa;
		sinal = 1;
	}
	
	return normalizaNumero(sinal, exp, soma_mantissa);
}

void main(void) {
    unionfloat n1, n2;
    n1.f = 1.0;
    n2.f = 2.0;
    add(n1, n2);
}