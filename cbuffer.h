#ifndef CBUFFER_H
#define CBUFFER_H

#include <ostream>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <cstddef>

/**
 @file dbuffer.h
 @brief Dichiarazione della classe cbuffer.
 */

/**
 @brief Array circolare di template.

 Classe che rappresenta un array circolare di template. La dimensione può essere scelta in fase di costruzione.

 */

template <typename T>
class cbuffer {

public:
    typedef unsigned int size_type; ///< Definizione del tipo corrispondente a size.

    typedef T value_type;

    /**
     @brief Costruttore di default (METODO FONDAMENTALE)

     Costruttore di default per istanziare un dbuffer vuoto. E' l'unico costruttore che può essere utilizzato per creare  un array di cbuffer.
     */
    cbuffer(): _size(0), _buffer(0), occupied_size(0), _head(0), _tail(0), _is_occupied(0) { // Initialization list

	#ifndef NDEBUG
	        std::cout << "cbuffer::cbuffer()" << std::endl;
	#endif

    }

    /**

    @brief Costruttore secondario

    Costruttore secondario. Permette di istanziare un cbuffer con una data dimensione.
    @param size Dimensione del cbuffer da istanziare.

    **/
    explicit cbuffer(size_type size) : _size(0), _buffer(0), occupied_size(0), _head(0), _tail(0), _is_occupied(0) {

        _size = size;
        _buffer = new T[size];
        occupied_size = 0;
        _head = 0;
        if (size > 0) {
            _tail = (occupied_size % _size);
        }
        else{
            _tail = 0;
        }

        _is_occupied = new bool[_size];

        try {

            for (int i = 0; i < _size; ++i) {
                _is_occupied[i] = false;
            }

        }
        catch( ... ) {
            delete[] _is_occupied;
            delete[] _buffer;
            _size = 0;
            _buffer = 0;
            _is_occupied = 0;
            occupied_size = 0;
            _head = 0;
            _tail = 0;
            throw;
        }

		#ifndef NDEBUG
		        std::cout << "cbuffer::cbuffer(int)" << std::endl;
		#endif
    }

    /**

	@brief Costruttore secondario

	Costruttore secondario. Permette di istanziare un cbuffer con una data dimensione e di inizializzare le celle dell'array con il valore dato.

	@param size Dimensione del cbuffer da istanziare.
	@param value Valore da usare per inizializzare le celle dell'array

    **/
    cbuffer(size_type size, const T &value) : _size(0), _buffer(0), occupied_size(0), _head(0), _tail(0), _is_occupied(0)  {

        _size = size;
        _buffer = new T[size];
        _is_occupied = new bool[_size];
        _head = 0;
        occupied_size = _size;
        if (size > 0) {
            _tail = _size % _size; 
        }
        else {
            _tail = 0;
        }
        

        try {
            for(size_type i=0 ; i < _size; ++i) {
                _buffer[i] = value;
            }
            for (size_type i = 0; i < _size; ++i) {
                _is_occupied[i] = true;
            }
        }
        catch(...) {
            delete[] _buffer;
            delete[] _is_occupied;
            _size = 0;
            _buffer = 0;
            occupied_size = 0;
            _is_occupied = 0;
            _head = 0;
            _tail = 0;
            throw;
        }

        #ifndef NDEBUG
        std::cout << "cbuffer::cbuffer(unsigned int,int)" << std::endl;
        #endif
    }

    /**
    @brief Costruttore secondario

    Costruttore secondario che costruisce il cbuffer a partire da una sequenza generica di dati identificata da due iteratori.

    @param begin iteratore di inizio della sequenza.
    @param end iteratore di fine della sequenza.

    @throw Eccezione di allocazione di memoria.

    */
    template <typename Q>
    cbuffer(size_type s, Q begin, Q end) : _size(0), _buffer(0), occupied_size(0), _head(0), _tail(0), _is_occupied(0) {

        _size = s;
        _buffer = new T[_size];
        _is_occupied = new bool[_size];
        occupied_size = 0;
        _head = 0;
        _tail = 0;

        int i = 0;
        try {

            if (_size > 0) {
                for(; begin != end; ++begin) { 
                    
                    _buffer[i % _size] = (static_cast <T> (*begin));
                    _is_occupied[i % _size] = true;
                    ++i;

                }

                _buffer[i % _size] = (static_cast <T> (*end));
            }
        }
        catch(...) {
            delete[] _buffer;
            delete[] _is_occupied;
            _size = 0;
            _buffer = 0;
            _is_occupied = 0;
            occupied_size = 0;
            _head = 0;
            _tail = 0;
            throw;
        }
        
        

        #ifndef NDEBUG
                std::cout << "cbuffer::cbuffer(size_type s, Q begin, Q end)" << std::endl;
        #endif
    }

