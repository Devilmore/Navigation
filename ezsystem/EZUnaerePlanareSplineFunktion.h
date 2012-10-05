#ifndef UNAEREPLANARESPLINEFUNKTION_H
#define UNAEREPLANARESPLINEFUNKTION_H

/////////////////////////////////////////////////////////////////////////////

#include "EZStandard.h"
#include "EZDiskreteUnaerePlanareFunktion.h"
#include "EZUnaereReelleSplineFunktion.h"
namespace EZ
{

/////////////////////////////////////////////////////////////////////////////

class UnaerePlanareSplineFunktion : public DiskreteUnaerePlanareFunktion
{
    SCHNITTSTELLENREIMPLEMENTATION(UnaerePlanareSplineFunktion, DiskreteUnaerePlanareFunktion);

protected:


	
	UnaereReelleSplineFunktion::Zeiger m_funktionx;
	UnaereReelleSplineFunktion::Zeiger m_funktiony;

public:
	virtual Punkt2D operator()(double);
	virtual bool wertHinzufuegen(double definitionswert, Punkt2D funktionswert);
	UnaerePlanareSplineFunktion();
	virtual Punkt2D bestimmeAbleitung(double d);

	virtual ~UnaerePlanareSplineFunktion();
   
};

/////////////////////////////////////////////////////////////////////////////
};
#endif
