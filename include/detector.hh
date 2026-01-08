#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VSensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include "G4PhysicsFreeVector.hh"

// #include 
#include "run.hh"



class SensitiveDetector: public G4VSensitiveDetector
{
    public:
        SensitiveDetector(G4String name);
        ~SensitiveDetector();
        
    private:
        virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
        G4PhysicsFreeVector* eff;
};


#endif