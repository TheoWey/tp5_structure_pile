#include "main.hh"

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
        clean_str(answer);
        printf("Operation a realiser "
               "(Modifier, Ajouter (etudiant),Afficher,noter)");
        scanf("%s", answer); // rendre non bloquant?
        switch (answer[2]) {
        case operation::ajouter:
            new_etu(&fiche, &nb_etu);
            init_etu(&fiche, &nb_etu);
            break;
        case operation::modifier:
            edit_etu(&fiche, &nb_etu);
            break;
        case operation::note:
            noter(&fiche, &nb_etu);
            break;
        case operation::afficher:
            clean_str(answer);
            printf("Un etudiant? Ou toute la base? "
                   "(si 1 seul a afficher donner directement "
                   "son numero, 'tout' pour toute la base 1->%i)",
                   nb_etu);
            scanf("%s", answer);
            if ((strcmp(answer, "tout") == 0)) {
                for (uint8_t index_aff = 1; index_aff <= nb_etu; index_aff++) {
                    afficher_etu(&fiche, &nb_etu, index_aff);
                }
            } else {
                afficher_etu(&fiche, &nb_etu, atoi(answer));
            }

            break;
        default:
            exit(1);
            break;
        }
    }
}
