#include <iostream>
#include <string>
#include <list>
#include<vector>
#include <stack>
using namespace std;
//#define max = 10;
const int Max = 10;
int pocetni=0;




class Odgovor {
	vector <Odgovor*>pokKomentar;
	int br = 0;
	int id = pocetni++;
	string odg;
	int ocena = 0;
public:
	Odgovor(string s) {
		odg = s;
	}
	Odgovor(const Odgovor& odgovor) {
		br = odgovor.br;
		id = odgovor.id;
		this->odg = odgovor.odg;
		ocena = odgovor.ocena;
		for (int i = 0; i < odgovor.pokKomentar.size(); i++) {
			pokKomentar[i]= odgovor.pokKomentar[i];
			
		}
	}
	~Odgovor() {
		for (int i = 0; i < dohvVelicinuVektora(); i++) {
			delete pokKomentar[i];
		}
	}

	Odgovor& dodajKomentar(Odgovor& kom,int k) {
		if (br < Max) {
			kom.postaviOcenu(k);
			pokKomentar.push_back(&kom);
			br++;
		}
		else {
			cout << "Greska! Ne moze vise od 10 komentara";
		}
		return *this;
	}
	string& dohvPitanje() { return odg; }
	int dohvBroj() { return br; }
	int dohvVelicinuVektora() { return pokKomentar.size(); }
	vector<Odgovor*>& dohvVektor() { return pokKomentar; }
	int dohvOcenu() { return ocena; }
	void postaviOcenu(int o) { ocena = o; }
	int dohvId() { return id; }
	void ispis() { cout << odg<<"  a ocena je:"<<ocena<<endl; }
	void inkrementiraj() { ocena++; }
};

class Pitanje{
	vector <Odgovor*> pokOdgovor;
	int br = 0;
	string pita;

public:
	
	Pitanje(string s) {

		pita = s;
	}
	void dodajOdgovor(Odgovor& p,int k) {
		if (pokOdgovor.size() < 10) {
			p.postaviOcenu(k);
			pokOdgovor.push_back(&p);
			br++;
		}
		else {
			cout << "previse dodatih odgovora";
		}
	}
	Pitanje(const Pitanje&p) {
		pita = p.pita;
		br = p.br;
		for (int i = 0; i < p.pokOdgovor.size(); i++) {
			pokOdgovor[i] = p.pokOdgovor[i];
		}
	}

	string& dohvPitanje() { return pita; }
	void ispis() { cout << pita<<endl; }
	int dohvBroj() { return pokOdgovor.size(); }
	vector<Odgovor*>& vektor() { return pokOdgovor; }
};

class proizvoljnoPitanja {
	vector <Pitanje*>pokPitanje;
	int br = 0;
public:

	void dodajPitanje(Pitanje& p) {
		pokPitanje.push_back(&p);
		br++;
	}
	void ispis() {
		for (int i = 0; i < pokPitanje.size() ; i++) {
			pokPitanje[i]->ispis();
		}
	}
	
	Pitanje* pretragaPitanja(string s) {
		for (int i = 0; i < pokPitanje.size(); i++) {
			
			if (s==pokPitanje[i]->dohvPitanje())return pokPitanje[i];
		}
		cout << "nema vaseg pitanja";
		return nullptr;
	}
	
	Odgovor* pretragaOdgovora(string pitanje, string odgovor) {
		Pitanje* root = pretragaPitanja(pitanje);
		stack <Odgovor*> stek;
		stack<Odgovor*>stek2;
		if (root->dohvBroj() == 0) {
			cout << "ne postoji zadati komentar/odgovor";
		}
		for (int i = root->dohvBroj(); i > 0; i--) {
			stek.push(root->vektor()[i - 1]);//na stek stavlja sa najvise pozicije element(najdesniji prvo pa onda ove levlje)
		}
		
		while (!stek.empty()) {
			//Odgovor next1=stek.top();
			Odgovor *next = stek.top();
			
			if (odgovor == next->dohvPitanje()) { return next; }//P(next)
			stek2.push(stek.top());
			stek.pop();
			if (stek2.top()->dohvVelicinuVektora() != 0) {
				for (int i = stek2.top()->dohvVelicinuVektora(); i > 0; i--) {
					stek.push(stek2.top()->dohvVektor()[i - 1]);
				}
			}
			stek2.pop();
		}
		
	}

