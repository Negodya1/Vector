#include <iostream>
#include <fstream>
#include <string>

using namespace std;
struct rectangle {
	unsigned short int id;

	string maincolor;
	double height;
	double width;

	bool stroke;
	string strokecolor;
	double strokewidth;

	int x, y;
};

struct List {
	struct Node {
		rectangle data;
		Node* next;
		Node* prev;
	};

	Node* F = NULL;
	Node* L = NULL;
	Node* C = NULL;
	int count;

	void Out();
	void Info();
	void Clear();

	bool MoveNext();
	bool MovePrev();
	bool MoveFirst();
	bool MoveLast();

	bool Init(rectangle);
	bool AddNext(rectangle);
	bool AddPrev(rectangle);
	bool AddFirst(rectangle);
	bool AddLast(rectangle);

	bool Del(rectangle&);
	bool DelNext(rectangle&);
	bool DelPrev(rectangle&);
	bool DelFirst(rectangle&);
	bool DelLast(rectangle&);
};

/*void List::Out() {
	if (!F) {
		cout << "\nList is empty" << endl;
		return;
	}

	Node* temp = F;
	cout << "List: ";
	do {
		cout << temp->data << " ";
		temp = temp->next;
	} while (temp);
	cout << endl;
}
/*void List::Info() {
	if (count) cout << "List node count: " << count << endl;
	else cout << "List is empty" << endl;
	if (C) cout << "Current node data = " << C->data << endl;
}
void List::Clear() {}*/

bool List::MoveNext() {
	if (!F) return false;
	if (!C) {
		C = F;
		return true;
	}
	if (!C->next) return false;
	C = C->next;
	return true;
}
bool List::MovePrev() {
	if (!F) return false;
	if (!C) {
		C = F;
		return true;
	}
	if (!C->prev) return false;
	C = C->prev;
	return true;
}
bool List::MoveFirst() {
	if (!F) return false;
	C = F;
	return true;
}
bool List::MoveLast() {
	if (!L) return false;
	C = L;
	return true;
}

bool List::Init(rectangle data) {
	if (!F) {
		F = new Node;
		L = F;
		C = F;
		F->prev = NULL;
		F->next = NULL;
		F->data = data;
		count = 1;
		return false;
	}
	else return false;
}
bool List::AddNext(rectangle data) {
	if (!F) return Init(data);

	Node* temp = C->next;
	C->next = new Node;
	C->next->next = temp;
	C->next->prev = C;

	if (!temp) L = C->next;
	else temp->prev = C->next;

	C = C->next;
	C->data = data;
	count++;
	return true;
}
bool List::AddPrev(rectangle data) {
	if (!F) return Init(data);

	Node* temp = C->prev;
	C->prev = new Node;
	C->prev->next = C;
	C->prev->prev = temp;

	if (!temp) F = C->prev;
	else temp->next = C->prev;

	C = C->prev;
	C->data = data;
	count++;
	return true;
}
bool List::AddFirst(rectangle data) {
	if (MoveFirst()) return AddPrev(data);
	else return Init(data);
}
bool List::AddLast(rectangle data) {
	if (MoveLast()) return AddNext(data);
	else return Init(data);
}

bool List::Del(rectangle& data) {
	if (!F) return false;
	if (!C) return false;

	if (C == F) return DelFirst(data);
	if (C == L) return DelLast(data);

	Node* temp = C->next;
	data = C->data;

	C->prev->next = C->next;
	C->next->prev = C->prev;

	delete C;
	C = temp;
	count--;
	return true;
}
bool List::DelNext(rectangle& data) {
	if (!F) return false;
	if (!C) return false;
	if (MoveNext()) return Del(data);
	return false;
}
bool List::DelPrev(rectangle& data) {
	if (!F) return false;
	if (!C) return false;
	if (MovePrev()) return Del(data);
	return false;
}
bool List::DelFirst(rectangle& data) {
	if (!F) return false;
	if (C != F) MoveFirst();

	Node* temp = C->next;
	data = C->data;

	if (temp) temp->prev = NULL;
	delete C;

	C = temp;
	F = temp;
	count--;
	if (!temp) {
		L = NULL;
		return false;
	}
	return true;
}
bool List::DelLast(rectangle& data) {
	if (!F) return false;
	if (C != L) MoveLast();

	Node* temp = C->prev;
	data = C->data;

	if (temp) temp->next = NULL;
	delete C;

	C = temp;
	L = temp;
	count--;
	if (!temp) {
		F = NULL;
		return false;
	}
	return true;
}

