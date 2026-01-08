#ifndef ACTION__HH
#define ACTION__HH


#include "G4VUserActionInitialization.hh"
#include "generator.hh"
#include "run.hh"

#include"stepping.hh"
#include "event.hh"


class MyActionInitialization : public G4VUserActionInitialization
{
    public:
        MyActionInitialization();
        ~MyActionInitialization();

        virtual void Build() const;
        virtual void BuildForMaster() const;
};

#endif