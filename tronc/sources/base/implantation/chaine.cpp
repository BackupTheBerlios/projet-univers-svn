/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "../chaine.h"
#include <stdlib.h>

namespace ProjetUnivers {

  namespace Base {    
    
    char Chaine::number_buffer[200];
    
    Chaine &Chaine::append(const char *_s, int _s_len) {
        TamponChaine *p_new_rep = new TamponChaine(*p_rep, p_rep->len(), _s, _s_len);
        drop_rep(p_rep);
        p_rep = p_new_rep;
        return *this;
    }
    
    Chaine &Chaine::operator += (char _c) {
        TamponChaine *p_new_rep = new TamponChaine(*p_rep, p_rep->len(), _c);
        drop_rep(p_rep);
        p_rep = p_new_rep;
        return *this;
    }
    
    short Chaine::cmp(const Chaine &_s) const {
    #ifdef DEBUG_STR
        cerr << *this << ".cmp(" << _s << ')' << endl;
    #endif
        int left_len = Minimum(len(), _s.len());
        short val = 0;
        const char *p1 = *this;
        const char *p2 = _s;
        while (left_len-- >= 0 && (val = *(p1++) - *(p2++)) == 0)
    	;
    #ifdef DEBUG_STR
        cerr << "Compare result : "<< val << endl;
    #endif
        return val;
    }
    
    int Chaine::find(const Chaine &_s) const {
        const char *s1 = *this;
        const char *s2 = _s;
        int len2 = _s.len();
        int last = len() - len2;
        for (int i = 0; i <= last; ++i) {
    	int j;
    	for (j = 0; j < len2; ++j)
    	    if (s1[i + j] != s2[j])
    		break;
    	if (j == len2)
    	    return i;
        }
        return -1;
    }
    
    Chaine Chaine::upper() const {
    	
    	Chaine resultat ;
    
    	for(int i(0) ; i < len() ; ++i) {
    
    		switch(operator[](i)) {
    
    		case 'a':
    
    			resultat += 'A' ;
    			break ;
    
    		case 'b':
    
    			resultat += 'B' ;
    			break ;
    		case 'c':
    
    			resultat += 'C' ;
    			break ;
    		case 'd':
    
    			resultat += 'D' ;
    			break ;
    		case 'e':
    
    			resultat += 'E' ;
    			break ;
    		case 'f':
    
    			resultat += 'F' ;
    			break ;
    		case 'g':
    
    			resultat += 'G' ;
    			break ;
    		case 'h':
    
    			resultat += 'H' ;
    			break ;
    		case 'i':
    
    			resultat += 'I' ;
    			break ;
    		case 'j':
    
    			resultat += 'J' ;
    			break ;
    		case 'k':
    
    			resultat += 'K' ;
    			break ;
    		case 'l':
    
    			resultat += 'L' ;
    			break ;
    
    		case 'm':
    
    			resultat += 'M' ;
    			break ;
    		case 'n':
    
    			resultat += 'N' ;
    			break ;
    		case 'o':
    
    			resultat += 'O' ;
    			break ;
    		case 'p':
    
    			resultat += 'P' ;
    			break ;
    		case 'q':
    
    			resultat += 'Q' ;
    			break ;
    		case 'r':
    
    			resultat += 'R' ;
    			break ;
    		case 's':
    
    			resultat += 'S' ;
    			break ;
    		case 't':
    
    			resultat += 'T' ;
    			break ;
    		case 'u':
    
    			resultat += 'U' ;
    			break ;
    
    		case 'v':
    
    			resultat += 'V' ;
    			break ;
    		case 'w':
    
    			resultat += 'W' ;
    			break ;
    		case 'x':
    
    			resultat += 'X' ;
    			break ;
    		case 'y':
    
    			resultat += 'Y' ;
    			break ;
    		case 'z':
    
    			resultat += 'Z' ;
    			break ;
    		default:
    
    			resultat += operator[](i) ;
    			break ;
    		}
    	
    	
    	}
    	
    	return resultat ;
    }
    
    /*
    Chaine::TamponChaine *Chaine::new_rep(int _size) {
        TamponChaine *p_rep = new TamponChaine;
        p_rep->nb_ref = 1;
        p_rep->size = _size;
        p_rep->s = new char [_size + 1];
        return p_rep;
    }
    
    Chaine::TamponChaine *Chaine::take_rep(TamponChaine *_p_rep) {
        ++(_p_rep->nb_ref);
        return _p_rep;
    }
    
    void Chaine::drop_rep(TamponChaine *_p_rep) {
        if (--(_p_rep->nb_ref) < 1) {
            delete _p_rep->s;
            delete _p_rep;
        }
    }
    */
    
    TamponChaine Chaine::empty_str_rep;
  }
}
