#include "../include/detector.hh"

SensitiveDetector::SensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
}


SensitiveDetector::~SensitiveDetector()
{
}

G4bool SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist)
{
    G4cout << "|@@@@@@-|-|----------------------" << G4endl;
    G4cout << "Processing hit in Sensitive Detector" << G4endl;
    G4cout << "|@@@@@@-|-|----------------------" << G4endl;

    G4Track* track = aStep->GetTrack();

    G4int eventNO = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    
    G4StepPoint* preStep = aStep->GetPreStepPoint();
    G4ThreeVector prePos = preStep->GetPosition();

    G4StepPoint* postStep = aStep->GetPostStepPoint();   
    G4ThreeVector postPos = postStep->GetPosition();

    G4double energy = preStep->GetKineticEnergy();
    const G4VTouchable* touchable = aStep->GetPreStepPoint()->GetTouchable();
    G4int copyNo = touchable->GetVolume()->GetCopyNo();

    G4double edep = aStep->GetTotalEnergyDeposit();

    G4cout << "Event ID: " << eventNO << G4endl;
    G4cout << "Pre-step position: " << prePos << G4endl;
    G4cout << "Post-step position: " << postPos << G4endl;
    G4cout << "Kinetic energy: " << energy << G4endl;
    G4cout << "Copy No: " << copyNo << G4endl;
    G4cout << "edep: " << edep << G4endl;

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    analysisManager->FillNtupleIColumn(0, 0, eventNO);
    analysisManager->FillNtupleDColumn(0, 1, prePos.x());
    analysisManager->FillNtupleDColumn(0, 2, prePos.z());
    analysisManager->FillNtupleDColumn(0, 3, energy);
    analysisManager->FillNtupleDColumn(0, 4, edep);
    analysisManager->FillNtupleIColumn(0, 5, copyNo);
    analysisManager->AddNtupleRow(0);

    return true;
}
