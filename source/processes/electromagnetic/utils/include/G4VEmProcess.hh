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
// $Id: G4VEmProcess.hh,v 1.1 2003/10/13 10:52:51 vnivanch Exp $
// GEANT4 tag $Name: geant4-06-00 $
//
// -------------------------------------------------------------------
//
// GEANT4 Class header file
//
//
// File name:     G4VEmProcess
//
// Author:        Vladimir Ivanchenko on base of Laszlo Urban code
//
// Creation date: 01.10.2003
//
// Modifications:
//
//
// Class Description:
//
// It is the unified process for e+ annililation at rest and in fly.

// -------------------------------------------------------------------
//

#ifndef G4VEmProcess_h
#define G4VEmProcess_h 1

#include "G4VDiscreteProcess.hh"
#include "globals.hh"
#include "G4Material.hh"
#include "G4MaterialCutsCouple.hh"
#include "G4Track.hh"
#include "G4EmModelManager.hh"
#include "G4UnitsTable.hh"
#include "G4ParticleDefinition.hh"

class G4Step;
class G4VEmModel;
class G4VEmFluctuationModel;
class G4DataVector;
class G4VParticleChange;
class G4PhysicsTable;
class G4PhysicsVector;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class G4VEmProcess : public G4VDiscreteProcess
{
public:

  G4VEmProcess(const G4String& name,
                         G4ProcessType type = fElectromagnetic);

 ~G4VEmProcess();

  G4VParticleChange* PostStepDoIt(const G4Track&, const G4Step&);

  virtual void SecondariesPostStep(
                                   G4VEmModel*,
                             const G4MaterialCutsCouple*,
                             const G4DynamicParticle*,
                                   G4double& tcut,
                                   G4double& kinEnergy) = 0;

  virtual G4bool IsApplicable(const G4ParticleDefinition& p) = 0;
    // True for all charged particles

  virtual
  void BuildPhysicsTable(const G4ParticleDefinition&);
  // Build physics table during initialisation

  virtual void PrintInfoDefinition();

  // Print out of the class parameters

  G4PhysicsTable* BuildLambdaTable();

  void SetLambdaBinning(G4int nbins);
  // Binning for lambda table

  void SetMinKinEnergy(G4double e);
  G4double MinKinEnergy() const;
  // Min kinetic energy for tables

  void SetMaxKinEnergy(G4double e);
  G4double MaxKinEnergy() const;
  // Max kinetic energy for tables

  G4bool StorePhysicsTable(G4ParticleDefinition*,
                                 const G4String& directory,
                                          G4bool ascii = false);
    // Store PhysicsTable in a file.
    // Return false in case of failure at I/O

  G4bool RetrievePhysicsTable(G4ParticleDefinition*,
                                      const G4String& directory,
                                               G4bool ascii);
    // Retrieve Physics from a file.
    // (return true if the Physics Table can be build by using file)
    // (return false if the process has no functionality or in case of failure)
    // File name should is constructed as processName+particleName and the
    // should be placed under the directory specifed by the argument.

  void AddEmModel(G4int, G4VEmModel*, G4VEmFluctuationModel* fluc = 0,
                                const G4Region* region = 0);
  // Add EM model coupled with fluctuation model for the region

  void UpdateEmModel(const G4String&, G4double, G4double);
  // Define new energy range for the model identified by the name

  //  void SetLambdaTable(G4PhysicsTable* p);
  //  G4PhysicsTable* LambdaTable() {return theLambdaTable;};

  G4double GetLambda(G4double kineticEnergy, const G4MaterialCutsCouple* couple);
  // It returns the Lambda of the process

  G4double MicroscopicCrossSection(G4double kineticEnergy,
                             const G4MaterialCutsCouple* couple);
  // It returns the cross section of the process for energy/ material

  void SetIntegral(G4bool val) {integral = val;};
  G4bool IsIntegral() const {return integral;}

  G4double MeanFreePath(const G4Track& track,
                              G4double previousStepSize,
                              G4ForceCondition* condition);

  const G4ParticleDefinition* Particle() const;
  const G4ParticleDefinition* SecondaryParticle() const;

protected:

  void SetParticle(const G4ParticleDefinition* p);
  void SetSecondaryParticle(const G4ParticleDefinition* p);

