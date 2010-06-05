//$$---- ATL unit HDR ---- (stATLUnitHdr)
//---------------------------------------------------------------------------


#ifndef id3mux_ATLH
#define id3mux_ATLH

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

// �m�[�g: TComModule �̔h���N���X���쐬���A�T�[�o�[���W���[���ɂł��܂�
//         �i�C���X�^���X�� _Module �ɃA�T�C���ł��܂��j
//         �A�� _Module �̖��O��ς��Ă͂����܂���
//
extern TComModule &_Module;

#include <atlcom.h>
#include <shellapi.h>

#endif


#endif	// Project1_ATLH