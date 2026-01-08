#include "../include/run.hh"

MyRunAction::MyRunAction()
{

}
MyRunAction::~MyRunAction()
{

}
void MyRunAction::BeginOfRunAction(const G4Run* run)
{



    G4AnalysisManager* aMan = G4AnalysisManager::Instance();
    G4int Rid = run->GetRunID();
    std::stringstream ss;
    ss << Rid;
    aMan->OpenFile("output"+ss.str()+".root");
    G4cout << "Run started" << G4endl;
    aMan->CreateNtuple("Hits", "Hits in Sensitive Detector");
    aMan->CreateNtupleIColumn("EventID");
    aMan->CreateNtupleDColumn("PrePosX");
    aMan->CreateNtupleDColumn("PrePosZ");
    aMan->CreateNtupleDColumn("KineticEnergy");
    aMan->CreateNtupleDColumn("Edep");
    aMan->CreateNtupleIColumn("CopyNo");
    aMan->FinishNtuple(0);  

    aMan->CreateNtuple("EventEdep", "Total energy deposited in event");
    aMan->CreateNtupleDColumn("TotalEdep");
    aMan->FinishNtuple(1);


}
void MyRunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
    G4cout << "Run ended" << G4endl;
}