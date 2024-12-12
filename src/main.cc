#include "main.h"

int main(void) {
    init();

    loop();
}

void init(void) {
    srand(time(0));
    printf("init ok\n");
}

void loop(void) {
    char answer[8] = "";
    uint8_t nb_etu = 0;
    unique_ptr<fiche_etu[]> fiche = make_unique<fiche_etu[]>(nb_etu);
    while (1) {
        printf("Operation a réaliser (Modifier, Ajouter, noter)");
        scanf("%s", answer); // rendre non bloquant?
        switch (answer[2]) {
        case operation::ajouter:
            new_etu(&fiche, &nb_etu);
            init_etu(&fiche, &nb_etu);
            break;
        case operation::modifier:
            /* code */
            break;
        case operation::noter:
            /* code */
            break;
        default:
            break;
        }
    }
}
