#ifndef EZ_WEGSTUECKSCHLANGETRANSFORMATION_H
#define EZ_WEGSTUECKSCHLANGETRANSFORMATION_H

///////////////////////////////////////////////////////////////////////////

#include "EZStandard.h"
#include "EZSchnittstelle.h"
#include "EZsObjektarchiv.h"
#include "EZWegstueckSchlange.h"

///////////////////////////////////////////////////////////////////////////

namespace EZ
{

//////////////////////////////////////////////////////////////////////
/// Transformation zwischen Objekten der Klasse 
/// Wegstueckschlange und Objektspeichern.
///
/// @ingroup    Persistenz
//--------------------------------------------------------------------
class WegstueckSchlangeTransformation : VERWENDE_SCHNITTSTELLE(sObjekttransformation)
{
    SCHNITTSTELLENIMPLEMENTATION(WegstueckSchlange);

public:
    
    //////////////////////////////////////////////////////////////////////
    /// Konstruktor.
    //--------------------------------------------------------------------
    WegstueckSchlangeTransformation();
    
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
