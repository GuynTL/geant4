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
#include "G4HadProjectile.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4LorentzVector.hh"

G4HadProjectile::
G4HadProjectile(const G4Track &aT) 
: theMat(aT.GetMaterial()),
  theOrgMom(aT.GetDynamicParticle()->Get4Momentum()),
  theDef(aT.GetDefinition())
{
  G4LorentzRotation toZ;
  toZ.rotateZ(-theOrgMom.phi());
  toZ.rotateY(-theOrgMom.theta());
  theMom = toZ*theOrgMom;
  toLabFrame = toZ.inverse();
  theTime = aT.GetGlobalTime();
  G4LorentzVector it(toLabFrame*theMom);
}

G4HadProjectile::
G4HadProjectile(const G4DynamicParticle &aT) 
: theMat(NULL),
  theOrgMom(aT.Get4Momentum()),
  theDef(aT.GetDefinition())
{
  G4LorentzRotation toZ;
  toZ.rotateZ(-theOrgMom.phi());
  toZ.rotateY(-theOrgMom.theta());
  theMom = toZ*theOrgMom;
  toLabFrame = toZ.inverse();
  theTime = 0;
}

G4double G4HadProjectile::GetTotalEnergy() const
{
  return Get4Momentum().e();
}

G4double G4HadProjectile::GetTotalMomentum() const
{
  return Get4Momentum().vect().mag();
}

G4double G4HadProjectile::
GetKineticEnergy() const 
{
  G4double m=GetDefinition()->GetPDGMass();
  return sqrt(Get4Momentum().vect().mag2()+m*m)-m;
}

const G4Material * G4HadProjectile::
GetMaterial() const {return theMat;}

const G4ParticleDefinition * G4HadProjectile::
GetDefinition() const {return theDef;}
