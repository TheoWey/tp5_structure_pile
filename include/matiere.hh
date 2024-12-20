#pragma region // librairie externes

#include <cstdint>
#include <cstring>
#include <ctime>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <stdlib.h>

#include "memory.hh"

#pragma endregion // librairie externes

#ifndef MATIERE_H
#define MATIERE_H

#pragma region // declaration des variables

const uint8_t MAX_NB_NOTES = 255;

typedef struct {
    float grades;
    float bareme;
} grade;

using namespace std;
class matiere {
  private:
    char nom[16];
    uint8_t nb_notes = 0;
    unique_ptr<grade[]> notes = make_unique<grade[]>(this->nb_notes);
    float mean = 0;
    uint8_t coef_matiere = 1;
    void add_grade(void);
    void calc_mean(void);

  public:
    matiere();
    ~matiere();

    // Custom copy constructor
    matiere(const matiere &other)
        : nb_notes(other.nb_notes),
          notes(make_unique<grade[]>(other.nb_notes)) {
        strcpy(nom, other.nom);
        std::copy(other.notes.get(), other.notes.get() + nb_notes, notes.get());
    }

    // Custom copy assignment operator
    matiere &operator=(const matiere &other) {
        if (this != &other) { // Check for self-assignment
            strcpy(nom, other.nom);
            nb_notes = other.nb_notes;
            notes = make_unique<grade[]>(other.nb_notes);
            std::copy(other.notes.get(), other.notes.get() + nb_notes,
                      notes.get());
        }
        return *this;
    }

    void get_matiere(char *mat);
    void set_matiere(char *mat);

    bool set_grade(grade *note, uint8_t num_note);
    void get_nbgrade(uint8_t *nb_notes);
    void get_grade(grade *note, uint8_t num_note);

    void get_mean(float *mean, uint8_t *coef);

    void prompt_grades(void);
    void prompt_mean(void);
};

#pragma endregion // declaration des variables

#pragma region // declaration des fonctions

#pragma endregion // declaration des fonctions
#endif            // MATIERE_H