    /**
	@brief Copy constructor (METODO FONDAMENTALE)

	Costruttore di copia. Permette di istanziare un cbuffer con i valori presi da un altro cbuffer.

	@param other cbuffer da usare per creare quello corrente.
    **/
    cbuffer(const cbuffer &other) : _size(0), _buffer(0), occupied_size(0), _head(0), _tail(0), _is_occupied(0) {

        _buffer = new T[other._size];
        _is_occupied = new bool[other._size];
        _size = other._size;
        _head = other._head;
        _tail = other._tail;
        occupied_size = other.occupied_size;

        try {

            for (size_type i = 0; i < _size; ++i) {
                _buffer[i] = other._buffer[i];
            }

            for (size_type i = 0; i < _size; ++i) {
                _is_occupied[i] = other._is_occupied[i];
            }
        }
        catch(...) {

            delete[] _buffer;
            delete[] _is_occupied;
            _size = 0;
            _buffer = 0;
            _is_occupied = 0;
            occupied_size = 0;
            _head = 0;
            _tail = 0;
            throw;
        }

		#ifndef NDEBUG
		        std::cout << "cbuffer::cbuffer(const cbuffer&)" << std::endl;
		#endif
    }

    /**

	@brief Operatore di assegnamento (METODO FONDAMENTALE)

	Operatore di assegnamento. Permette la copia fra cbuffer.
	@param other cbuffer sorgente.
	@return Riferimento a this.

    **/
    cbuffer &operator= (const cbuffer &other) {

        if (this != &other) {

            try {

                cbuffer tmp (other);
                this -> swap(tmp);
            }
            catch ( ... ) {
                throw;
            }

        }

    	#ifndef NDEBUG
    	        std::cout << "cbuffer::operator=(const cbuffer&)" << std::endl;
    	#endif

        return *this;
    }

    /**
	@brief Distruttore (METODO FONDAMENTALE)

	Distruttore. Rimuove la memoria allocata dal cbuffer.

    **/
    ~cbuffer() {

        delete[] _buffer;
        delete[] _is_occupied;
        _size = 0;
        _buffer = 0;
        _is_occupied = 0;
        occupied_size = 0;
        _head = 0;
        _tail = 0;
           

	#ifndef NDEBUG
	        std::cout << "cbuffer::~cbuffer()" << std::endl;
	#endif
    }

    /**
	@brief  Dimensione dell'array circolare (stile java).

	Ritorna la dimensione dell'array circolare.

	@return La dimensione dell'array circolare.
    **/
    size_type get_size() const {
        return _size;
    }

    /**
    @brief Dimensione dell'array circolare (stile C++).

    Ritorna la dimensione dell'array circolare.

    @return La dimensione dell'array circolare.
    **/
    size_type size() const {
        return _size;
    }

    /**
    @brief Dimensione del cbuffer effettivamente occupata.

    Ritorna la dimensione effettivamente occupata del cbuffer.

    @return Dimensione del cbuffer effettivamente occupata.
    **/
    size_type o_size() const {

        if (occupied_size <= _size) {

            return occupied_size;
        }
        else
            return _size;
    }

    /**
    @brief Valore di verità circa l'assenza di elementi nel cbuffer.

    Ritorna "true" se il cbuffer è vuoto, "false" altrimenti.

    @return Valore di verità circa l'assenza di elementi nel cbuffer.
    **/
    bool empty() const {

        return (occupied_size == 0); 
    }

    /**
    @brief Valore di verità circa la saturazione del cbuffer.

    Ritorna "true" se il cbuffer è saturo, "false" altrimenti.

    @return Valore di verità circa la saturazione del cbuffer.
    **/
    bool full() const {

        for (int i = 0; i < _size; ++i) {
            if (_is_occupied[i] == false) {
                return false;
            }
            return true;
        }
    }

