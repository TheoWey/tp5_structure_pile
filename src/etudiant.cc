#include "etudiant.h"

etudiant_class::etudiant_class(etudiant etu) {
    this->etu = etu;
}
etudiant_class::~etudiant_class() {
}
void etudiant_class::set_note(uint8_t note) {
    this->note = note;
}
void etudiant_class::get_note(uint8_t *note) {
    *note = this->note;
}
etudiant etudiant_class::get_name(void) {
    return this->etu;
}