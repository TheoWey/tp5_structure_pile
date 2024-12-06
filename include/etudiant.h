#pragma region // librairie externes

#include "stdio.h"
#include "stdlib.h"
#include <cstdint>

#pragma endregion // librairie externes

#ifndef ETUDIANT_H
#define ETUDIANT_H

#pragma region // declaration des fonctions

#pragma endregion // declaration des fonctions

#pragma region // declaration des variables
struct etudiant {
    char prenom[16];
    char nom[16];
};
class etudiant_class {
  private:
    etudiant etu;
    uint8_t note;

  public:
    etudiant_class(etudiant etu);
    void set_note(uint8_t note);
    void get_note(uint8_t *note);
    etudiant get_name(void);
    ~etudiant_class();
};

#pragma endregion // declaration des variables
#endif