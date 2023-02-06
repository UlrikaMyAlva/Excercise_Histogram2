#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
//DEKLARATION AV KONSTANTER
const int ANTAL_BOKSTAVER = 26; // A-Z
const int ANTAL_SPRAK = 4;
const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER]=
 {{8.27,1.48,2.94,4.03,11.78,2.22,1.72,6.77, // engelska
 7.39,0.12,0.81,3.76,2.85,6.71,7.79,1.54,
 0.05,5.95,6.69,9.07,2.66,1.13,2.14,0.19,
 1.89,0.03},
 {7.97,1.40,3.55,3.79,16.89,1.02,1.00,0.75, // franska
 7.08,0.38,0.04,5.51,2.82,8.11,5.19,2.78,
 1.01,6.69,8.35,7.22,6.09,1.35,0.02,0.54,
 0.30,0.15},
 {9.50,1.11,1.53,5.30,8.94,1.74,3.57,3.94, // svenska
 3.98,0.89,3.26,4.93,3.41,8.46,5.01,1.77,
 0.00,6.73,5.56,9.20,1.94,2.42,0.00,0.05,
 0.45,0.00},
 {5.12,1.95,3.57,5.07,16.87,1.35,3.00,5.79, // tyska
 8.63,0.19,1.14,3.68,3.12,10.64,1.74,0.42,
 0.01,6.30,6.99,5.19,3.92,0.77,1.79,0.01,
 0.69,1.24}};