int main() {
	setlocale(LC_ALL, "rus");
	unsigned short int viewheight = 480, viewwidth = 640;
	cout << "\nВведите ширину рабочей области: ";
	cin >> viewwidth;
	cout << "Введите длину рабочей области: ";
	cin >> viewheight;

	//q << "\t<g class=\"layer\">" << endl;
	//q << "\t\t<title>Layer 1</title>" << endl;
	rectangle rect;
	List l;

	unsigned short int m;
	unsigned short id = 1;

	do {
		rect.id = id;
		rect.maincolor = "ffffff";
		rect.height = 50;
		rect.width = 50;
		rect.stroke = true;
		rect.strokecolor = "000000";
		rect.strokewidth = 5;
		rect.x = 0;
		rect.y = 0;
		
		if (l.count > 0) {
			cout << "\nТекущий слой: ";
			cout << "\nЦвет = #" << l.C->data.maincolor << "\nРазмеры = " << l.C->data.height << 'x' << l.C->data.width;
			if (l.C->data.stroke == true) {
				cout << "\nЦвет обводки = #" << l.C->data.strokecolor << "\tШирина обводки = " << l.C->data.strokewidth;
			}
			else cout << "\nОбводка: выкл";
			cout << "\nКоординаты: " << l.C->data.x << 'x' << l.C->data.y << endl;
		}
		
		cout << "\nВыберите действие\n1. Добавить прямоугольник над текущим слоем\n2. Добавить прямоугольник под текущим слоем\n3. Изменить текущий слой\n4. Удалить текущий слой\n5. Следующий слой\n6. Предыдущий слой\n7. Сохранить в файл\n0. Выход: ";
		cin >> m;

		if (m == 1 || m == 2) {
			unsigned short int n;
			do {
				cout << "\n1. Цвет = #" << rect.maincolor << "\n2. Размеры = " << rect.height << 'x' << rect.width;
				if (rect.stroke == true) {
					cout << "\n3. Цвет обводки = #" << rect.strokecolor << "\tШирина обводки = " << rect.strokewidth;
				}
				else cout << "\n3. Обводка: выкл";
				cout << "\n4. Координаты: " << rect.x << 'x' << rect.y;

				cout << "\n\nВыберите параметр для изменения: ";
				cin >> n;

				if (n == 1) {
					cout << "\nЦвет: ";
					cin >> rect.maincolor;
				}
				if (n == 2) {
					cout << "\nШирина: ";
					cin >> rect.width;
					cout << "\nДлина: ";
					cin >> rect.height;
				}
				if (n == 3) {
					if (rect.stroke == true) {
						unsigned short int t;
						cout << "\n1. Выключить обводку\n2. Изменить цвет обводки\n3. Изменить толщину обводки: ";
						cin >> t;
						if (t == 2) {
							cout << "\nЦвет: ";
							cin >> rect.strokecolor;
						}
						if (t == 3) {
							cout << "\nШирина: ";
							cin >> rect.strokewidth;
						}
						if (t == 1) rect.stroke = false;
					}
					else rect.stroke = true;
				}
				if (n == 4) {
					cout << "x: ";
					cin >> rect.x;
					cout << "y: ";
					cin >> rect.y;
				}
			} while (n > 0 && n < 5);
			if (m == 1) l.AddNext(rect);
			if (m == 2) l.AddPrev(rect);
			id++;
		}
		if (m == 3) {
			unsigned short int n;
			do {
				cout << "\n1. Цвет = #" << l.C->data.maincolor << "\n2. Размеры = " << l.C->data.height << 'x' << l.C->data.width;
				if (l.C->data.stroke == true) {
					cout << "\n3. Цвет обводки = #" << l.C->data.strokecolor << "\tШирина обводки = " << l.C->data.strokewidth;
				}
				else cout << "\n3. Обводка: выкл";
				cout << "\n4. Координаты: " << l.C->data.x << 'x' << l.C->data.y;

				cout << "\n\nВыберите параметр для изменения: ";
				cin >> n;

				if (n == 1) {
					cout << "\nЦвет: ";
					cin >> l.C->data.maincolor;
				}
				if (n == 2) {
					cout << "\nШирина: ";
					cin >> l.C->data.width;
					cout << "\nДлина: ";
					cin >> l.C->data.height;
				}
				if (n == 3) {
					if (l.C->data.stroke == true) {
						unsigned short int t;
						cout << "\n1. Выключить обводку\n2. Изменить цвет обводки\n3. Изменить толщину обводки: ";
						cin >> t;
						if (t == 2) {
							cout << "\nЦвет: ";
							cin >> l.C->data.strokecolor;
						}
						if (t == 3) {
							cout << "\nШирина: ";
							cin >> l.C->data.strokewidth;
						}
						if (t == 1) l.C->data.stroke = false;
					}
					else l.C->data.stroke = true;
				}
				if (n == 4) {
					cout << "x: ";
					cin >> l.C->data.x;
					cout << "y: ";
					cin >> l.C->data.y;
				}
			} while (n > 0 && n < 5);
		}
		if (m == 4) {
			l.Del(rect);
		}
		
		if (m == 5) l.MoveNext();
		if (m == 6) l.MovePrev();

		if (m == 7) {
			unsigned int c = l.count;

			ofstream q("output.svg");
			q << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
			q << "<svg width = \"" << viewwidth << "\" height = \"" << viewheight << "\" xmlns = \"http://www.w3.org/2000/svg\" xmlns:svg = \"http://www.w3.org/2000/svg\">" << endl;

			l.MoveFirst();
			for (unsigned int i = 0; i < c; i++) {
				rect = l.C->data;

				if (rect.stroke == true) q << "\t\t<rect fill=\"#" << rect.maincolor << "\" height=\"" << rect.height << "\" id=\"" << rect.id << "\" stroke=\"#" << rect.strokecolor << "\" stroke-width=\"" << rect.strokewidth << "\" width=\"" << rect.width << "\" x=\"" << rect.x << "\" y=\"" << rect.y << "\"/>" << endl;
				else q << "\t\t<rect fill=\"#" << rect.maincolor << "\" height=\"" << rect.height << "\" id=\"" << rect.id << "\" width=\"" << rect.width << "\" x=\"" << rect.x << "\" y=\"" << rect.y << "\"/>" << endl;

				l.MoveNext();
			}

			q << "</svg>" << endl;
			q.close();
		}
	} while (m > 0 && m < 8);
	
	l.AddLast(rect);
	ofstream f("output.svg");
	f << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
	f << "<svg width = \"" << viewwidth << "\" height = \"" << viewheight << "\" xmlns = \"http://www.w3.org/2000/svg\" xmlns:svg = \"http://www.w3.org/2000/svg\">" << endl;

	while (l.DelFirst(rect)) {
		if (rect.stroke == true) f << "\t\t<rect fill=\"#" << rect.maincolor << "\" height=\"" << rect.height << "\" id=\"" << rect.id << "\" stroke=\"#" << rect.strokecolor << "\" stroke-width=\"" << rect.strokewidth << "\" width=\"" << rect.width << "\" x=\"" << rect.x << "\" y=\"" << rect.y << "\"/>" << endl;
		else f << "\t\t<rect fill=\"#" << rect.maincolor << "\" height=\"" << rect.height << "\" id=\"" << rect.id << "\" width=\"" << rect.width << "\" x=\"" << rect.x << "\" y=\"" << rect.y << "\"/>" << endl;
	}

	f << "</svg>" << endl;
	f.close();
	
	//q << "\t</g>" << endl;
}