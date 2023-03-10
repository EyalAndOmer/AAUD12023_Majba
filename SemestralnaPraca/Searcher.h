#include "CSVElement.h"
#include <functional>  // Import pre lambdu

// Prvy generic urcuje druh iteratora z udajovej struktury kde su objekty ulozene
// Druhy generic urcuje atribut ktory porovnavame z daneho objektu v udajovej strukture
template <typename Iterator, typename Attribute>
class Searcher
{
private:
	Iterator begin_;
	Iterator end_;
	std::vector<CSVElement*> output;

public:
	Searcher(Iterator begin, Iterator end):
	begin_(begin),
	end_(end)
	{
	};

	// Genericka metoda na porovnanie dvoch stringov pomocou lambda funkcie. Metoda vie porovnavat attributy objektoveho typu
	void search(const std::string& substring, std::function<bool(const std::string&, const std::string&)> compare_function, Attribute attribute)
	{
		output.clear();

		for (auto iter = begin_; iter != end_; iter++)
		{
			// Cierna magia, zevraj dokazeme genericky zavolat hocijaku metodu *Facepalm*
			// Dereferencia attribute je tam preto, lebo posielam attribute ako adresu metody
			if (compare_function(((*iter)->*attribute)(), substring))
			{
				output.push_back(*iter);
			}
		}
	}

	// Metoda na vypis udajov
	void print()
	{
		for (auto element: output)
		{
			std::cout << element->get_code() << " " << element->get_official_title() << " " << element->get_medium_title() << " " <<
				element->get_short_title() << " " << element->get_note() << '\n';
		}
	}

};