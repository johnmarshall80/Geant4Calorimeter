/**
 *  @file   include/G4MCParticleUserAction.hh
 *
 *  @brief  Header file for the geant4 MCParticle user action class.
 *
 *  $Log: $
 */

#ifndef GEANT4_MCPARTICLE_USER_ACTION_H
#define GEANT4_MCPARTICLE_USER_ACTION_H 1

#include <map>

#include "globals.hh"

#include "EventContainer.hh"
#include "G4UserEventAction.hh"
#include "G4UserRunAction.hh"
#include "G4UserSteppingAction.hh"
#include "G4UserTrackingAction.hh"

#include "MCParticle.hh"

/**
 *  @brief G4MCParticleUserAction class
 */
class G4MCParticleUserAction: public G4UserRunAction, public G4UserEventAction, public G4UserTrackingAction, public G4UserSteppingAction
{
public:
    /**
    *  @brief  Constructor
    *
    *  @param  pEventContainer event information
    *  @param  energyCut particle energy threshold
    *  @param  keepEMShowerDaughters option to keep or discard em shower daughters
    */
    G4MCParticleUserAction(EventContainer *pEventContainer, const double energyCut = 0.001, const bool keepEMShowerDaughters = false);

    /**
     *  Destructor
     */
    ~G4MCParticleUserAction();

    /**
    *  @brief  Start of run acction
    *
    *  @param  pG4Run the current run
    */
    void BeginOfRunAction(const G4Run *pG4Run) override;

    /**
    *  @brief  End of run action
    *
    *  @param  pG4Run the current run
    */
    void EndOfRunAction(const G4Run *pG4Run) override;

    /**
    *  @brief  Start of event action
    *
    *  @param  pG4Event the current event
    */
    void BeginOfEventAction(const G4Event *pG4Event) override;

    /**
    *  @brief  End of event action
    *
    *  @param  pG4Event the current event
    */
    void EndOfEventAction(const G4Event *pG4Event) override;

    /**
    *  @brief  Get the parent MC particle track id if it exists
    *
    *  @param  trackId of target particle
    *
    *  @return track id of parent particle
    */
    int GetParent(const int trackId) const;

    /**
    *  @brief  Is the give trackId used in the current event
    *
    *  @param  trackId of target particle
    *
    *  @return is track id of target in current event
    */
    bool KnownParticle(const int trackId) const;

    /**
    *  @brief  Start tracking action
    *
    *  @param  pG4Track the current track
    */
    void PreUserTrackingAction(const G4Track *pG4Track) override;

    /**
    *  @brief  End tracking action
    *
    *  @param  pG4Track the current track
    */
    void PostUserTrackingAction(const G4Track *pG4Track) override;

    /**
    *  @brief  Action to apply to given step
    *
    *  @param  pG4Step the current step
    */
    void UserSteppingAction(const G4Step *pG4Step) override;

private:
    typedef std::map<int, int> IntIntMap;

    EventContainer  *m_pEventContainer;        ///< Current event information
    bool             m_keepEMShowerDaughters;  ///< Option to keep or discard daughters of em showers
    double           m_energyCut;              ///< Energy threshold for tracking particles
    MCParticleInfo   m_currentMCParticleInfo;  ///< Active MC particle information
    MCParticleList   m_mcParticleList;         ///< List of MC particles in the event
    IntIntMap        m_parentIdMap;            ///< Map of MC particle track id to parent MCParticle id
    int              m_currentPdgCode;         ///< PDG code of active MC particle
    int              m_currentTrackId;         ///< Current track id of active MC particle
    int              m_trackIdOffset;          ///< Track id offset
};

//------------------------------------------------------------------------------------------------------------------------------------------ 

#endif // #ifndef GEANT4_MCPARTICLE_USER_ACTION_H
