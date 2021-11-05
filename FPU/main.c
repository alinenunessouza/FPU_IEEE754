#include<stdio.h>
#include<math.h>
#include<locale.h>
#include<conio.h>

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

float reconstruirNumero(unionfloat numero) {
	return pow(-1, (numero.field.sinal)) * (1.0 + numero.field.mantissa / pow(2, 23)) * pow(2, (numero.field.exponente - 127));
}

unionfloat normalizaNumero(int sinal, int exp, int mantissa) {
	unionfloat n;
	n.field.sinal = sinal;
	int desloc_exp = 0;
	
	if (mantissa & 0xFFFFFF != 0) {
		for (desloc_exp; (mantissa & 0x800000) == 0; desloc_exp++) {
			mantissa = mantissa << 1;
		}
	} else if (mantissa != 0) {
		int mascara = 0x800000;
		for (int i = 0; i < 5; i--) {
			if ((mantissa & mascara) != 0) {
				desloc_exp = i;
			}
			mascara = mascara << 1;
		}	
		mantissa = mantissa << desloc_exp;	
	}
	n.field.exponente = exp - desloc_exp + 127;
	n.field.mantissa = mantissa;

	return n;
}

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

void exibeNumero(unionfloat n, char * descricao) {
	printf("\n");
	printf("%d ", n.field.sinal);
	binario(n.field.exponente, 8);
	printf(" ");
	binario(n.field.mantissa, 23);
	printf("\n");
	printf("%s reconstituído  : %f \n", descricao, reconstruirNumero(n));
	printf("\n");
}

int main() {
    setlocale(LC_ALL, "Portuguese");

	unionfloat numero1;
	unionfloat numero2;
	char op;

	unionfloat numeroResultadoOperacao;

	printf("Entre com um ponto flutuante 1: ");
	//scanf("%f", &numero1.f);
	numero2.f = 1;
	printf("Entre com um ponto flutuante 2: ");
	//scanf("%f", &numero2.f);
	numero1.f = 1;
	printf("Informe a operação (+/-): ");
	//op = getch();
	
	if (op == '-') {
		numero2.f = - numero2.f;
	}
	printf("\n\n");
	
	exibeNumero(numero1, "Numero 1");
	exibeNumero(numero2, "Numero 2");

	numeroResultadoOperacao = add(numero1, numero2);
	
	exibeNumero(numeroResultadoOperacao, "Resultado");
	return 0;
}
