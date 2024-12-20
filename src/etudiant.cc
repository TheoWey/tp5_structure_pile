#include "etudiant.hh"

fiche_etu::fiche_etu() {
    // this->etu = etu;
}
fiche_etu::~fiche_etu() {
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

void new_etu(unique_ptr<fiche_etu[]> *fiche, uint8_t *nb_etu) {
    try {
        smart_malloc(fiche, nb_etu);
    } catch (const std::exception &e) {
        cout << "Erreur : " << e.what() << endl;
    }
}

void init_etu(unique_ptr<fiche_etu[]> *fiche, uint8_t *nb_etu) {
    etudiant new_etu;
    (*fiche)[*nb_etu - 1].get_fiche(&new_etu);
    char selection[10] = "";
    bool first_pass = true;
    if (first_pass) {
    prenom:
        saisie(&new_etu.prenom, "Prenom etudiant :", "%16s");
    }
    if (first_pass) {
    nom:
        saisie(&new_etu.nom, "Nom etudiant :", "%16s");
    }
    if (first_pass) {
    age:
        saisie(&new_etu.age);
    }
    if (first_pass) {
    formation:
        saisie(&new_etu.formation, "Formation etudiant :", "%2s");
    }
    if (first_pass) {
    groupe:
        saisie(&new_etu.groupe, "Groupe etudiant :", "%hhu");
    }
    if (first_pass) {
    redoublement:
        saisie(&new_etu.redoublant);
    }
    if (!first_pass) {
    correction:
        clean_str(selection);
        printf("Quel information modifier ( valider)?");
        scanf("%s", selection);
        switch (selection[0]) {
        case info_etu::prenom:
            goto prenom;
            break;
        case info_etu::nom:
            goto nom;
            break;
        case info_etu::age:
            goto age;
            break;
        case info_etu::formation:
            goto formation;
            break;
        case info_etu::groupe:
            goto groupe;
            break;
        case info_etu::redoublant:
            goto redoublement;
            break;
        case info_etu::validation:
            goto valide;
            break;
        default:
            printf(
                "Reponse attendu :\n - prenom\n - nom\n - age\n - formaion\n - "
                "groupe\n - redoublant\n");
            goto correction;
            break;
        }
    }
valide:
    first_pass = false;
    if (confirm(false)) {
        (*fiche)[*nb_etu - 1].set_fiche(&new_etu);
    } else {
        goto correction;
    }
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
    do {
        printf("Etudiant a modifer?");
        scanf("%i", &index_edit);
        if (index_edit > *nb_etu) {
            printf("Index saisie hors plage, aucun etudiant n'a encore ete "
                   "cree a cette adresse (max %i)\n",
                   *nb_etu);
        }
    } while (index_edit > *nb_etu);
    afficher_etu(fiche, nb_etu, index_edit);
    index_edit--;
    (*fiche)[index_edit].get_fiche(&edit_etu);
selector:
    clean_str(selection);
    printf("Que souhaitez vous modifier? "
           "(nom/prenom/age/formation/groupe/redoublant/Fin) : ");
    scanf("%10s", selection);
    switch (selection[0]) {
    case info_etu::nom:
        saisie(&edit_etu.nom, "Nom etudiant :", "%16s");
        break;
    case info_etu::prenom:
        saisie(&edit_etu.prenom, "Prenom etudiant :", "%16s");
        break;
    case info_etu::age:
        saisie(&edit_etu.age);
        break;
    case info_etu::formation:
        saisie(&edit_etu.formation, "Formation etudiant :", "%2s");
        break;
    case info_etu::groupe:
        saisie(&edit_etu.groupe, "Groupe etudiant :", "%hhu");
        break;
    case info_etu::redoublant:
        saisie(&edit_etu.redoublant);
        break;
    case 'F':
        return;

    default:
        printf("nom/prenom/age/formation/groupe/redoublant/Fin attendu\n");
        goto selector;
        break;
    }
    clean_str(selection);
    printf("Continuer les modification? (YES/NO) : ");
    scanf("%10s", selection);
    if ((strcmp(selection, "YES") == 0)) {
        goto selector;
    } else if (confirm(false)) {
        (*fiche)[index_edit].set_fiche(&edit_etu);
    }
}

void afficher_etu(unique_ptr<fiche_etu[]> *fiche, uint8_t *nb_etu,
                  uint8_t index_aff) {
    etudiant aff_etu;
    if (index_aff >= *nb_etu) {
        printf("Index saisi hors plage (%i/%i)\n", index_aff, *nb_etu);
        index_aff = (*nb_etu);
    }
    printf("Etudiant %d enregistre :\n", index_aff);
    index_aff--;
    (*fiche)[index_aff].prompt_etu();
}

// void noter(unique_ptr<fiche_etu[]> *fiche, uint8_t *nb_etu) {
//     char answer[9];
//     uint8_t num_etu, nb_notes, num_note;
//     float note;
//     (*fiche)[num_etu].get_nbnote(&nb_notes);
//     clean_str(answer);
//     printf("Ajouter noter ou Modifier note?");
//     scanf("%9s", answer);
//     do {
//         printf("etudiant a noter (1->%i) : ", *nb_etu);
//         scanf("%i", &num_etu);
//         if (num_etu > *nb_etu) {
//             printf("saisi hors plage max : %i", *nb_etu);
//         }
//     } while (num_etu > *nb_etu);
//     num_etu--;
//     if (strcmp(answer, "Modifier") == 0) {
//         (*fiche)[num_etu].prompt_grade();
//         do {
//             printf("note a corriger : ");
//             scanf("%i", &num_note);
//         } while (num_note > nb_notes);
//         num_note--;
//         saisie_note(&note);
//         (*fiche)[num_etu].set_note(&note, nb_notes - 1);

//     } else if (strcmp(answer, "ajouter") == 0) {
//         (*fiche)[num_etu].add_note();
//         saisie_note(&note);
//         (*fiche)[num_etu].set_note(&note, nb_notes - 1);

//     } else if (strcmp("moyenne", answer) == 0) {
//         (*fiche)[num_etu].prompt_mean();
//     }
// }