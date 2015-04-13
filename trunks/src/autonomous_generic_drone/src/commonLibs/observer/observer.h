/**
  *@author : Ricardo Rodriguez
  *@email: aricardorodriguez@hotmail.com
  *@date: 12-04-2015
  *@brief:
  *
  */
#ifndef OBSERVER_H
#define OBSERVER_H


namespace NSUtils {
template<class T>
class Observer
{
public:
    virtual void update(T &, int & )=0;
};

}
#endif // OBSERVER_H
