// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4OpenInventor.hh,v 1.4 1999/05/10 15:38:53 johna Exp $
// GEANT4 tag $Name: geant4-00-01 $
//
// Guy Barrand 26 Mar 1998.
// OpenInventor graphics system factory.

#ifndef G4OPENINVENTOR_HH
#define G4OPENINVENTOR_HH

#if defined(G4VIS_BUILD_OI_DRIVER) || defined(G4VIS_USE_OI)

#include "G4VGraphicsSystem.hh"

class G4VInteractorManager;

class G4OpenInventor: public G4VGraphicsSystem {
public:
  G4OpenInventor(const G4String,const G4String,G4VGraphicsSystem::Functionality);
  virtual ~G4OpenInventor();
  G4VViewer* CreateViewer(G4VSceneHandler&,const G4String& name = "");
  void SetInteractorManager(G4VInteractorManager*);
  G4VInteractorManager* GetInteractorManager();
  G4VSceneHandler* CreateSceneHandler (const G4String& name);
  void InitHEPVis();
private:
  G4VInteractorManager* interactorManager;
};

#endif

#endif