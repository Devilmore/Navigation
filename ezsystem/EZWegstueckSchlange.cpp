#include "EZWegstueckSchlange.h"
#include "EZKreiswegstueck.h"
#include "EZUnaerePlanareFunktionsvisualisierung.h"


namespace EZ
{

	IMPLEMENTIERE_SCHNITTSTELLE_BEGINN(WegstueckSchlange)
		IMPLEMENTIERT_SCHNITTSTELLE(sWegstueckSchlange)
		IMPLEMENTIERT_SCHNITTSTELLE(sUnaerePlanareFunktion)
	IMPLEMENTIERE_SCHNITTSTELLE_ENDE(WegstueckSchlange)

	WegstueckSchlange::WegstueckSchlange()
	{
		KONSTRUIERE_SCHNITTSTELLE;
	}

	sWegstueck::Zeiger WegstueckSchlange::wegstueck( int nummer )
	{
		if ((nummer<anzahl()) && (nummer>=0))
			return m_schlange[nummer];
		else 
			return NULL;
	}

	sWegstueck::Zeiger WegstueckSchlange::wegstueck( double definitionswert )
	{
		for (deque<sWegstueck::Zeiger>::iterator iter = m_schlange.begin();iter < m_schlange.end();iter++)
		{
			if (definitionswert<=(*iter)->weglaenge())
				return *iter;
			definitionswert -= (*iter)->weglaenge();
		}
		return NULL;
	}

	WegstueckSchlange::~WegstueckSchlange()
	{
		m_schlange.clear();
	}

	double WegstueckSchlange::startDefinitionswert( double def )
	{
		double definitionswert = 0.0;
		for (deque<sWegstueck::Zeiger>::iterator iter = m_schlange.begin();iter < m_schlange.end();iter++)
		{
			double alterDefwert = definitionswert;
			definitionswert += (*iter)->weglaenge();
			if (def<definitionswert)
				return alterDefwert;
		}
		return NaN();
	}

	double WegstueckSchlange::startDefinitionswert( int nummer )
	{
		double definitionswert = 0.0;
		for (deque<sWegstueck::Zeiger>::iterator iter = m_schlange.begin();iter < m_schlange.end();iter++)
		{
			if (nummer-- == 0)
				return definitionswert;
			definitionswert=definitionswert+=(*iter)->weglaenge();
		}
		return NaN();
	}
	EZ::Punkt2D WegstueckSchlange::position( double definitionswert )
	{
		sWegstueck::Zeiger weg = wegstueck(definitionswert);
		if (weg!=NULL)
		{
			return weg->position(definitionswert-startDefinitionswert(definitionswert));
		}
		else
			return letztesWegstueck()->position(definitionswert-startDefinitionswert(anzahl()-1));
	}

	double WegstueckSchlange::ausrichtung( double definitionswert )
	{
		sWegstueck::Zeiger weg = wegstueck(definitionswert);
		if (weg!=NULL)
		{
			return weg->ausrichtung(definitionswert-startDefinitionswert(definitionswert));
		}
		else
			return letztesWegstueck()->ausrichtung(definitionswert-startDefinitionswert(anzahl()-1));
	}

	double WegstueckSchlange::endausrichtung( double defintionswert )
	{
		sWegstueck::Zeiger weg = wegstueck(defintionswert);
		if (weg!= NULL)
			return weg->endausrichtung();
		else
			return NaN(); 
	}

	double WegstueckSchlange::endausrichtung( int nummer )
	{
		sWegstueck::Zeiger weg = wegstueck(nummer);
		if (weg!= NULL)
			return weg->endausrichtung();
		else
			return NaN();
	}

	double WegstueckSchlange::endausrichtung()
	{
		if (anzahl()>0)
			return letztesWegstueck()->endausrichtung();
		else
			return NaN();
	}

	double WegstueckSchlange::startausrichtung( int nummer )
	{
		sWegstueck::Zeiger weg = wegstueck(nummer);
		if (weg!= NULL)
			return weg->startausrichtung();
		else
			return NaN(); 
	}

	double WegstueckSchlange::startausrichtung( double definitionswert )
	{
		sWegstueck::Zeiger weg = wegstueck(definitionswert);
		if (weg!= NULL)
			return weg->startausrichtung();
		else
			return NaN();
	}

