#include "CSVElement.h"
#include <functional>  // Import pre lambdu

// Prvy generic urcuje druh iteratora z udajovej struktury kde su objekty ulozene
// Druhy generic urcuje atribut ktory porovnavame z daneho objektu v udajovej strukture
template <typename Iterator, typename Attribute>
class Searcher
{
private:
	ImplicitList<CSVElement*> output;


public:
	Searcher()
	{
	};

	// Genericka metoda na porovnanie dvoch stringov pomocou lambda funkcie. Metoda vie porovnavat attributy objektoveho typu
	void search(const std::string& substring, std::function<bool(const std::string&, const std::string&)> compare_function, Attribute attribute, Iterator& begin, Iterator& end)
	{

		for (auto iter = begin; iter != end; ++iter)
		{
			// Cierna magia, zevraj dokazeme genericky zavolat hocijaku metodu *Facepalm*
			// Dereferencia attribute je tam preto, lebo posielam attribute ako adresu metody
			if (compare_function(((*iter)->*attribute)(), substring))
			{
				output.insertLast((*iter));
			}
		}
	}


	void clear()
	{
		this->output.clear();
	}


	ImplicitList<CSVElement*>& getOutput()
	{
		return output;
	}
};