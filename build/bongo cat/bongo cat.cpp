#include "pch.h"
#include <SFML/Graphics.hpp>
#include "windows.h"
#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>


std::tuple<float, float> bezier(float ratio, float * points, int length) {
	float fact[22] = { 0.001, 0.001, 0.002, 0.006, 0.024, 0.12, 0.72, 5.04, 40.32, 362.88, 3628.8, 39916.8, 479001.6, 6227020.8, 87178291.2, 1307674368.0, 20922789888.0, 355687428096.0, 6402373705728.0, 121645100408832.0, 2432902008176640.0, 51090942171709440 };
	int nn = (length / 2) - 1;
	float xx = 0;
	float yy = 0;

	for (int point = 0; point < length / 2; point++) {
		xx += points[2 * point] * (fact[nn] / (fact[point] * fact[nn - point])) * (pow(ratio, point)) * pow((1 - ratio), (nn - point));
		yy += points[2 * point + 1] * (fact[nn] / (fact[point] * fact[nn - point])) * (pow(ratio, point)) * pow((1 - ratio), (nn - point));
	}

	return std::make_tuple(xx / 1000, yy / 1000);
}


void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int addyy = 29;// 448;//29
	int addxx = 0;// 188;
	sf::RenderWindow window(sf::VideoMode(612+addxx, 352+addyy), "PATRICK STAR", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(240);
	RECT oblong;
	HWND handle;




	


	std::ifstream infile;
	infile.open("skin\\skin settings.txt");
	std::string line;
	std::string args[17];
	int cc = 0;
	std::string lin;
	while (std::getline(infile, line))
	{

		std::size_t index = line.find(":");
		if (index < 100) {
			lin = line.substr(index+1, std::string::npos);
			args[cc] = std::regex_replace(lin, std::regex("^ +| +$|( ) +"), "$1");
			cc++;
		}

	}
	infile.close();


	int horizontal = 0;
	int vertical = 0;
	int blinktimer = 0;
	GetDesktopResolution(horizontal, vertical);


	
	
	int allkeys[113] = { VK_BACK, VK_TAB, VK_CLEAR, VK_RETURN, VK_SHIFT, VK_CONTROL, VK_MENU, VK_PAUSE, VK_CAPITAL, VK_ESCAPE, VK_SPACE, VK_PRIOR, VK_NEXT, VK_END, VK_HOME, VK_LEFT, VK_UP, VK_RIGHT, VK_DOWN, VK_SELECT, VK_LWIN, VK_RWIN, VK_APPS, VK_SLEEP, VK_MULTIPLY, VK_ADD, VK_SEPARATOR, VK_SUBTRACT, VK_DECIMAL, VK_DIVIDE, VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10, VK_F11, VK_F12, VK_NUMLOCK, VK_SCROLL, VK_LSHIFT, VK_RSHIFT, VK_LCONTROL, VK_RCONTROL, VK_LMENU, VK_RMENU, VK_OEM_1, VK_OEM_PLUS, VK_OEM_COMMA, VK_OEM_MINUS, VK_OEM_PERIOD, VK_OEM_2, VK_OEM_3, VK_OEM_4, VK_OEM_5, VK_OEM_6, VK_OEM_7, VK_OEM_8, VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9, VK_PRINT, VK_SNAPSHOT, VK_INSERT, VK_DELETE, VK_HELP, '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	int trackkeys[113];



	
	
	float mousedx = std::stof(args[0]);
	float mousedy = std::stof(args[1]);
	float mousescale = std::stof(args[2]);
	int redv = std::stoi(args[3]);;
	int greenv = std::stoi(args[4]);;
	int bluev = std::stoi(args[5]);;
	int redf = std::stoi(args[6]);;
	int greenf = std::stoi(args[7]);;
	int bluef = std::stoi(args[8]);;
	int redef = std::stoi(args[9]);;
	int greenef = std::stoi(args[10]);;
	int blueef = std::stoi(args[11]);
	int redtip = std::stoi(args[12]);;
	int greentip = std::stoi(args[13]);;
	int bluetip = std::stoi(args[14]);

	float widd = std::stoi(args[15]);
	float widd2 = std::stoi(args[16]);

	float xletter = 0;
	float yletter = 0;
	float swidth = 1920;
	float sheight = 1080;


	int hittimer = 0;
	int hittimer2 = 0;
	int hittimer3 = 0;


	bool mousel = false;
	bool mouser = false;

	bool anykey = false;

	int mstate = 0;

	bool flipperup = true;




	sf::Texture texture;
	if (!texture.loadFromFile("skin\\bg.png")) {}
	sf::Sprite bg(texture);

	sf::Texture texturef;
	if (!texturef.loadFromFile("skin\\fg.png")) {}
	sf::Sprite fg(texturef);

	sf::Texture sleeve;
	if (!sleeve.loadFromFile("skin\\sleeve.png")) {}
	sf::Sprite sl(sleeve);

		/*
	sf::Texture texture2;
	if (!texture2.loadFromFile("skin\\blink.png")) {}
	sf::Sprite blink(texture2);
	*/

	sf::Texture up;
	if (!up.loadFromFile("skin\\up.png")) {}
	sf::Sprite u(up);

	sf::Texture left;
	if (!left.loadFromFile("skin\\down.png")) {}
	sf::Sprite l(left);

	sf::Texture mouse;
	if (!mouse.loadFromFile("skin\\mouse.png")) {}
	sf::Sprite m(mouse);
	m.setScale(mousescale, mousescale);
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		
	
		
	
		swidth = horizontal;
		sheight = vertical;
		xletter = 0;
		yletter = 0;



		float x = 0;
		float y = 0;
		POINT point;
		if (GetCursorPos(&point)) {
			float fx = ((float)point.x - xletter) / swidth;
			float fy = ((float)point.y - yletter) / sheight;
			if (fx > 1) { fx = 1; }
			if (fx < 0) { fx = 0; }
			if (fy < 0) { fy = 0; }
			if (fy > 1) { fy = 1; }
			x = -97 * fx + 44 * fy + 184;
			y = -76 * fx - 40 * fy + 324;
		}


		window.clear(sf::Color(redv, greenv, bluev));
		/*blinktimer++;
		if (blinktimer % 1700 < 70) {
			window.draw(blink);
		}
		else {
			window.draw(bg);
		}*/
		window.draw(bg);

		hittimer3++;
		if ((GetKeyState(VK_LBUTTON) & 0x8000) && (GetKeyState(VK_RBUTTON) & 0x8000)) {
			if (hittimer3 > 31 && mstate != 3) {
				mstate = 3;
				if (!mouse.loadFromFile("skin\\mouselr.png")) {}
				m.setScale(mousescale, mousescale);
				hittimer3 = 0;
			}
		}
		if (!(GetKeyState(VK_LBUTTON) & 0x8000) && (GetKeyState(VK_RBUTTON) & 0x8000)) {
			if (hittimer3 > 31 && mstate != 2) {
				mstate = 2;
				if (!mouse.loadFromFile("skin\\mouser.png")) {}
				m.setScale(mousescale, mousescale);
				hittimer3 = 0;
			}
		}
		if ((GetKeyState(VK_LBUTTON) & 0x8000) && !(GetKeyState(VK_RBUTTON) & 0x8000)) {
			if (hittimer3 > 31 && mstate != 1) {
				mstate = 1;
				if (!mouse.loadFromFile("skin\\mousel.png")) {}
				m.setScale(mousescale, mousescale);
				hittimer3 = 0;
			}
		}
		if (!(GetKeyState(VK_LBUTTON) & 0x8000) && !(GetKeyState(VK_RBUTTON) & 0x8000)) {
			if (hittimer3 > 31 && mstate != 0) {
				mstate = 0;
				if (!mouse.loadFromFile("skin\\mouse.png")) {}
				m.setScale(mousescale, mousescale);
				hittimer3 = 0;
			}
		}


		
		
	


		hittimer++;
		hittimer2++;
		anykey = false;
		for (int polk = 0; polk < 113; polk++) {//113
			if (GetKeyState(allkeys[polk]) & 0x8000) {
				anykey = true;
				if (!trackkeys[polk]) {
					trackkeys[polk] = true;
					if (!flipperup) {
						hittimer = 0;
					}
				}
			}
			else {
				trackkeys[polk] = false;
			}
		}
		if ((anykey && hittimer>31) || hittimer2<31) {
			window.draw(l);
			if (flipperup) {
				hittimer2 = 0;
			}
			
			flipperup = false;
		}
		else {
			window.draw(u);
			flipperup = true;
		}


		


		int cc = 0;
		cc = 0;
		float pss[38];
		int oof = 6;
		pss[cc] = 211;
		cc++;
		pss[cc] = 159;
		cc++;
		float dist = pow((pow(211 - x, 2) + pow(159 - y, 2)), 0.5);
		float centreleft0 = 211 - 0.7237*dist / 2;
		float centreleft1 = 159 + 0.69*dist / 2;
		for (float i = 1; i < oof; i++) {
			float p0;
			float p1;
			float bez[6] = { 211,159,centreleft0,centreleft1,x,y};
			std::tie(p0, p1) = bezier(i / oof, bez, 6);
			pss[cc] = p0;
			cc++;
			pss[cc] = p1;
			cc++;
		}
		pss[cc] = x;
		cc++;
		pss[cc] = y;
		cc++;
		float a = y - centreleft1;
		float b = centreleft0 - x;
		float le = pow((pow(a, 2) + pow(b, 2)), 0.5);
		a = x + a / le * 60;
		b = y + b / le * 60;
		int a1 = 258;
		int a2 = 228;
		dist = pow((pow((a1 - a), 2) + pow((a2 - b), 2)), 0.5);
		float centreright0 = a1 - 0.6*dist / 2;
		float centreright1 = a2 + 0.8*dist / 2;
		int push = 20;
		float s = x - centreleft0;
		float t = y - centreleft1;
		le = pow((pow(s, 2) + pow(t, 2)), 0.5);
		s *= push / le;
		t *= push / le;
		float s2 = a - centreright0;
		float t2 = b - centreright1;
		le = pow((pow(s2, 2) + pow(t2, 2)), 0.5);
		s2 *= push / le;
		t2 *= push / le;
		for (float i = 1; i < oof; i++) {
			float p0;
			float p1;
			float bez2[8] = { x, y,x + s, y + t,a + s2, b + t2,a, b };
			std::tie(p0, p1) = bezier(i / oof, bez2, 8);
			pss[cc] = p0;
			cc++;
			pss[cc] = p1;
			cc++;
		}
		pss[cc] = a;
		cc++;
		pss[cc] = b;
		cc++;
		for (float i = oof - 1; i > 0; i--) {
			float p0;
			float p1;
			float bez3[6] = { a1, a2,centreright0,centreright1,a,b };
			std::tie(p0, p1) = bezier(i / oof, bez3, 6);
			pss[cc] = p0;
			cc++;
			pss[cc] = p1;
			cc++;
		}
		pss[cc] = a1;
		cc++;
		pss[cc] = a2;
		cc++;
		float mpos0 = (a + x) / 2 - 52 - 15;
		float mpos1 = (b + y) / 2 - 34 + 5;
		float dx = -38;
		float dy = -50;

		const int iter = 25;

		m.setPosition(mpos0 + dx + mousedx, mpos1 + dy + mousedy + addyy);


		float pss2[2 * iter + 2];
		int cc2 = 0;
		pss2[cc2] = pss[0] + dx;
		cc2++;
		pss2[cc2] = pss[1] + dy;
		cc2++;
		for (float i = 1; i < iter; i++) {
			float p0;
			float p1;
			std::tie(p0, p1) = bezier(i / iter, pss, 38);
			pss2[cc2] = p0 + dx;
			cc2++;
			pss2[cc2] = p1 + dy;
			cc2++;
		}
		pss2[cc2] = pss[36] + dx;
		cc2++;
		pss2[cc2] = pss[37] + dy;



		window.draw(m);


		sf::VertexArray fill(sf::TriangleStrip, 26);
		for (int i = 0; i < 26; i += 2) {
			fill[i].position = sf::Vector2f(pss2[i], pss2[i + 1]+addyy);
			fill[i + 1].position = sf::Vector2f(pss2[52 - i - 2], pss2[52 - i - 1]+addyy);

		}
		window.draw(fill);

		sf::VertexArray fill9(sf::TriangleStrip, 26);
		for (int i = 0; i < 26; i += 2) {
			fill9[i].position = sf::Vector2f(pss2[i], pss2[i + 1] + addyy);
			fill9[i + 1].position = sf::Vector2f(pss2[52 - i - 2], pss2[52 - i - 1] + addyy);
			fill9[i].color = sf::Color(redtip, greentip, bluetip, 255);
			fill9[i + 1].color = sf::Color(redtip, greentip, bluetip, 255);

		}
		window.draw(fill9);
		/*
		sf::VertexArray fill2(sf::TriangleStrip, 14);//14 for sleeve
		for (int i = 0; i < 14; i += 2) {  //14 for sleeve
			fill2[i].position = sf::Vector2f(pss2[i], pss2[i + 1]+addyy);
			fill2[i + 1].position = sf::Vector2f(pss2[52 - i - 2], pss2[52 - i - 1] + addyy);
			fill2[i].color = sf::Color(redf, greenf, bluef, 255);
			fill2[i + 1].color = sf::Color(redf, greenf, bluef, 255);

		}
		window.draw(fill2);
		*/

		



		

		int shad = 77;
		sf::VertexArray edge(sf::TriangleStrip, 52);
		float width = widd;
		sf::CircleShape circ(width / 2);
		circ.setFillColor(sf::Color(redef, greenef, blueef, shad));
		circ.setPosition(pss2[0] - width / 2, pss2[1] - width / 2+addyy);
		window.draw(circ);
		for (int i = 0; i < 50; i += 2) {
			float vec0 = pss2[i] - pss2[i + 2];
			float vec1 = pss2[i + 1] - pss2[i + 3];
			float dist = pow((pow(vec0, 2) + pow(vec1, 2)), 0.5);
			edge[i].position = sf::Vector2f(pss2[i] + vec1 / dist * width / 2, pss2[i + 1] - vec0 / dist * width / 2 + addyy);
			edge[i + 1].position = sf::Vector2f(pss2[i] - vec1 / dist * width / 2, pss2[i + 1] + vec0 / dist * width / 2 + addyy);
			edge[i].color = sf::Color(redef,greenef,blueef, shad);
			edge[i + 1].color = sf::Color(redef, greenef, blueef, shad);
			width -= widd2/100;

		}
		float vec0 = pss2[50] - pss2[48];
		float vec1 = pss2[51] - pss2[49];
		dist = pow((pow(vec0, 2) + pow(vec1, 2)), 0.5);
		edge[51].position = sf::Vector2f(pss2[50] + vec1 / dist * width / 2, pss2[51] - vec0 / dist * width / 2 + addyy);
		edge[50].position = sf::Vector2f(pss2[50] - vec1 / dist * width / 2, pss2[51] + vec0 / dist * width / 2 + addyy);
		edge[50].color = sf::Color(redef, greenef, blueef, shad);
		edge[51].color = sf::Color(redef, greenef, blueef, shad);
		window.draw(edge);
		circ.setRadius(width / 2);
		circ.setPosition(pss2[50] - width / 2, pss2[51] - width / 2+addyy);
		window.draw(circ);


		sf::VertexArray edge2(sf::TriangleStrip, 52);
		width = widd - 1;
		sf::CircleShape circ2(width / 2);
		circ2.setFillColor(sf::Color(redef, greenef, blueef, 255));
		circ2.setPosition(pss2[0] - width / 2, pss2[1] - width / 2+addyy);
		window.draw(circ2);
		for (int i = 0; i < 50; i += 2) {
			vec0 = pss2[i] - pss2[i + 2];
			vec1 = pss2[i + 1] - pss2[i + 3];
			float dist = pow((pow(vec0, 2) + pow(vec1, 2)), 0.5);
			edge2[i].position = sf::Vector2f(pss2[i] + vec1 / dist * width / 2, pss2[i + 1] - vec0 / dist * width / 2 + addyy);
			edge2[i + 1].position = sf::Vector2f(pss2[i] - vec1 / dist * width / 2, pss2[i + 1] + vec0 / dist * width / 2 + addyy);
			edge2[i].color = sf::Color(redef, greenef, blueef, 255);
				edge2[i + 1].color = sf::Color(redef, greenef, blueef, 255);
			width -= widd2/100;

		}
		vec0 = pss2[50] - pss2[48];
		vec1 = pss2[51] - pss2[49];
		dist = pow((pow(vec0, 2) + pow(vec1, 2)), 0.5);
		edge2[51].position = sf::Vector2f(pss2[50] + vec1 / dist * width / 2, pss2[51] - vec0 / dist * width / 2 + addyy);
		edge2[50].position = sf::Vector2f(pss2[50] - vec1 / dist * width / 2, pss2[51] + vec0 / dist * width / 2 + addyy);
		edge2[50].color = sf::Color(redef, greenef, blueef, 255);
			edge2[51].color = sf::Color(redef, greenef, blueef, 255);
		window.draw(edge2);
		circ2.setRadius(width / 2);
		circ2.setPosition(pss2[50] - width / 2, pss2[51] - width / 2+addyy);
		window.draw(circ2);

		/*
		float angle = std::atan2(pss2[39] - pss2[13], pss2[38] - pss2[12]);
		float ddd = pow(pow(pss2[13] - pss2[39], 2) + pow(pss2[12] - pss2[38], 2), 0.5);
		sl.setRotation(angle * 180 / 3.1415 - 13);
		sl.setScale(ddd / 78, ddd / 78);
		sl.setPosition(pss2[12] - 4, pss2[13] - 11 + 29);
		window.draw(sl);
		*/

		window.draw(fg);


		window.display();
	}
	return 0;
}
