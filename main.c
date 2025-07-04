#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VENDAS 50
#define MAX_CARACTERE 50
#define MAX_DATA 20

typedef enum { NULO = 0, VALIDO = 1 } Estado;

typedef struct {
    Estado estado;
    char data[MAX_DATA];
    int codigo;
    char nome[MAX_CARACTERE];
    char marca[MAX_CARACTERE];
    int quantidade;
    float precoUnitario;
} ItensVendidos;

typedef struct {
    int totalItens;
    int totalClientes;
    float faturamentoBruto;    
} EstatisticasDiarias;

void CalculaPrecoPago(); // ainda não implementada

void EntradaManual(ItensVendidos produtosVendidos[12][30][MAX_VENDAS]) {
    bool continua = true;
    char data[MAX_DATA];
    int dia, mes;
    int codigo = 0;
    int opcao;
    
    while (continua) {
        printf("\nRegistro da Venda\nData da Venda - dia/mes: ");
        scanf("%19s", data);  // garante limite do array
        
        if (sscanf(data, "%d/%d", &dia, &mes) != 2) {
            printf("Formato inválido. Use dia/mes (ex: 03/07)\n");
            continue;
        }
        
        int idxDia = dia - 1;
        int idxMes = mes - 1;
        
        if (idxMes < 0 || idxMes >= 12 || idxDia < 0 || idxDia >= 30) {
            printf("Data inválida! Mês deve ser entre 1 e 12, dia entre 1 e 30.\n");
            continue;
        }
        
        if (codigo >= MAX_VENDAS) {
            printf("Limite de vendas atingido para este dia!\n");
            break;
        }
        
        ItensVendidos *item = &produtosVendidos[idxMes][idxDia][codigo];
        item->estado = VALIDO;
        strcpy(item->data, data);
        item->codigo = codigo;
        
        printf("Nome do Produto: ");
        scanf("%49s", item->nome);
        
        printf("Marca do produto: ");
        scanf("%49s", item->marca);
        
        printf("Quantidades do Produto: ");
        scanf("%d", &item->quantidade);
        
        printf("Preco Unitario do Produto: ");
        scanf("%f", &item->precoUnitario);
        
        printf("Deseja adicionar outra venda? (1 - Sim, 0 - Não): ");
        scanf("%d", &opcao);
        
        continua = (opcao == 1);
        if (continua) codigo++;
    }
}

int main() {
    static ItensVendidos produtosVendidos[12][30][MAX_VENDAS] = {0}; // zera todos os valores
    EntradaManual(produtosVendidos);
    
    return 0;
}