    /**
    @brief Valore di testa del cbuffer.

    Ritorna il valore di testa del cbuffer.

    @return Valore di testa del cbuffer.
    **/
    value_type& head () {

        return _buffer[_head];

    }

    /**
    @brief Valore di coda del cbuffer.

    Ritorna il valore di coda del cbuffer.

    @return Valore di coda del cbuffer.

    **/
    value_type& tail () {

            return _buffer[_tail];
      
    }

    /**
    @brief Inserimento di un elemento in coda al cbuffer.

    Funzione di inserimento di un valore in coda al cbuffer.

    @param x Valore da inserire in coda al cbuffer.

    **/
    void insert_in_tail(const value_type& x) {

        if (_size != 0) {
            if(o_size() == _size) {
                _head = (_head + 1) % _size;
            }
            else {
                occupied_size++;
            }

            tail() = x;
            _tail = (_tail + 1) % _size;
            _is_occupied[_tail] = true;
        }
    }

    /**
    @brief Rimozione dell'elemento in testa.

    Metodo per la rimozione dell'elemento in testa al cbuffer.

    **/
    void remove_head() {
        //head() = NULL;

        if (_size != 0) {
            _is_occupied[_head] = false;
            _head = (_head + 1) % _size;
            occupied_size --;
        }
    }


    /**
    @brief Accesso ai dati in lettura (stile Java)

    Metodo getter per leggere il valore index-esimo dell'array. Se il valore di index è maggiore del valore _size dell'array, allora, poichè ci troviamo in presenza di un array circolare, ripartiamo daccapo nel conteggio dell'indice.

    @param index Indice della cella dell'array da leggere.
    @return Il valore della cella index-esima.

    **/
    T get_value (size_type index) const {

        if (_size != 0) {
            if (index < _size) {
                return _buffer[index];
            }
            else {
                while (index >= _size) {
                    index = index - _size;
                }
                return _buffer[index];
            }
        }

        throw std::runtime_error ("Buffer size equal to 0.");
    }

    /**
    @brief Accesso ai dati in scrittura (stile Java)

    Metodo setter per scrivere il valore index-esimo dell'array. Se il valore di index è maggiore del valore _size dell'array, allora, poichè ci troviamo in presenza di un array circolare, ripartiamo daccapo nel conteggio dell'indice.

    @param index Indice della cella dell'array da scrivere.
    @param value Valore da scrivere nella cella.

    **/
    void set_value(size_type index, const T &value) {

        if (_size != 0) {
            if (index < _size) {

                if(!full()) {
                    _buffer[index] = value;
                    occupied_size ++;
                    _is_occupied[index] = true;
                }
                else {
                    _buffer[index] = value;
                }
            }
            else {
                while (index >= _size) {
                    index = index - _size;
                }

                if(!full()) {
                    _buffer[index] = value;
                    occupied_size ++;
                    _is_occupied[index] = true;
                }
                else {
                    _buffer[index] = value;
                }
                
            }
        }
    }

    /**
    @brief Accesso ai dati in lettura/scrittura (stile C++)

    Metodo getter per leggere il valore index-esimo dell'array. Se il valore di index è maggiore del valore _size dell'array, allora, poichè ci troviamo in presenza di un array circolare, ripartiamo daccapo nel conteggio dell'indice.

    @param index indice della cella dell'array da leggere.
    @return Il valore della cella index-esima.

    **/
    T &value (size_type index) {

        if (_size != 0) {
            if (index < _size) {
                return _buffer[index];
            }
            else {
                while (index >= _size) {
                    index = index - _size;
                }
                return _buffer[index];
            }
        }

        throw std::runtime_error ("Buffer size equal to 0.");
    }
   

    /**
    @brief Accesso ai dati in lettura (stile C++)

    Metodo setter per scrivere il valore index-esimo dell'array. Se il valore di index è maggiore del valore _size dell'array, allora, poichè ci troviamo in presenza di un array circolare, ripartiamo daccapo nel conteggio dell'indice.

    @param index Indice della cella dell'array da scrivere.

    **/
    const T &value(size_type index) const {

        if (_size != 0) {
            if (index < _size) {
                return _buffer[index];
            }
            else {
                while (index >= _size) {
                    index = index - _size;
                }
                return _buffer[index];
            }
        }
        throw std::runtime_error ("Buffer size equal to 0.");
    }
    

