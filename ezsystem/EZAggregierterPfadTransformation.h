#ifndef EZ_AGGREGIERTERPFADTRANSFORMATION_H
#define EZ_AGGREGIERTERPFADTRANSFORMATION_H

///////////////////////////////////////////////////////////////////////////

#include "EZStandard.h"
#include "EZSchnittstelle.h"
#include "EZsObjektarchiv.h"
#include "EZAggregierterPfad.h"

///////////////////////////////////////////////////////////////////////////

namespace EZ
{

//////////////////////////////////////////////////////////////////////
/// Transformation zwischen Objekten der Klasse 
/// Wegstueckschlange und Objektspeichern.
///
/// @ingroup    Persistenz
//--------------------------------------------------------------------
class AggregierterPfadTransformation : VERWENDE_SCHNITTSTELLE(sObjekttransformation)
{
    SCHNITTSTELLENIMPLEMENTATION(AggregierterPfadTransformation);

public:
    
    //////////////////////////////////////////////////////////////////////
    /// Konstruktor.
    //--------------------------------------------------------------------
    AggregierterPfadTransformation();
    
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
