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
    uint8_t nb_etu = 0;
    unique_ptr<fiche_etu[]> fiche = make_unique<fiche_etu[]>(nb_etu);
    while (1) {
    }
}

void new_etu(unique_ptr<fiche_etu[]> *fiche, uint8_t *nb_etu) {
    (*nb_etu)++;
    unique_ptr<fiche_etu[]> new_fiche = make_unique<fiche_etu[]>(*nb_etu);
    // Correctly move elements from the old array to the new one
    if (*nb_etu >= 1) // Ensure there is something to move
    {
        for (int8_t i = 0; i < (*nb_etu) - 1; ++i) {
            new_fiche[i] = move((*fiche)[i]); // Move each element
        }
    }
    {
        *fiche = move(new_fiche); // Transfer ownership to the new array
    }
    create_fiche(fiche);
}