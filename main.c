#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct FloatTransport {
    char name[30];
    float tonnage;
    char material[30];
    int crew;
    float speed;
};

int main() {
    system("chcp 65001");

    int num_ships;

    printf("Введіть кількість плаваючих засобів: ");
    scanf("%d", &num_ships);

    if (num_ships <= 0) {
        printf("Кількість плаваючих засобів повинна бути додатнім числом.\n");
        return 1;
    }

    struct FloatTransport *ships = (struct FloatTransport *)malloc(num_ships * sizeof(struct FloatTransport));

    if (ships == NULL) {
        printf("Помилка: Не вдалося виділити пам'ять для плаваючих засобів.\n");
        return 1;
    }

    char searchMaterial[30];
    float minSpeed;

    FILE *outFile = fopen("ships_out.txt", "w");
    if (!outFile) {
        printf("Не вдалося створити файл ships_out.txt.\n");
        free(ships);
        return 1;
    }

    printf("Введіть дані про %d плаваючих засобів:\n", num_ships);
    for (int i = 0; i < num_ships; i+=1) {
        printf("\nЗасіб #%d:\n", i + 1);
        printf("Назва: ");
        scanf(" %[^\n]", ships[i].name);
        printf("Водотоннажність (т): ");
        scanf("%f", &ships[i].tonnage);
        printf("Матеріал корпусу: ");
        scanf(" %[^\n]", ships[i].material);
        printf("Кількість екіпажу: ");
        scanf("%d", &ships[i].crew);
        printf("Швидкість (км/год): ");
        scanf("%f", &ships[i].speed);
    }

    while(getchar() != '\n' && getchar() != EOF); 

    printf("\nВведіть матеріал корпусу для пошуку: ");
    scanf(" %[^\n]", searchMaterial);
    printf("Введіть мінімальну допустиму швидкість: ");
    scanf("%f", &minSpeed);

    fprintf(outFile, "Засоби з корпусом із \"%s\" і швидкістю не менше %.2f км/год:\n\n", searchMaterial, minSpeed);
    int found = 0;

    for (int i = 0; i < num_ships; i+=1) {
        if (strcmp(ships[i].material, searchMaterial) == 0 && ships[i].speed >= minSpeed) {
            found = 1;
            fprintf(outFile, "Назва: %s\n", ships[i].name);
            fprintf(outFile, "Водотоннажність: %.2f т\n", ships[i].tonnage);
            fprintf(outFile, "Матеріал корпусу: %s\n", ships[i].material);
            fprintf(outFile, "Кількість екіпажу: %d\n", ships[i].crew);
            fprintf(outFile, "Швидкість: %.2f км/год\n\n", ships[i].speed);
        }
    }

    if (!found) {
        fprintf(outFile, "Не знайдено жодного засобу з заданими параметрами.\n");
    }

    fclose(outFile);
    free(ships);
    printf("Результати записано у файл ships_out.txt\n");

    return 0;
}