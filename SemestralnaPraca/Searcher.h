#include "CSVElement.h"
#include <functional>  // Import pre lambdu
#include <libds/amt/implicit_sequence.h>

// Prvy generic urcuje druh iteratora z udajovej struktury kde su objekty ulozene
// Druhy generic urcuje atribut ktory porovnavame z daneho objektu v udajovej strukture
template <typename Iterator, typename Attribute>
class Searcher
{
private:
	/*std::vector<CSVElement*> output;*/
	ds::amt::ImplicitSequence<CSVElement*> output;


public:
	Searcher()
	{
	};

	// Genericka metoda na porovnanie dvoch stringov pomocou lambda funkcie. Metoda vie porovnavat attributy objektoveho typu
	void search(const std::string& substring, std::function<bool(const std::string&, const std::string&)> compare_function, Attribute attribute, Iterator begin, Iterator end)
	{
		if (output.size() > 0)
		{
			output.clear();
		}

		for (auto iter = begin; iter != end; ++iter)
		{
			// Cierna magia, zevraj dokazeme genericky zavolat hocijaku metodu *Facepalm*
			// Dereferencia attribute je tam preto, lebo posielam attribute ako adresu metody
			if (compare_function(((*iter)->*attribute)(), substring))
			{
				output.insertLast().data_ = (*iter);
			}
		}
	}


	ds::amt::ImplicitSequence<CSVElement*> getOutput()
	{
		return output;
	}
};