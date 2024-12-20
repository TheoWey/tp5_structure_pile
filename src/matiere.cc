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

bool matiere::set_grade(grade *note, uint8_t num_note) {
    if (num_note == this->nb_notes+1) {
        this->add_grade();
    } else if (num_note > this->nb_notes + 1)
    {
        printf("Note hors plage\n");
        return false;
    }
    this->notes[num_note] = *note;
    return true;
}
void matiere::get_nbgrade(uint8_t *nb_notes) {
    *nb_notes = this->nb_notes;
}
void matiere::get_grade(grade *note, uint8_t num_note) {
    if(num_note > this->nb_notes) {
        printf("Note hors plage\n");
        return;
    }
    *note = this->notes[num_note];
}

void matiere::get_mean(float *mean, uint8_t *coef) {
    this->calc_mean();
    *mean = this->mean;
    *coef = this->coef_matiere;
}

void matiere::add_grade(void) {
    smart_malloc(&(this->notes), &(this->nb_notes));
}
void matiere::calc_mean(void) {
    this->mean = 0;
    for (uint8_t i = 0; i < this->nb_notes; i++) {
        this->mean += this->notes[i].grades;
    }
    this->mean /= this->nb_notes;
}

void matiere::prompt_grades(void) {
    for (uint8_t i = 0; i < this->nb_notes; i++) {
        printf("note %i : %f", i, this->notes[i].grades);
    }
}

void matiere::prompt_mean(void) {
    this->calc_mean();
    printf("Moyenne : %f", this->mean);
}
