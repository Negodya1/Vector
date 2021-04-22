#include <iostream>
#include <fstream>

using namespace std;

struct rectangle {
	unsigned short int id;
	
	string maincolor;
	double height;
	double width;

	string strokecolor;
	double strokewidth;

	int x, y;
};

int main() {
	unsigned short int viewheight = 480, viewWidth = 640;

	ofstream q("output.svg");
	q << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
	q << "<svg width = \"" << viewWidth << "\" height = \"" << viewheight << "\" xmlns = \"http://www.w3.org/2000/svg\" xmlns:svg = \"http://www.w3.org/2000/svg\">" << endl;
	q << "\t<g class=\"layer\">" << endl;
	q << "\t\t<title>Layer 1</title>" << endl;

	rectangle test;
	test.id = 1;
	test.maincolor = "#FF00FF";
	test.height = 100;
	test.width = 50;
	test.strokecolor = "#00FF00";
	test.strokewidth = 3;
	test.x = 50;
	test.y = 35;
	q << "\t\t<rect fill=\"" << "#FF00FF" << "\" height=\"" << test.height << "\" id=\"" << test.id << "\" stroke=\"#00FF00\" stroke-width=\"" << test.strokewidth << "\" width=\"" << test.width << "\" x=\"" << test.x << "\" y=\"" << test.y << "\"/>" << endl;

	q << "\t</g>" << endl;
	q << "</svg>" << endl;
	q.close();
}