  virtual
  G4double GetMeanFreePath(const G4Track& track,
                                         G4double previousStepSize,
                                         G4ForceCondition* condition);

  virtual
  G4PhysicsVector* LambdaPhysicsVector(const G4MaterialCutsCouple*);

  virtual G4double MinPrimaryEnergy(const G4ParticleDefinition*,
                                    const G4Material*, G4double cut) = 0;

  G4VEmModel* SelectModel(G4double& kinEnergy);

  size_t CurrentMaterialCutsCoupleIndex() const {return currentMaterialIndex;};

  void      ResetNumberOfInteractionLengthLeft();
  // reset (determine the value of)NumberOfInteractionLengthLeft

private:

  void Initialise();

  void DefineMaterial(const G4MaterialCutsCouple* couple);

  // hide  assignment operator

  G4VEmProcess(G4VEmProcess &);
  G4VEmProcess & operator=(const G4VEmProcess &right);

// =====================================================================

private:

  G4EmModelManager*           modelManager;

  // tables and vectors
  G4PhysicsTable*                  theLambdaTable;

  const G4ParticleDefinition*  particle;
  const G4ParticleDefinition*  baseParticle;
  const G4ParticleDefinition*  secondaryParticle;
  const G4DataVector*            theCuts;

  // cash
  const G4Material*                   currentMaterial;
  const G4MaterialCutsCouple* currentCouple;
  size_t                                     currentMaterialIndex;

  G4int                            nLambdaBins;

  G4double                     minKinEnergy;
  G4double                     maxKinEnergy;

  G4double                     preStepLambda;
  G4double                     preStepKinEnergy;

  G4bool                         integral;
  G4bool                         meanFreePath;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline void G4VEmProcess::DefineMaterial(const G4MaterialCutsCouple* couple)
{
  if(couple != currentCouple) {
    currentCouple   = couple;
    currentMaterial = couple->GetMaterial();
    currentMaterialIndex = couple->GetIndex();
    if(integral && !meanFreePath) ResetNumberOfInteractionLengthLeft();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline G4double G4VEmProcess::GetMeanFreePath(const G4Track& track,
                                                            G4double,
                                                            G4ForceCondition* cond)
{
  *cond = NotForced;

  DefineMaterial(track.GetMaterialCutsCouple());
  preStepKinEnergy = track.GetKineticEnergy();
  if (meanFreePath) {
    G4bool b;
    preStepLambda = (((*theLambdaTable)[currentMaterialIndex])->
                      GetValue(preStepKinEnergy, b));
    if (integral) meanFreePath = false;
  }
  G4double x = DBL_MAX;
  if(0.0 < preStepLambda) x = 1.0/preStepLambda;
//  G4cout << GetProcessName() << ": e= " << preStepKinEnergy << " mfp= " << x << G4endl;
  return x;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline void G4VEmProcess::ResetNumberOfInteractionLengthLeft()
{
  meanFreePath = true;
  G4VProcess::ResetNumberOfInteractionLengthLeft();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline G4VEmModel* G4VEmProcess::SelectModel(G4double& kinEnergy)
{
  return modelManager->SelectModel(kinEnergy, currentMaterialIndex);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline const G4ParticleDefinition* G4VEmProcess::Particle() const
{
  return particle;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline const G4ParticleDefinition* G4VEmProcess::SecondaryParticle() const
{
  return secondaryParticle;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline void G4VEmProcess::SetLambdaBinning(G4int nbins)
{
  nLambdaBins = nbins;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline void G4VEmProcess::SetMinKinEnergy(G4double e)
{
  minKinEnergy = e;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline G4double G4VEmProcess::MinKinEnergy() const
{
  return minKinEnergy;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline void G4VEmProcess::SetMaxKinEnergy(G4double e)
{
  maxKinEnergy = e;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline G4double G4VEmProcess::MaxKinEnergy() const
{
  return maxKinEnergy;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline G4double G4VEmProcess::GetLambda(G4double kineticEnergy,
                                      const G4MaterialCutsCouple* couple)
{
  DefineMaterial(couple);
  G4double x = DBL_MAX;
  G4bool b;
  if(theLambdaTable) {
    G4double y = (((*theLambdaTable)[currentMaterialIndex])->GetValue(kineticEnergy, b));
    if(y > 0.0) x = 1.0/y;
  }
  return x;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif