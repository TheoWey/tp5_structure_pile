#include "main.h"

int main(void) {
    printf("hello world");
    init();
    etudiant_class etu[5] = {name1, name2, name3, name4, name5};
    for (uint8_t i = 0; i < 5; i++) {
        etu[i].set_note((rand() % 20) + 1);
    }
    for (uint8_t i = 0; i < 5; i++) {
        uint8_t note = 0;
        etudiant name;
        etu[i].get_note(&note);
        if (note >= 10) {
            name = etu[i].get_name();
            printf("%s %s a %i/20\n", name.prenom, name.nom, note);
        }
    }
    loop();
}

void init(void) {
    srand(time(0));
    printf("init ok\n");
}
void loop(void) {
    while (1) {
    }
}
