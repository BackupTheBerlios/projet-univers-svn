// min_max.h
#ifdef __GNUG__
#pragma interface
#endif

#ifndef MIN_MAX_H_
#define MIN_MAX_H_

template <class T> inline T Min(T _v1, T _v2) {
    return _v1 < _v2 ? _v1 : _v2;
}

template <class T> inline T Max(T _v1, T _v2) {
    return _v1 > _v2 ? _v1 : _v2;
}


#endif
