// ---------------------------------------------------------------------------
// MP2ENCODERIMPL : Implementation of TMp2EncoderImpl (CoClass: Mp2Encoder, Interface: IMp2Encoder)
// ---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Mp2EncoderImpl.h"


// ---------------------------------------------------------------------------
// TMp2EncoderImpl
// ---------------------------------------------------------------------------
__fastcall TMp2EncoderImpl::TMp2EncoderImpl()
{
}


// ---------------------------------------------------------------------------
// TMp2EncoderImpl
// ---------------------------------------------------------------------------
__fastcall TMp2EncoderImpl::TMp2EncoderImpl(const System::_di_IInterface Controller)
                              : inherited(Controller)
{
}


// ---------------------------------------------------------------------------
// TMp2EncoderImpl
// ---------------------------------------------------------------------------
__fastcall TMp2EncoderImpl::TMp2EncoderImpl(Comobj::TComObjectFactory* Factory,
                                      const System::_di_IInterface Controller)
                              : inherited(Factory, Controller)
{
}

// ---------------------------------------------------------------------------
// TMp2EncoderImpl - Class Factory
// ---------------------------------------------------------------------------
static void createFactory()
{
  new TCppComObjectFactory<TMp2EncoderImpl>(Comserv::GetComServer(),
                           __classid(TMp2EncoderImpl),
                           CLSID_Mp2Encoder,
                           "TMp2EncoderImpl",
                           "",
                           Comobj::ciMultiInstance,
                           Comobj::tmBoth);
}
#pragma startup createFactory 32



