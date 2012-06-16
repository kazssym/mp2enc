// ---------------------------------------------------------------------------
// Mp2EncoderImpl.h : Declaration of the TMp2EncoderImpl
// ---------------------------------------------------------------------------
#ifndef Mp2EncoderImplH
#define Mp2EncoderImplH

#include <ComServ.hpp>
#include <axbase.h>
#include "mp2dmoe_TLB.h"

// ---------------------------------------------------------------------------
// TMp2EncoderImpl     Implements IMp2Encoder, default interface of Mp2Encoder
// ThreadingModel : tmBoth
// Dual Interface : FALSE
// Event Support  : FALSE
// Description    : 
// ---------------------------------------------------------------------------
class DAX_COM_CLASS TMp2EncoderImpl : public TCppComObject<IMp2Encoder>
{
  typedef _COM_CLASS inherited;

public:
  __fastcall TMp2EncoderImpl();
  __fastcall TMp2EncoderImpl(const System::_di_IInterface Controller);
  __fastcall TMp2EncoderImpl(Comobj::TComObjectFactory* Factory, const System::_di_IInterface Controller);
  

  // IMp2Encoder
protected:
};




#endif //Mp2EncoderImplH

