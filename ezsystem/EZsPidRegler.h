#ifndef EZ_SPIDREGLER_H
#define EZ_SPIDREGLER_H

///////////////////////////////////////////////////////////////////////////

#include "EZSchnittstelle.h"

///////////////////////////////////////////////////////////////////////////
namespace EZ 
{

///////////////////////////////////////////////////////////////////////////
/// Schnittstelle für einen PID-Regler
//-------------------------------------------------------------------

class sPidRegler : VERWENDE_SCHNITTSTELLE(Schnittstelle) 
{
    DEKLARIERE_SCHNITTSTELLE(sPidRegler);
public:
    virtual double berechneAusgabe(double eingabeP, double eingabeI=0)=0;
	virtual void reset()=0;
};

};
#endif // EZ_SPIDREGLER_H
