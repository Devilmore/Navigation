#ifndef EZ_KREISWEGSTUECKTRANSFORMATION_H
#define EZ_KREISWEGSTUECKTRANSFORMATION_H

///////////////////////////////////////////////////////////////////////////

#include "EZStandard.h"
#include "EZSchnittstelle.h"
#include "EZsObjektarchiv.h"
#include "EZKreiswegstueck.h"

///////////////////////////////////////////////////////////////////////////

namespace EZ
{

//////////////////////////////////////////////////////////////////////
/// Transformation zwischen Objekten der Klasse 
/// Kreiswegstueck und Objektspeichern.
///
/// @ingroup    Persistenz
//--------------------------------------------------------------------
class KreiswegstueckTransformation : VERWENDE_SCHNITTSTELLE(sObjekttransformation)
{
    SCHNITTSTELLENIMPLEMENTATION(KreiswegstueckTransformation);

public:
    
    //////////////////////////////////////////////////////////////////////
    /// Konstruktor.
    //--------------------------------------------------------------------
    KreiswegstueckTransformation();
    
    virtual std::string typ();
    virtual int version();
    virtual Schnittstelle::Zeiger erzeugeObjekt();
    virtual bool transformiere(int version, sObjektleser::Zeiger leser, Schnittstelle::Zeiger objekt);
    virtual bool transformiere(Schnittstelle::Zeiger objekt, sObjektschreiber::Zeiger schreiber);   
};
    
//////////////////////////////////////////////////////////////////////

};

//////////////////////////////////////////////////////////////////////

#endif
