#include <stdio.h>
#include <string.h>

// Define o número máximo de vendas diárias e clientes
#define MAX_VENDAS 100

// Estrutura que representa um item vendido
typedef struct {
    int codigo;       // Código do item
    char nome[50];    // Nome do item
    char marca[50];   // Marca do item
    int quantidade;    // Quantidade de itens
    float preco_unitario; // Preço unitário do item
} ItemVendido;

// Estrutura que contém os dados de cada venda
typedef struct {
    ItemVendido itens[MAX_VENDAS];
    int total_itens;
    float total_venda;
    int cliente_id;
} VendaDiaria;

// Função para calcular o preço pago na venda
float calcularPreco(ItemVendido item) {
    float subtotal = item.quantidade * item.preco_unitario;

    // Aplicação de desconto (10%) se a quantidade for maior ou igual a 3
    if (item.quantidade >= 3) {
        subtotal *= 0.9; // Desconto de 10%
    }

    return subtotal;
}

// Função para entrada manual de dados
void entradaManual(VendaDiaria *vendas, int *total_clientes) {
    int continuar = 1; // Controla se o usuário deseja continuar cadastrando vendas
    int cliente_id = 1; // ID único para cada cliente

    while (continuar) {
        printf("\n=== Registro de Venda para o Cliente %d ===\n", cliente_id);

        // Inicializa a estrutura de venda
        vendas[*total_clientes].total_itens = 0;
        vendas[*total_clientes].cliente_id = cliente_id;

        int continuar_itens = 1; // Controla se o usuário deseja adicionar mais itens
        while (continuar_itens) {
            if (vendas[*total_clientes].total_itens >= MAX_VENDAS) {
                printf("Limite de itens excedido para este cliente.\n");
                break;
            }

            // Cadastro de um novo item
            printf("\n--- Registro de Item ---\n");
            printf("Código do item: ");
            scanf("%d", &vendas[*total_clientes].itens[vendas[*total_clientes].total_itens].codigo);

            printf("Nome do item: ");
            scanf("%s", vendas[*total_clientes].itens[vendas[*total_clientes].total_itens].nome);

            printf("Marca do item: ");
            scanf("%s", vendas[*total_clientes].itens[vendas[*total_clientes].total_itens].marca);

            printf("Quantidade de itens: ");
            scanf("%d", &vendas[*total_clientes].itens[vendas[*total_clientes].total_itens].quantidade);

            printf("Preço unitário do item: ");
            scanf("%f", &vendas[*total_clientes].itens[vendas[*total_clientes].total_itens].preco_unitario);

            // Incrementa o contador de itens
            vendas[*total_clientes].total_itens++;

            // Verifica se o usuário deseja adicionar mais itens
            printf("\nDeseja adicionar outro item? (1 - Sim, 0 - Não): ");
            scanf("%d", &continuar_itens);
        }

        // Incrementa o contador de clientes
        (*total_clientes)++;
        cliente_id++;

        // Verifica se o usuário deseja registrar outra venda
        printf("\nDeseja registrar outra venda? (1 - Sim, 0 - Não): ");
        scanf("%d", &continuar);
    }
}

// Função para calcular o total das vendas de um cliente
void calcularTotalVenda(VendaDiaria *venda) {
    venda->total_venda = 0;

    for (int i = 0; i < venda->total_itens; i++) {
        venda->total_venda += calcularPreco(venda->itens[i]);
    }
}

// Função principal
int main() {
    // Declaração das estruturas para armazenar vendas
    VendaDiaria vendas[MAX_VENDAS];
    int total_clientes = 0;

    printf("=== Sistema de Registro de Vendas Diárias ===\n");

    // Entrada manual de dados
    entradaManual(vendas, &total_clientes);

    // Calcula o total das vendas para cada cliente
    for (int i = 0; i < total_clientes; i++) {
        calcularTotalVenda(&vendas[i]);
    }

    // Exibe um resumo das vendas registradas
    printf("\n=== Resumo das Vendas Registradas ===\n");
    for (int i = 0; i < total_clientes; i++) {
        printf("\nCliente %d:\n", vendas[i].cliente_id);
        printf("Itens vendidos: %d\n", vendas[i].total_itens);
        printf("Valor total da venda: R$%.2f\n", vendas[i].total_venda);
    }

    // Exibe a quantidade total de clientes
    printf("\nQuantidade total de clientes que realizaram compras: %d\n", total_clientes);

    return 0;
}