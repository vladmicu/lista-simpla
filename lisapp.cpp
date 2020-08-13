#include<iostream>
#include<string>

#include"lissim.h"

using namespace std;

void quick_sort(int pos1, int pos2, Lista<int> &l){
	PosPoint<int> piv, prim, sec, fin;
	
	if(pos2 - pos1 == 1){
		if(l.get_elem(pos1) > l.get_elem(pos2)){
			l.swap(pos1,pos2);
		}
		return;
	}
	if(pos2 <= pos1){
		return;
	}
		 
	piv.set(&l ,(pos1 + pos2)/2);
	sec.copy(piv.get_next());
	prim.set(&l,pos1);
	fin.set(&l,pos2);
	
	while(!prim.is(piv)){
	
		if(prim.get_elem() > piv.get_elem()){
			prim.move_after(piv);
		}
		
		prim.next();
	}
	
	if(pos1 != 0){
		prim.set(&l,pos1-1);
		while(1){
			if(sec.get_elem() < piv.get_elem()){
				sec.move_after(prim);
			}
			
			if(sec.is(fin)){
				break;
			}
			
			sec.next();	
		}
	}else{
		while(1){
			if(sec.get_elem() < piv.get_elem()){
				sec.move_first();
			}
			
			if(sec.is(fin)){
				break;
			}
			
			sec.next();
		}
	}
	
	quick_sort(pos1, piv.get_pos() - 1, l);
	quick_sort(piv.get_pos() + 1, pos2, l);
}	
int main(){
	Lista<int> l;
	Lista<int> save[5];
	string cmd;
	int nr,pos,pos1,pos2;
	while(1){
		if(cin.fail()){
			cout<<"A avut loc o problema."<<endl;
			return 1;
		}
		cout<<"Comanda:";
		cin>>cmd;
		
	//Comenzi care afiseaza informatii/elemente ale listei
		if(cmd.compare("lung") == 0){
			cout<<"Lungimea listei: "<<l.get_lung()<<endl;
			continue;
		}
		if(cmd.compare("get") == 0){
			cout<<"Pozitie:";
			cin>>pos;
			try{
				nr = l.get_elem(pos);
			}catch(char const *c){
				cout<<c<<endl;
				continue;
			}
			cout<<nr<<endl;
			continue;
		}
		if(cmd.compare("listall") == 0){
			PosPoint<int> it;
			if(l.get_lung() == 0){
				continue;
			}	
			it.set(&l,0);
			for(int i=0;i<l.get_lung();i++){
				cout<<"["<<i<<"]:"<<it.get_elem()<<endl;
				if(it.has_next()){
					it.next();
				}
			}
			continue;
		}
		
	//Comenzi care adauga elemente
		if(cmd.compare("add") == 0){
			cout<<"Numar:";
			cin>>nr;
			l.add_elem(nr);
			continue;
		}
		if(cmd.compare("addpos") == 0){
			cout<<"Numar:";
			cin>>nr;
			cout<<"Pozitie:";
			cin>>pos;
			try{
				l.add_elem(nr,pos);
			}catch(char const *c){
				cout<<c<<endl;
				continue;
			}
			continue;
		}
		
	//Comanda care schimba valoarea unui element
		if(cmd.compare("change") == 0){
			cout<<"Pozitie:";
			cin>>pos;
			cout<<"Nr. nou:";
			cin>>nr;
			try{
				l.change_val(pos,nr);
			}catch(char const *c){
				cout<<c<<endl;
				continue;
			}
			continue;
		}
		
	//Comenzi care muta elemente
		if(cmd.compare("swap") == 0){
			cout<<"Pozitie 1:";
			cin>>pos1;
			cout<<"Pozitie 2:";
			cin>>pos2;
			try{
				l.swap(pos1,pos2);
			}catch(char const *c){
				cout<<c<<endl;
				continue;
			}
			continue;
		}
		if(cmd.compare("move") == 0){
			cout<<"Pozitie sursa:";
			cin>>pos1;
			cout<<"Pozitie destinatie:";
			cin>>pos2;
			try{
				l.move(pos1,pos2);
			}catch(char const *c){
				cout<<c<<endl;
				continue;
			}
			continue;
		}
		
	//Comenzi care sterg elemente	
		if(cmd.compare("delpos") == 0){
			cout<<"Pozitie:";
			cin>>pos;
			try{
				l.del_elem(pos);
			}catch(char const *c){
				cout<<c<<endl;
				continue;
			}
			continue;
		}
		if(cmd.compare("delafter") == 0){
			cout<<"Pozitie:";
			cin>>pos;
			try{
				l.del_after(pos);
			}catch(char const *c){
				cout<<c<<endl;
				continue;
			}
			continue;
		}
		if(cmd.compare("reset") == 0){
			l.del_all();
			continue;
		}
		
	//Comenzi care stocheaza si incarca lista folosind vectorul save
		if(cmd.compare("save") == 0){
			cout<<"Pozitie[0-4]:";
			cin>>pos;
			save[pos].copy(l);
			continue;
		}
		if(cmd.compare("load") == 0){
			cout<<"Pozitie[0-4]:";
			cin>>pos;
			l.copy(save[pos]);
			continue;
		}
	
	//Comanda care sorteaza lista
		if(cmd.compare("sort") == 0){
			
			try{
				quick_sort(0, l.get_lung()-1, l);
			}catch(char const *c){
				cout<<c<<endl;
				continue;
			}
			continue;
		}
			
	
	//Comanda de iesire
		if(cmd.compare("exit") == 0){
			break;
		}
		
		cout<<"Comanda nu a fost recunoscuta."<<endl;
	}
	return 0;
}