    /**
    @brief Accesso ai dati in lettura/scrittura (stile C++ con operatore)

    Metodo getter per leggere il valore index-esimo dell'array. Se il valore di index è maggiore del valore _size dell'array, allora, poichè ci troviamo in presenza di un array circolare, ripartiamo daccapo nel conteggio dell'indice.

    @param index Indice della cella dell'array da leggere.
    @return Il valore della cella index-esima.

    **/
        T &operator[](size_type index) {

        if (_size != 0) {
            occupied_size++;
            //_is_occupied[index % _size] = true;
            index = index % _size;
                if (index == occupied_size-1 && (_is_occupied[index] == false)) {

                    if (index != 0 && _is_occupied[index-1] == true) {
                        _is_occupied[index] = true;
                        _tail = (occupied_size % _size);
                        return _buffer[index % _size];
                    }
                    else {
                       _is_occupied[index] = true;
                       _head = (index%_size);
                       _tail = (occupied_size % _size);
                       return _buffer[index % _size]; 
                    }
                }
                else {

                    if (_is_occupied[index] == true) {

                        if (occupied_size < _size) {
                            occupied_size --;
                            size_type tmp = _tail;
                            _tail = (tmp%_size);
                            _head = (index % _size) + 1;

                            return _buffer[index % _size];
                        }
                        else {
                            occupied_size --;
                            if(index == 0) {
                                _head = 0;
                                _tail = 0;
                                return _buffer[index % _size];
                            }
                            else {
                                size_type tmp = _tail;
                                _tail = tmp % _size;
                                _head = _tail;
                                return _buffer[index % _size];
                            }
                        }
                    }

                    else {
            
                        _is_occupied[index] = true;
                        size_type tmp = _tail;
                        _head = (index % _size);
                        _tail = ((_head + 1)%_size);
                        
                        return _buffer[index % _size]; 
                    
                    }
                } 
            }
            throw std::runtime_error ("Buffer size equal to 0.");
        }  


    

    /**
    @brief Accesso ai dati in lettura (stile C++ con operatore)

    Metodo setter per scrivere il valore index-esimo dell'array. Se il valore di index è maggiore del valore _size dell'array, allora, poichè ci troviamo in presenza di un array circolare, ripartiamo daccapo nel conteggio dell'indice.

    @param index Indice della cella dell'array da scrivere.

    **/
    const T &operator[] (size_type index) const {

        if (index < _size) {
            return _buffer[index];
        }
        else {
            while (index >= _size) {
                index = index - _size;
            }
            return _buffer[index];
        }
    }

    /**
    @brief Scambia il contenuto di due cbuffer.

    Scambia il contenuto di due cbuffer.

    @param other cbuffer con il quale scambiare i dati.

    **/
    void swap (cbuffer &other) {

        std::swap(other._size, this -> _size);
        std::swap(other._buffer, this -> _buffer);
    }

    class const_iterator;

    class iterator {

        T *ptr;

    public:

        typedef std::forward_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;

        iterator() : ptr(0) {}

        iterator(const iterator &other) : ptr(other.ptr) {}

        iterator& operator=(const iterator &other) {
            ptr = other.ptr;
            return *this;
        }

        ~iterator() {}

        // Ritorna il dato riferito dall'iteratore (dereferenziamento)
        reference operator*() const {
            return *ptr;
        }

        // Ritorna il puntatore al dato riferito dall'iteratore
        pointer operator->() const {
            return ptr;
        }

        // Operatore di iterazione post-incremento
        iterator operator++(int) {
            iterator tmp(*this);
            ++ptr;
            return tmp;
        }

        // Operatore di iterazione pre-incremento
        iterator& operator++() {
            ++ptr;
            return *this;
        }

        // Uguaglianza
        bool operator==(const iterator &other) const {
            return ptr == other.ptr;
        }

        // Diversità
        bool operator!=(const iterator &other) const {
            return ptr != other.ptr;
        }

        // Definizioni per const_iterator

        friend class const_iterator;

        // Uguaglianza
        bool operator== (const const_iterator &other) const {
            return ptr == other.ptr;
        }

