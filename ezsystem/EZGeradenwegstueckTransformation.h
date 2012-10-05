#ifndef EZ_GERADENWEGSTUECKTRANSFORMATION_H
#define EZ_GERADENWEGSTUECKTRANSFORMATION_H

///////////////////////////////////////////////////////////////////////////

#include "EZStandard.h"
#include "EZSchnittstelle.h"
#include "EZsObjektarchiv.h"
#include "EZGeradenwegstueck.h"

///////////////////////////////////////////////////////////////////////////

namespace EZ
{

//////////////////////////////////////////////////////////////////////
/// Transformation zwischen Objekten der Klasse 
/// Geradenwegstueck und Objektspeichern.
///
/// @ingroup    Persistenz
//--------------------------------------------------------------------
class GeradenwegstueckTransformation : VERWENDE_SCHNITTSTELLE(sObjekttransformation)
{
    SCHNITTSTELLENIMPLEMENTATION(GeradenwegstueckTransformation);

public:
    
    //////////////////////////////////////////////////////////////////////
    /// Konstruktor.
    //--------------------------------------------------------------------
    GeradenwegstueckTransformation();
    
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
