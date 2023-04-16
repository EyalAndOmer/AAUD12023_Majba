#include <string>
#include "types.h"

class CSVElement {
private:
	std::string code;
	std::string official_title;
	std::string medium_title;
	std::string short_title;
	std::string note;
	std::string UC_type;
public:
	CSVElement(ImplicitList<std::string>& content) {
		this->code = content[0];
		this->official_title = content[1];
		this->medium_title = content[2];
		this->short_title = content[3];
		this->note = content[4];
		this->UC_type = content[5];
	}

	std::string get_code()
	{
		return this->code;
	}

	std::string get_official_title()
	{
		return this->official_title;
	}

	std::string get_medium_title()
	{
		return this->medium_title;
	}

	std::string get_short_title()
	{
		return this->short_title;
	}

	std::string get_note()
	{
		return this->note;
	}

	std::string get_UC_type()
	{
		return this->UC_type;
	}

};