        // Diversità
        bool operator!=(const const_iterator &other) const {
            return ptr != other.ptr;
        }

    private:

        friend class cbuffer;

        iterator (T *p) : ptr(p) {}

    }; // Fine classe iterator

    // Ritorna l'iteratore all'inizio della sequenza dati
    iterator begin() {
        return iterator(_buffer + _head);
    }

    iterator end() {
    
            if(_size != 0 && _head != 0) {
                return iterator(_buffer + (_head - 1));
            }
            else {

                if(_head == 0 && full()) {
                    return iterator(_buffer + occupied_size-1);
                }
                else {
                    return iterator(_buffer + (_tail));
                }
            }


    }

    class const_iterator {

        const T *ptr;

    public:

        typedef std::forward_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef const T* pointer;
        typedef const T& reference;

        const_iterator() : ptr(0) {}

        const_iterator(const const_iterator &other) : ptr(other.ptr) {}

        const_iterator(const iterator &other) : ptr(other.ptr) {}

        const_iterator& operator= (const const_iterator &other) {
            ptr = other.ptr;
            return *this;
        }

        const_iterator& operator=(const iterator &other) {
            ptr = other.ptr;
            return *this;
        }

        ~const_iterator() {}

        // Ritorna il dato riferito dall'iteratore (dereferenziamento)
        reference operator*() const {
            return *ptr;
        }

        // Ritorna il puntatore al dato riferito dall'iteratore
        pointer operator->() const {
            return ptr;
        }

        // Operatore di iterazione post-incremento
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++ptr;
            return tmp;
        }

        // Operatore di iterazione pre-incremento
        const_iterator& operator++() {
            ++ptr;
            return *this;
        }

        // Uguaglianza
        bool operator==(const const_iterator &other) const {
            return ptr == other.ptr;
        }

        // Diversità
        bool operator!=(const const_iterator &other) const {
            return ptr != other.ptr;
        }

        friend class iterator;

        // Uguaglianza
        bool operator==(const iterator &other) const {
            return ptr == other.ptr;
        }

        // Diversità
        bool operator!=(const iterator &other) const {
            return ptr != other.ptr;
        }

    private:
        friend class cbuffer;

        // Costruttore privato di inizializzazione usato dalla classe container tipicamente nei metodi begin ed end
        const_iterator(const T*p) : ptr(p) {}

    };

    // Ritorna l'iteratore all'inizio della sequenza dati
    const_iterator begin() const {
        return const_iterator(_buffer + _head);
    }

    // Ritorna l'iteratore alla fine della sequenza dati
    const_iterator end() const {

        if (_size != 0 && _head != 0) {
                return const_iterator(_buffer + (_head - 1));
                //return begin();
        }
        else {

            if(_head == 0 && full()) {
                return const_iterator(_buffer + occupied_size-1);
            }
            else {

                return const_iterator(_buffer + _tail);
            }

        }
    
    }

private:

    T *_buffer; ///< Puntatore all'array di template
    bool *_is_occupied; ///< Puntatore all'array di booleani
    size_type _size; ///< Dimensione dell'array

    size_type occupied_size; ///< cbuffer non vuoto

    size_type _head;
    size_type _tail;


};	// cbuffer

/**
@brief Operatore di stream

Permette di spedire su uno stream di output il contanuto dell'array.

@param os stream di output.
@param cb cbuffer da utilizzare.
@return Il riferimento allo stream di output.

**/

template <typename T>
std::ostream& operator<<(std::ostream &os, const cbuffer<T> & cb) {

    for (typename cbuffer<T>::size_type i = 0; i < cb.size(); ++i)
        os << cb[i] << " ";

    return os;

}

/**
@brief Funzione evaluate_if.

Richiama una funzione booleana su ciascun elemento di un cbuffer.

@param (* P) (T) Funzione ricevuta in input.
@param cb cbuffer ricevuto in input.

**/
template <typename T>
void evaluate_if(bool (* P) (T), const cbuffer<T> & cb) {
    
    for (int i = 0; i < cb.size(); ++i) {

        if (P(cb[i]) == true) { 
        std::cout << "[" << i << "]: true " << std::endl;
    }
    else
        std::cout << "[" << i << "]: false " << std::endl;
    }
}

#endif //CBUFFER_H
