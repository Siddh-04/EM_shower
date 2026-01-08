#include "../include/construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
    // fMessenger = new G4GenericMessenger(this, "/Detector/", "Detector construction control");

    nCols = 2;
    nRows = 2;
    xWorld = 1.0*m;
    yWorld = 1.0*m;
    zWorld = 1.0*m;
    xDetector = xWorld/2;
    yDetector = yWorld/2;
    zDetector = 0.01*mm;
    detectGap = 1.0*mm;
    

}
MyDetectorConstruction::~MyDetectorConstruction()
{
}


G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
    nist = G4NistManager::Instance();
    // material Definitions
    air = nist->FindOrBuildMaterial("G4_AIR");
    W = nist->FindOrBuildMaterial("G4_W");
    G4Material* Si = nist->FindOrBuildMaterial("G4_Si");


    
    // World
    solidWorld = new G4Box("World", xWorld/2, yWorld/2, zWorld/2);
    logicWorld = new G4LogicalVolume(solidWorld, W, "World");
    physWorld = new G4PVPlacement(0, {0,0,0}, logicWorld, "World", nullptr, false, 0);

    // Radiator
    // solidRadiator = new G4Box("Radiator", xWorld/4, yWorld/4, 50.0*cm);
    // logicRadiator = new G4LogicalVolume(solidRadiator, W, "Radiator");
    // physRadiator = new G4PVPlacement(0, G4ThreeVector(0,0, 0), logicRadiator, "Radiator", logicWorld, false, 0);



    // Detector
    solidDetector = new G4Box("Detector", xDetector/2, yDetector/2, zDetector/2);
    logicDetector = new G4LogicalVolume(solidDetector, W, "Detector");
    G4int nodet = 100; // number of detectors

    // detector array one after another in stacked formation along z axis
    G4int copyNo = 0;
    for(G4int i = 0; i < nodet; i++)
    {

        G4double xPos =0;
        G4double yPos = 0;
        G4double zPos = i * (zDetector + detectGap);
        physDetector = new G4PVPlacement(0, G4ThreeVector(xPos, yPos, zPos), logicDetector,
                                          "Detector", logicWorld, true, copyNo++);
    }

    fScoringVolume = logicDetector;
    return physWorld;


}

void MyDetectorConstruction::ConstructSDandField()
{
      G4cout << "ConstructSDandField called..." << G4endl;

  // Check scoring volume pointer
  if (!fScoringVolume) {
    G4cerr << "ERROR: fScoringVolume is null. Cannot assign SensitiveDetector." << G4endl;
    return;
  }

  // Create SD and register it with G4SDManager
  auto sdManager = G4SDManager::GetSDMpointer();
  SensitiveDetector* sd = new SensitiveDetector("SD");
  sdManager->AddNewDetector(sd);

  // Assign SD to the scoring logical volume
  fScoringVolume->SetSensitiveDetector(sd);
  G4cout << "Sensitive detector assigned to fScoringVolume = " << fScoringVolume << G4endl;

}