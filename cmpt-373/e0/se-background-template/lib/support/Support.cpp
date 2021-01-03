// ID cbdaaf363f8f199871c6a35420714712

#include <cassert>
#include <cstdio>
#include <malloc.h>
#include "Support.h"

using ex0::HotPotato;
using ex0::ButterPats;


////////////////////////////////////////////////////////////////////////////////
//  HotPotato special member definitions
////////////////////////////////////////////////////////////////////////////////

HotPotato::HotPotato(ButterPats pats) noexcept
  : butterCount{pats} {
  printf("Create\n");
}

HotPotato::~HotPotato() noexcept {
  printf("Destroy\n");
}

HotPotato::HotPotato(const HotPotato& other) noexcept
  : butterCount{other.butterCount} {
  printf("Copy\n");
}

HotPotato::HotPotato(HotPotato&& other) noexcept
  : butterCount{other.butterCount} {
  printf("Move\n");
}

HotPotato&
HotPotato::operator=(const HotPotato& other) noexcept {
  printf("Assign\n");
  return *this;
}

HotPotato&
HotPotato::operator=(HotPotato&& other) noexcept {
  printf("Move Assign\n");
  return *this;
}
