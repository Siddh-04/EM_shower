#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4GenericMessenger.hh"
#include "G4SDManager.hh"
#include "G4Material.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4RotationMatrix.hh"
#include "G4PVReplica.hh"

#include "detector.hh"
#include "stepping.hh"



class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  MyDetectorConstruction();
  virtual ~MyDetectorConstruction();
  
  G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

  virtual G4VPhysicalVolume* Construct();

private:
  virtual void ConstructSDandField();
  G4GenericMessenger* fMessenger;

  G4int nCols, nRows;
  G4double xWorld, yWorld, zWorld;
  G4double xDetector, yDetector, zDetector, detectGap, detectorSize;
  
  G4Material *air, *W;

  G4NistManager* nist = G4NistManager::Instance();
  G4Box* solidWorld, *solidDetector, *solidRadiator;
  G4LogicalVolume* logicWorld, *logicDetector, *logicRadiator;
  G4VPhysicalVolume* physWorld, *physDetector, *physRadiator;
  
  G4LogicalVolume* fScoringVolume;

  
};

#endif