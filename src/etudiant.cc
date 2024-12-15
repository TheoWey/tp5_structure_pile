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

void new_etu(unique_ptr<fiche_etu[]> *fiche, uint8_t *nb_etu) {
    smart_malloc(fiche, nb_etu);
}

void init_etu(unique_ptr<fiche_etu[]> *fiche, uint8_t *nb_etu) {
    etudiant new_etu;
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
        printf("Quel information modifier?");
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
        case 'O':
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
        (*fiche)[*nb_etu].set_fiche(&new_etu);
    }
    // else {
    //     goto correction;
    // }
}

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
    char char_date[10];
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
        scanf("%4s", etu->formation);
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
        printf("Etudiant redoublant : (YES/NO)");
        scanf("%3s", selection);
        etu->redoublant = (strcmp("YES", selection) == 0);
    } while (!confirm(true));
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
                   "cree a cette adresse\n");
        }
    } while (index_edit > *nb_etu);
    afficher_etu(fiche, nb_etu, index_edit);
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
    if (index_aff > *nb_etu) {
        printf("Index saisi hors plage (%i/%i)", index_aff, *nb_etu);
        index_aff = (*nb_etu);
    }
    (*fiche)[index_aff].get_fiche(&aff_etu);
    printf("Etudiant %d enregistre :\n", index_aff);
    printf(" - Nom : %16s\n", aff_etu.nom);
    printf(" - Prenom : %16s\n", aff_etu.prenom);
    printf(" - date de naissance : %i/%i/%i\n - Age : %i\n", aff_etu.age.jour,
           aff_etu.age.mois, aff_etu.age.annee, aff_etu.age.age);
    printf(" - Formation : %4s\n", aff_etu.formation);
    printf(" - groupe : %d\n", aff_etu.groupe);
    if (aff_etu.redoublant) {
        printf(" - Redoublant\n");
    } else {
        printf(" - Non redoublant\n");
    }
}
