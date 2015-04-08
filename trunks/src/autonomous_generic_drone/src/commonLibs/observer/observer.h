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
