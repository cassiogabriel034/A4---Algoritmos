#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VENDAS 10
#define MAX_CARACTERE 50
#define MAX_DATA 20

typedef enum { NULO = 0, VALIDO = 1 } Estado;

typedef enum { 
    CAMISA = 1, 
    CALCA = 2, 
    SAPATO = 3, 
    JAQUETA = 4, 
    VESTIDO = 5 
} TipoProduto;

typedef struct {
    Estado estado;
    char data[MAX_DATA];
    int codigo;
    TipoProduto produto;
    char marca[MAX_CARACTERE];
    int quantidade;
    float precoUnitario;
    int clienteId;  // Corrigido nome (estava clinteId)
} ItensVendidos;

typedef struct {
    int totalItens;
    int totalClientes;
    float faturamentoBruto;    
} EstatisticasDiarias;

// Função para verificar se um cliente já está na lista
bool clienteJaExiste(int clientesUnicos[], int totalClientes, int clienteId) {
    for (int i = 0; i < totalClientes; i++) {
        if (clientesUnicos[i] == clienteId) {
            return true;
        }
    }
    return false;
}

void CalculaEstatisticasDiarias(EstatisticasDiarias dadosDiarios[12][30], ItensVendidos produtosVendidos[12][30][MAX_VENDAS]) {
    for (int mes = 0; mes < 12; mes++) {
        for (int dia = 0; dia < 30; dia++) {
            EstatisticasDiarias *estat = &dadosDiarios[mes][dia];
            int totalItens = 0;
            float faturamento = 0;
            int totalClientes = 0;
            
            // Array para armazenar IDs dos clientes únicos do dia
            int clientesUnicos[MAX_VENDAS];

            for (int i = 0; i < MAX_VENDAS; i++) {
                ItensVendidos *item = &produtosVendidos[mes][dia][i];
                
                if (item->estado == VALIDO) {
                    totalItens += item->quantidade;
                    
                    // Aplicar desconto de 10% se quantidade >= 3
                    float precoFinal = item->quantidade * item->precoUnitario;
                    if (item->quantidade >= 3) {
                        precoFinal = precoFinal * 0.9; // 10% de desconto
                    }
                    faturamento += precoFinal;
                    
                    // Verificar se o cliente já foi contado hoje
                    if (!clienteJaExiste(clientesUnicos, totalClientes, item->clienteId)) {
                        clientesUnicos[totalClientes] = item->clienteId;
                        totalClientes++;
                    }
                }
            }

            estat->totalItens = totalItens;
            estat->faturamentoBruto = faturamento;
            estat->totalClientes = totalClientes;
        }
    }
}

void EntradaManual(ItensVendidos produtosVendidos[12][30][MAX_VENDAS]) {
    bool continua = true;
    char data[MAX_DATA];
    int dia, mes;
    int codigo = 0;
    int opcao;
    
    while (continua) {
        printf("\nRegistro de Vendas");
        printf("Data da Venda - dia/mes: ");
        scanf("%19s", data);
        
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
        
        printf("Id do Cliente: ");
        scanf("%d", &item->clienteId);
        
        strcpy(item->data, data);
        item->codigo = codigo;
        
        printf("Escolha o Produto:\n");
        printf("1 - Camisa\n");
        printf("2 - Calca\n");
        printf("3 - Sapato\n");
        printf("4 - Jaqueta\n");
        printf("5 - Vestido\n");
        printf("Opcao: ");
        int opcaoProduto;
        scanf("%d", &opcaoProduto);
        
        if (opcaoProduto >= 1 && opcaoProduto <= 5) {
            item->produto = (TipoProduto)opcaoProduto;
        } else {
            printf("Opcao invalida! Definindo como Camisa.\n");
            item->produto = CAMISA;
        }
        
        printf("Marca do produto: ");
        scanf("%49s", item->marca);
        
        printf("Quantidades do Produto: ");
        scanf("%d", &item->quantidade);
        
        printf("Preco Unitario do Produto: ");
        scanf("%f", &item->precoUnitario);
        
        // Mostrar total de itens vendidos até agora (requisito do trabalho)
        printf("Total de itens vendidos nesta venda: %d\n", item->quantidade);
        
        printf("Deseja adicionar outra venda? (1 - Sim, 0 - Não): ");
        scanf("%d", &opcao);
        
        continua = (opcao == 1);
        if (continua) {
            codigo++;
        }
    }
}

// Função para testar e mostrar os dados
void MostrarEstatisticas(EstatisticasDiarias dadosDiarios[12][30]) {
    printf("\n=== RELATÓRIO DE ESTATÍSTICAS ===\n");
    for (int mes = 0; mes < 12; mes++) {
        for (int dia = 0; dia < 30; dia++) {
            EstatisticasDiarias *estat = &dadosDiarios[mes][dia];
            if (estat->totalItens > 0) {
                printf("Data: %02d/%02d - Itens: %d, Clientes: %d, Faturamento: R$ %.2f\n",
                       dia + 1, mes + 1, estat->totalItens, estat->totalClientes, estat->faturamentoBruto);
            }
        }
    }
}

int main() {
    static ItensVendidos produtosVendidos[12][30][MAX_VENDAS] = {0};
    static EstatisticasDiarias dadosDiarios[12][30] = {0};

    EntradaManual(produtosVendidos);
    CalculaEstatisticasDiarias(dadosDiarios, produtosVendidos);
    MostrarEstatisticas(dadosDiarios);
    
    return 0;
}