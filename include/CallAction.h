#ifndef INCLUDED_CALLACTION_H
#define INCLUDED_CALLACTION_H

#include <hamcrest/core/hc_matcher.h>

#include <boost/function.hpp>

namespace carnamock {

template <class ReturnType= nulltype
, class Param1= nulltype
, class Param2= nulltype
, class Param3=nulltype
, class Param4=nulltype
, class Param5=nulltype> 
class CallAction;

class CallActionBase
{   
public:
   virtual ~CallActionBase() {}

   //if some other type will be added this must be factored to inheritance 
   enum ActionType { RETURNABLE, DELEGATE_TO_FUNCTION };

protected:
   ActionType actionType;
};

template <class ReturnType>
class CallAction<ReturnType> : public CallActionBase
{
	ReturnType returns;
   boost::function0<ReturnType> func;
public:
	ReturnType Execute()
	{
      return actionType == RETURNABLE ? returns : func();
	}

	ReturnType GetReturn() { return returns; }

	void SetReturn(ReturnType _returns)
	{
      actionType= RETURNABLE;
		returns= _returns;
	}

   void SetFunction(boost::function0<ReturnType> _func) 
   {
      actionType= DELEGATE_TO_FUNCTION;
      func= _func;
   }
};

template <>
class CallAction<void> : public CallActionBase
{
   boost::function0<void> func;
public:
   void Execute() {
      func();
   }
   //TODO: refactor that to some base class
   void SetFunction(boost::function0<void> _func) 
   { 
      func= _func; 
   }
};


template <class ReturnType, class Param1>
class CallAction<ReturnType, Param1> : public CallActionBase
{
	ReturnType returns;
   hamcrest::matcher<Param1> *matcher_hc;
   boost::function1<ReturnType, Param1> func;
public:	
	bool KnowsThat(Param1 p1)
	{
		return (*matcher_hc)(p1);
	}

	ReturnType Execute(Param1 p1)
	{
		return actionType == RETURNABLE ? returns : func(p1);
	}

   void SetParam(hamcrest::matcher<Param1> &p1)
   {
      matcher_hc= p1.copy();
   }

	void SetReturn(ReturnType _returns)
	{
      actionType= RETURNABLE;
		returns= _returns;
	}

   void SetFunction(boost::function1<ReturnType, Param1> _func) 
   { 
      actionType= DELEGATE_TO_FUNCTION;
      func= _func; 
   }
};


template <class Param1>
class CallAction<void, Param1> : public CallActionBase
{
   hamcrest::matcher<Param1> *matcher;
   boost::function1<void, Param1> func;
public:	
	bool KnowsThat(Param1 p1)
	{
		return (*matcher)(p1);
	}

	void Execute(Param1 p1)
	{
      func(p1);
	}

   void SetParam(hamcrest::matcher<Param1> &p1)
   {
      matcher= p1.copy();
   }

   void SetFunction(boost::function1<void, Param1> _func) 
   { 
      func= _func;
   }
};


//2 arity

template <class ReturnType, class Param1, class Param2>
class CallAction<ReturnType, Param1, Param2> : public CallActionBase
{
	ReturnType returns;
   hamcrest::matcher<Param1> *matcher1;
   hamcrest::matcher<Param2> *matcher2;
   boost::function2<ReturnType, Param1, Param2> func;
public:	
	bool KnowsThat(Param1 p1, Param2 p2)
	{
		return (*matcher1)(p1) && (*matcher2)(p2);
	}

	ReturnType Execute(Param1 p1, Param2 p2)
	{
		return actionType == RETURNABLE ? returns : func(p1, p2);
	}	

   void SetParam(hamcrest::matcher<Param1> &p1, hamcrest::matcher<Param2> &p2)
   {
      matcher1= p1.copy();
      matcher2= p2.copy();
   }

	void SetReturn(ReturnType _returns)
	{
      actionType= RETURNABLE;
		returns= _returns;
	}

