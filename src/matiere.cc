#include "matiere.hh"

matiere::matiere() {
}
matiere::~matiere() {
}

void matiere::get_matiere(char *mat) {
    for (uint8_t i = 0; i < 16; i++) {
        mat[i] = this->nom[i];
    }
}
void matiere::set_matiere(char *mat) {
    for (uint8_t i = 0; i < 16; i++) {
        this->nom[i] = mat[i];
    }
}

bool matiere::set_note(grade *note, uint8_t num_note) {
    if (num_note == this->nb_notes+1) {
        this->add_note();
    } else if (num_note > this->nb_notes + 1)
    {
        printf("Note hors plage\n");
        return false;
    }
    this->notes[num_note] = *note;
    return true;
}
void matiere::get_nbnote(uint8_t *nb_notes) {
    *nb_notes = this->nb_notes;
}
void matiere::get_note(grade *note, uint8_t num_note) {
    if(num_note > this->nb_notes) {
        printf("Note hors plage\n");
        return;
    }
    *note = this->notes[num_note];
}

void matiere::add_note(void) {
    smart_malloc(&(this->notes), &(this->nb_notes));
}

void matiere::prompt_grade(void) {
    for (uint8_t i = 0; i < this->nb_notes; i++) {
        printf("note %i : %f", i, this->notes[i].grades);
    }
}

void matiere::prompt_mean(void) {
    float mean = 0;
    for (uint8_t i = 0; i < this->nb_notes; i++) {
        mean += this->notes[i].grades;
    }
    mean /= this->nb_notes;
    printf("Moyenne : %f", mean);
}

void saisie_note(float *note) {
    do {
        printf("Note : ");
        scanf("%f", note);
    } while (!confirm(true));
}