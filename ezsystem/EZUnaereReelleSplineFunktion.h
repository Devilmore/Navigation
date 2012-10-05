#ifndef UNAEREREELLESPLINEFUNKTION_H
#define UNAEREREELLESPLINEFUNKTION_H

/////////////////////////////////////////////////////////////////////////////

#include "EZStandard.h"
#include "EZDiskreteUnaereReelleFunktion.h"
#include "EZAggregierteUnaereReelleFunktion.h"
#include "EZUnaereReelleKubischePolynomFunktion.h"
#include <list>
namespace EZ
{

/////////////////////////////////////////////////////////////////////////////

class UnaereReelleSplineFunktion : public DiskreteUnaereReelleFunktion
{
    SCHNITTSTELLENREIMPLEMENTATION(UnaereReelleSplineFunktion, DiskreteUnaereReelleFunktion);

protected:
	typedef std::list<UnaereReelleKubischePolynomFunktion::Zeiger> PolynomListe;

	virtual void berechneKoeffizienten();

	std::vector<double> m_a,m_b,m_c,m_d,m_x;
	
	virtual void berechne_a();
	virtual void berechne_b();
	virtual void berechne_c();
	virtual void berechne_d();
	virtual void berechne_x();
	PolynomListe m_polynomListe;
	UnaereReelleKubischePolynomFunktion::Zeiger findePolynom(double d);
	//virtual bool erstelleAggregierteFunktion();
	//AggregierteUnaereReelleFunktion::Zeiger m_aggregierteFunktion;


public:
	virtual bool wertHinzufuegen(double definitionswert, double funktionswert);
	virtual double operator()(double);
	virtual Punkt3D bestimmeAbleitungen(double);
	UnaereReelleSplineFunktion();


	virtual ~UnaereReelleSplineFunktion();
   
};

/////////////////////////////////////////////////////////////////////////////
};
#endif
