/**
  *@author : Ricardo Rodriguez
  *@email: aricardorodriguez@hotmail.com
  *@date: 12-04-2015
  *@brief:
  *
  */
#ifndef SUJETO_H
#define SUJETO_H
#include <vector>
#include <iostream>
#include "observer.h"


namespace NSUtils {
template <class T>
class Sujeto
{
	protected:
	    void notificarObservador(T aCmd, int & aErrorCode)
	    {
		aErrorCode=-1;
		if(mObservador!=nullptr){
			aErrorCode=0;
			mObservador->update(aCmd,aErrorCode);
		}
	    }

	    void agregarObserver(Observer<T> * const aObserver)
	    {
		mObservador=aObserver;
	    }

	    Sujeto():mObservador(nullptr)
	    {}
	    virtual ~ Sujeto(){}
	    Observer<T> * getObserver() const
	    {
		return mObservador;
	    }
	private:
	    Observer<T> * mObservador;
  };
}


#endif // SUJETO_H
