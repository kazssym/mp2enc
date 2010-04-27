//$$---- ATL unit HDR ---- (stATLUnitHdr)
//---------------------------------------------------------------------------


#ifndef mp2dmoe_ATLH
#define mp2dmoe_ATLH

// Check if we're using ATLVCL
//
#if defined(USING_ATLVCL)

// To get declaration of _Module
//
#include <atl\atlvcl.h>

#elif defined(USING_ATL)

// Light-weight ATL support
//

#include <utilcls.h>	// _ASSERTE
#include <atlbase.h>

// ノート: TComModule の派生クラスを作成し、サーバーモジュールにできます
//         （インスタンスを _Module にアサインできます）
//         但し _Module の名前を変えてはいけません
//
extern CComModule &_Module;

#include <atlcom.h>
#include <shellapi.h>

#endif


#endif	// Project1_ATLH
