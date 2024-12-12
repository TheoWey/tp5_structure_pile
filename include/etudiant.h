#pragma region // librairie externes

#include <cstdint>
#include <cstring>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

#include "memory.hh"

#pragma endregion // librairie externes

#ifndef ETUDIANT_H
#define ETUDIANT_H

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
 * This function prompts the user for student information (first name, last name,
 * and date of birth) and stores it in a new student record.
 *
 * @param fiche A pointer to the array of student records.
 * @param nb_etu A pointer to the number of students.
 */
void init_etu(unique_ptr<fiche_etu[]> *fiche, uint8_t *nb_etu);
void saisie_prenom(etudiant *new_etu);
void saisie_nom(etudiant *new_etu);
void saisie_age(etudiant *new_etu);
void saisie_formation(etudiant *new_etu);
void saisie_groupe(etudiant *new_etu);
void saisie_redoublant(etudiant *new_etu);


#pragma endregion // declaration des fonctions

#pragma region // declaration des variables

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

struct etudiant {
    char prenom[16];
    char nom[16];
    date age;
    char formation[2];
    uint8_t groupe;
    bool redoublant;
};

enum info_etu{
    prenom = 'p',
    nom = 'n',
    age = 'a',
    formation = 'f',
    groupe = 'g',
    redoublant ='r'
};

using namespace std;
class fiche_etu {
  private:
    etudiant etu;
    uint8_t nb_notes = 0;
    unique_ptr<float[]> notes = make_unique<float[]>(this->nb_notes);
    void add_note(void);

  public:
    fiche_etu();
    fiche_etu(const fiche_etu &) = delete; // Disable copy constructor
    fiche_etu &operator=(const fiche_etu &) = delete; // Disable copy assignment
    fiche_etu(fiche_etu &&) noexcept = default;       // Move constructor
    fiche_etu &operator=(fiche_etu &&) noexcept = default; // Move assignment
    ~fiche_etu();

    void get_fiche(etudiant *fiche_etu);
    void set_fiche(etudiant *fiche_etu);

    void set_note(uint8_t *note, uint8_t num_note);
    void get_note(uint8_t *note, uint8_t num_note);
    void get_moyenne(float *moyenne);
};

#pragma endregion // declaration des variables
#endif