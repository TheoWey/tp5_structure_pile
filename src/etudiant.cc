#include "etudiant.h"

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
prenom:
    saisie_prenom(&new_etu);
nom:
    saisie_nom(&new_etu);
age:
    saisie_age(&new_etu);
formation:
    saisie_formation(&new_etu);
groupe:
    saisie_groupe(&new_etu);
redoublement:
    saisie_redoublant(&new_etu);

    if (confirm(false)) {
        (*fiche)[*nb_etu].set_fiche(&new_etu);
        return;
    }
correction:
    for (uint8_t i = 0; i < sizeof(selection) / sizeof(char); i++) {
        // reset de selection pour eviter les risques de mauvaise selection
        selection[i] = ' ';
    }
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
    default:
        printf("Réponse attendu :\n - prenom\n - nom\n - age\n - formaion\n - "
               "groupe\n - redoublant");
        goto correction;
        break;
    }
}

void saisie_prenom(etudiant *new_etu) {
    do {
        printf("Prénom étudiant :");
        scanf("%16s", new_etu->prenom);
    } while (!confirm(true));
}

void saisie_nom(etudiant *new_etu) {
    do {
        printf("Nom étudiant :");
        scanf("%16s", new_etu->nom);
    } while (!confirm(true));
}

void saisie_age(etudiant *new_etu) {
    char char_date[8];
    date birthdate;
    do {
        printf(
            "Age étudiant (saisir date de naissance au format JJ/MM/AAAA) :");
        scanf("%8s", char_date);
    } while (!traitement_date(char_date, &birthdate.jour, &birthdate.mois,
                              &birthdate.annee) &&
             !confirm(true));
}

void saisie_formation(etudiant *new_etu) {
    do {
        printf("Formation étudiant :");
        scanf("%16s", new_etu->formation);
    } while (!confirm(true));
}

void saisie_groupe(etudiant *new_etu) {
    do {
        printf("Groupe étudiant :");
        scanf("%16s", new_etu->groupe);
    } while (!confirm(true));
}

void saisie_redoublant(etudiant *new_etu) {
    char selection[10] = "";
    do {
        for (uint8_t i = 0; i < sizeof(selection) / sizeof(char); i++) {
            // reset de selection pour eviter les risques de mauvaise selection
            selection[i] = ' ';
        }
        printf("Etudiant redoublant : (YES/NO)");
        scanf("%16s", selection);
        new_etu->redoublant = strcmp("YES", selection);
    } while (!confirm(true));
}