	void pretragaOdgovoraiUbacivanje(string pitanje, string odgovor,string komentar, int k) {
		Pitanje* root = pretragaPitanja(pitanje);
		stack <Odgovor*> stek;
		stack<Odgovor*>stek2;
		if (root->dohvBroj() == 0) {
			cout << "ne postoji zadati komentar/odgovor";
		}
		for (int i = root->dohvBroj(); i > 0; i--) {
			stek.push(root->vektor()[i - 1]);//na stek stavlja sa najvise pozicije element(najdesniji prvo pa onda ove levlje)
		}

		while (!stek.empty()) {
			
			if (odgovor == stek.top()->dohvPitanje()) {
				stek.top()->dodajKomentar(*new Odgovor(komentar), k);
				break;
			}//P(next)
			stek2.push(stek.top());
			stek.pop();
			if (stek2.top()->dohvVelicinuVektora() != 0) {
				for (int i = stek2.top()->dohvVelicinuVektora(); i > 0; i--) {
					stek.push(stek2.top()->dohvVektor()[i - 1]);
				}
			}
			stek2.pop();
		}
	}
	Pitanje* pretragaNajviseOcene() {
		Pitanje* pitanjaSaNajvisomOcenom=pokPitanje[0];//da ne bi dolazilo do greske memroija ovog pokazivaca mozda nije inicijalizovana
		int najvisaOcena = 0;
		for (int i = 0; i < pokPitanje.size(); i++) {
			Pitanje* root = pokPitanje[i];
			stack <Odgovor*> stek;
			int najvisaSt1 = 0;
			if (root->dohvBroj() == 0) {
				cout << "ne postoji zadati komentar/odgovor";
				return nullptr;
			}
			for (int j = root->dohvBroj(); j > 0; j--) {
				stek.push(root->vektor()[j - 1]);//na stek stavlja sa najvise pozicije element(najdesniji prvo pa onda ove levlje)
			}

			while (!stek.empty()) {
				Odgovor* next = stek.top();
				stek.pop();
				if (next->dohvOcenu() > najvisaSt1) {
					najvisaSt1 = next->dohvOcenu();
					
					if (next->dohvOcenu() > najvisaOcena) {
						
						pitanjaSaNajvisomOcenom=pokPitanje[i];
						najvisaOcena = next->dohvOcenu();
					}
					
				}	
				if (next->dohvVelicinuVektora() != 0) {
					for (int j = next->dohvVelicinuVektora(); j > 0; j--) {
						stek.push(next->dohvVektor()[j - 1]);
					}
				}
				
			}
		}
		return pitanjaSaNajvisomOcenom;
	}
	

	void uredi() {
		stack <Odgovor*> stek;
		stack<Odgovor*>stek2;
		if (pokPitanje.size()== 0) {
			cout << "ne postoje Pitanja";
			return;
		}
		
		for (int i = 0; i < pokPitanje.size();i++) {
			Pitanje* root = pokPitanje[i];
			if (root->vektor().size() > 0) {
				for (int i = 0; i < root->vektor().size() - 1; i++)
					for (int j = i + 1; j < root->vektor().size(); j++)
						if (root->vektor()[i]->dohvOcenu() < root->vektor()[j]->dohvOcenu()) {
							stek2.push(root->vektor()[i]);
							root->vektor()[i] = root->vektor()[j];
							root->vektor()[j] = stek2.top();
							stek2.pop();
						}//sortirani odgovori na nivou 1
			}
			
			
			for (int i = root->dohvBroj(); i > 0; i--) {
				stek.push(root->vektor()[i - 1]);//na stek stavlja sa najvise pozicije element(najdesniji prvo pa onda ove levlje)
			}

			while (!stek.empty()) {
				//Odgovor next1=stek.top();
				Odgovor* next = stek.top();

				if (next->dohvVektor().size() > 0) {
					for (int i = 0; i < next->dohvVektor().size() - 1; i++) {
						for (int j = i + 1; j < next->dohvVektor().size(); j++) {
							cout << next->dohvVektor().size();
							if (next->dohvVektor()[i]->dohvOcenu() < next->dohvVektor()[j]->dohvOcenu()) {
								stek2.push(root->vektor()[i]);
								next->dohvVektor()[i] = next->dohvVektor()[j];
								next->dohvVektor()[j] = stek2.top();
								stek2.pop();
							}//P(next) sortirano za sinove cvora koji se obradjuje
						}
					}
				}

				stek2.push(stek.top());
				stek.pop();
				if (stek2.top()->dohvVelicinuVektora() != 0) {
					for (int i = stek2.top()->dohvVelicinuVektora(); i > 0; i--) {
						stek.push(stek2.top()->dohvVektor()[i - 1]);
					}
				}
				stek2.pop();
			}
		}
	}

