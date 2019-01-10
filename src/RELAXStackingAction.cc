//////////////////////////////
// Nickolas Upole           //
// University of Chicago    //
// Winter 2018              //
// RELAXStackingAction.cc   //
//////////////////////////////

#include "RELAXStackingAction.hh"

RELAXStackingAction::RELAXStackingAction() : G4UserStackingAction()
{

}

RELAXStackingAction::~RELAXStackingAction()
{
    
}

G4ClassificationOfNewTrack RELAXStackingAction::ClassifyNewTrack(const G4Track* pTrack)
{
    if(pTrack->GetParentID() == 0)
    {
        return fUrgent;
    }
    
    else
    {
        sVolume = pTrack->GetVolume()->GetName();
    
        if((sVolume == "RegionX") || (sVolume == "LXeActiveVolume") || (sVolume == "GateLXe") || (sVolume == "GateGXe") || (sVolume == "RegionY"))
        {
            sParticleType = pTrack->GetDefinition()->GetParticleType();
        
            if(sParticleType == "nucleus")
            {
                return fKill;
            }
        }
    
        else if(sVolume == "EJ301")
        {
            sParticleName = pTrack->GetDefinition()->GetParticleName();
        
            if((sParticleName == "proton") || (sParticleName == "deuteron") || (sParticleName == "C12") || (sParticleName == "C13"))
            {
                return fKill;
            }
        }
        
        return fUrgent;
    }
}
