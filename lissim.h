template<class T>
class Lista;

template<class T>
class PosPoint;


template<class T>
class nod{
	friend class Lista<T>;
	friend class PosPoint<T>;
	T elem;
	nod *next;
};

template<class T>
class PosPoint{
	Lista<T> *list;	//Pointer catre lista din care face parte nodul
	nod<T> *nod_curent;	//Pointer catre nodul cu care se lucreaza
	nod<T> *nod_urm;	//Pointer catre urmatorul element (pentru iteratii)
	public:
		//Functii pentru initializare
		void set(Lista<T> *l,int pos){
			list = l;
			nod_curent = l->get_point(pos);
			nod_urm = nod_curent->next;
		}
		void copy(PosPoint<T> p){
			list = p.list;
			nod_curent = p.nod_curent;
			nod_urm = p.nod_urm;
		}
		//Functii utile pentru iteratie
		bool has_next(){
			return nod_urm != NULL;
		}
		PosPoint<T> get_next(){
			PosPoint p;
			p.list = list;
			p.nod_curent = nod_urm;
			p.nod_urm = p.nod_curent->next;
			return p;
		}
		void next(){
			nod_curent = nod_urm;
			nod_urm = nod_curent->next;
		}
		bool is(PosPoint p){
			return nod_curent == p.nod_curent;
		}
		//Functii pentru citirea si schimbarea elementului curent
		T get_elem(){
			return nod_curent->elem;
		}
		void ch_elem(T elem){
			nod_curent->elem = elem;
		}
		//Functii pentru stergerea sau mutarea elementului curent
		void del_elem(){
			nod<T> *prev;
			if(nod_curent == list->cap){
				list->cap = nod_curent->next;
			}else{	
				prev = list->get_prev(nod_curent);
				prev->next = nod_curent->next;
			}
			list->lungime--;
			delete nod_curent;
			
		}
		void move_after(PosPoint<T> target){
			nod<T> *prev;
			
			if(is(target)){
				//Nu putem muta nodul dupa el insusi
				return;
			}
			
			if(nod_curent == list->cap){
				list->cap = nod_curent->next;
			}else{	
				prev = list->get_prev(nod_curent);
				prev->next = nod_curent->next;
			}
			
			nod_curent->next = target.nod_curent->next;
			target.nod_curent->next = nod_curent;
			
			if(list != target.list){
				list->lungime--;
				target.list->lungime++;
				list = target.list;
				//Nu se mai poate itera in lista initiala daca nodul a fost mutat in alta lista
				//Daca se doreste acest lucru se poate folosi get_next() inainte de aceasta functie
				nod_urm = nod_curent->next;
			}
		}
		void move_first(){
			nod<T> *prev;
			if(nod_curent == list->cap){
				return;
			}
				
			prev = list->get_prev(nod_curent);
			prev->next = nod_curent->next;
			
			nod_curent->next = list->cap;
			list->cap = nod_curent;
		}
		//Functie care returneaza pozitia in lista a nodului curent
		int get_pos(){
			nod<T> *elemp = list->cap;
			int i = 0;
			while(elemp != nod_curent){
				i++;
				elemp = elemp->next;
			}
			return i;
		}						
};	
		
				

template<class T>
class Lista{
	friend class PosPoint<T>;
	nod<T> *cap;
	int lungime;
	
	public:
	//Constructor
		Lista<T>(){
			cap = NULL;
			lungime = 0;
		}
		
	//Functii care returneaza informatii, elemente, pointeri
		//Lungimea listei	
		int get_lung(){
			return lungime;
		}
		//Pointer catre nodul aflat la pos spatii dupa elemp
		nod<T>* get_point(nod<T> *elemp,int pos){
			int i = 0;
			if(pos >= lungime || pos < 0 || lungime == 0){
				throw "Pozitie invalida";
			}
			if(pos == 0){
				return elemp;
			}
			while(i<pos-1){
				elemp = elemp->next;
				i++;
				if(elemp->next == NULL){
					throw "Pozitie invalida";
				}
			}
			return elemp->next;
		}
		//Pointer catre nodul de la positia pos
		nod<T>* get_point(int pos){
			return get_point(cap,pos);
		}
		//Valoarea elementului de la positia pos
		T get_elem(int pos){
			nod<T> *elemp;
			elemp = get_point(pos);
			return elemp->elem;
		}
		//Pointer catre nodul precedent lui elemp
		nod<T>* get_prev(nod<T> *elemp){
			nod<T> *p = cap;
			if(cap == NULL || elemp == NULL){
				throw "Element inexistent";
			}
			if(cap == elemp){
				//Daca nu exista element precedent se returneaza NULL
				return NULL;
			}
			while(p->next != elemp){
				if(p->next == NULL){
					//Am ajuns la capatul listei si nu am gasit nodul elemp
					throw "Element inexistent";
				}
				p = p->next;
			}
			return p;
		}		
		

