#include "main.h"


int main() {


	cout << "data loading/creating" << endl;

	for (int i = 0; i < 50; ++i) {
		equalSigns += "=";
	}
	fileM.load();
	nlohmann::json data = fileM.getLists();
	
	lists.load(data);

	listsData = lists.GetData();
		
	cout << "data loaded/created" << endl;
	
	clearConsole();
	int listIndex;

	if(listsData["stats"]["total"] != 0){
		cout << "Tu as finis " + std::to_string(listsData["stats"]["ended"].get<int>()) + " listes sur " + std::to_string(listsData["stats"]["total"].get<int>()) << endl;
		 listIndex= AskListIndex();
	}
	else {
		cout << "Création de la première liste." << endl;
		listIndex = CreateList();
	}
	if (listIndex == 0) {
		listIndex = CreateList();
	}
	manageList(listIndex);

	return 0;
	


}

int AskListIndex() {
	int listIndex = 0;
	cout << "Choisis la listes que tu veux voir" << endl;


	cout << equalSigns << endl;

	string listsStr = listsData["lists"];
	size_t pos = 0;
	while ((pos = listsStr.find("\\n", pos)) != std::string::npos) {
		listsStr.replace(pos, 2, "\n");
	}

	cout << "[0] Ajouter une nouvelle liste." << endl;
	cout << listsStr;
	cout << equalSigns << endl;
	cout << "[?]>>";
	cin >> listIndex;
	return listIndex;
}

void manageList(int listIndex) {
	List list = lists.GetList(listIndex);
	int elementIndex = AskElementIndex(list);

	while (elementIndex == 0) {

		Element elm = createElement();
		list.newElement(elm);
		lists.SetList(1, list);
		elementIndex = AskElementIndex(list);
	}

	Element elm2 = list.getElement(elementIndex);
	clearConsole();
	int actionIndex;
	cout << "[1] - Changer le nom" << endl;
	cout << "[2] - Terminer" << endl;
	cin >> actionIndex;
	if (actionIndex == 1) {
		clearConsole();
		std::string name;
		cout << "Quel nom veut tu donner a cet element?" << endl;
		cout << "[?] >>";
		cin >> name;
		elm2.update(name, NULL);
	}
	if (actionIndex == 2) {
		elm2.update("", true);
	}
	list.setElement(elementIndex, elm2);
	lists.SetList(listIndex, list);
	clearConsole();
	fileM.saveFile(lists.to_json());
	manageList(listIndex);
	

}

int AskElementIndex(List list) {
	nlohmann::json elementsData = list.getElements();

	clearConsole();

	int elementIndex;

	cout << "Tu as termine " << std::to_string(elementsData["stats"]["percent"].get<int>()) << "% de cette liste!" << endl;
	equalsLines();
	cout << "Choisis l'element de la liste que tu veux modifier." << endl;
	equalsLines();
	cout << "[0] Ajouter un nouvelle elements." << endl;
	string elementStr = elementsData["elements"];
	size_t pos = 0;
	while ((pos = elementStr.find("\\n", pos)) != std::string::npos) {
		elementStr.replace(pos, 2, "\n");
	}

	cout << elementStr;
	equalsLines();
	cout << "[?]>>";
	cin >> elementIndex;
	return elementIndex;
}

Element createElement() {
	clearConsole();
	std::string name;
	cout << "Quel est le nom du nouvelle element que tu veux creer ??";
	cin >> name;
	Element elm;
	elm.update(name, false);
	clearConsole();
	centerText("Element " + name + " cree avec succes!");
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	clearConsole();
	return elm;

}

int CreateList() {
	clearConsole();
	std::string name;
	cout << "Quel est le nom de la nouvelle liste que tu veux creer ?";
	cin >> name;
	List list;
	list.setName(name);
	int index = lists.newList(list);
	return index;
}

void clearConsole() {
	system("cls");
}

void equalsLines() {
	cout << equalSigns << endl;
}
void centerText(const std::string& texte) {
	// Obtenir la taille de la console
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int consoleWidth = csbi.dwSize.X;
	int consoleHeight = csbi.dwSize.Y;

	int texteWidth = texte.length();
	int espacementHorizontal = (consoleWidth - texteWidth) / 2;
	int espacementVertical = (consoleHeight - 1) / 2;

	// Centrer verticalement
	for (int i = 0; i < espacementVertical; ++i) {
		std::cout << std::endl;
	}

	// Centrer horizontalement et afficher le texte
	std::cout << std::setw(espacementHorizontal + texteWidth) << texte << std::endl;
}