// string_buffer.h

#ifndef STRING_BUFFER_H_
#define STRING_BUFFER_H_

#include "types.h"

/*
CLASS
  StringBuffer
  
  Classe repr�sentant une copie partag�e d'une cha�ne.
  
  
FONCTIONNEMENT
    
  Lorsque le nombre de r�f�rences � cette copie tombe � 0, elle est 
  d�truite.
*/
class StringBuffer {
  
  ////////////////////
  // Nombre de r�f�rences � la cha�ne.
  EntierNonSigne nb_ref ;
  
  ////////////////////
  // Taille de la cha�ne.
  EntierNonSigne size ;
  
  ///////////////////
  // Cha�ne proprment dite.
  
  char* s ;
  
public:
  
  // GROUP: Constructeurs
  
  StringBuffer(const EntierNonSigne& _size);
  StringBuffer(const char* _s, const EntierNonSigne& _len);
  StringBuffer(const char* _s);
  StringBuffer(char _c);
  StringBuffer();
  StringBuffer(const char* _s1, const EntierNonSigne& _s1_len, 
                const char*_s2, const EntierNonSigne& _s2_len);
                
  StringBuffer(const char* _s, const EntierNonSigne& _s_len, char _c);
  StringBuffer(char _c, const char* _s, const EntierNonSigne& _s_len);
  
  ~StringBuffer();
  
  ///////////////
  // Acc�s � la longueur de la cha�ne.
  EntierNonSigne len() const;

  ////////////////////
  // tient une copie de la chaine, augmente le 
  // nombre de r�f�rences
  StringBuffer* take() ;
  
  /////////////////
  // Laisse tomber une r�f�rence � la copie courante, 
  // diminue le nombre de r�f�rences
  Booleen drop() ;
  
  //////////////////
  // Op�rateur de conversion en char*.
  operator char*() const ;
  
private:
  
  StringBuffer(const StringBuffer& _s) ;
  StringBuffer& operator=(const StringBuffer& _s) ;
};

inline StringBuffer::StringBuffer(const EntierNonSigne& _size)
  : nb_ref(1), size(_size), s(new char[_size + 1])
{}

inline StringBuffer::StringBuffer(const char *_s, const EntierNonSigne& _len)
  : nb_ref(1), size(_len), s(new char[_len + 1])
{
  memcpy(s, _s, _len);
  s[_len] = '\0';
}

inline StringBuffer::StringBuffer(const char *_s)
  : nb_ref(1), size(strlen(_s)), s(new char[size + 1])
{
  strcpy(s, _s);
}

inline StringBuffer::StringBuffer(char _c)
  : nb_ref(1), size(1), s(new char[2])
{
  s[0] = _c;
  s[1] = '\0';
}

inline StringBuffer::StringBuffer()
  : nb_ref(1), size(0), s(new char[1])
{
  s[0] = '\0';
}

inline StringBuffer::StringBuffer(const char *_s1, 
  const EntierNonSigne& _s1_len, 
    const char *_s2, const EntierNonSigne& _s2_len)
  : nb_ref(1), size(_s1_len + _s2_len), s(new char[size + 1])
{
  memcpy(s, _s1, _s1_len);
  memcpy(s + _s1_len, _s2, _s2_len);
  s[size] = '\0';
}

inline StringBuffer::StringBuffer(const char *_s, 
  const EntierNonSigne& _s_len, char _c)
  : nb_ref(1), size(_s_len + 1), s(new char[size + 1])
{
  memcpy(s, _s, _s_len);
  s[_s_len] = _c;
  s[size] = '\0';
}

inline StringBuffer::StringBuffer(char _c, const char *_s, 
  const EntierNonSigne& _s_len)
  : nb_ref(1), size(_s_len + 1), s(new char[size + 1])
{
  s[0] = _c;
  memcpy(s + 1, _s, _s_len);
  s[size] = '\0';
}

inline StringBuffer::~StringBuffer() {
  delete [] s;
}

inline EntierNonSigne StringBuffer::len() const {
  return size;
}

inline StringBuffer *StringBuffer::take() {
  ++nb_ref;
  return this;
}

inline Booleen StringBuffer::drop() {
  return --nb_ref == 0;
}

inline StringBuffer::operator char *() const {
  return s;
}

#endif

