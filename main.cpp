#include "cbuffer.h"
#include <iostream> // std::cout
#include <stdexcept> // std::out_of_range
#include <cassert> // assert
#include <string>

bool f (int i) {
    if (i == 1) {
        return true;
    }
    return false;
}

struct product {

      int weight;
      double price;

};

int main() {

    product apple;
    apple.weight = 3;
    apple.price = 2.3;

    // Testo i costruttori

        // Testo cbuffer().

	    cbuffer<int> cbuf1();
        cbuffer<std::string> cbuf2();
        cbuffer<product> cbuf3();

        // Testo cbuffer(size_type size).

        // Testo il caso limite in cui size = -1 --> ERRORE
        //cbuffer<int> cbuf4(-1);

        // Testo il caso limite in cui size = 0.
        cbuffer<int> cbuf5(0);
        std::cout << "cbuf5(0) : " << cbuf5 << std::endl;

        // Testo i casi non limite
        cbuffer<int> cbuf6(8);
        std::cout << "cbuf6(8) : " << cbuf6 << std::endl;
        cbuffer<double> cbuf7(4);
        cbuffer<std::string> cbuf8(2);
        cbuffer<product> cbuf9 (20);

        // Testo cbuffer(size_type size, const T &value)

        // Testo il caso limite in cui size = -1 --> ERRORE
        //cbuffer<int> cbuf10 (-1, 6);

        // Testo il caso limite in cui size = 0.
        cbuffer<int> cbuf11(0, 4);
        std::cout << "cbuf11 : " << cbuf11 << std::endl;

        // Testo i casi non limite
        cbuffer<int> cbuf12(8, 2);
        std::cout << "cbuf12(8, 2) : " << cbuf12 << std::endl;
        cbuffer<double> cbuf13(4, 2.1);
        std::cout << "cbuf13(4, 2.1) : " << cbuf13 << std::endl;
        cbuffer<std::string> cbuf14(2, "Foo");
        std::cout << "cbuf14(2, 'Foo') : " << cbuf14 << std::endl;
        cbuffer<product> cbuf15(20, apple);

        // Testo cbuffer(size_type s, Q begin, Q end)

        cbuffer<int> cbuf16 (4);
        std::cout << "cbuf16 (4) : " << cbuf16 << std::endl;
        cbuf16.insert_in_tail(1);
        cbuf16.insert_in_tail(2);
        std::cout << "cbuf16: " << cbuf16 << std::endl;
        std::cout << "*cbuf16.begin(): " << *cbuf16.begin() << std::endl;
        std::cout << "*cbuf16.end(): " << *cbuf16.end() << std::endl; 

        // Testo il caso limite in cui size = -1 --> ERRORE
        //cbuffer<int> cbuf17 (-1, cbuf16.begin(), cbuf16.end());

        cbuffer<int> cbuf18 (2, cbuf16.begin(), cbuf16.end());
        std::cout << "cbuf18 (2, cbuf16.begin(), cbuf16.end()) : " << cbuf18 << std::endl;
        std::cout << "*cbuf18.begin(): " << *cbuf18.begin() << std::endl;
        std::cout << "*cbuf18.end(): " << *cbuf18.end() << std::endl;

        cbuffer<int> cbuf19 (4, cbuf16.begin(), cbuf16.end());
        std::cout << "cbuf19 (4, cbuf16.begin(), cbuf16.end()) : " << cbuf19 << std::endl;
        std::cout << "*cbuf19.begin(): " << *cbuf19.begin() << std::endl;
        std::cout << "*cbuf19.end(): " << *cbuf19.end() << std::endl;

        cbuffer<int> cbuf20 (6, cbuf16.begin(), cbuf16.end());
        std::cout << "cbuf20 (6, cbuf16.begin(), cbuf16.end()) : " << cbuf20 << std::endl;
        std::cout << "*cbuf20.begin(): " << *cbuf20.begin() << std::endl;
        std::cout << "*cbuf20.end(): " << *cbuf20.end() << std::endl;

        // Testo ulteriori casi non limite
        cbuffer<double> cbuf21(3);
        cbuf21.insert_in_tail(2.343);
        cbuf21.insert_in_tail(8.432);
        cbuf21.insert_in_tail(3.212);
        std::cout << "cbuf21 : " << cbuf21 << std::endl;
        std::cout << "*cbuf21.begin() : " <<  *cbuf21.begin() << std::endl;
        std::cout << "*cbuf21.end() : " << *cbuf21.end() << std::endl;
        cbuffer<double> cbuf22(2, cbuf21.begin(), cbuf21.end());
        std::cout << "cbuf22(2, cbuf21.begin(), cbuf21.end()) : " << cbuf22 << std::endl;

        cbuffer<double> cbuf23(3, cbuf21.begin(), cbuf21.end());
        std::cout << "cbuf23(3, cbuf21.begin(), cbuf21.end()) : " << cbuf23 << std::endl;

        cbuffer<double> cbuf24(4, cbuf21.begin(), cbuf21.end());
        std::cout << "cbuf24(4, cbuf21.begin(), cbuf21.end()) : " << cbuf24 << std::endl;

        cbuffer<std::string> cbuf25(3);
        cbuf25.insert_in_tail("Foo");
        cbuf25.insert_in_tail("Bar");
        cbuf25.insert_in_tail("Pluto");
        std::cout << "cbuf25 : " << cbuf25 << std::endl;
        std::cout << "*cbuf25.begin() : " << *cbuf25.begin() << std::endl;
        std::cout << "*cbuf25.end() : " << *cbuf25.end() << std::endl;
        cbuffer<std::string> cbuf26(2, cbuf25.begin(), cbuf25.end());
        std::cout << "cbuf26(2, cbuf25.begin(), cbuf25.end()) : " << cbuf26 << std::endl;
        cbuffer<std::string> cbuf27(3, cbuf25.begin(), cbuf25.end());
        std::cout << "cbuf27(3, cbuf25.begin(), cbuf25.end()) : " << cbuf27 << std::endl;
        cbuffer<std::string> cbuf28(4, cbuf25.begin(), cbuf25.end());
        std::cout << "cbuf28(4, cbuf25.begin(), cbuf25.end()) : " << cbuf28 << std::endl;

        // Testo cbuffer(const cbuffer &other)

        // Testo un primo caso limite : provo ad creare un nuovo cbuffer passandogli un cbuffer i cui elementi hanno tipo diverso e non convertibile --> ERRORE
        /*cbuffer<int> cbuf29 (4, 5);
        std::cout << "cbuf29 (4, 5) : " << cbuf29 << std::endl;
        cbuffer<std::string> cbuf30(cbuf29);*/

        // Testo i casi non limite
        cbuffer<int> cbuf30 (4, 5);
        std::cout << "cbuf30 (4, 5) : " << cbuf30 << std::endl;
        cbuffer<int> cbuf31(cbuf30);
        std::cout << "cbuf31(cbuf30) : " << cbuf31 << std::endl;

        cbuffer<std::string> cbuf32 (4, "Foo");
        std::cout << "cbuf32 (4, 'Foo') : " << cbuf32 << std::endl;
        cbuffer<std::string> cbuf33 (cbuf32);
        std::cout << "cbuf33 (cbuf32) : " << cbuf33 << std::endl;

        product milk;
        milk.weight = 3.14;
        milk.price = 1.1;
        cbuffer<product> cbuf34 (0, milk);
        cbuffer<product> cbuf35 (cbuf34);

        // Testo &operator= (const cbuffer &other)

        //Testo un primo caso limite: eguaglio due cbuffer di tipo diverso --> ERRORE
        /*cbuffer<int> cbuf36 (6, 8);
        std::cout << "cbuf36 (6, 8) : " << cbuf36 << std::endl;
        cbuffer<double> cbuf37 = cbuf36;
        std::cout << "cbuf37 : " << cbuf37 << std::endl;*/

        cbuffer<int> cbuf38 (6, 8);
        std::cout << "cbuf38 (6, 8) : " << cbuf38 << std::endl;
        cbuffer<int> cbuf39 = cbuf38;
        std::cout << "cbuf39 : " << cbuf39 << std::endl;

        // Testo get_size(), size(), o_size()

        //Testo un primo caso limite
        cbuffer<int> cbuf40 (0, 8);
        std::cout << "cbuf40 (0, 8) : " << cbuf40 << std::endl;
        std::cout << "cbuf40.get_size() : " << cbuf40.get_size() << std::endl;
        std::cout << "cbuf40.size() : " << cbuf40.size() << std::endl;
         std::cout << "cbuf40.o_size() : " << cbuf40.o_size() << std::endl;

        cbuffer<int> cbuf41 (6, 8);
        std::cout << "cbuf41 (6, 8) : " << cbuf41 << std::endl;
        std::cout << "cbuf41.get_size() : " << cbuf41.get_size() << std::endl;
        std::cout << "cbuf41.size() : " << cbuf41.size() << std::endl;
        std::cout << "cbuf41.o_size() : " << cbuf41.o_size() << std::endl;

        cbuffer<int> cbuf42 (6);
        std::cout << "cbuf42(6) : " << cbuf42 << std::endl;
        std::cout << "cbuf42.get_size () : " << cbuf42.get_size() << std::endl;
        std::cout << "cbuf42.size() : " << cbuf42.size() << std::endl;
        std::cout << "cbuf42.o_size() : " << cbuf42.o_size() << std::endl;

        // Testo .head(), .tail(), *.begin(), *.end()

        /*cbuffer<int> cbuffer(3);
        cbuffer[0] = 1;
        cbuffer[1] = 2;
        cbuffer[2] = 3;
        cbuffer[4] = 6;

        std::cout << "cbuffer.head() : " << cbuffer.head() << std::endl;
        std::cout << "cbuffer.tail() : " << cbuffer.tail() << std::endl;
        std::cout << "*cbuffer.begin() :"<< *cbuffer.begin() << std::endl;
        std::cout<< "*cbuffer.end() : " << *cbuffer.end() << std::endl;*/

        cbuffer<int> cbuffer1(3);
        cbuffer1.insert_in_tail(1);
        cbuffer1.insert_in_tail(2);
        cbuffer1.insert_in_tail(3);
        cbuffer1.insert_in_tail(4);

        std::cout << "cbuffer1 after many insertions in tail : " << cbuffer1 << std::endl;
        std::cout << "cbuffer1.head() : " << cbuffer1.head() << std::endl;
        std::cout << "cbuffer1.tail() : " << cbuffer1.tail() << std::endl;
        std::cout << "*cbuffer1.begin() :"<< *cbuffer1.begin() << std::endl;
        std::cout<< "*cbuffer1.end() : " << *cbuffer1.end() << std::endl;

        cbuffer<int> cbuffer2(3);
        cbuffer2[2] = 5;
        cbuffer2[0] = 6;
        cbuffer2[1] = 7; 
        cbuffer2[3] = 4;


        std::cout << "cbuffer2 after many insertions in tail : " << cbuffer2 << std::endl;
        std::cout << "cbuffer2.o_size() : " << cbuffer2.o_size() << std::endl;
        std::cout << "cbuffer2.head() : " << cbuffer2.head() << std::endl;
        std::cout << "cbuffer2.tail() : " << cbuffer2.tail() << std::endl;
        std::cout << "*cbuffer2.begin() :"<< *cbuffer2.begin() << std::endl;
        std::cout<< "*cbuffer2.end() : " << *cbuffer2.end() << std::endl;

        cbuffer<int> cbuffer3(8);
        cbuffer3[3] = 1;
        cbuffer3[6] = 2;
        cbuffer3[1] = 3;
        cbuffer3[0] = 4;
        cbuffer3[5] = 5;
        cbuffer3[2] = 6;
        cbuffer3[7] = 7;
        cbuffer3[4] = 8;
        cbuffer3[8] = 9;

        std::cout << "cbuffer3 after many insertions in tail : " << cbuffer3 << std::endl;
        std::cout << "cbuffer3.o_size() : " << cbuffer3.o_size() << std::endl;
        std::cout << "cbuffer3.head() : " << cbuffer3.head() << std::endl;
        std::cout << "cbuffer3.tail() : " << cbuffer3.tail() << std::endl;
        std::cout << "*cbuffer3.begin() :"<< *cbuffer3.begin() << std::endl;
        std::cout<< "*cbuffer3.end() : " << *cbuffer3.end() << std::endl;

        // Testo il metodo remove.head().

        // Testo il caso limite in cui creo un nuovo buffer circolare di quattro elementi inizialmente vuoto e rimuovo la head --> ERRORE
        /*cbuffer<int> cbuffer4(4);
        std::cout << "cbuffer4(4) : " << cbuffer4 << std::endl;
        std::cout << "cbuffer4.head() : " << cbuffer4.head() << std::endl;
        std::cout << "cbuffer4.tail() : " << cbuffer4.tail() << std::endl;
        std::cout << "cbuffer4.remove_head() : " << cbuffer4.remove_head() << std::endl;
        std::cout << "cbuffer4 after head removing : " << cbuffer4 << std::endl;*/

        // Testo casi non limite
        cbuffer<std::string> cbuffer5(5);
        cbuffer5.insert_in_tail("Foo");
        cbuffer5.insert_in_tail("Bar");
        cbuffer5.insert_in_tail("Pluto");
        cbuffer5.insert_in_tail("Pippo");
        cbuffer5.insert_in_tail("Paperino");

        std::cout << "cbuffer5(3) : " << cbuffer5 << std::endl;
        std::cout << "cbuffer5.head() : " << cbuffer5.head() << std::endl;
        std::cout << "cbuffer5.tail() : " << cbuffer5.tail() << std::endl;
        std::cout << "*cbuffer5.begin() : " << *cbuffer5.begin() << std::endl;
        std::cout << "*cbuffer5.end() : " << *cbuffer5.end() << std::endl;
        cbuffer5.remove_head();
        std::cout << "cbuffer5.head() after head removing : " << cbuffer5.head() << std::endl;
        std::cout << "cbuffer5.tail() after head removing : " << cbuffer5.tail() << std::endl;
        std::cout << "*cbuffer5.begin() after head removing : " << *cbuffer5.begin() << std::endl;
        std::cout << "*cbuffer5.end() after head removing : " << *cbuffer5.end() << std::endl;
        cbuffer5.remove_head();
        std::cout << "cbuffer5.head() after a second head removing : " << cbuffer5.head() << std::endl;
        std::cout << "cbuffer5.tail() after a second head removing : " << cbuffer5.tail() << std::endl;
        std::cout << "*cbuffer5.begin() after a second head removing : " << *cbuffer5.begin() << std::endl;
        std::cout << "*cbuffer5.end() after a second head removing : " << *cbuffer5.end() << std::endl;

        // Testo empty() e full()

        // Testo i casi limite
        cbuffer<double> cbuffer6(0);
        std::cout << "cbuffer6(0) : " << cbuffer6 << std::endl;
        std::cout << "cbuffer6.empty() : " << cbuffer6.empty() << std::endl;
        std::cout << "cbuffer6.full() : " << cbuffer6.full() << std::endl;

        /*cbuffer<std::string> cbuffer7();
        std::cout << "cbuffer7() : " << cbuffer7 << std::endl;
        std::cout << "cbuffer7.empty() : " << cbuffer7.empty() << std::endl;
        std::cout << "cbuffer7.full() : " << cbuffer7.full() << std::endl; --> ERRORE */

        // Testo i casi non limite
        cbuffer<int> cbuffer8(4);
        std::cout << "cbuffer8(4) : " << cbuffer8 << std::endl;
        std::cout << "cbuffer8.empty() : " << cbuffer8.empty() << std::endl;
        std::cout << "cbuffer8.full() : " << cbuffer8.full() << std::endl;
        cbuffer8.insert_in_tail(1);
        cbuffer8.insert_in_tail(2);
        cbuffer8.insert_in_tail(3);
        cbuffer8.insert_in_tail(4);
        std::cout << "cbuffer8 after many insert_in_tail : " << cbuffer8 << std::endl;
        std::cout << "cbuffer8.empty() : " << cbuffer8.empty() << std::endl;
        std::cout << "cbuffer8.full() : " << cbuffer8.full() << std::endl;
        cbuffer8.remove_head();
        cbuffer8.remove_head();
        std::cout << "cbuffer8.empty() after have removed two elements : " << cbuffer8.empty() << std::endl;
        std::cout << "cbuffer8.full() after have removed two elements : " << cbuffer8.full() << std::endl;
        cbuffer8.remove_head();
        cbuffer8.remove_head();
        std::cout << "cbuffer8.empty() after have removed other two elements : " << cbuffer8.empty() << std::endl;
        std::cout << "cbuffer8.full() after have removed other two elements : " << cbuffer8.full() << std::endl;
        cbuffer8[3];
        std::cout << "cbuffer8.empty() : " << cbuffer8.empty() << std::endl;
        std::cout << "cbuffer8.full() : " << cbuffer8.full() << std::endl;
        cbuffer8[2];
        std::cout << "cbuffer8.empty() : " << cbuffer8.empty() << std::endl;
        std::cout << "cbuffer8.full() : " << cbuffer8.full() << std::endl;
        cbuffer8[1];
        cbuffer8[0];
        std::cout << "cbuffer8.empty() : " << cbuffer8.empty() << std::endl;
        std::cout << "cbuffer8.full() : " << cbuffer8.full() << std::endl;

        // Testo get_value(), set_value(), value(), const value()

        // Testo il caso limite per cui la dimensione del buffer circolare istanziato sia pari a 0 --> ERRORE
        /*cbuffer<std::string> cbuffer9 (0); 
        std::cout << "cbuffer9 (0) : " << cbuffer9 << std::endl;
        std::cout << "cbuffer9.get_value(0) : " << cbuffer9.get_value(0) << std::endl;*/

        // Testo casi non limite
        cbuffer<std::string> cbuffer10(4);
        cbuffer10.insert_in_tail("Foo");
        cbuffer10.insert_in_tail("Bar");
        cbuffer10.insert_in_tail("Pippo");
        cbuffer10.insert_in_tail("Pluto");
        std::cout << "cbuffer10(4) after many insertions in tail : " << cbuffer10 << std::endl;
        std::cout << "cbuffer10.empty() : " << cbuffer10.empty() << std::endl;
        std::cout << "cbuffer10.full() : " << cbuffer10.full() << std::endl;
        std::cout << "cbuffer10.head() : " << cbuffer10.head() << std::endl;
        std::cout << "cbuffer10.tail() : " << cbuffer10.tail() << std::endl;
        std::cout << "*cbuffer10.begin() : " << *cbuffer10.begin() << std::endl;
        std::cout << "*cbuffer10.end() : " << *cbuffer10.end() << std::endl;
        std::cout << "cbuffer10.get_value(-1) : " << cbuffer10.get_value(-1) << std::endl;
        std::cout << "cbuffer10.value(5) : " << cbuffer10.value(5) << std::endl;
        std::cout << "cbuffer10.head() : " << cbuffer10.head() << std::endl;
        std::cout << "cbuffer10.tail() : " << cbuffer10.tail() << std::endl;
        std::cout << "*cbuffer10.begin() : " << *cbuffer10.begin() << std::endl;
        std::cout << "*cbuffer10.end() : " << *cbuffer10.end() << std::endl;
        cbuffer10.set_value(8, "Paperino");
        std::cout << "cbuffer10 after cbuffer10.set_value(2, true) : " << cbuffer10 << std::endl;
        std::cout << "cbuffer10.head() : " << cbuffer10.head() << std::endl;
        std::cout << "cbuffer10.tail() : " << cbuffer10.tail() << std::endl;
        std::cout << "*cbuffer10.begin() : " << *cbuffer10.begin() << std::endl;
        std::cout << "*cbuffer10.end() : " << *cbuffer10.end() << std::endl;
        cbuffer10.value(8) = "Topolino";
        std::cout << "cbuffer10 after cbuffer10.value(8) = 'Topolino' : " << cbuffer10 << std::endl;
        std::cout << "cbuffer10.head() : " << cbuffer10.head() << std::endl;
        std::cout << "cbuffer10.tail() : " << cbuffer10.tail() << std::endl;
        std::cout << "*cbuffer10.begin() : " << *cbuffer10.begin() << std::endl;
        std::cout << "*cbuffer10.end() : " << *cbuffer10.end() << std::endl;


        // Testo l'operatore [] in lettura (scrittura precedentemente testata)

        //Testo il caso limite per cui l'array è nullo e tento di accedere in scrittura e in lettura ad un suo elemento --> ERRORE
        /*cbuffer<int> cb(0);
        std::cout << "cb(0) : " << cb << std::endl;
        std::cout << "cb[1] : " << cb[1] << std::endl;
        cb[1] = 2;
        std::cout << "cb after cb[1] = 2 : " << cb << std::endl;*/

        // Testo il caso limite per cui l'array non è nullo ma si passa un indice negativo (fase lettura).
        cbuffer<int> cb1(4);
        cb1.insert_in_tail(1);
        cb1.insert_in_tail(2);
        cb1.insert_in_tail(3);
        cb1.insert_in_tail(4);
        std::cout << "cb1 after many insertions in tail : " << cb1 << std::endl;
        std::cout << "cb1[-1] : " << cb1[-1] << std::endl;

        // Testo casi non limite
        std::cout << "cb1[2] : " << cb1[2] << std::endl;
        std::cout << "cb1[98] : " << cb1[98] << std::endl;

        // Testo swap()
        cbuffer<std::string> cb2 (3, "Pippo");
        cbuffer<std::string> cb3 (5, "Pluto");
        cbuffer<double> cb4 (3, 3);

        std::cout << "cb2 (3, 'Pippo') : " << cb2 << std::endl;
        std::cout << "cb3 (5, 'Pluto') : " << cb3 << std::endl;
        std::cout << "cbuffer<double> cb4 (3, 3) : " << cb4 << std::endl;


        // Testo il caso limite in cui cerco di scambiare il contenuto di due arrai i cui elementi sono di titpo diverso --> ERRORE
        /*cb2.swap(cb4);
        std::cout << "cb2.swap(cb4) : " << cb2 << std::endl;*/

        // Testo i casi non limite
        cb2.swap(cb3);
        std::cout << "cb2 after cb2.swap(cb3) : " << cb2 << std::endl;
        std::cout << "cb3 after cb2.swap(cb3) : " << cb3 << std::endl;
        cb3.swap(cb2);
        std::cout << "cb3 after cb3.swap(cb2) : " << cb3 << std::endl;
        std::cout << "cb2 after cb3.swap(cb2) : " << cb2 << std::endl;

        // Testo gli iteratori
        cbuffer<int>::iterator iter0();
        cbuffer<double>::iterator iter1();
        cbuffer<std::string>::iterator iter2();
        cbuffer<product>::iterator iter3();

        cbuffer<int> ct1 (2, 3);
        cbuffer<int> ct4 (2, 8);
        cbuffer<std::string> ct2 (3, "Pippo");
        cbuffer<std::string> ct5 (3, "Foo");
        cbuffer<product> ct3 (4, apple);
        cbuffer<product> ct6 (4, milk);

        cbuffer<int>::iterator iter4 = ct1.begin();
        std::cout << "cbuffer<int>::iterator iter4 = ct1.begin() : " <<*iter4 << std::endl;
        cbuffer<std::string>::iterator iter5 = ct2.end();
        std::cout << "cbuffer<std::string>::iterator iter5 = ct2.end() : " << *iter5 << std::endl;

        // Semplice test generico sugli iteratori (ulteriori test svolti precedentemente)

        cbuffer<int> a1(5);
        a1[0] = 1;
        a1[1] = 2;
        a1[2] = 3;
        a1[3] = 4;
        a1[4] = 5;

        std::cout << a1 << std::endl;
        std::cout << *a1.begin() << std::endl;
        std::cout << *a1.end() << std::endl;
        std::cout << a1.o_size() << std::endl;

        cbuffer<int>::const_iterator first, last;
        for(first=a1.begin(),last=++a1.end(); first!=last; first++){
            std::cout << *first << " " << std::endl; 
        }


        // Test su evaluate_if

        // Testo il caso limite in cui il buffer passato alla funzione evaluate_if sia nullo. 
        cbuffer<int> fc1 (0);
        std::cout << " evaluate_if(f, fc1) where cbuffer<int> fc1 (0) : " << std::endl;
        evaluate_if(f, fc1);

        // testo un caso limite in cui il tipo del buffer passato alla funzione evaluate_if sia diverso dal tipo sul quale lavora la funzione stessa -> ERRORE
        /*cbuffer<std::string> fc2(3, "Pippo");
        evaluate_if(f, fc2);*/

        // testo un caso non limite
        std::cout << "evaluate_if(f, a1) where a1 is full (value 5 in each cell) : " << std::endl;
        evaluate_if(f, a1);

        
}