	bool WegstueckSchlange::fuegeWegstueckHinzu( sWegstueck::Zeiger weg)
	{
		if (weg!=NULL)
		{
			m_schlange.push_back(weg);
			return true;
		}
		return false;
	}

	bool WegstueckSchlange::entferneWegstueckVorne( int anz/*=1*/ )
	{
		if (anz>=anzahl())
			return entferneWegstuecke();
		for (int i = 0;i<anz;i++)
			m_schlange.pop_front();
		return true;
	}

	bool WegstueckSchlange::entferneWegstueckHinten( int anz/*=1*/ )
	{
		if (anz>=anzahl())
			return entferneWegstuecke();
		for (int i = 0;i<anz;i++)
			m_schlange.pop_back();
		return true;
	}

	bool WegstueckSchlange::entferneWegstuecke()
	{
		m_schlange.clear();
		return true;
	}

	bool WegstueckSchlange::rueckwaerts( double definitionswert )
	{
		sWegstueck::Zeiger weg = wegstueck(definitionswert);
		if (weg!= NULL)
			return weg->rueckwaerts();
		return false;
	}

	bool WegstueckSchlange::rueckwaerts( int nummer )
	{
		sWegstueck::Zeiger weg = wegstueck(nummer);
		if (weg!= NULL)
			return weg->rueckwaerts();
		return false;
	}

	bool WegstueckSchlange::rechtsfahrt( double definitionswert )
	{
		Kreiswegstueck::Zeiger kreisweg = Kreiswegstueck::Zeiger::konvertiere(wegstueck(definitionswert));
		if (kreisweg!=NULL)
			return kreisweg->rechtsfahrt();
		else 
			return false;
	}

	bool WegstueckSchlange::rechtsfahrt( int nummer )
	{
		Kreiswegstueck::Zeiger kreisweg = Kreiswegstueck::Zeiger::konvertiere(wegstueck(nummer));
		if (kreisweg!=NULL)
			return kreisweg->rechtsfahrt();
		else 
			return false;
	}

	bool WegstueckSchlange::kreis( double definitionswert )
	{
		Kreiswegstueck::Zeiger kreisweg = Kreiswegstueck::Zeiger::konvertiere(wegstueck(definitionswert));
		return (kreisweg!=NULL);
	}

	bool WegstueckSchlange::kreis( int nummer )
	{
		Kreiswegstueck::Zeiger kreisweg = Kreiswegstueck::Zeiger::konvertiere(wegstueck(nummer));
		return (kreisweg!=NULL);
	}

	double WegstueckSchlange::radius( double definitionswert )
	{
		Kreiswegstueck::Zeiger kreisweg = Kreiswegstueck::Zeiger::konvertiere(wegstueck(definitionswert));
		if (kreisweg!=NULL)
			return kreisweg->radius();
		else 
			return NaN();
	}

	double WegstueckSchlange::radius( int nummer )
	{
		Kreiswegstueck::Zeiger kreisweg = Kreiswegstueck::Zeiger::konvertiere(wegstueck(nummer));
		if (kreisweg!=NULL)
			return kreisweg->radius();
		else 
			return NaN();
	}

	double WegstueckSchlange::laenge( int nummer )
	{
		if (nummer<anzahl())
			return (wegstueck(nummer)->weglaenge());
		else
			return NaN();
	}

	double WegstueckSchlange::laenge( double definitionswert )
	{
		sWegstueck::Zeiger weg = wegstueck(definitionswert);
		if (weg!= NULL)
			return weg->weglaenge();
		else
			return NaN();
	}
	double WegstueckSchlange::definitionsminimum()
	{
		return 0.0;
	}

	EZ::Punkt2D WegstueckSchlange::operator()( double definitionswert)
	{
		return position(definitionswert);
	}
	double WegstueckSchlange::definitionsmaximum()
	{
		double result = 0;
		for (deque<sWegstueck::Zeiger>::iterator iter = m_schlange.begin();iter < m_schlange.end();iter++)
		{
			result += (*iter)->weglaenge();
		}
		return result;
	}

	double WegstueckSchlange::winkel( double definitionswert )
	{
		Kreiswegstueck::Zeiger kreisweg = Kreiswegstueck::Zeiger::konvertiere(wegstueck(definitionswert));
		if (kreisweg!=NULL)
			return kreisweg->winkel();
		else 
			return NaN();
	}