//FUNKTIONSDEKLARATION
string namn_pa_fil(); //Kollar om namnet p filen har .txt p slutet, och l gger � � �
annars till det
string inlasning(string filnamn); //L ser in den inskrivna filen. Om filen inte �
existerar st ngs programmet av. �
//KLASSEN TEXT
class Text
{
 //VARIABLER
private:
 string text; //Str ngen som ska analyseras. �
 int absHistogram[ANTAL_BOKSTAVER]; //Det absoluta histogrammet, 26 bokst ver �
l ngt. �
 int antaletBokstaver; //Antalet bokst ver i histogrammet �
 double relHistogram[ANTAL_BOKSTAVER];//Histogram i procent, 26 bokst ver l ngt � �
 //METODER
public:
 Text(); //Konstruktor
 void setText(const string &nyText); //S tter privata variabeln text �
 bool beraknaHistogramAbs(); //Ber knar histogram �
 void skrivHistogramAbs(); // Skriver ut histogram
 void abs_till_rel();//Konverterar de absoluta talen till relativa
 void plottaHistogramRel();//Skapar en tabell d r varje procent representeras av �
tv stj rnor ** � �
 void beraknaHistogram();//anropar funktionerna beraknaHistogramAbs samt
abs_till_rel
 string tolka();
};
int main()
{
 // Deklarera variabler
 string sprak;
 string filnamn;
 string filtext;
 //Variabeln minText av typen Text
 Text minText;
 filnamn = namn_pa_fil(); //Namnet p filen sparas i filnamn. �
 filtext = inlasning(filnamn); //Texten i filen sparas i str ngen filtext. �
Filnamet ovan skickas till metoden inl sning och returnar hela texten. �
 minText.setText(filtext);
 minText.beraknaHistogram();
 minText.skrivHistogramAbs();
 sprak = minText.tolka();
 minText.plottaHistogramRel();
 return 0;
}
// -------------------------------------------------------
//FUNKTIONER
string namn_pa_fil(){
 string filnamn;
 bool exit = true;
 while (exit) {
 cout << "Please enter name of your file: " << endl;
 getline(cin, filnamn);
 string reversed = filnamn;
 string txt = ".txt";
 //filnamet omv nds, sedan kollas om de fyra f rsta elementen r "txt.". Om � � �
txt ej r d r l ggs det till. � � �
 int size = reversed.length();
 int n = size-1;
 for(int i=0; i < (size/2);i++){
 swap(reversed[i],reversed[n]);
 n = n-1;
 }
 if (reversed[0] == 't'&& reversed[1] == 'x' && reversed[2] == 't' &&
reversed[3] == '.') {
 exit = false;
 }
 else{
 filnamn = filnamn + txt;
 exit = false;
 }
 }
 return filnamn;
}
string inlasning(string filnamn) {
 string textFil;
 string fulltext;
 ifstream fil(filnamn);
 if (fil.fail()) {
 cout << "Filen existerar ej, programmet avslutas" << endl;
 exit(0);
 }
 while (getline (fil, textFil)) {
 fulltext += textFil; //Filen l ses in f r varje line � �
 }
 return fulltext;
 //Filen st ngs �
 fil.close();
}
//TILLH R KLASSEN TEXT �
//Konstruktor
Text::Text()
{
 //S tts till tomma n r klassen skapas. � �
 text = "";
 for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
 absHistogram[i] = 0;
 relHistogram[i] = 0;
 }
 antaletBokstaver = 0;
}
//Medlemsfunktioner
void Text::setText(const string &nyText)
{
 text = nyText;
}
bool Text::beraknaHistogramAbs()
{
 int letter = 0;
 //Sm och stora bokst ver sorteras in. Antalet bokst ver r knas. � � � �
 for (int i=0; i< (int) text.length(); i++) {
 int index;
 if (text.at(i)>='a' && text.at(i)<='z'){
 index = text.at(i) - 'a';
 absHistogram[index]++;
 antaletBokstaver++;
 }
 if (text.at(i)>='A' && text.at(i)<='Z'){
 index = text.at(i) - 'A';
 absHistogram[index]++;
 antaletBokstaver++;
 }
 }
 if (antaletBokstaver > 0)
 {
 return true;
 }
 else
 {
 return false;
 }
}
void Text::skrivHistogramAbs()
{
 cout << "\nResultat f\x94r bokst\x84verna A-Z: \n\nTotalt antal bokst\x84ver: "
<< antaletBokstaver << endl; //"\n" << "Bokstavsf\x94rdelning: " << endl;
//Kan tas med om man vill se varje bokstav
// for (int i = 0; i < ANTAL_BOKSTAVER; i++){
// cout << char (i+'A') << ":";
// cout << absHistogram[i] << endl;
// }
}
void Text::abs_till_rel()
{
 for (int i=0; i<ANTAL_BOKSTAVER; i++) {
 char bokstav = char (i+'A');
 relHistogram[i] = double (absHistogram[i]);
 relHistogram[i] = relHistogram[i] / antaletBokstaver * 100; //Beh vde ske i �
tv steg f r att kunna konvertera till double. � �
 //Skriver ut procent, kan tas med om man vill se
 //cout << bokstav << ": " << relHistogram[i] << "%" << endl;
 }
 cout << "\n";
}
void Text::plottaHistogramRel()
{
 cout << "\nTabell" << endl;
 double svar = 0.0;
 for (int i=0; i<ANTAL_BOKSTAVER; i++) {
 char bokstav = char (i+'A');
 cout << "\n" << bokstav << ": ";
 svar = (relHistogram[i] / 0.5) - 0.5; //Avrundas genom -0.5
 for (int j = 0; j < svar; j++){
 cout << "*";
 }
 }
 cout << "\n\n";
}
void Text::beraknaHistogram() {
 bool finnsBokstaver = beraknaHistogramAbs();
 if (finnsBokstaver == 1) {
 abs_till_rel();
 }
}
string Text::tolka() {
 int resultat = 0;
 int minsta = 10000; //H g siffra f r att alltid vara st rre i nedan if sats. � � �
 int sprak;
 double skillnad;
 double sum = 0.0;
 string spraken [] = {"Engelska", "Franska", "Svenska", "Tyska"};
 cout <<"Spr\x86k: \n"<< endl;
 for (int i = 0; i < ANTAL_SPRAK; i++) {
 for (int j=0; j<ANTAL_BOKSTAVER; j++)
 {
 skillnad=TOLK_HJALP[i][j]- relHistogram[j];
 sum = sum + skillnad*skillnad;
 }
 cout << spraken[i] << ": " << sum << endl;
 if (sum < minsta) {
 minsta = sum;
 sprak = i + 1;
 }
 sum = 0;
 }
 switch (sprak) {
 case 1:
 cout << "\nSpr\x86ket \x84r troligtvis Engelska.\n";
 return "Engelska";
 case 2:
 cout << "\nSpr\x86ket \x84r troligtvis Franska.\n";
 return "Franska";
 case 3:
 cout << "\nSpr\x86ket \x84r troligtvis Svenska.\n";
 return "Svenska";
 case 4:
 cout << "\nSpr\x86ket \x84r troligtvis Tyska.\n";
 return "Tyska";
 }
}
//--------------------------------------------------------
// Funktionsdefinitioner:
// ----------------------
