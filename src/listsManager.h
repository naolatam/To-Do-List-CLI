#ifndef LISTSMANAGER_H
#define LISTSMANAGER_H

#include <nlohmann/json.hpp>

class Element
{
public:

	void load(nlohmann::json json);
	void update(std::string name = "", bool finished = NULL);
	nlohmann::json to_json();


private:

	nlohmann::json data = { {"name", ""}, {"finished", false } };
};

class List
{
public:
	void load(nlohmann::json json, int ListIndex);
	nlohmann::json getElements();
	Element getElement(int index);
	void setName(std::string);
	void setElement(int index, Element elm);
	void newElement(Element elm);
	nlohmann::json to_json();



private:
	int ListIndex;
	nlohmann::json data = { {"name", ""}, {"elements", nlohmann::json::array()} };

};



class Lists
{
public:
	void load(nlohmann::json json);
	nlohmann::json GetData();
	List GetList(int index);
	void SetList(int index, List list);
	int newList(List list);
	nlohmann::json to_json();


private:
	nlohmann::json data;
};







#endif // !LISTSMANAGER_H
