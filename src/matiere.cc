#include "matiere.hh"

matiere::matiere() {
}
matiere::~matiere() {
}

void matiere::get_matiere_name(char *mat) {
    for (uint8_t i = 0; i < 16; i++) {
        mat[i] = this->nom[i];
    }
}
void matiere::set_matiere_name(char *mat) {
    for (uint8_t i = 0; i < 16; i++) {
        this->nom[i] = mat[i];
    }
}

void matiere::get_matiere_coef(uint8_t *coef) {
    *coef = this->coef_matiere;
}
void matiere::set_matiere_coef(uint8_t coef) {
    this->coef_matiere = coef;
}

bool matiere::set_grade(grade *note, uint8_t num_note) {
    if (num_note == this->nb_notes + 1) {
        this->add_grade();
    } else if (num_note > this->nb_notes + 1) {
        printf("Note hors plage\n");
        return false;
    }
    this->notes[this->nb_notes-1] = *note;
    return true;
}
void matiere::get_nbgrade(uint8_t *nb_notes) {
    *nb_notes = this->nb_notes;
}
void matiere::get_grade(grade *note, uint8_t num_note) {
    if (num_note > this->nb_notes) {
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

void edit_matiere(unique_ptr<matiere[]> *matieres, uint8_t *nb_matieres) {
    char selection[10] = "";
    uint8_t index_edit = 0;
    ask_index("Matiere a modifier (1->%i) : ", &index_edit, nb_matieres);
    index_edit--;
    clean_str(selection);
    printf("modifier nom ou coef?");
    scanf("%10s", selection);
    if (strcmp(selection, "nom") == 0) {
        char new_name[16];
        saisie(new_name, "Nouveau nom de matiere : ", "%16s");
        (*matieres)[index_edit].set_matiere_name(new_name);
    } else if (strcmp(selection, "coef") == 0) {
        uint8_t new_coef;
        saisie(&new_coef, "Nouveau coef de matiere : ", "%i");
        if (new_coef > 0) {
            (*matieres)[index_edit].set_matiere_coef(new_coef);
        }
    }
}