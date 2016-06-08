//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: G4C11GEMProbability.cc,v 1.1 2002/06/06 17:59:51 larazb Exp $
// GEANT4 tag $Name: geant4-05-00 $
//
// Hadronic Process: Nuclear De-excitations
// by V. Lara (Nov 1999)
//


#include "G4C11GEMProbability.hh"

G4C11GEMProbability::G4C11GEMProbability() :
  G4GEMProbability(11,6,3.0/2.0) // A,Z,Spin
{

  ExcitEnergies.push_back(2000.0*keV);
  ExcitSpins.push_back(1.0/2.0);
  ExcitLifetimes.push_back(24.0e-15*s);

  ExcitEnergies.push_back(4318.8*keV);
  ExcitSpins.push_back(5.0/2.0);
  ExcitLifetimes.push_back(8.3e-15*s);

  ExcitEnergies.push_back(4804.2*keV);
  ExcitSpins.push_back(3.0/2.0);
  ExcitLifetimes.push_back(7.6e-15*s);

  ExcitEnergies.push_back(6339.2*keV);
  ExcitSpins.push_back(1.0/2.0);
  ExcitLifetimes.push_back(77.0e-15*s);

  ExcitEnergies.push_back(6478.2*keV);
  ExcitSpins.push_back(7.0/2.0);
  ExcitLifetimes.push_back(6.0e-15*s);

  ExcitEnergies.push_back(6904.8*keV);
  ExcitSpins.push_back(5.0/2.0);
  ExcitLifetimes.push_back(48.0e-15*s);

  ExcitEnergies.push_back(7499.7*keV);
  ExcitSpins.push_back(3.0/2.0);
  ExcitLifetimes.push_back(63.0e-15*s);

  ExcitEnergies.push_back(8104.5*keV);
  ExcitSpins.push_back(3.0/2.0);
  ExcitLifetimes.push_back(hbar_Planck*log(2.0)/(11*eV));

  ExcitEnergies.push_back(8420*keV);
  ExcitSpins.push_back(5.0/2.0);
  ExcitLifetimes.push_back(hbar_Planck*log(2.0)/(15.2*eV));

  ExcitEnergies.push_back(8655*keV);
  ExcitSpins.push_back(7.0/2.0);
  ExcitLifetimes.push_back(hbar_Planck*log(2.0)/(9*keV));

  ExcitEnergies.push_back(8701*keV);
  ExcitSpins.push_back(5.0/2.0);
  ExcitLifetimes.push_back(hbar_Planck*log(2.0)/(15*keV));

  ExcitEnergies.push_back(9.20E+3*keV);
  ExcitSpins.push_back(5.0/2.0);
  ExcitLifetimes.push_back(hbar_Planck*log(2.0)/(500*keV));

  ExcitEnergies.push_back(9.65E+3*keV);
  ExcitSpins.push_back(3.0/2.0);
  ExcitLifetimes.push_back(hbar_Planck*log(2.0)/(210*keV));

  ExcitEnergies.push_back(9.78E+3*keV);
  ExcitSpins.push_back(5.0/2.0);
  ExcitLifetimes.push_back(hbar_Planck*log(2.0)/(240*keV));

  ExcitEnergies.push_back(9.97E+3*keV);
  ExcitSpins.push_back(7.0/2.0);
  ExcitLifetimes.push_back(hbar_Planck*log(2.0)/(120*keV));

  ExcitEnergies.push_back(10083*keV);
  ExcitSpins.push_back(7.0/2.0);
  ExcitLifetimes.push_back(hbar_Planck*log(2.0)/(230*keV));

  ExcitEnergies.push_back(10679*keV);
  ExcitSpins.push_back(9.0/2.0);
  ExcitLifetimes.push_back(hbar_Planck*log(2.0)/(200*keV));

  ExcitEnergies.push_back(12.51E+3*keV);
  ExcitSpins.push_back(1.0/2.0);
  ExcitLifetimes.push_back(hbar_Planck*log(2.0)/(490*keV));

  ExcitEnergies.push_back(12.65E+3*keV);
  ExcitSpins.push_back(7.0/2.0);
  ExcitLifetimes.push_back(hbar_Planck*log(2.0)/(360*keV));

  SetExcitationEnergiesPtr(&ExcitEnergies);
  SetExcitationSpinsPtr(&ExcitSpins);
  SetExcitationLifetimesPtr(&ExcitLifetimes);
}


G4C11GEMProbability::G4C11GEMProbability(const G4C11GEMProbability &right)
{
  G4Exception("G4C11GEMProbability::copy_constructor meant to not be accessable");
}




const G4C11GEMProbability & G4C11GEMProbability::
operator=(const G4C11GEMProbability &right)
{
  G4Exception("G4C11GEMProbability::operator= meant to not be accessable");
  return *this;
}


G4bool G4C11GEMProbability::operator==(const G4C11GEMProbability &right) const
{
  return false;
}

G4bool G4C11GEMProbability::operator!=(const G4C11GEMProbability &right) const
{
  return true;
}