	void obrisiPitanje(string& s) {
		if (pokPitanje.size() > 0) {
			for (int i = 0; i < pokPitanje.size(); i++) {
				if (pokPitanje[i]->dohvPitanje() == s) {
					if (pokPitanje.size() > 1) {
						for (int j = i; j < pokPitanje.size()-1; j++)pokPitanje[j] = pokPitanje[j + 1];
						pokPitanje.resize(pokPitanje.size() - 1);
					}
					else {
						pokPitanje.clear();
					}
					return;
				}
			}
		}
		else {
			cout << "Ne postoji ni jedno pitanje";
		}

	}

	void ispisPitanjaiOdgovora(string&pitanje) {
		Pitanje* root = pretragaPitanja(pitanje);
		stack <Odgovor*> stek;
		stack<Odgovor*>stek2;
		root->ispis();
		if (root->dohvBroj() == 0) {
			return;
		}
		for (int i = root->dohvBroj(); i > 0; i--) {
			stek.push(root->vektor()[i - 1]);//na stek stavlja sa najvise pozicije element(najdesniji prvo pa onda ove levlje)
		}

		while (!stek.empty()) {
			//Odgovor next1=stek.top();
			Odgovor* next = stek.top();

			next->ispis();//P(next)
			stek2.push(stek.top());
			stek.pop();

			if (stek2.top()->dohvVelicinuVektora() != 0) {
				for (int i = stek2.top()->dohvVelicinuVektora(); i > 0; i--) {
					stek.push(stek2.top()->dohvVektor()[i - 1]);
				}
			}
			stek2.pop();
		}

	}
	
	

	void obrisiOdgovor(string& pitanje, string& odgovor) {
		Pitanje* p = pretragaPitanja(pitanje);
		stack<Odgovor*>stek;
		for (int i = p->dohvBroj(); i > 0; i--) {
			if (p->vektor()[i - 1]->dohvPitanje() == odgovor) {
				Odgovor *r= p->vektor()[i-1];
				
				if (p->vektor().size() > 1 ) {//ukoliko ima samo jednog sina pitanje
					for (int j = i - 1; j < p->vektor().size() - 1; j++) {
						p->vektor()[j] = p->vektor()[j + 1];
					}
					p->vektor().resize(p->vektor().size() - 1);//slucaj ako je otac ustvari pitanje
				}
				else {
					p->vektor().clear();
				}
				delete r;
				return;
			}			
			stek.push(p->vektor()[i-1]);
		}
		
		while (!stek.empty()) {
			Odgovor* next = stek.top();
			stek.pop();
			for (int i = next->dohvVektor().size(); i > 0; i--) {
				if (next->dohvVektor()[i-1]->dohvPitanje() == odgovor) {
					Odgovor* r = next->dohvVektor()[i-1];
					if (next->dohvVektor().size() > 1) {//ukoliko ima samo jednog sina odgovor
						for (int j = i - 1; j < next->dohvVelicinuVektora(); j++) {
							next->dohvVektor()[j] = next->dohvVektor()[j + 1];
						}
						next->dohvVektor().resize(next->dohvVelicinuVektora() - 1);
					}
					else {
						next->dohvVektor().clear();
					}
					
					delete r;
					return;
				}
				stek.push(next->dohvVektor()[i - 1]);
			}
		}
	}
};

