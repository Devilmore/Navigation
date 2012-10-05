#include "EZStandard.h"
#include "EZPfadaufbereitung.h"
#include "EZWegstueckSchlange.h"
#include "EZGeradenwegstueck.h"
#include "EZKreiswegstueck.h"
#include "EZUnaerePlanareSplineFunktion.h"
#include "EZWinkelWrapper.h"
//////////////////////////////////////////////////////////////////////

namespace EZ
{

	//////////////////////////////////////////////////////////////////////////////////
	IMPLEMENTIERE_SCHNITTSTELLE_BEGINN(Pfadaufbereitung)
	IMPLEMENTIERE_SCHNITTSTELLE_ENDE(Pfadaufbereitung)

	//////////////////////////////////////////////////////////////////////////////////

	sWegstueckSchlange::Zeiger Pfadaufbereitung::konvertiereAggregiertenPfad( AggregierterPfad::Zeiger pfad ,double schrittweite)
	{
		sWegstueckSchlange::Zeiger ergebnis = new WegstueckSchlange();
		ergebnis->referenzEntfernen();

		for (size_t i = 0;i<pfad->anzahlPfade();i++)
		{
			ergebnis->fuegeWegstueckSchlangeHinzu(konvertiere(pfad->pfad(i),schrittweite));
		}
		return ergebnis;
	}

	sWegstueckSchlange::Zeiger Pfadaufbereitung::konvertierePfadstueck( Pfadstueck::Zeiger pfad , double schrittweite)
	{
		sWegstueckSchlange::Zeiger ergebnis = new WegstueckSchlange();
		ergebnis->referenzEntfernen();
		bool rueckwaerts = pfad->rueckwaerts(pfad->definitionsminimum());

		double definitionsweite = pfad->definitionsmaximum()-pfad->definitionsminimum();

		int anzahlSchritte = std::max(2,(int) floor (definitionsweite/schrittweite));
		schrittweite = definitionsweite/anzahlSchritte;

		UnaerePlanareSplineFunktion::Zeiger spline= new UnaerePlanareSplineFunktion();
		spline->referenzEntfernen();

		for (int i = 0;i<=anzahlSchritte;i++)
		{
			double d = pfad->definitionsminimum() + i *schrittweite;
			spline->wertHinzufuegen(d,(*pfad)(d));
		}

 		schrittweite *= 2.0;
 		anzahlSchritte = std::max(2,(int) floor (definitionsweite/schrittweite));
 		schrittweite = definitionsweite/anzahlSchritte;

		for (int i = 0;i<anzahlSchritte;i++)
		{
			double d = pfad->definitionsminimum() + i *schrittweite;
			Punkt2D punkt = (*spline)(d);
			double ausrichtung = WinkelWrapper(spline->bestimmeAbleitung(d)).bogenmass();
			Punkt2D naechsterPunkt = (*spline)(d+schrittweite);

			double deltaX = punkt.x-naechsterPunkt.x;
			double deltaY = punkt.y-naechsterPunkt.y;

			if ((deltaY*cos(ausrichtung)==deltaX*sin(ausrichtung)))
			{
				// Gerade
				Geradenwegstueck::Zeiger wegstueck = new Geradenwegstueck(punkt,naechsterPunkt,rueckwaerts,0.1);
				wegstueck->referenzEntfernen();
				ergebnis->fuegeWegstueckHinzu(wegstueck);
			}
			else
			{
				// Kreis
				double radius = (deltaX*deltaX+deltaY*deltaY)/(2*(deltaY*cos(ausrichtung)-deltaX*sin(ausrichtung)));
				if (fabs(radius)>10000.0)
				{
					Geradenwegstueck::Zeiger wegstueck = new Geradenwegstueck(punkt,naechsterPunkt,rueckwaerts,0.1);
					wegstueck->referenzEntfernen();
					ergebnis->fuegeWegstueckHinzu(wegstueck);
				}
				else
				{
					Punkt2D mittelpunkt = Punkt2D(sin(ausrichtung),-cos(ausrichtung))*radius+punkt;
					Kreiswegstueck::Zeiger wegstueck = new Kreiswegstueck(punkt,naechsterPunkt,mittelpunkt,radius<0,rueckwaerts,0.1);
					wegstueck->referenzEntfernen();
					ergebnis->fuegeWegstueckHinzu(wegstueck);
				}

			}
		}

		return ergebnis;
	}

	sWegstueckSchlange::Zeiger Pfadaufbereitung::konvertiere( sZeitInvarianterPfad::Zeiger pfad, double schrittweite )
	{
		AggregierterPfad::Zeiger aggregierterPfad = AggregierterPfad::Zeiger::konvertiere(pfad);
		if (aggregierterPfad!=NULL)
			return konvertiereAggregiertenPfad(aggregierterPfad,schrittweite);

		Pfadstueck::Zeiger pfadstueck = Pfadstueck::Zeiger::konvertiere(pfad);
		if (pfadstueck!=NULL)
			return konvertierePfadstueck(pfadstueck, schrittweite);

		meldeWarnung("Pfadaufbereitung::konvertiere: unbekannter Pfadtyp");
		return NULL;
	}
};