   void SetFunction(boost::function2<ReturnType, Param1, Param2> _func) 
   { 
      actionType= DELEGATE_TO_FUNCTION;
      func= _func; 
   }
};

template <class Param1, class Param2>
class CallAction<void, Param1, Param2> : public CallActionBase
{
   hamcrest::matcher<Param1> *matcher1;
   hamcrest::matcher<Param2> *matcher2;
   boost::function2<void, Param1, Param2> func;
   
public:	
	bool KnowsThat(Param1 p1, Param2 p2)
	{
		return (*matcher1)(p1) && (*matcher2)(p2);
	}

	void Execute(Param1 p1, Param2 p2)
	{
      func(p1, p2);
	}

   void SetParam(hamcrest::matcher<Param1> &p1, hamcrest::matcher<Param2> &p2)
   {
      matcher1= p1.copy();
      matcher2= p2.copy();
   }

   void SetFunction(boost::function2<void, Param1, Param2> _func) 
   { 
      actionType= DELEGATE_TO_FUNCTION;
      func= _func; 
   }
};


//3 arity

template <class ReturnType, class Param1, class Param2, class Param3>
class CallAction<ReturnType, Param1, Param2, Param3> : public CallActionBase
{
	ReturnType returns;
   hamcrest::matcher<Param1> *matcher1;
   hamcrest::matcher<Param2> *matcher2;
   hamcrest::matcher<Param3> *matcher3;
   boost::function3<ReturnType, Param1, Param2, Param3> func;

public:
	bool KnowsThat(Param1 p1, Param2 p2, Param3 p3)
	{
		return (*matcher1)(p1) && (*matcher)(p2) && (*matcher3)(p3);
	}

	ReturnType Execute(Param1 p1, Param2 p2, Param3 p3)
	{
		return actionType == RETURNABLE ? returns : func(p1, p2, p3);
	}

   void SetParam(hamcrest::matcher<Param1> &p1, hamcrest::matcher<Param2> &p2, hamcrest::matcher<Param3> &p3)
	{
		matcher1= p1.copy();
		matcher2= p2.copy();
		matcher3= p3.copy();
   }   

	void SetReturn(ReturnType _returns)
	{
      actionType= RETURNABLE;
		returns= _returns;
	}

   void SetFunction(boost::function3<ReturnType, Param1, Param2, Param3> _func) 
   { 
      actionType= DELEGATE_TO_FUNCTION;
      func= _func; 
   }
};

template <class Param1, class Param2, class Param3>
class CallAction<void, Param1, Param2, Param3> : public CallActionBase
{   
   hamcrest::matcher<Param1> *matcher1;
   hamcrest::matcher<Param2> *matcher2;
   hamcrest::matcher<Param3> *matcher3;
   boost::function3<void, Param1, Param2, Param3> func;

public:
   bool KnowsThat(Param1 p1, Param2 p2, Param3 p3)
   {
      return (*matcher1)(p1) && (*matcher2)(p2) && (*matcher3)(p3);
   }

   void Execute(Param1 p1, Param2 p2, Param3 p3)
   {
      return func(p1, p2, p3);
   }

   void SetParam(hamcrest::matcher<Param1> &p1, hamcrest::matcher<Param2> &p2, hamcrest::matcher<Param3> &p3)
   {
      matcher1= p1.copy();
      matcher2= p2.copy();
      matcher3= p3.copy();
   }

   void SetFunction(boost::function3<void, Param1, Param2, Param3> _func) 
   { 
      func= _func; 
   }
};

//4 arity

template <class ReturnType, class Param1, class Param2, class Param3, class Param4>
class CallAction<ReturnType, Param1, Param2, Param3, Param4> : public CallActionBase
{
	ReturnType returns;
	hamcrest::matcher<Param1> *matcher1;
	hamcrest::matcher<Param2> *matcher2;
	hamcrest::matcher<Param3> *matcher3;
	hamcrest::matcher<Param4> *matcher4;
   boost::function4<ReturnType, Param1, Param2, Param3, Param4> func;
public:	
	bool KnowsThat(Param1 p1, Param2 p2, Param3 p3, Param4 p4)
	{
		return (*matcher1)(p1) && (*matcher)(p2) && (*matcher3)(p3) && (*matcher4)(p4);
	}

