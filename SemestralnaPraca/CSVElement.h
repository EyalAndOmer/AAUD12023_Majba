#include <string>
#include <libds/amt/implicit_sequence.h>

class CSVElement {
private:
	std::string code;
	std::string official_title;
	std::string medium_title;
	std::string short_title;
	std::string note;
public:
	CSVElement(ds::amt::ImplicitSequence<std::string>& content) {
		this->code = content.access(0)->data_;
		this->official_title = content.access(1)->data_;
		this->medium_title = content.access(2)->data_;
		this->short_title = content.access(3)->data_;
		this->note = content.access(4)->data_;
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

};