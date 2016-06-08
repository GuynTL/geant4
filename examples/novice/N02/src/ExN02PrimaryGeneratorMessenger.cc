// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: ExN02PrimaryGeneratorMessenger.cc,v 1.1 1999/01/07 16:05:50 gunter Exp $
// GEANT4 tag $Name: geant4-00-01 $
//
// 

#include "ExN02PrimaryGeneratorMessenger.hh"

#include "ExN02PrimaryGeneratorAction.hh"
#include "G4UIcmdWithAString.hh"
#include "globals.hh"

ExN02PrimaryGeneratorMessenger::ExN02PrimaryGeneratorMessenger(ExN02PrimaryGeneratorAction* myGun)
:myAction(myGun)
{ 

  RndmCmd = new G4UIcmdWithAString("/gun/random",this);
  RndmCmd->SetGuidance("Shoot randomly the incident particle.");
  RndmCmd->SetGuidance("  Choice : on, off(default)");
  RndmCmd->SetParameterName("choice",true);
  RndmCmd->SetDefaultValue("off");
  RndmCmd->SetCandidates("on off");
  RndmCmd->AvailableForStates(PreInit,Idle);
}

ExN02PrimaryGeneratorMessenger::~ExN02PrimaryGeneratorMessenger()
{
  delete RndmCmd;
}

void ExN02PrimaryGeneratorMessenger::SetNewValue(G4UIcommand * command,G4String newValues)
{ 
  if( command == RndmCmd )
   { myAction->SetRndmFlag(newValues);}
}
