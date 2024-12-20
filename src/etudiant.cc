#include "etudiant.hh"

fiche_etu::fiche_etu() {
    // this->etu = etu;
}
fiche_etu::~fiche_etu() {
}

void fiche_etu::add_matiere(void) {
    try {
        if (this->nb_matieres >= MAX_NB_MATIERES) {
            printf("Nombre de matiere maximum atteint");
        } else {
            smart_malloc(&matieres, &this->nb_matieres);
        }
    } catch (const std::exception &e) {
        cout << "Erreur : " << e.what() << endl;
    }
}

void fiche_etu::set_fiche(etudiant *etu) {
    time_t now = time(0);
    tm *localTime = localtime(&now);
    this->etu = *etu;
    this->etu.age.age = (localTime->tm_year + 1900) - this->etu.age.annee;
}
void fiche_etu::get_fiche(etudiant *etu) {
    *etu = this->etu;
}

bool fiche_etu::set_matiere(matiere *mat, uint8_t num_matiere) {
    char name[16];
    uint8_t coef;
    if (num_matiere == this->nb_matieres + 1) {
        this->add_matiere();
    } else if (num_matiere > this->nb_matieres + 1) {
        printf("Matière hors plage\n");
        return false;
    }
    mat->get_matiere_name(name);
    mat->get_matiere_coef(&coef);
    this->matieres[this->nb_matieres - 1].set_matiere_name(name);
    this->matieres[this->nb_matieres - 1].set_matiere_coef(coef);
    return true;
}

void fiche_etu::prompt_etu(void) {
    printf(" - Nom : %s\n", this->etu.nom);
    printf(" - Prenom : %s\n", etu.prenom);
    printf(" - date de naissance : %02i/%02i/%i\n - Age : %i\n",
           this->etu.age.jour, this->etu.age.mois, this->etu.age.annee,
           this->etu.age.age);
    printf(" - Formation : %s\n", this->etu.formation);
    printf(" - groupe : %d\n", this->etu.groupe);
    if (this->etu.redoublant) {
        printf(" - Redoublant\n");
    } else {
        printf(" - Non redoublant\n");
    }
}

void menu_edit_etu(etudiant *edit_etu) {
    static char selection[10] = "";
    do {
        clean_str(selection);
        printf("Que souhaitez vous modifier? "
               "(nom/prenom/age/formation/groupe/redoublant/Fin) : ");
        scanf("%10s", selection);
        if (strcmp(selection, "nom") == 0) {
            saisie(edit_etu->nom, "Nom etudiant :", "%16s");
        } else if (strcmp(selection, "prenom") == 0) {
            saisie(edit_etu->prenom, "Prenom etudiant :", "%16s");
        } else if (strcmp(selection, "age") == 0) {
            saisie(&edit_etu->age);
        } else if (strcmp(selection, "formation") == 0) {
            saisie(edit_etu->formation, "Formation etudiant :", "%2s");
        } else if (strcmp(selection, "groupe") == 0) {
            saisie(&edit_etu->groupe, "Groupe etudiant :", "%hhu");
        } else if (strcmp(selection, "redoublant") == 0) {
            saisie(&edit_etu->redoublant);
        } else if (strcmp(selection, "Fin") == 0) {
            return;
        } else {
            printf("nom/prenom/age/formation/groupe/redoublant/Fin attendu\n");
        }
        printf("Continuer les modification? (YES/NO) : ");
        scanf("%10s", selection);
    } while (strcmp(selection, "YES") != 0);
}

void new_etu(unique_ptr<fiche_etu[]> *fiche, uint8_t *nb_etu) {
    try {
        if (*nb_etu >= MAX_NB_ETU) {
            printf("Nombre d'etudiant maximum atteint");
        } else {
            smart_malloc(fiche, nb_etu);
        }
    } catch (const std::exception &e) {
        cout << "Erreur : " << e.what() << endl;
    }
}

void init_etu(unique_ptr<fiche_etu[]> *fiche, uint8_t *nb_etu) {
    etudiant new_etu;
    (*fiche)[*nb_etu - 1].get_fiche(&new_etu);
    char selection[10] = "";
    saisie(new_etu.prenom, "Prenom etudiant :", "%16s");
    saisie(new_etu.nom, "Nom etudiant :", "%16s");
    saisie(&new_etu.age);
    saisie(new_etu.formation, "Formation etudiant :", "%2s");
    saisie(&new_etu.groupe, "Groupe etudiant :", "%hhu");
    saisie(&new_etu.redoublant);
    menu_edit_etu(&new_etu);
    while (!confirm(false)) {
        menu_edit_etu(&new_etu);
    }
    (*fiche)[*nb_etu - 1].set_fiche(&new_etu);
}

void edit_etu(unique_ptr<fiche_etu[]> *fiche, uint8_t *nb_etu) {
    char selection[10] = "";
    etudiant edit_etu;
    uint8_t index_edit;
    if (*nb_etu == 0) {
        printf("Aucun etudiant enregistrer\n");
        return;
    }
    for (uint8_t index_aff = 1; index_aff <= *nb_etu; index_aff++) {
        afficher_etu(fiche, nb_etu, index_aff);
    }
    ask_index("Etudiant a modifier (1->%i) : ", &index_edit, nb_etu);
    afficher_etu(fiche, nb_etu, index_edit);
    index_edit--;
    (*fiche)[index_edit].get_fiche(&edit_etu);
    do {
        menu_edit_etu(&edit_etu);
        clean_str(selection);
    } while (!confirm(false));
    (*fiche)[index_edit].set_fiche(&edit_etu);
}

void afficher_etu(unique_ptr<fiche_etu[]> *fiche, uint8_t *nb_etu,
                  uint8_t index_aff) {
    if (index_aff >= *nb_etu) {
        printf("Index saisi hors plage (%i/%i)\n", index_aff, *nb_etu);
        index_aff = (*nb_etu);
    }
    printf("Etudiant %d enregistre :\n", index_aff);
    index_aff--;
    (*fiche)[index_aff].prompt_etu();
}
