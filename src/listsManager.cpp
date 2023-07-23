#include "listsManager.h";


 // Fonction de la classe "Lists":

void Lists::load(nlohmann::json json)
{

	Lists::data = json;

}

nlohmann::json Lists::GetData()
{
	nlohmann::json data = Lists::data;

	// NBR List encours & terminé
	// Index & List 

	nlohmann::json res;
	int ended = 0;
	int progress = 0;

	std::string listsStr = "";

	int index = 1;
	for (const auto& objet : data["lists"]) {

		int size = objet["elements"].size();
		int finished = 0;
		for (const auto& element : objet["elements"])
		{
			if (element["finished"] == true)
			{
				finished += 1;
			}
		}
		if (finished == size)
		{
			ended += 1;
		}
		else {
			progress += 1;
		}

		listsStr += "[" + std::to_string(index) + "] " + (objet["name"]).get<std::string>() + "\n";
		index += 1;
	}
	float percent = 100;
	if (ended + progress != 0) {
		percent = (ended * 100) / (ended + progress);
	}
	res["stats"] = {
		{"ended", ended},
		{"progress", progress },
		{"total", ended + progress},
		{"percent", percent}

	};
	res["lists"] = listsStr;

	return res;

}

List Lists::GetList(int index) {
	int ind = index - 1;
	List list;
	list.load(Lists::data["lists"][ind], ind);
	return list;

}

void Lists::SetList(int index, List list) {
	int ind = index - 1;
	Lists::data["lists"][ind] = list.to_json();

}

int Lists::newList(List list) {

	Lists::data["lists"].push_back(list.to_json());
	int index;
	index = Lists::data["lists"].size() - 1;
	return index;
}

nlohmann::json Lists::to_json() {
	return Lists::data;
}


//FIN



// Fonction de la classe "List";


void List::load(nlohmann::json json, int ListIndex) {
	List::data = json;
	List::ListIndex = ListIndex;
}

nlohmann::json List::getElements() {

	nlohmann::json res;
	int ended = 0;
	int progress = 0;

	std::string str = "";

	int index = 1;

	int size = List::data["elements"].size();
	for (const auto& element : List::data["elements"])
	{
		std::string state = "progress";
		if (element["finished"] == true)
		{
			state = "ended";
			ended += 1;
		}
		else
		{
			progress += 1;
		}

		str += "[" + std::to_string(index) + "] " + (element["name"]).get<std::string>() + " - " + state + "\n";
		index += 1;
	}

	float percent = 100;
	if (ended + progress != 0) {
		percent = (ended * 100) / (size);
	}
	res["stats"] = {
		{"ended", ended},
		{"progress", progress },
		{"total", size},
		{"percent", percent}

	};
	res["elements"] = str;

	return res;
}

Element List::getElement(int index){

	Element elm;
	int ind = index - 1;
	elm.load(List::data["elements"][ind]);
	return elm;

}

void List::setElement(int index, Element elm) {
	int ind = index - 1;
	List::data["elements"][ind] = elm.to_json();

}

void List::setName(std::string name) {
	List::data["name"] = name;
}

void List::newElement(Element elm) {

	List::data["elements"].push_back(elm.to_json());
}

nlohmann::json List::to_json() {
	return List::data;
}

// FIN


// Fonction de la classe "Element";


void Element::load(nlohmann::json json) {
	Element::data = json;
}

void Element::update(std::string name, bool finished) {

	if (name != "") {
		Element::data["name"] = name;
	}
	if (finished != NULL) {
		Element::data["finished"] = finished;
	}

}

nlohmann::json Element::to_json() {
	return Element::data;
}


 // FIN