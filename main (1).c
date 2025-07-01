#include <stdio.h>
#include <string.h>

#define MAX_CARTAS 100

typedef struct {
    char codigo[4];
    char nome[50];
    long populacao;
    double area;
    double pib;
    int pontos;
    // campos calculados (nível Aventureiro)
    double densidade;
    double pibPerCapita;
} Carta;

void cadastrarCarta(Carta cartas[], int *total);
void listarCartas(Carta cartas[], int total);
void compararCartas(Carta cartas[], int total);
void calcularAventureiro(Carta *c);

int main() {
    Carta cartas[MAX_CARTAS];
    int total = 0;
    int opcao;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Cadastrar carta\n");
        printf("2. Listar cartas\n");
        printf("3. Comparar cartas\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch (opcao) {
            case 1:
                cadastrarCarta(cartas, &total);
                break;
            case 2:
                listarCartas(cartas, total);
                break;
            case 3:
                compararCartas(cartas, total);
                break;
            case 0:
                printf("Saindo... Até a próxima!\n");
                break;
            default:
                printf("Opcao inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

void cadastrarCarta(Carta cartas[], int *total) {
    if (*total >= MAX_CARTAS) {
        printf("Limite de cartas atingido.\n");
        return;
    }

    Carta *c = &cartas[*total];
    printf("\n--- Cadastro de Carta ---\n");

    printf("Código (ex: A01): ");
    fgets(c->codigo, sizeof(c->codigo), stdin);
    c->codigo[strcspn(c->codigo, "\n")] = '\0';

    printf("Nome da cidade: ");
    fgets(c->nome, sizeof(c->nome), stdin);
    c->nome[strcspn(c->nome, "\n")] = '\0';

    printf("População: ");
    scanf("%ld", &c->populacao);

    printf("Área (km²): ");
    scanf("%lf", &c->area);

    printf("PIB (em bilhões): ");
    scanf("%lf", &c->pib);

    printf("Pontos turísticos (0 a 10): ");
    scanf("%d", &c->pontos);
    getchar(); // limpar buffer

    calcularAventureiro(c);  // nível aventureiro
    (*total)++;
    printf("Carta cadastrada com sucesso!\n");
}

void calcularAventureiro(Carta *c) {
    c->densidade = c->populacao / c->area;
    c->pibPerCapita = (c->populacao > 0) ? (c->pib * 1e9 / c->populacao) : 0;
}

void listarCartas(Carta cartas[], int total) {
    if (total == 0) {
        printf("Nenhuma carta cadastrada.\n");
        return;
    }

    printf("\n--- Lista de Cartas (%d) ---\n", total);
    for (int i = 0; i < total; i++) {
        Carta *c = &cartas[i];
        printf("[Índice %d]\n", i);
        printf("  Código: %s\n", c->codigo);
        printf("  Nome: %s\n", c->nome);
        printf("  População: %ld\n", c->populacao);
        printf("  Área: %.2f km²\n", c->area);
        printf("  PIB: %.2f bilhões\n", c->pib);
        printf("  Pontos turísticos: %d\n", c->pontos);
        printf("  Densidade: %.2f hab/km²\n", c->densidade);
        printf("  PIB per capita: R$ %.2f\n", c->pibPerCapita);
        printf("----------------------------\n");
    }
}

void compararCartas(Carta cartas[], int total) {
    if (total < 2) {
        printf("Cadastre pelo menos duas cartas para comparar.\n");
        return;
    }

    int i1, i2;
    printf("Índice da primeira carta: ");
    scanf("%d", &i1);
    printf("Índice da segunda carta: ");
    scanf("%d", &i2);
    getchar(); // limpar buffer

    if (i1 < 0 || i1 >= total || i2 < 0 || i2 >= total || i1 == i2) {
        printf("Índices inválidos ou iguais!\n");
        return;
    }

    Carta *c1 = &cartas[i1];
    Carta *c2 = &cartas[i2];

    printf("\n--- Comparação ---\n");
    printf("%s vs %s\n\n", c1->nome, c2->nome);

    // População
    printf("População: %ld x %ld => %s\n",
           c1->populacao, c2->populacao,
           (c1->populacao > c2->populacao ? c1->nome : c2->nome));

    // Área (maior ganha)
    printf("Área: %.2f x %.2f => %s\n",
           c1->area, c2->area,
           (c1->area > c2->area ? c1->nome : c2->nome));

    // PIB (maior ganha)
    printf("PIB: %.2f x %.2f => %s\n",
           c1->pib, c2->pib,
           (c1->pib > c2->pib ? c1->nome : c2->nome));

    // Pontos turísticos
    printf("Pontos turísticos: %d x %d => %s\n",
           c1->pontos, c2->pontos,
           (c1->pontos > c2->pontos ? c1->nome : c2->nome));

    // Densidade (menor ganha)
    printf("Densidade (menor é melhor): %.2f x %.2f => %s\n",
           c1->densidade, c2->densidade,
           (c1->densidade < c2->densidade ? c1->nome : c2->nome));

    // PIB per capita
    printf("PIB per capita: R$ %.2f x R$ %.2f => %s\n",
           c1->pibPerCapita, c2->pibPerCapita,
           (c1->pibPerCapita > c2->pibPerCapita ? c1->nome : c2->nome));

    // Super poder (soma de atributos numéricos)
    double poder1 = c1->populacao + c1->pib * 1e9 + c1->pontos;
    double poder2 = c2->populacao + c2->pib * 1e9 + c2->pontos;
    printf("Super poder: %.2f x %.2f => %s\n",
           poder1, poder2, (poder1 > poder2 ? c1->nome : c2->nome));
}
