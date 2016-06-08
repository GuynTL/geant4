// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4UserSteppingAction.hh,v 1.3 1999/04/15 08:47:09 asaim Exp $
// GEANT4 tag $Name: geant4-00-01 $
//
//
//---------------------------------------------------------------
//
//  G4UserSteppingAction.hh
//
//  Description:
//    This class represents actions taken place by the user at each
//    end of stepping. 
//
// Contact:
//   Questions and comments to this code should be sent to
//     Katsuya Amako  (e-mail: Katsuya.Amako@kek.jp)
//     Takashi Sasaki (e-mail: Takashi.Sasaki@kek.jp)
//
//---------------------------------------------------------------

#ifndef G4UserSteppingAction_h
#define G4UserSteppingAction_h 1

class G4Step;
class G4SteppingManager;               // Forward declaration

///////////////////////////
class G4UserSteppingAction 
///////////////////////////
{

//--------
   public:
//--------

// Constructor and destructors
   G4UserSteppingAction(){;}
   virtual ~G4UserSteppingAction(){;}

// Member functions
   void SetSteppingManagerPointer(G4SteppingManager* pValue);
   virtual void UserSteppingAction(const G4Step* aStep){;}

//-----------
   protected:
//-----------

// Member data
   G4SteppingManager* fpSteppingManager;

};

#endif

