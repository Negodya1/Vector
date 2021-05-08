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
struct ellipse {
	unsigned short int id;

	string maincolor;
	int rx;
	int ry;

	bool stroke;
	string strokecolor;
	double strokewidth;

	int x, y;
};

struct List {
	struct Node {
		short int type;
		rectangle data;
		ellipse data2;

		Node* next;
		Node* prev;
	};

	Node* F = NULL;
	Node* L = NULL;
	Node* C = NULL;
	int count;
	/*
	void Out();
	void Info();
	void Clear();
	*/
	short int Type();

	bool MoveNext();
	bool MovePrev();
	bool MoveFirst();
	bool MoveLast();

	//---
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
	//---
	//---
	bool Init(ellipse);
	bool AddNext(ellipse);
	bool AddPrev(ellipse);
	bool AddFirst(ellipse);
	bool AddLast(ellipse);

	bool Del(ellipse&);
	bool DelNext(ellipse&);
	bool DelPrev(ellipse&);
	bool DelFirst(ellipse&);
	bool DelLast(ellipse&);
	//---
	bool Copy(rectangle&);
	bool Copy(ellipse&);
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

short int List::Type() {
	if (C) return C->type;
	else return 404;
}

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
		F->type = 0;
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
	C->type = 0;
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
	C->type = 0;
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

bool List::Init(ellipse data) {
	if (!F) {
		F = new Node;
		L = F;
		C = F;
		F->prev = NULL;
		F->next = NULL;
		F->data2 = data;
		F->type = 1;
		count = 1;
		return false;
	}
	else return false;
}
bool List::AddNext(ellipse data) {
	if (!F) return Init(data);

	Node* temp = C->next;
	C->next = new Node;
	C->next->next = temp;
	C->next->prev = C;

	if (!temp) L = C->next;
	else temp->prev = C->next;

	C = C->next;
	C->data2 = data;
	C->type = 1;
	count++;
	return true;
}
bool List::AddPrev(ellipse data) {
	if (!F) return Init(data);

	Node* temp = C->prev;
	C->prev = new Node;
	C->prev->next = C;
	C->prev->prev = temp;

	if (!temp) F = C->prev;
	else temp->next = C->prev;

	C = C->prev;
	C->data2 = data;
	C->type = 1;
	count++;
	return true;
}
bool List::AddFirst(ellipse data) {
	if (MoveFirst()) return AddPrev(data);
	else return Init(data);
}
bool List::AddLast(ellipse data) {
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

bool List::Del(ellipse& data) {
	if (!F) return false;
	if (!C) return false;

	if (C == F) return DelFirst(data);
	if (C == L) return DelLast(data);

	Node* temp = C->next;
	data = C->data2;

	C->prev->next = C->next;
	C->next->prev = C->prev;

	delete C;
	C = temp;
	count--;
	return true;
}
bool List::DelNext(ellipse& data) {
	if (!F) return false;
	if (!C) return false;
	if (MoveNext()) return Del(data);
	return false;
}
bool List::DelPrev(ellipse& data) {
	if (!F) return false;
	if (!C) return false;
	if (MovePrev()) return Del(data);
	return false;
}
bool List::DelFirst(ellipse& data) {
	if (!F) return false;
	if (C != F) MoveFirst();

	Node* temp = C->next;
	data = C->data2;

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
bool List::DelLast(ellipse& data) {
	if (!F) return false;
	if (C != L) MoveLast();

	Node* temp = C->prev;
	data = C->data2;

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

bool List::Copy(rectangle& data) {
	if (C) {
		data.maincolor = C->data.maincolor;
		data.height = C->data.height;
		data.width = C->data.width;
		data.stroke = C->data.stroke;
		data.strokecolor = C->data.strokecolor;
		data.strokewidth = C->data.strokewidth;
		data.x = C->data.x;
		data.y = C->data.y;
		return true;
	}
	return false;
}
bool List::Copy(ellipse& data) {
	if (C) {
		data.maincolor = C->data2.maincolor;
		data.rx = C->data2.rx;
		data.ry = C->data2.ry;
		data.stroke = C->data2.stroke;
		data.strokecolor = C->data2.strokecolor;
		data.strokewidth = C->data2.strokewidth;
		data.x = C->data2.x;
		data.y = C->data2.y;
		return true;
	}
	return false;
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
	short int type = -1;
	rectangle rect, rectbuf;
	ellipse ell, ellbuf;
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

		ell.id = id;
		ell.maincolor = "ffffff";
		ell.rx = 50;
		ell.ry = 50;
		ell.stroke = true;
		ell.strokecolor = "000000";
		ell.strokewidth = 5;
		ell.x = 0;
		ell.y = 0;
		
		if (l.count > 0) {
			if (l.Type() == 0) {
				cout << "\nТекущий слой (прямоугольник): ";
				cout << "\nЦвет = #" << l.C->data.maincolor << "\nРазмеры = " << l.C->data.height << 'x' << l.C->data.width;
				if (l.C->data.stroke == true) {
					cout << "\nЦвет обводки = #" << l.C->data.strokecolor << "\tШирина обводки = " << l.C->data.strokewidth;
				}
				else cout << "\nОбводка: выкл";
				cout << "\nКоординаты: " << l.C->data.x << 'x' << l.C->data.y << endl;
			}
			if (l.Type() == 1) {
				cout << "\nТекущий слой (эллипс): ";
				cout << "\nЦвет = #" << l.C->data2.maincolor << "\nРадиусы:\nx = " << l.C->data2.rx << "\ny = " << l.C->data2.ry;
				if (l.C->data2.stroke == true) {
					cout << "\nЦвет обводки = #" << l.C->data2.strokecolor << "\tШирина обводки = " << l.C->data2.strokewidth;
				}
				else cout << "\nОбводка: выкл";
				cout << "\nКоординаты: " << l.C->data2.x << 'x' << l.C->data2.y << endl;
			}
		}
		
		cout << "\nВыберите действие\n1. Добавить слой над текущим\n2. Добавить слой под текущим\n3. Изменить текущий слой\n4. Скопировать/вставить слой\n5. Удалить текущий слой\n6. Следующий слой\n7. Предыдущий слой\n8. Сохранить в файл\n0. Выход: ";
		cin >> m;

		if (m == 1 || m == 2) {
			unsigned short int n;
			unsigned short t;
			cout << "\n1. Прямоугольник\n2. Эллипс: ";
			cin >> t;
			do {
				if (t == 1) {
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
				}
				if (t == 2) {
					cout << "\n1. Цвет = #" << ell.maincolor << "\n2. Радиусы:\nx = " << ell.rx << "\ny = " << ell.ry;
					if (ell.stroke == true) {
						cout << "\n3. Цвет обводки = #" << ell.strokecolor << "\tШирина обводки = " << ell.strokewidth;
					}
					else cout << "\n3. Обводка: выкл";
					cout << "\n4. Координаты: " << ell.x << 'x' << ell.y;

					cout << "\n\nВыберите параметр для изменения: ";
					cin >> n;

					if (n == 1) {
						cout << "\nЦвет: ";
						cin >> ell.maincolor;
					}
					if (n == 2) {
						cout << "\nx: ";
						cin >> ell.rx;
						cout << "\ny: ";
						cin >> ell.ry;
					}
					if (n == 3) {
						if (ell.stroke == true) {
							unsigned short int t;
							cout << "\n1. Выключить обводку\n2. Изменить цвет обводки\n3. Изменить толщину обводки: ";
							cin >> t;
							if (t == 2) {
								cout << "\nЦвет: ";
								cin >> ell.strokecolor;
							}
							if (t == 3) {
								cout << "\nШирина: ";
								cin >> ell.strokewidth;
							}
							if (t == 1) ell.stroke = false;
						}
						else ell.stroke = true;
					}
					if (n == 4) {
						cout << "x: ";
						cin >> ell.x;
						cout << "y: ";
						cin >> ell.y;
					}
				}
			} while (n > 0 && n < 5);
			if (m == 1) {
				if (t == 1) l.AddNext(rect);
				if (t == 2) l.AddNext(ell);
			}
			if (m == 2) {
				if (t == 1) l.AddPrev(rect);
				if (t == 2) l.AddPrev(ell);
			}
			id++;
		}

		if (m == 3) {
			unsigned short int n;
			do {
				if (l.Type() == 0) {
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
				}
				if (l.Type() == 1) {
					cout << "\n1. Цвет = #" << l.C->data2.maincolor << "\n2. Радиусы:\nx = " << l.C->data2.rx << "\ny = " << l.C->data2.ry;
					if (l.C->data2.stroke == true) {
						cout << "\n3. Цвет обводки = #" << l.C->data2.strokecolor << "\tШирина обводки = " << l.C->data2.strokewidth;
					}
					else cout << "\n3. Обводка: выкл";
					cout << "\n4. Координаты: " << l.C->data2.x << 'x' << l.C->data2.y;

					cout << "\n\nВыберите параметр для изменения: ";
					cin >> n;

					if (n == 1) {
						cout << "\nЦвет: ";
						cin >> l.C->data2.maincolor;
					}
					if (n == 2) {
						cout << "\nx: ";
						cin >> l.C->data2.rx;
						cout << "\ny: ";
						cin >> l.C->data2.ry;
					}
					if (n == 3) {
						if (l.C->data2.stroke == true) {
							unsigned short int t;
							cout << "\n1. Выключить обводку\n2. Изменить цвет обводки\n3. Изменить толщину обводки: ";
							cin >> t;
							if (t == 2) {
								cout << "\nЦвет: ";
								cin >> l.C->data2.strokecolor;
							}
							if (t == 3) {
								cout << "\nШирина: ";
								cin >> l.C->data2.strokewidth;
							}
							if (t == 1) l.C->data2.stroke = false;
						}
						else l.C->data2.stroke = true;
					}
					if (n == 4) {
						cout << "x: ";
						cin >> l.C->data2.x;
						cout << "y: ";
						cin >> l.C->data2.y;
					}
				}
			} while (n > 0 && n < 5);
		}
		if (m == 4) {
			if (l.count > 0) {
				if (type != -1) {
					unsigned short int t;
					cout << "\n1. Скопировать текущий слой\n2. Вырезать текущий слой\n3. Вставить над текущим слоем\n4.Вставить под текущий слой: ";
					cin >> t;

					if (t == 1) {
						if (l.Type() == 0) {
							type = 0;
							l.Copy(rectbuf);
						}
						if (l.Type() == 1) {
							type = 1;
							l.Copy(ellbuf);
						}
					}
					if (t == 2) {
						if (l.Type() == 0) {
							type = 0;
							l.Del(rectbuf);
						}
						else if (l.Type() == 1) {
							type = 1;
							l.Del(ellbuf);
						}
					}

					if (t == 3) {
						if (type == 0) l.AddNext(rectbuf);
						if (type == 1) l.AddNext(ellbuf);
					}
					if (t == 4) {
						if (type == 0) l.AddPrev(rectbuf);
						if (type == 1) l.AddPrev(ellbuf);
					}
				}
				else {
					if (l.Type() == 0) {
						type = 0;
						l.Copy(rectbuf);
					}
					if (l.Type() == 1) {
						type = 1;
						l.Copy(ellbuf);
					}
				}
			}
			else cout << "\nСписок пуст\n";
		}
		if (m == 5) {
			if (l.Type() == 0) l.Del(rect);
			else if (l.Type() == 1) l.Del(ell);
		}
		
		if (m == 6) l.MoveNext();
		if (m == 7) l.MovePrev();

		if (m == 8) {
			unsigned int c = l.count;

			ofstream q("output.svg");
			q << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
			q << "<svg width = \"" << viewwidth << "\" height = \"" << viewheight << "\" xmlns = \"http://www.w3.org/2000/svg\" xmlns:svg = \"http://www.w3.org/2000/svg\">" << endl;

			l.MoveFirst();
			for (unsigned int i = 0; i < c; i++) {
				if (l.Type() == 0) {
					rect = l.C->data;

					if (rect.stroke == true) q << "\t\t<rect fill=\"#" << rect.maincolor << "\" height=\"" << rect.height << "\" id=\"" << rect.id << "\" stroke=\"#" << rect.strokecolor << "\" stroke-width=\"" << rect.strokewidth << "\" width=\"" << rect.width << "\" x=\"" << rect.x << "\" y=\"" << rect.y << "\"/>" << endl;
					else q << "\t\t<rect fill=\"#" << rect.maincolor << "\" height=\"" << rect.height << "\" id=\"" << rect.id << "\" width=\"" << rect.width << "\" x=\"" << rect.x << "\" y=\"" << rect.y << "\"/>" << endl;
				}
				if (l.Type() == 1) {
					ell = l.C->data2;

					if (ell.stroke == true) q << "\t\t<ellipse cx=\"" << ell.x << "\" cy=\"" << ell.y << "\" fill=\"#" << ell.maincolor << "\" id=\"" << ell.id << "\" rx=\"" << ell.rx << "\" ry=\"" << ell.ry << "\" stroke=\"#" << ell.strokecolor << "\" stroke-width=\"" << ell.strokewidth << "\"/>" << endl;
					else q << "\t\t<ellipse cx=\"" << ell.x << "\" cy=\"" << ell.y << "\" fill=\"#" << ell.maincolor << "\" id=\"" << ell.id << "\" rx=\"" << ell.rx << "\" ry=\"" << ell.ry << "\"/>" << endl;
				}
				l.MoveNext();
			}

			q << "</svg>" << endl;
			q.close();
		}
	} while (m > 0 && m < 9);
	
	unsigned int c = l.count;

	ofstream q("output.svg");
	q << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
	q << "<svg width = \"" << viewwidth << "\" height = \"" << viewheight << "\" xmlns = \"http://www.w3.org/2000/svg\" xmlns:svg = \"http://www.w3.org/2000/svg\">" << endl;

	l.MoveFirst();
	for (unsigned int i = 0; i < c; i++) {
		if (l.Type() == 0) {
			rect = l.C->data;

			if (rect.stroke == true) q << "\t\t<rect fill=\"#" << rect.maincolor << "\" height=\"" << rect.height << "\" id=\"" << rect.id << "\" stroke=\"#" << rect.strokecolor << "\" stroke-width=\"" << rect.strokewidth << "\" width=\"" << rect.width << "\" x=\"" << rect.x << "\" y=\"" << rect.y << "\"/>" << endl;
			else q << "\t\t<rect fill=\"#" << rect.maincolor << "\" height=\"" << rect.height << "\" id=\"" << rect.id << "\" width=\"" << rect.width << "\" x=\"" << rect.x << "\" y=\"" << rect.y << "\"/>" << endl;
		}
		if (l.Type() == 1) {
			ell = l.C->data2;

			if (ell.stroke == true) q << "\t\t<ellipse cx=\"" << ell.x << "\" cy=\"" << ell.y  << "\" fill=\"#" << ell.maincolor << "\" id=\"" << ell.id << "\" rx=\"" << ell.rx <<"\" ry=\"" << ell.ry << "\" stroke=\"#" << ell.strokecolor << "\" stroke-width=\"" << ell.strokewidth << "\"/>" << endl;
			else q << "\t\t<ellipse cx=\"" << ell.x << "\" cy=\"" << ell.y << "\" fill=\"#" << ell.maincolor << "\" id=\"" << ell.id << "\" rx=\"" << ell.rx << "\" ry=\"" << ell.ry << "\"/>" << endl;
		}
		l.MoveNext();
	}

	q << "</svg>" << endl;
	q.close();
	
	//q << "\t</g>" << endl;
}