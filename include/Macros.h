#pragma once
#ifndef INCLUDED_MACROS_H
#define INCLUDED_MACROS_H

#ifndef INCLUDED_MOCKMAP_H
#include "MockMap.h"
#endif

#ifndef INCLUDED_CALLREGISTRY_H
#include "CallRegistry.h"
#endif


#define VOID_METHOD0(returnType, methodName) \
   returnType methodName() { \
      MOCK_CONFIGURATIONS(methodName) \
      carna##methodName.Execute(); \
   } CallRegistry<returnType> carna##methodName 

#define VOID_METHOD1(returnType, methodName, p1) \
   returnType methodName(p1 p1Value) { \
      MOCK_CONFIGURATIONS(methodName) \
      carna##methodName.Execute(p1Value); \
   } CallRegistry<returnType, p1> carna##methodName

#define VOID_METHOD2(returnType, methodName, p1, p2) \
   returnType methodName(p1 p1Value, p2 p2Value) { \
      MOCK_CONFIGURATIONS(methodName) \
      carna##methodName.Execute(p1Value, p2Value); \
   } CallRegistry<returnType, p1, p2> carna##methodName

#define VOID_METHOD3(returnType, methodName, p1, p2, p3) \
   returnType methodName(p1 p1Value, p2 p2Value, p3 p3Value) { \
      MOCK_CONFIGURATIONS(methodName) \
      carna##methodName.Execute(p1Value, p2Value, p3Value); \
   } CallRegistry<returnType, p1, p2, p3> carna##methodName

#define VOID_METHOD4(returnType, methodName, p1, p2, p3, p4) \
   returnType methodName(p1 p1Value, p2 p2Value, p3 p3Value, p4 p4Value) { \
      MOCK_CONFIGURATIONS(methodName) \
      carna##methodName.Execute(p1Value, p2Value, p3Value, p4Value); \
   } CallRegistry<returnType, p1, p2, p3, p4> carna##methodName

#define RETURN_METHOD0(returnType, methodName) \
   returnType methodName() { \
      MOCK_CONFIGURATIONS(methodName) \
      return carna##methodName.Execute(); \
   } CallRegistry<returnType> carna##methodName

#define RETURN_METHOD0_CONST(returnType, methodName) \
   returnType methodName() const { \
	  MOCK_CONFIGURATIONS(methodName) \
	  return carna##methodName.Execute(); \
   } CallRegistry<returnType> carna##methodName

#define RETURN_METHOD1(returnType, methodName, p1) \
   returnType methodName(p1 p1Value) { \
      MOCK_CONFIGURATIONS(methodName) \
      return carna##methodName.Execute(p1Value); \
   } CallRegistry<returnType, p1> carna##methodName

#define RETURN_METHOD2(returnType, methodName, p1, p2) \
   returnType methodName(p1 p1Value, p2 p2Value) { \
      MOCK_CONFIGURATIONS(methodName) \
      return carna##methodName.Execute(p1Value, p2Value); \
   } CallRegistry<returnType, p1, p2> carna##methodName

#define RETURN_METHOD3(returnType, methodName, p1, p2, p3) \
   returnType methodName(p1 p1Value, p2 p2Value, p3 p3Value) { \
      MOCK_CONFIGURATIONS(methodName) \
      return carna##methodName.Execute(p1Value, p2Value, p3Value); \
   } CallRegistry<returnType, p1, p2, p3> carna##methodName

#define RETURN_METHOD4(returnType, methodName, p1, p2, p3, p4) \
   returnType methodName(p1 p1Value, p2 p2Value, p3 p3Value, p4 p4Value) { \
      MOCK_CONFIGURATIONS(methodName) \
      return carna##methodName.Execute(p1Value, p2Value, p3Value, p4Value); \
   } CallRegistry<returnType, p1, p2, p3, p4> carna##methodName

#define EXPECT(instance, methodName) \
   (instance).carna##methodName.SetMethodName(#methodName); \
   (instance).carna##methodName.VerifyOnDestructor(!carnamock::internal::MockMap::IsNiceMock(&instance)); \
   (instance).carna##methodName.SetOwner(&instance); \
   (instance).carna##methodName.ThrowsOnError(!carnamock::internal::MockMap::IsNiceReportMock(&instance)); \
   (instance).carna##methodName.Expect()

#define WHEN_CALL(instance, methodName) \
   (instance).carna##methodName.WhenCall()

#define MOCK_CONFIGURATIONS(methodName) \
   carna##methodName.VerifyOnDestructor(!carnamock::internal::MockMap::IsNiceMock(this)); \
   carna##methodName.SetOwner(this); \
   carna##methodName.ThrowsOnError(!carnamock::internal::MockMap::IsNiceReportMock(this)); \
   carna##methodName.SetMethodName(#methodName); \

#endif