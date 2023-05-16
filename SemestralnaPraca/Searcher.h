#include <functional> 

#include "CSVElement.h"

// Prvy generic urcuje druh iteratora z udajovej struktury kde su objekty ulozene
// Druhy generic urcuje atribut ktory porovnavame z daneho objektu v udajovej strukture
template <typename Iterator, typename Attribute>
class Searcher
{
private:
	ds::adt::ImplicitList<CSVElement*> output;


public:
	Searcher()
	{
	};

	// Genericka metoda na porovnanie dvoch stringov pomocou lambda funkcie. Metoda vie porovnavat attributy objektoveho typu
	template<typename ElementAttribute, typename FilterAttribute>
	void search(const FilterAttribute& filter_attribute, std::function<bool(const ElementAttribute&, const FilterAttribute&)> compare_function, Attribute attribute, Iterator& begin, Iterator& end)
	{

		for (auto iter = begin; iter != end; ++iter)
		{

			// Dereferencia attribute je tam preto, lebo posielam attribute ako adresu metody
			if (compare_function(((*iter)->*attribute)(), filter_attribute))
			{
				output.insertLast((*iter));
			}
		}
	}


	void clear()
	{
		this->output.clear();
	}


	ds::adt::ImplicitList<CSVElement*>& getOutput()
	{
		return output;
	}
};