int main()
{
	bool flag = true;
	proizvoljnoPitanja struktura;
	while (flag) {
		cout << "Izaberite jednu od opcija:" << endl << "1-Dodavanje novog pitanja" << endl << "2-Dodavanje odgovora na pitanje" << endl;
		cout << "3-Dodavanje odgovora na odgovor" << endl;
		cout << "4-Pretraga pitanja, unesite tekst pitanja" << endl << "5-pretraga odgovora, unesite tekst pitanja i odgovora" <<endl<< "6-pretraga pitanja ciji odgovor ili komentar imaju najvisu ocenu" << endl;
		cout << "7-inkrementiranje odredjenog odgovora" << endl<<"8-uredi sve cvorove tako da se sortiraju tj prednost imaju oni sa visom ocenom"<<endl;
		cout << "9-ispis svih pitanja" << endl << "10-ispis pitanja i njemu pridruzenih odgovora i komentara" << endl;
		cout << "11-Brisanje odgovora i svih njegovih potomaka" << endl;
		cout << "12-Brisanje pitanja i svih povezanih odgovora" << endl<<"Za izlaz izaberite bilo koji broj a da nije 1-12"<<endl;
		int izbor;
		cin >> izbor;
		cin.ignore();
		switch (izbor)
		{
		case 1: {
			cout << "Napisite tekst vaseg pitanja:";
			string s;
			//cin.ignore();
			getline(cin, s);
			struktura.dodajPitanje(*new Pitanje(s));
		}
			break;
		
		case 2: {
			cout << "Napisite pitanje na koje zelite da odgovorite:" << endl;
			//cin.ignore();
			string s;
			getline(cin, s);
			Pitanje* p=struktura.pretragaPitanja(s);
			
			cout << "Napisite odgovor" << endl;
			//cin.ignore();
			getline(cin, s);
			cout << "Napisite koju ocenu dajete odgovoru" << endl;
			int k;
			cin >> k;
			cin.ignore();
			p->dodajOdgovor(*new Odgovor(s),k);
			
			
		}
			break;
		
		case 3: {//prvo pitanje pa odgovor
			cout << "Napisite na koji odgovor zelite da odgovorite, prvo upisete pitanje"<<endl;
			//cin.ignore();
			string s;
			getline(cin, s);
			
			cout << "A sada odgovor" << endl;
			string s1;
			//cin.ignore();
			getline(cin, s1);
			
			
			
			cout << "Napisite odgovor na odgovor" << endl;
			string s2;
			//cin.ignore();
			getline(cin, s2);
			cout << "Napisite ocenu" << endl;
			int k;
			cin >> k;
			cin.ignore();
			struktura.pretragaOdgovoraiUbacivanje(s, s1, s2, k);
			//struktura.pretragaOdgovora(s, s1)->dodajKomentar(*new Odgovor(s2), k);
		}
			break;
		
		case 4: {
			cout << "Napisite koje pitanje zelite da pretrazite" << endl;
			//cin.ignore();
			string s;
			getline(cin, s);

			struktura.pretragaPitanja(s)->ispis();
		}
			break;
		
		case 5: {
			cout << "Napisite koje pitanje zelite da pretrazite" << endl;
			//cin.ignore();
			string s;
			getline(cin, s);
			
			cout << "Napisite koji odgovor zelite da pretrazite" << endl;
			//cin.ignore();
			string s1;
			getline(cin, s1);
			
			struktura.pretragaOdgovora(s, s1)->ispis();
		}
			break;
		case 6: {
			cout << "Pitanje sa odgovorom ili komentarom sa najvisom ocenom je:" << endl;
			struktura.pretragaNajviseOcene()->ispis();
		}
			  break;
		
		case 7: {
			cout << "Napisite na kojem pitanju je odgovor" << endl;
			//cin.ignore();
			string s;
			getline(cin, s);

			cout << "Napisite koji odgovor zelite da inkrementirate" << endl;
			//cin.ignore();
			string s1;
			getline(cin, s1);

			struktura.pretragaOdgovora(s, s1)->inkrementiraj();
			struktura.pretragaOdgovora(s, s1)->ispis();
		}
			break;
		
		case 8: {
			struktura.uredi();
			cout << pocetni;
		}
			break;
		case 9: {
			struktura.ispis();
		}
			  break;

		case 10: {
			cout << "Unesite koje pitanje i njegove odgovore i komentare zelite da se ispisu" << endl;
			//cin.ignore();
			string s;
			getline(cin, s);
			struktura.ispisPitanjaiOdgovora(s);
		}
			   break;
		case 11: {
			cout << "Unesite pitanje iz kog biste odgovor" << endl;
			//cin.ignore();
			string s;
			getline(cin, s);

			cout << "Unesite odgovor" << endl;
			//cin.ignore();
			string s1;
			getline(cin, s1);

			struktura.obrisiOdgovor(s,s1);
		}
			   break;
		case 12: {
			cout << "Upisite pitanje koje zelite da izbacite:" << endl;
			string s;
			getline(cin, s);

			struktura.obrisiPitanje(s);
		}
			   break;
		default:flag = false;
			break;
		}
	}
	//struktura.ispis();
}

