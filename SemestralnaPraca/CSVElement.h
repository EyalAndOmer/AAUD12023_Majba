#include <string>
#include <libds/adt/list.h>

#ifndef CSVELEMENT_H
#define CSVELEMENT_H

class CSVElement {
private:
	std::string code;
	std::string official_title;
	std::string medium_title;
	std::string short_title;
	std::string note;
	std::string UC_type;

	int no_education_young;
	int basic_education;
	int high_lower_education;
	int high_higher_education;
	int higher_education;
	int university_education;
	int no_education_old;
	int not_clarified;

	bool has_education;

public:
	CSVElement(ds::adt::ImplicitList<std::string>& content) {
		this->code = content[0];
		this->official_title = content[1];
		this->medium_title = content[2];
		this->short_title = content[3];
		this->note = content[4];
		this->UC_type = content[5];
		this->has_education = false;
	}

	void set_education(ds::adt::ImplicitList<int>* content)
	{
		this->no_education_young = content->access(0);
		this->basic_education = content->access(1);
		this->high_lower_education = content->access(2);
		this->high_higher_education = content->access(3);
		this->higher_education = content->access(4);
		this->university_education = content->access(5);
		this->no_education_old = content->access(6);
		this->not_clarified = content->access(7);

		this->has_education = true;
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

	int get_no_education_young()
	{
		return this->no_education_young;
	};
	int get_basic_education()
	{
		return this->basic_education;
	};
	int get_high_lower_education()
	{
		return this->high_lower_education;
	};
	int get_high_higher_education()
	{
		return this->high_higher_education;
	};
	int get_higher_education()
	{
		return this->higher_education;
	};
	int get_university_education()
	{
		return this->university_education;
	};
	int get_no_education_old()
	{
		return this->no_education_old;
	};
	int get_not_clarified()
	{
		return this->not_clarified;
	};

	bool get_has_education()
	{
		return this->has_education;
	}

};
#endif