	double WegstueckSchlange::winkel( int nummer )
	{
		Kreiswegstueck::Zeiger kreisweg = Kreiswegstueck::Zeiger::konvertiere(wegstueck(nummer));
		if (kreisweg!=NULL)
			return kreisweg->winkel();
		else 
			return NaN();
	}

	double WegstueckSchlange::endDefintionswert( double def )
	{
		double definitionswert = 0.0;
		for (deque<sWegstueck::Zeiger>::iterator iter = m_schlange.begin();iter < m_schlange.end();iter++)
		{
			double alterDefwert = definitionswert;
			definitionswert += (*iter)->weglaenge();
			if (def>alterDefwert)
				return definitionswert;
		}
		return NaN();

	}

	double WegstueckSchlange::endDefintionswert( int nummer )
	{
		double definitionswert = 0.0;
		for (deque<sWegstueck::Zeiger>::iterator iter = m_schlange.begin();iter < m_schlange.end();iter++)
		{
			definitionswert=definitionswert+=(*iter)->weglaenge();
			if (nummer-- == 0)
				return definitionswert;
		}
		return NaN();

	}

	EZ::Punkt2D WegstueckSchlange::startpunkt( int nummer )
	{
		sWegstueck::Zeiger weg = wegstueck(nummer);
		if (weg!= NULL)
			return weg->startpunkt();
		else
			return Punkt2D(NaN(),NaN());
	}

	EZ::Punkt2D WegstueckSchlange::startpunkt( double definitionswert )
	{
		sWegstueck::Zeiger weg = wegstueck(definitionswert);
		if (weg!= NULL)
			return weg->startpunkt();
		else
			return Punkt2D(NaN(),NaN());
	}

	EZ::Punkt2D WegstueckSchlange::endpunkt( int nummer )
	{
		sWegstueck::Zeiger weg = wegstueck(nummer);
		if (weg!= NULL)
			return weg->endpunkt();
		else
			return Punkt2D(NaN(),NaN());
	}

	EZ::Punkt2D WegstueckSchlange::endpunkt()
	{
		if (anzahl()>0)
			return letztesWegstueck()->endpunkt();
		else 
			return Punkt2D(NaN(),NaN()); 
	}

	EZ::Punkt2D WegstueckSchlange::endpunkt( double definitionswert )
	{
		sWegstueck::Zeiger weg = wegstueck(definitionswert);
		if (weg!= NULL)
			return weg->endpunkt();
		else
			return Punkt2D(NaN(),NaN());
	}

	void WegstueckSchlange::zeichne( sZeichenflaeche::Zeiger zeichenflaeche )
	{
		for (int i = 0; i < anzahl(); i++)
		{
			UnaerePlanareFunktionsvisualisierung::Zeiger visualisierung = new UnaerePlanareFunktionsvisualisierung(wegstueck(i));
			visualisierung->referenzEntfernen();
			double schrittweite;
			if (kreis(i))
			{
				schrittweite = radius(i)*winkel(i) /  40.0;
			} else 
				schrittweite = laenge(i);

			visualisierung->setzeSchrittweite(schrittweite);
			visualisierung->setzeBeginn(0.0);
			visualisierung->setzeEnde  (laenge(i));
			visualisierung->zeichne(zeichenflaeche);
		}
	}

	bool WegstueckSchlange::setzeStartlage( Punkt2D pos, double aus )
	{
		Punkt2D positionDifferenz = pos-startpunkt();
		double ausrichtungDifferenz = aus-startausrichtung();
		for (int i = 0; i < anzahl(); i++)
		{
			//meldeInfo(std::to_string(i)+":   "+std::to_string((pos-startpunkt()).x)+" "+std::to_string((pos-startpunkt()).y));

			wegstueck(i)->verschiebe(positionDifferenz);
			wegstueck(i)->rotiere(pos,ausrichtungDifferenz);
		}
		return true;
	}

	bool WegstueckSchlange::fuegeWegstueckSchlangeHinzu( sWegstueckSchlange::Zeiger schlange )
	{
		for (int i = 0; i < schlange->anzahl(); i++)
		{
			fuegeWegstueckHinzu(schlange->wegstueck(i));
		}
		return true;
	}
}