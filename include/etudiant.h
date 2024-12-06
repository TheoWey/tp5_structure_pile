#pragma region // librairie externes

#include "cstring"
#include "memory"
#include "stdio.h"
#include "stdlib.h"
#include <cstdint>

#pragma endregion // librairie externes

#ifndef ETUDIANT_H
#define ETUDIANT_H

#pragma region // declaration des fonctions

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
    uint8_t groupe;
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

    void set_note(uint8_t *note,uint8_t num_note);
    void get_note(uint8_t *note,uint8_t num_note);
    void get_moyenne(float *moyenne);
};

#pragma endregion // declaration des variables
#endif