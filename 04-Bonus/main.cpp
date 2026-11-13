#include <iostream>
#include <string>

using namespace std;

class Date{
    private:
        int j;
        int m; 
        int a;
    public:
        Date(): j(1), m(1), a(2000){}
        Date(int j,int m,int a){
            setDate(j);
            setMonth(m);
            setYear(a);
        }
        Date(const Date &d): j(d.j), m(d.m), a(d.a){}
        ~Date(){}

        void setDate(int nj){j = nj;}
        void setMonth(int nm){m = nm;}
        void setYear(int na){a = na;}

        int getDate(){return j;}
        int getMonth(){return m;}
        int getYear(){return a;}

        static string affiche_jj_mm_aaaa(int j, int m, int a){
            string sj = to_string(j);
            string sm = to_string(m);
            string sa = to_string(a);
            return sj+"_"+sm+"_"+sa;
        }
};

class Livre{
    private:
        string auteur;
        string titre;
        Date datePub;
    public:
        Livre(): auteur("Amaury"), titre("Ma vie"), datePub({13,11,2026}){}
        Livre(string auteur, string titre, Date datePub){
            setAuteur(auteur);
            setTitre(titre);
            setDate(datePub);
        }
        Livre(const Livre &l): auteur(l.auteur), titre(l.titre), datePub(l.datePub){}
        ~Livre(){}

        void setAuteur(string na){auteur = na;}
        void setTitre(string nt){titre = nt;}
        void setDate(Date nd){datePub = nd;}

        string getAuteur(){return auteur;}
        string getTitre(){return titre;}
        string getDate(){return datePub.affiche_jj_mm_aaaa(datePub.getDate(), datePub.getMonth(), datePub.getYear());}

        void afficherLivre(){
            cout << getAuteur()+"\n" << getTitre()+"\n" << getDate() <<endl;
        }
};