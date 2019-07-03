//============================================================================
// Name        : gnomever.cpp
// Description : Gnome version view
//             : Usage - |  gnomever | or |  gnomever [FILE]  |
//             : Default FILE - "/usr/share/gnome/gnome-version.xml"
//             : Use -O3 and -s gcc options to reduce binary file size
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#define ISNR(C) C=='2'||C=='0'||C=='1'||C=='3'||C=='4'||C=='5'||C=='7'||C=='6'||C=='8'||C=='9'
#define ISFIELD(F) F=="platform"||F=="minor"||F=="micro"
#define UNKNOWNVERSION cout << "?.?.?" << endl
#define GNOMEVERSIONFILE R"(/usr/share/gnome/gnome-version.xml)"

using namespace std;

bool checkfield(const char * strch) {

	static string accstr { };

	if (*strch == '>')
		accstr = "";
	else
		accstr.push_back(*strch);

	if (ISFIELD(accstr))
		return 1;
	else
		return 0;
}

string readchstream(stringstream * in) {

	string ts;
	int cfield { 0 };
	bool goodFile { false };
	char n;

	while (*in >> n) {
		if (n == '<') {
			do {
				n = in->get();
				cfield += checkfield(&n);
			} while (n != '>');
		}
		if (cfield > 0) {
			n = in->peek();
			while (ISNR(n)) {
				n = in->get();
				if (n == '<' && cfield == 3) {
					n = '\n';
					cfield = 0;
					goodFile = true;
				} else if (n == '<') {
					n = '.';
				}
				ts += n;
			}
		}
	}
	//we saw 3 right fields likely a file is right
	if (goodFile)
		return ts;
	else
		return "wrong_file";
}

int main(int argc, char *argv[]) {

	string gv_file { GNOMEVERSIONFILE };

	if (argc == 1)
		;
	else if (argc == 2) {
		auto &vc = argv[1];
		gv_file.clear();
		gv_file.append(vc);
		if (gv_file == "-v" || gv_file == "-h") {
			cout << '\n' << '\t' << "Gnome version view\n" << endl;
			cout << '\t' << R"(Usage - |  gnomever | or |  gnomever [FILE]  |)"
					<< endl;
			cout << '\n' << '\t'
					<< R"(Default FILE - "/usr/share/gnome/gnome-version.xml")"
					<< endl;
			cout << '\n' << '\t' << "gnomever 153.04072019\n" << endl;
			return 0;
		}
	} else {
		cout << "The typed file name isn't correct, please try again." << endl;
		return 0;
	}

	bool isXML { false };
	ifstream fs(gv_file);
	int sizegvf = gv_file.size();
	if (sizegvf > 4)
		isXML = "xml" == gv_file.substr(sizegvf - 3, sizegvf);

	if (!fs || !isXML)
		UNKNOWNVERSION;
	else {
		stringstream sbuff;
		sbuff << fs.rdbuf();
		fs.close();
		string result = readchstream(&sbuff);
		if (result != "wrong_file")
			cout << result;
		else
			UNKNOWNVERSION;
	}
	return 0;
}