	ReturnType Execute(Param1 p1, Param2 p2, Param3 p3, Param4 p4)
	{
		return actionType == RETURNABLE ? returns : func(p1, p2, p3, p4);
	}

	void SetParam(hamcrest::matcher<Param1> &p1, hamcrest::matcher<Param2> &p2, hamcrest::matcher<Param3> &p3, hamcrest::matcher<Param4> &p4)
	{
		matcher1= p1.copy();
		matcher2= p2.copy();
		matcher3= p3.copy();
		matcher4= p4.copy();
	}

	void SetReturn(ReturnType _returns)
	{
      actionType= RETURNABLE;
		returns= _returns;
	}

   void SetFunction(boost::function4<ReturnType, Param1, Param2, Param3, Param4> _func) 
   { 
      actionType= DELEGATE_TO_FUNCTION;
      func= _func; 
   }
};

template <class Param1, class Param2, class Param3, class Param4>
class CallAction<void, Param1, Param2, Param3, Param4> : public CallActionBase
{
   hamcrest::matcher<Param1> *matcher1;
   hamcrest::matcher<Param2> *matcher2;
   hamcrest::matcher<Param3> *matcher3;
   hamcrest::matcher<Param4> *matcher4;
   boost::function4<void, Param1, Param2, Param3, Param4> func;
public:	
   bool KnowsThat(Param1 p1, Param2 p2, Param3 p3, Param4 p4)
   {
      return (*matcher1)(p1) && (*matcher2)(p2) && (*matcher3)(p3) && (*matcher4)(p4);
   }

   void Execute(Param1 p1, Param2 p2, Param3 p3, Param4 p4)
   {
      return func(p1, p2, p3, p4);
   }

   void SetParam(hamcrest::matcher<Param1> &p1, hamcrest::matcher<Param2> &p2, hamcrest::matcher<Param3> &p3, hamcrest::matcher<Param4> &p4)
   {
      matcher1= p1.copy();
      matcher2= p2.copy();
      matcher3= p3.copy();
      matcher4= p4.copy();
   }

   void SetFunction(boost::function4<void, Param1, Param2, Param3, Param4> _func) 
   { 
      func= _func; 
   }
};

//
////5 arity
//
//template <class ReturnType, class Param1, class Param2, class Param3, class Param4, class Param5>
//class CallAction<ReturnType, Param1, Param2, Param3, Param4, Param5>
//{
//	ReturnType returns;
//	hamcrest::matcher<Param1> *matcher1;
//	hamcrest::matcher<Param2> *matcher2;
//	hamcrest::matcher<Param3> *matcher3;
//	hamcrest::matcher<Param4> *matcher4;
//	hamcrest::matcher<Param5> *matcher5;
//public:	
//	bool KnowsThat(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5)
//	{
//		return (*matcher1)(p1) && (*matcher)(p2) && (*matcher3)(p3) && (*matcher4)(p4) && (*matcher5)(p5);
//	}
//
//	ReturnType Execute(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5)
//	{
//		return returns;
//	}
//
//	void SetParam(hamcrest::matcher<Param1> &p1, hamcrest::matcher<Param2> &p2, hamcrest::matcher<Param3> &p3, hamcrest::matcher<Param4> &p4, hamcrest::matcher<Param5> p5)
//	{
//		matcher1= &p1;
//		matcher2= &p2;
//		matcher3= &p3;
//		matcher4= &p4;
//		matcher5= &p5;
//	}
//
//	void SetReturn(ReturnType _returns)
//	{
//		returns= _returns;
//	}
//};

//
//template <class ReturnType, class Param1>
//class CallAction<ReturnType, Param1&>
//{
//	Param1 param1;
//	ReturnType returns;
//public:
//
//	Param1 GetParam() { return param1; }
//	ReturnType GetReturn() { return returns; }
//	void SetParam(Param1 p1)
//	{
//		param1= p1;
//	}
//
//	void SetReturn(ReturnType _returns)
//	{
//		returns= _returns;
//	}
//};

} //namespace carnamock

#endif