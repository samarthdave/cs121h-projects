#pragma once

#include <string>

#include "codons.hpp"

char aa(std::string &s) {
  if (s=="TTA") return 'L';
  if (s=="TTG") return 'L';
  if (s=="CTT") return 'L';
  if (s=="CTC") return 'L';
  if (s=="CTA") return 'L';
  if (s=="CTG") return 'L';
  if (s=="TGG") return 'W';
  if (s=="TAA") return '*';
  if (s=="TAG") return '*';
  if (s=="TGA") return '*';
  if (s=="ATG") return 'M';
  if (s=="TTT") return 'F';
  if (s=="TTC") return 'F';
  if (s=="TAT") return 'Y';
  if (s=="TAC") return 'Y';
  if (s=="TCT") return 'S';
  if (s=="TCC") return 'S';
  if (s=="TCA") return 'S';
  if (s=="TCG") return 'S';
  if (s=="AGT") return 'S';
  if (s=="AGC") return 'S';
  if (s=="CCT") return 'P';
  if (s=="CCC") return 'P';
  if (s=="CCA") return 'P';
  if (s=="CCG") return 'P';
  if (s=="TGT") return 'C';
  if (s=="TGC") return 'C';
  if (s=="CAT") return 'H';
  if (s=="CAC") return 'H';
  if (s=="CAA") return 'Q';
  if (s=="CAG") return 'Q';
  if (s=="AAT") return 'N';
  if (s=="AAC") return 'N';
  if (s=="CGT") return 'R';
  if (s=="CGC") return 'R';
  if (s=="CGA") return 'R';
  if (s=="CGG") return 'R';
  if (s=="AGA") return 'R';
  if (s=="AGG") return 'R';
  if (s=="ATT") return 'I';
  if (s=="ATC") return 'I';
  if (s=="ATA") return 'I';
  if (s=="AAA") return 'K';
  if (s=="AAG") return 'K';
  if (s=="GAT") return 'D';
  if (s=="GAC") return 'D';
  if (s=="GAA") return 'E';
  if (s=="GAG") return 'E';
  if (s=="ACT") return 'T';
  if (s=="ACC") return 'T';
  if (s=="ACA") return 'T';
  if (s=="ACG") return 'T';
  if (s=="GTT") return 'V';
  if (s=="GTC") return 'V';
  if (s=="GTA") return 'V';
  if (s=="GTG") return 'V';
  if (s=="GCT") return 'A';
  if (s=="GCC") return 'A';
  if (s=="GCA") return 'A';
  if (s=="GCG") return 'A';
  if (s=="GGT") return 'G';
  if (s=="GGC") return 'G';
  if (s=="GGA") return 'G';
  if (s=="GGG") return 'G';
  return '?';
}