	//Functii care adauga elemente
		//Adauga un element dupa nodul elemp
		void add_elem(T elem, nod<T> *elemp){
			nod<T> *aux;
			aux = elemp->next;
			elemp->next = new nod<T>;
			elemp->next->elem = elem;
			elemp->next->next = aux;
			lungime++;
		}
		//Adauga un element la inceputul listei
		void add_first(T elem){
			nod<T> *aux;
			aux = cap;
			cap = new nod<T>;
			cap->elem = elem;
			cap->next = aux;
			lungime++;
		}
		//Adauga un element la sfarsitul listei
		void add_elem(T elem){
			nod<T> *last;
			if(cap == NULL){
				add_first(elem);
			}else{
				last = get_point(lungime-1);
				add_elem(elem,last);
			}
		}
		//Adauga un element la o anume pozitie
		void add_elem(T elem,int pos){
			nod<T> *elemp;
			if(pos == 0){
				add_first(elem);
			}else{
				elemp = get_point(pos - 1);
				add_elem(elem,elemp);
			}
		}
		
	//Functii care sterg elemente
		//Sterge elementul de dupa elemp
		void del_elem(nod<T> *elemp){
			nod<T> *aux;
			if(elemp->next == NULL){
				return;
			}
			aux = elemp->next->next;
			delete elemp->next;
			elemp->next = aux;
			lungime--;
		}
		//Sterge primul element
		void del_first(){
			nod<T> *aux;
			if(cap == NULL){
				return;
			}
			aux = cap->next;
			delete cap;
			cap = aux;
			lungime--;
		}
		//Sterge elmentul de la pozitia pos
		void del_elem(int pos){
			if(pos == 0){
				del_first();
			}else{	
				nod<T> *elemp;
				elemp = get_point(pos - 1);
				del_elem(elemp);
			}
		}
		//Sterge toate elementele de dupa elemp
		void del_after(nod<T> *elemp){
			nod<T> *aux1,*aux2;
			if(elemp->next != NULL){
				//Sterge elementul urmator
				aux1 = elemp->next;
				aux2 = aux1->next;
				delete aux1;
				lungime--;
				elemp->next = NULL;
				//Sterge restul listei
				while(aux2 != NULL){
					aux1 = aux2;
					aux2 = aux1->next;
					delete aux1;
					lungime--;
				}
			}
		}
		//Sterge toate elementele de dupa pozitia pos
		void del_after(int pos){
			nod<T> *elemp;
			elemp = get_point(pos);
			del_after(elemp);
		}
		//Sterge toate elementele
		void del_all(){
			if(cap != NULL){
				del_after(cap);
				del_first();
			}
		}			
		
	//Functie care schimba valoarea unui element
		void change_val(int pos,T elem){
			nod<T> *elemp = get_point(pos);
			elemp->elem = elem;
		}
	
	//Functii care schimba elemente intre ele
		void swap(nod<T> *p1,nod<T> *p2){
			T aux;
			aux = p1->elem;
			p1->elem = p2->elem;
			p2->elem = aux;
		}		
		void swap(int pos1, int pos2){
			nod<T> *elemp1, *elemp2;
			int pmin,pmax;
			if(pos1 > pos2){
				pmin = pos2;
				pmax = pos1;
			}else{
				pmin = pos1;
				pmax = pos2;
			}
			elemp1 = get_point(pmin);
			elemp2 = get_point(elemp1,pmax-pmin);
			swap(elemp1,elemp2);
		}
	
	//Functii care muta noduri
		//Muta nodul de la pozitia pos la inceput
		void move_first(int pos){
			nod<T> *tomove,*aux;
			if(pos >= lungime){
				throw "Pozitie invalida";
			}
			if(pos != 0){
				aux = get_point(pos - 1);
				tomove = aux->next;
				aux->next = tomove->next;
				tomove->next = cap;
				cap = tomove;
			}
		}
		//Muta nodul de la pozitia pos1 la pozitia pos2	
		void move(int pos1, int pos2){	
			nod<T> *tomove,*target,*aux;
			
			if(pos1 >= lungime | pos1 < 0 | pos2 >= lungime | pos2 < 0){
				throw "Pozitie inexistenta";
			}	
			if(pos1 == pos2){
				return;
			}
			
			if(pos2 == 0){
				move_first(pos1);
			}else{
				//Daca pos2 > pos1 pozitia nodului target scade cu 1 dupa mutare
				if(pos1 > pos2){ 
					target = get_point(pos2 - 1);
				}else{
					target = get_point(pos2);
				}
					
				if(pos1 == 0){
					tomove = cap;
					cap = cap->next;
				}else{
					aux = get_point(pos1 - 1);
					tomove = aux->next;
					aux->next = tomove->next;
			}
			tomove->next = target->next;
			target->next = tomove;
			}
		}			
	//Functii care copiaza alte liste
		//Atasaza o copie a altei liste la sfarsitul listei
		void append(Lista<T> l){
			nod<T> *p = l.cap;

			while(p != NULL){
				add_elem(p->elem);
				p = p->next;
			}
		}
		//Transforma lista intr-o copie a altei liste
		void copy(Lista<T> l){
			del_all();
			append(l);
		}				
};
			
