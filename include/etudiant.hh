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

#ifndef ETUDIANT_H
#define ETUDIANT_H

#pragma region // declaration des variables

const uint8_t MAX_NB_ETU = 255;

enum mois {
    janvier,
    fevrier,
    mars,
    avril,
    mai,
    juin,
    juillet,
    aout,
    septembre,
    octobre,
    novembre,
    decembre
};

/**
 * @struct date
 * @brief Structure representing a date with day, month, year, and age.
 *
 * This structure contains the day, month, year, and an additional field for
 * age.
 */
struct date {
    uint8_t jour;
    uint8_t mois;
    uint32_t annee;
    uint8_t age;
};

struct heure {
    uint8_t seconde;
    uint8_t minute;
    uint32_t heure;
};

/**
 * @struct etudiant
 * @brief Structure representing a student with personal information.
 *
 * This structure contains the student's name, date of birth (as a `date`
 * structure), formation, group, and whether the student is a repeat student.
 */
struct etudiant {
    char prenom[16];
    char nom[16];
    date age;
    char formation[2];
    int groupe;
    bool redoublant;
};

/**
 * @enum info_etu
 * @brief Enum representing the student information fields.
 *
 * This enum is used to represent specific fields of the student structure.
 */
enum info_etu {
    prenom = 'p',
    nom = 'n',
    age = 'a',
    formation = 'f',
    groupe = 'g',
    redoublant = 'r',
    validation = 'v'
};

using namespace std;
/**
 * @class fiche_etu
 * @brief Represents a student's record, containing personal information and
 * grades.
 *
 * The `fiche_etu` class manages information related to a student, such as
 * grades, and provides methods to manipulate these grades.
 */
class fiche_etu {
  private:
    etudiant etu;
    uint8_t nb_matieres = 0;
    unique_ptr<matiere[]> matieres = make_unique<matiere[]>(nb_matieres);

  public:
    fiche_etu();
    ~fiche_etu();
    // Custom copy constructor
    fiche_etu(const fiche_etu &other)
        : etu(other.etu), nb_matieres(other.nb_matieres),
          matieres(make_unique<matiere[]>(other.nb_matieres)) {
        std::copy(other.matieres.get(), other.matieres.get() + nb_matieres, matieres.get());
    }

    // Custom copy assignment operator
    fiche_etu &operator=(const fiche_etu &other) {
        if (this != &other) { // Check for self-assignment
            etu = other.etu;
            nb_matieres = other.nb_matieres;
            matieres = make_unique<matiere[]>(other.nb_matieres);
            std::copy(other.matieres.get(), other.matieres.get() + nb_matieres,
                      matieres.get());
        }
        return *this;
    }

    void get_fiche(etudiant *fiche_etu);
    void set_fiche(etudiant *fiche_etu);

    void prompt_etu(void);
};

#pragma endregion // declaration des variables

#pragma region // declaration des fonctions

/**
 * @brief Creates a new array of student records.
 *
 * This function allocates memory for a new array of student records and
 * initializes it with default values.
 *
 * @param fiche A pointer to a pointer to the array of student records.
 * @param nb_etu A pointer to the number of students.
 */
void new_etu(unique_ptr<fiche_etu[]> *fiche, uint8_t *nb_etu);

/**
 * @brief Initializes a new student record.
 *
 * This function prompts the user for student information (first name, last
 * name, and date of birth) and stores it in a new student record.
 *
 * @param fiche A pointer to the array of student records.
 * @param nb_etu A pointer to the number of students.
 */
void init_etu(unique_ptr<fiche_etu[]> *fiche, uint8_t *nb_etu);

void edit_etu(unique_ptr<fiche_etu[]> *fiche, uint8_t *nb_etu);
void afficher_etu(unique_ptr<fiche_etu[]> *fiche, uint8_t *nb_etu,
                  uint8_t index_aff);
void noter(unique_ptr<fiche_etu[]> *fiche, uint8_t *nb_etu);

#pragma endregion // declaration des fonctions
#endif