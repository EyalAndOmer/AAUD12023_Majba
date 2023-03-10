#include <string>
#include <vector>

class CSVElement {
private:
	std::string code;
	std::string official_title;
	std::string medium_title;
	std::string short_title;
	std::string note;
public:
	CSVElement(std::vector<std::string>& content) {
		this->code = content[0];
		this->official_title = content[1];
		this->medium_title = content[2];
		this->short_title = content[3];
		this->note = content[4];
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