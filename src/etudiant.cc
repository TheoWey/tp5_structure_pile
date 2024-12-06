#include "etudiant.h"

fiche_etu::fiche_etu() {
    // this->etu = etu;
}

fiche_etu::~fiche_etu() {
}
void fiche_etu::set_fiche(etudiant *etu) {
    this->etu = *etu;
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
    this->nb_notes++;
    unique_ptr<float[]> new_notes = make_unique<float[]>(this->nb_notes);
    // Vérifier si l'ancien tableau est vide
    if (this->nb_notes > 1) {
        // Copier les éléments de l'ancien tableau vers le nouveau
        copy(this->notes.get(), this->notes.get() + (this->nb_notes - 1),
             new_notes.get());
    }
    // L'ancien tableau sera automatiquement détruit à la sortie de son scope
    this->notes = move(new_notes); // Transférer la propriété au nouveau tableau
    this->notes[this->nb_notes-1] = -0.0f;
}

void fiche_etu::get_moyenne(float *moyenne) {
    *moyenne = 0;
    for (uint8_t i = 0; i < this->nb_notes; i++) {
        *moyenne += this->notes[i];
    }
    *moyenne /= this->nb_notes;
}

bool confirm(void) {
    char confirmation[3];
    printf("Etes vous sur de vouloir faire cette modification?(YES/NO)");
    scanf("%2s", confirmation);
    return strcmp(confirmation, "YES");
}