#pragma once
class Filter
{
public:
	virtual bool compare(int value) const = 0;
	virtual std::string toString() const = 0;
	virtual int (CSVElement::*& getSelectedMethod())() = 0;


	Filter() = default;
	virtual ~Filter() = default;
};

class OneSideFilter : public Filter
{
protected:
	int bound;
	int (CSVElement::* selectedMethod)();
	std::string attribute_name;

public:
	OneSideFilter(int bound, int (CSVElement::* selectedMethodP)(), std::string att):
	bound(bound),
	selectedMethod(selectedMethodP),
	attribute_name(att)
	{
	}

	int (CSVElement::*& getSelectedMethod())() override {
		return selectedMethod;
	}

	~OneSideFilter() = default;

	virtual bool compare(int value) const = 0;
	virtual std::string toString() const = 0;
};

class TwoSideFilter: public Filter
{
protected:
	int lowerBound;
	int upperBound;
	int (CSVElement::* selectedMethod)();
	std::string attribute_name;
public:

	TwoSideFilter(int& lowerBound, int& upperBound, int (CSVElement::*& selectedMethodP)(), std::string& att):
	lowerBound(lowerBound),
	upperBound(upperBound),
	selectedMethod(selectedMethodP),
	attribute_name(att)
	{
	}

	int (CSVElement::*& getSelectedMethod())() override {
		return selectedMethod;
	}

	~TwoSideFilter() = default;

	virtual bool compare(int value) const = 0;
	virtual std::string toString() const = 0;
};

//*******************
//Jednostranne filtre
//*******************

class FilterLessThan : public OneSideFilter
{
public:
	FilterLessThan(int bound, int (CSVElement::* selectedMethodP)(), std::string att) :
		OneSideFilter(bound, selectedMethodP, att)
	{
	}

	~FilterLessThan() = default;

	bool compare(int value) const override {
		return value < this->bound;
	}

	std::string toString() const override
	{
		return "Hodnota " + this->attribute_name + " je menej ako " + std::to_string(this->bound);
	}
};

class FilterMoreThan : public OneSideFilter
{
public:
	FilterMoreThan(int bound, int (CSVElement::* selectedMethodP)(), std::string att):
	 OneSideFilter(bound, selectedMethodP, att)
	{
	}

	~FilterMoreThan() = default;

	bool compare(int value) const override
	{
		return value > this->bound;
	}

	std::string toString() const override
	{
		return "Hodnota " + this->attribute_name + " je viac ako " + std::to_string(this->bound);
	}

};

class FilterMax : public OneSideFilter
{
public:
	FilterMax(int bound, int (CSVElement::*& selectedMethodP)(), std::string& att) :
		OneSideFilter(bound, selectedMethodP, att)
	{
	}

	~FilterMax() = default;

	bool compare(int value) const override
	{
		return value <= this->bound;
	}

	std::string toString() const override
	{
		return "Hodnota " + this->attribute_name + " je najviac " + std::to_string(this->bound);
	}
};

class FilterMin : public OneSideFilter
{
public:
	FilterMin(int bound, int (CSVElement::*& selectedMethodP)(), std::string& att) :
		OneSideFilter(bound, selectedMethodP, att)
	{
	}

	~FilterMin() = default;

	bool compare(int value) const override
	{
		return value >= this->bound;
	}

	std::string toString() const override
	{
		return "Hodnota " + this->attribute_name + " je najmenej " + std::to_string(this->bound);
	}
};


//******************
//Obojstranne filtre
//******************

class FilterBetween : public TwoSideFilter
{
public:
	FilterBetween(int lowerBound, int upperBound, int (CSVElement::*& selectedMethodP)(), std::string& att) :
		TwoSideFilter(lowerBound, upperBound, selectedMethodP, att)
	{
	}

	~FilterBetween() = default;

	bool compare(int value) const override {
		return value >= this->lowerBound && value <= this->upperBound;
	}

	std::string toString() const override
	{
		return "Hodnota " + this->attribute_name + " je medzi " + std::to_string(this->lowerBound) + " " + 
			std::to_string(this->upperBound);
	}
};

