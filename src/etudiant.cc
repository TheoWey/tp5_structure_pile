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

void fiche_etu::set_note(uint8_t *note, uint8_t num_note) {
    this->notes[num_note] = *note;
}
void fiche_etu::get_nbnote(uint8_t *nb_notes) {
    *nb_notes = this->nb_notes;
}
void fiche_etu::get_note(uint8_t *note, uint8_t num_note) {
    *note = this->notes[num_note];
}

void fiche_etu::add_note(void) {
    smart_malloc(&(this->notes), &(this->nb_notes));
}

void fiche_etu::get_moyenne(float *moyenne) {
    *moyenne = 0;
    for (uint8_t i = 0; i < this->nb_notes; i++) {
        *moyenne += this->notes[i];
    }
    *moyenne /= this->nb_notes;
}

void fiche_etu::afficher(void) {
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
        saisie_prenom(&new_etu);
    }
    if (first_pass) {
    nom:
        saisie_nom(&new_etu);
    }
    if (first_pass) {
    age:
        saisie_age(&new_etu);
    }
    if (first_pass) {
    formation:
        saisie_formation(&new_etu);
    }
    if (first_pass) {
    groupe:
        saisie_groupe(&new_etu);
    }
    if (first_pass) {
    redoublement:
        saisie_redoublant(&new_etu);
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

// generalisation?
void saisie_prenom(etudiant *etu) {
    do {
        printf("Prenom etudiant :");
        scanf("%16s", etu->prenom);
    } while (!confirm(true));
}

void saisie_nom(etudiant *etu) {
    do {
        printf("Nom etudiant :");
        scanf("%16s", etu->nom);
    } while (!confirm(true));
}

void saisie_age(etudiant *etu) {
    char char_date[11];
    date birthdate;
    birthdate.age = 0;
    do {
        printf(
            "Age etudiant (saisir date de naissance au format JJ/MM/AAAA) :");
        scanf("%10s", char_date);
        if (traitement_date(char_date, &birthdate.jour, &birthdate.mois,
                            &birthdate.annee)) {
            etu->age = birthdate;
            if (confirm(true)) {
                break;
            }
        }
    } while (true);
}

void saisie_formation(etudiant *etu) {
    do {
        printf("Formation etudiant :");
        scanf("%2s", etu->formation);
    } while (!confirm(true));
}

void saisie_groupe(etudiant *etu) {
    do {
        printf("Groupe etudiant :");
        scanf("%hhu", &etu->groupe);
    } while (!confirm(true));
}

void saisie_redoublant(etudiant *etu) {
    char selection[4] = "";
    do {
        clean_str(selection);
        printf("Etudiant redoublant(YES/NO) : ");
        scanf("%3s", selection);
        etu->redoublant = (strcmp("YES", selection) == 0);
    } while (!confirm(true));
}
//

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
        saisie_nom(&edit_etu);
        break;
    case info_etu::prenom:
        saisie_prenom(&edit_etu);
        break;
    case info_etu::age:
        saisie_age(&edit_etu);
        break;
    case info_etu::formation:
        saisie_formation(&edit_etu);
        break;
    case info_etu::groupe:
        saisie_groupe(&edit_etu);
        break;
    case info_etu::redoublant:
        saisie_redoublant(&edit_etu);
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
    (*fiche)[index_aff].afficher();
}

void noter(unique_ptr<fiche_etu[]> *fiche, uint8_t *nb_etu) {
    char answer[9];
    uint8_t num_etu, nb_notes, note;
    clean_str(answer);
    printf("Ajouter noter ou Modifier note?");
    scanf("%9s", answer);
    if (strcmp(answer, "Modifier") == 0) {
        do {
            printf("etudiant a noter (1->%i) : ", *nb_etu);
            scanf("%i", &num_etu);
            if (num_etu > *nb_etu) {
                printf("saisi hors plage max : %i", *nb_etu);
            }
        } while (num_etu > *nb_etu);
        num_etu--;
        (*fiche)[num_etu].get_nbnote(&nb_notes);
        for (uint8_t i = 0; i < nb_notes; i++) {
            (*fiche)[num_etu].get_note(&note, i);
            printf("note %i : %i", i, note);
        }
    } else if (strcmp(answer, "ajouter") == 0) {
        do {
            printf("etudiant a noter (1->%i) : ", *nb_etu);
            scanf("%i", &num_etu);
            if (num_etu > *nb_etu) {
                printf("saisi hors plage max : %i", *nb_etu);
            }
        } while (num_etu > *nb_etu);
        num_etu--;
        (*fiche)[num_etu].add_note();
        (*fiche)[num_etu].get_nbnote(&nb_notes);
        printf("votre note : ");
        scanf("%i", &note);
        (*fiche)[num_etu].set_note(&note, nb_notes - 1);
    } else if (strcmp("moyenne", answer) == 0) {
        float moy;
        do {
            printf("etudiant a noter (1->%i) : ", *nb_etu);
            scanf("%i", &num_etu);
            if (num_etu > *nb_etu) {
                printf("saisi hors plage max : %i", *nb_etu);
            }
        } while (num_etu > *nb_etu);
        num_etu--;
        (*fiche)[num_etu].get_moyenne(&moy);
        printf("moyenne actuel : %f\n", moy);
    }
}