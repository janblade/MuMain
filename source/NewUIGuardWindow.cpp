// NewUIGuardWindow.cpp: implementation of the CNewUIGuardWindow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NewUIGuardWindow.h"
#include "NewUISystem.h"
#include "NewUICustomMessageBox.h"
#include "ZzzBMD.h"
#include "ZzzEffect.h"
#include "ZzzObject.h"
#include "ZzzInventory.h"
#include "ZzzInterface.h"
#include "ZzzInfomation.h"
#include "ZzzCharacter.h"
#include "wsclientinline.h"
#include "DSPlaySound.h"
#include "UIGuildInfo.h"
#include "UIGuardsMan.h"

using namespace SEASON3B;

extern DWORD g_dwActiveUIID;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNewUIGuardWindow::CNewUIGuardWindow()
{
	m_pNewUIMng = NULL;
	m_Pos.x = m_Pos.y = 0;
	m_iNumCurOpenTab = TAB_SIEGE_INFO;
}

CNewUIGuardWindow::~CNewUIGuardWindow()
{
	Release();
}

bool CNewUIGuardWindow::Create(CNewUIManager* pNewUIMng, int x, int y)
{
	if(NULL == pNewUIMng)
		return false;

	m_pNewUIMng = pNewUIMng;
	m_pNewUIMng->AddUIObj(SEASON3B::INTERFACE_GUARDSMAN, this);

	SetPos(x, y);

	LoadImages();

	list<unicode::t_string> ltext;
	ltext.push_back(GlobalText[1448]);
	ltext.push_back(GlobalText[1439]);
	ltext.push_back(GlobalText[1449]);

	m_TabBtn.CreateRadioGroup( 3, IMAGE_GUARDWINDOW_TAB_BTN );
	m_TabBtn.ChangeRadioText(ltext);
	m_TabBtn.ChangeRadioButtonInfo(true, m_Pos.x+12.f, m_Pos.y+84.f, 56, 22 );
	m_TabBtn.ChangeFrame( m_iNumCurOpenTab );

	m_BtnExit.ChangeButtonImgState(true, IMAGE_GUARDWINDOW_EXIT_BTN, false);
	m_BtnExit.ChangeButtonInfo(m_Pos.x+13, m_Pos.y+391, 36, 29);
	m_BtnExit.ChangeToolTipText(GlobalText[1002], true); // 225 "닫기(I,V)"

	InitButton(&m_BtnProclaim, m_Pos.x + INVENTORY_WIDTH / 2 - 27, m_Pos.y + 120, GlobalText[1435]);
	InitButton(&m_BtnRegister, m_Pos.x + INVENTORY_WIDTH / 2 - 27, m_Pos.y + 200, GlobalText[1439]);
	InitButton(&m_BtnGiveUp, m_Pos.x + INVENTORY_WIDTH / 2 - 27, m_Pos.y + 370, GlobalText[1549]);
	
	Show(false);

	return true;
}

void CNewUIGuardWindow::InitButton(CNewUIButton * pNewUIButton, int iPos_x, int iPos_y, const unicode::t_char * pCaption)
{
	pNewUIButton->ChangeText(pCaption);
	pNewUIButton->ChangeTextBackColor(RGBA(255,255,255,0));
	pNewUIButton->ChangeButtonImgState( true, IMAGE_GUARDWINDOW_BUTTON, true );
	pNewUIButton->ChangeButtonInfo(iPos_x, iPos_y, 53, 23);
	pNewUIButton->ChangeImgColor(BUTTON_STATE_UP, RGBA(255, 255, 255, 255));
	pNewUIButton->ChangeImgColor(BUTTON_STATE_DOWN, RGBA(255, 255, 255, 255));
}

void CNewUIGuardWindow::Release()
{
	UnloadImages();

	if(m_pNewUIMng)
	{
		m_pNewUIMng->RemoveUIObj(this);
		m_pNewUIMng = NULL;
	}
}

void CNewUIGuardWindow::SetPos(int x, int y)
{
	m_Pos.x = x;
	m_Pos.y = y;
}

bool CNewUIGuardWindow::UpdateMouseEvent()
{
	switch(m_iNumCurOpenTab)
	{
	case TAB_SIEGE_INFO:
		UpdateSeigeInfoTab();
		break;
	case TAB_REGISTER:
		UpdateRegisterTab();
		break;
	case TAB_REGISTER_INFO:
		UpdateRegisterInfoTab();
		break;
	}

	//. 버튼 처리
	if(true == BtnProcess())	//. 처리가 완료 되었다면
		return false;

	//. 인벤토리 내의 영역 클릭시 하위 UI처리 및 이동 불가
	if(CheckMouseIn(m_Pos.x, m_Pos.y, INVENTORY_WIDTH, INVENTORY_HEIGHT))
		return false;

	return true;
}

bool CNewUIGuardWindow::UpdateKeyEvent()
{
	if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_GUARDSMAN) == true)
	{
		if(SEASON3B::IsPress(VK_ESCAPE) == true)
		{
			g_pNewUISystem->Hide(SEASON3B::INTERFACE_GUARDSMAN);
			PlayBuffer(SOUND_CLICK01);

			return false;
		}
	}
	return true;
}

bool CNewUIGuardWindow::Update()
{
	if(IsVisible())
	{
		int iNumCurOpenTab = m_TabBtn.UpdateMouseEvent();
		
		if( iNumCurOpenTab == RADIOGROUPEVENT_NONE )	// 탭 버튼의 변경이 없을시에는 Update skip
			return true;
		
		m_iNumCurOpenTab = iNumCurOpenTab;

		if (iNumCurOpenTab == TAB_REGISTER_INFO)
		{
			if( m_eTimeType == CASTLESIEGE_STATE_REGSIEGE || m_eTimeType == CASTLESIEGE_STATE_REGMARK )
			{
				SendRequestBCDeclareGuildList();
			}
			else if( m_eTimeType == CASTLESIEGE_STATE_NOTIFY || m_eTimeType == CASTLESIEGE_STATE_READYSIEGE )
			{
				SendRequestBCGuildList();
			}
		}
	}
	return true;
}
bool CNewUIGuardWindow::Render()
{
	EnableAlphaTest();
	glColor4f(1.f, 1.f, 1.f, 1.f);
	
	RenderFrame();
	
	static list<unicode::t_string> ltext;
	if( m_eTimeType == CASTLESIEGE_STATE_REGSIEGE )
	{
		ltext.push_back(GlobalText[1448]);
		ltext.push_back(GlobalText[1435]);	// 1435 "선포하기"
		ltext.push_back(GlobalText[1449]);
	}
	else
	{
		ltext.push_back(GlobalText[1448]);
		ltext.push_back(GlobalText[1439]);	// 1439 "표식등록하기"
		ltext.push_back(GlobalText[1449]);
	}
	m_TabBtn.ChangeRadioText(ltext);

	m_TabBtn.Render();

	switch(m_iNumCurOpenTab)
	{
	case TAB_SIEGE_INFO:
		RenderSeigeInfoTab();
		break;
	case TAB_REGISTER:
		RenderRegisterTab();
		break;
	case TAB_REGISTER_INFO:
		RenderRegisterInfoTab();
		break;
	}
	
	// 닫기 버튼 표시
	m_BtnExit.Render();

	DisableAlphaBlend();

	return true;
}

void CNewUIGuardWindow::OpeningProcess()
{
	m_iNumCurOpenTab = TAB_SIEGE_INFO;
	m_TabBtn.ChangeFrame(TAB_SIEGE_INFO);
	
	SendRequestBCRegInfo();
}

void CNewUIGuardWindow::ClosingProcess()
{
	m_DeclareGuildListBox.Clear();
	m_GuildListBox.Clear();

	SendExitInventory();
}

float CNewUIGuardWindow::GetLayerDepth()
{ return 5.0f; }

void CNewUIGuardWindow::LoadImages()
{
	LoadBitmap("Interface\\newui_msgbox_back.jpg", IMAGE_GUARDWINDOW_BACK, GL_LINEAR);
	LoadBitmap("Interface\\newui_item_back01.tga", IMAGE_GUARDWINDOW_TOP, GL_LINEAR);
	LoadBitmap("Interface\\newui_item_back02-L.tga", IMAGE_GUARDWINDOW_LEFT, GL_LINEAR);
	LoadBitmap("Interface\\newui_item_back02-R.tga", IMAGE_GUARDWINDOW_RIGHT, GL_LINEAR);
	LoadBitmap("Interface\\newui_item_back03.tga", IMAGE_GUARDWINDOW_BOTTOM, GL_LINEAR);
	LoadBitmap("Interface\\newui_exit_00.tga", IMAGE_GUARDWINDOW_EXIT_BTN, GL_LINEAR);
	LoadBitmap("Interface\\newui_guild_tab04.tga", IMAGE_GUARDWINDOW_TAB_BTN, GL_LINEAR);
	LoadBitmap("Interface\\newui_btn_empty_very_small.tga", IMAGE_GUARDWINDOW_BUTTON, GL_LINEAR);

	LoadBitmap("Interface\\newui_item_table03(Up).tga", IMAGE_GUARDWINDOW_TOP_PIXEL, GL_LINEAR);
	LoadBitmap("Interface\\newui_item_table03(Dw).tga", IMAGE_GUARDWINDOW_BOTTOM_PIXEL, GL_LINEAR);
	LoadBitmap("Interface\\newui_item_table03(L).tga", IMAGE_GUARDWINDOW_LEFT_PIXEL, GL_LINEAR);
	LoadBitmap("Interface\\newui_item_table03(R).tga", IMAGE_GUARDWINDOW_RIGHT_PIXEL, GL_LINEAR);

	LoadBitmap("Interface\\newui_scrollbar_up.tga", IMAGE_GUARDWINDOW_SCROLL_TOP);
	LoadBitmap("Interface\\newui_scrollbar_m.tga", IMAGE_GUARDWINDOW_SCROLL_MIDDLE);
	LoadBitmap("Interface\\newui_scrollbar_down.tga", IMAGE_GUARDWINDOW_SCROLL_BOTTOM);
	LoadBitmap("Interface\\newui_scroll_on.tga", IMAGE_GUARDWINDOW_SCROLLBAR_ON, GL_LINEAR);
	LoadBitmap("Interface\\newui_scroll_off.tga", IMAGE_GUARDWINDOW_SCROLLBAR_OFF, GL_LINEAR);
}
void CNewUIGuardWindow::UnloadImages()
{
	DeleteBitmap(IMAGE_GUARDWINDOW_BOTTOM);
	DeleteBitmap(IMAGE_GUARDWINDOW_RIGHT);
	DeleteBitmap(IMAGE_GUARDWINDOW_LEFT);
	DeleteBitmap(IMAGE_GUARDWINDOW_TOP);
	DeleteBitmap(IMAGE_GUARDWINDOW_BACK);
	DeleteBitmap(IMAGE_GUARDWINDOW_EXIT_BTN);
	DeleteBitmap(IMAGE_GUARDWINDOW_TAB_BTN);
	DeleteBitmap(IMAGE_GUARDWINDOW_BUTTON);

	DeleteBitmap(IMAGE_GUARDWINDOW_TOP_PIXEL);
	DeleteBitmap(IMAGE_GUARDWINDOW_BOTTOM_PIXEL);
	DeleteBitmap(IMAGE_GUARDWINDOW_RIGHT_PIXEL);
	DeleteBitmap(IMAGE_GUARDWINDOW_LEFT_PIXEL);

	DeleteBitmap(IMAGE_GUARDWINDOW_SCROLL_TOP);
	DeleteBitmap(IMAGE_GUARDWINDOW_SCROLL_MIDDLE);
	DeleteBitmap(IMAGE_GUARDWINDOW_SCROLL_BOTTOM);
	DeleteBitmap(IMAGE_GUARDWINDOW_SCROLLBAR_ON);
	DeleteBitmap(IMAGE_GUARDWINDOW_SCROLLBAR_OFF);
}

void CNewUIGuardWindow::RenderFrame()
{
	RenderImage(IMAGE_GUARDWINDOW_BACK, m_Pos.x, m_Pos.y, 190.f, 429.f);
	RenderImage(IMAGE_GUARDWINDOW_TOP, m_Pos.x, m_Pos.y, 190.f, 64.f);
	RenderImage(IMAGE_GUARDWINDOW_LEFT, m_Pos.x, m_Pos.y+64, 21.f, 320.f);
	RenderImage(IMAGE_GUARDWINDOW_RIGHT, m_Pos.x+INVENTORY_WIDTH-21, m_Pos.y+64, 21.f, 320.f);
	RenderImage(IMAGE_GUARDWINDOW_BOTTOM, m_Pos.x, m_Pos.y+INVENTORY_HEIGHT-45, 190.f, 45.f);

	unicode::t_char szText[256] = { 0, };
	float fPos_x = m_Pos.x + 15.0f, fPos_y = m_Pos.y;
	float fLine_y = 13.0f;

	g_pRenderText->SetFont(g_hFontBold);
	g_pRenderText->SetTextColor(220, 220, 220, 255);
	g_pRenderText->SetBgColor(0, 0, 0, 0);

	// 창 제목 표시
	unicode::_sprintf(szText, "%s", GlobalText[1445]);
	g_pRenderText->RenderText(fPos_x, fPos_y + fLine_y, szText, 160.0f, 0, RT3_SORT_CENTER);

	POINT ptOrigin = { m_Pos.x, m_Pos.y+50 };
	g_pRenderText->SetFont(g_hFontBold);
	
	if( m_szOwnerGuildMaster[0] )
	{
		unicode::_sprintf( szText, GlobalText[1446], m_szOwnerGuildMaster );	// 1446 "왕의 직인 : %s"
	}
	else
	{
		unicode::_sprintf( szText, GlobalText[1446], GlobalText[1361] );		// 1446 "왕의 직인 : %s"
	}
	g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, szText, 190, 0, RT3_SORT_CENTER);
	
	ptOrigin.y += 15;
	if( m_szOwnerGuild[0] )
	{
		unicode::_sprintf( szText, GlobalText[1447], m_szOwnerGuild );			// 1447 "소속길드 : %s"
	}
	else
	{
		unicode::_sprintf( szText, GlobalText[1447], GlobalText[1361] );		// 1447 "소속길드 : %s"
	}

	g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, szText, 190, 0, RT3_SORT_CENTER);
}

bool CNewUIGuardWindow::BtnProcess()
{
	POINT ptExitBtn1 = { m_Pos.x+169, m_Pos.y+7 };
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	POINT ptExitBtn2 = { m_Pos.x+13, m_Pos.y+391 };
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX

	//. Exit1 버튼 (기본처리)
	if(SEASON3B::IsPress(VK_LBUTTON) && CheckMouseIn(ptExitBtn1.x, ptExitBtn1.y, 13, 12))
	{
		g_pNewUISystem->Hide(SEASON3B::INTERFACE_GUARDSMAN);
	}

	// 닫기 버튼
	if(m_BtnExit.UpdateMouseEvent() == true)
	{
		g_pNewUISystem->Hide(SEASON3B::INTERFACE_GUARDSMAN);
		return true;
	}

	return false;
}

void CNewUIGuardWindow::UpdateSeigeInfoTab()
{
}

void CNewUIGuardWindow::UpdateRegisterTab()
{
	switch( m_eTimeType )
	{
	case CASTLESIEGE_STATE_REGSIEGE:	// 신청기간
		if (m_BtnProclaim.UpdateMouseEvent() == true)
		{
			if( g_GuardsMan.IsSufficentDeclareLevel() )
			{
				// 공성전 등록 요청
				SendRequestBCReg();
			}
			else
			{
				// 레벨 제한 200 표시
				SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CSiegeLevelMsgBoxLayout));
			}
		}
		break;
	case CASTLESIEGE_STATE_REGMARK:		// 표식등록 기간
		if (m_BtnRegister.UpdateMouseEvent() == true)
		{
			int nMarkSlot = g_GuardsMan.GetMyMarkSlotIndex();
			if( nMarkSlot != -1 )
				SendRequestBCRegMark( nMarkSlot );
		}
		break;
	}
}

void CNewUIGuardWindow::UpdateRegisterInfoTab()
{
	if( m_eTimeType == CASTLESIEGE_STATE_REGSIEGE || m_eTimeType == CASTLESIEGE_STATE_REGMARK )
	{
		//g_dwActiveUIID = m_DeclareGuildListBox.GetUIID();
		m_DeclareGuildListBox.DoAction();
		//g_dwActiveUIID = 0;
		if(PressKey(VK_PRIOR))
			m_DeclareGuildListBox.Scrolling(-1 * m_DeclareGuildListBox.GetBoxSize());
		if(PressKey(VK_NEXT))
			m_DeclareGuildListBox.Scrolling(m_DeclareGuildListBox.GetBoxSize());
	}
	else if( m_eTimeType == CASTLESIEGE_STATE_NOTIFY || m_eTimeType == CASTLESIEGE_STATE_READYSIEGE )
	{
		//g_dwActiveUIID = m_DeclareGuildListBox.GetUIID();
		m_GuildListBox.DoAction();
		//g_dwActiveUIID = 0;
		if(PressKey(VK_PRIOR))
			m_GuildListBox.Scrolling(-1 * m_GuildListBox.GetBoxSize());
		if(PressKey(VK_NEXT))
			m_GuildListBox.Scrolling(m_GuildListBox.GetBoxSize());
	}
	
	// 공성 등록상태일때 포기가능 기간에만 포기버튼 표시
	if( g_GuardsMan.HasRegistered() &&
		CASTLESIEGE_STATE_REGSIEGE <= m_eTimeType && m_eTimeType <= CASTLESIEGE_STATE_REGMARK 
		&& Hero->GuildStatus == G_MASTER)
	{
		if (m_BtnGiveUp.UpdateMouseEvent() == true)
		{
			// 공성전 포기
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CSiegeGiveUpMsgBoxLayout));
		}
	}
}

void CNewUIGuardWindow::RenderSeigeInfoTab()
{
	POINT ptOrigin = { m_Pos.x, m_Pos.y+125 };
	unicode::t_char szTemp[256];

	g_pRenderText->SetFont(g_hFont);
	// 1533 "%u-%u-%u %u : %u 부터"
	sprintf( szTemp, GlobalText[1533], m_wStartYear, m_byStartMonth, m_byStartDay, m_byStartHour, m_byStartMinute );
	g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, szTemp, 190, 0, RT3_SORT_CENTER);
	
	ptOrigin.y += 14;
	// 1534 "%u-%u-%u %u : %u 까지는"
	sprintf( szTemp, GlobalText[1534], m_wEndYear, m_byEndMonth, m_byEndDay, m_byEndHour, m_byEndMinute );
	g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, szTemp, 190, 0, RT3_SORT_CENTER);
	
	ptOrigin.y += 14;
	// 현재 공성상태 표시
	switch( m_eTimeType )
	{
	case CASTLESIEGE_STATE_NONE:		// 상태없음
	case CASTLESIEGE_STATE_IDLE_1:		// 신청대기 기간		// 1535 "공성기간이 아닙니다."
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y,  GlobalText[1535], 190, 0, RT3_SORT_CENTER);
		break;
	case CASTLESIEGE_STATE_REGSIEGE:	// 신청기간				// 1536 "공성신청 기간입니다."
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y,  GlobalText[1536], 190, 0, RT3_SORT_CENTER);
		break;
	case CASTLESIEGE_STATE_IDLE_2:		// 표식등록 대기기간	// 1537 "표식등록 대기기간입니다."
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y,  GlobalText[1537], 190, 0, RT3_SORT_CENTER);
		break;
	case CASTLESIEGE_STATE_REGMARK:		// 표식등록 기간		// 1538 "표식등록 기간입니다."
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y,  GlobalText[1538], 190, 0, RT3_SORT_CENTER);
		break;
	case CASTLESIEGE_STATE_IDLE_3:		// 발표 대기기간		// 1539 "발표 대기기간입니다."
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y,  GlobalText[1539], 190, 0, RT3_SORT_CENTER);
		break;
	case CASTLESIEGE_STATE_NOTIFY:		// 발표 기간			// 1540 "발표 기간입니다."
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y,  GlobalText[1540], 190, 0, RT3_SORT_CENTER);
		break;
	case CASTLESIEGE_STATE_READYSIEGE:	// 공성준비 기간		// 1541 "공성준비 기간입니다."
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y,  GlobalText[1541], 190, 0, RT3_SORT_CENTER);
		break;
	case CASTLESIEGE_STATE_STARTSIEGE:	// 공성 기간			// 1542 "공성 기간입니다."
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y,  GlobalText[1542], 190, 0, RT3_SORT_CENTER);
		break;
	case CASTLESIEGE_STATE_ENDSIEGE:	// 휴전 기간			// 1543 "휴전 기간입니다."
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y,  GlobalText[1543], 190, 0, RT3_SORT_CENTER);
		break;
	case CASTLESIEGE_STATE_ENDCYCLE:	// 공성주기 종료		// 1544 "공성이 끝났습니다."
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y,  GlobalText[1544], 190, 0, RT3_SORT_CENTER);
		break;
	}

	if( m_eTimeType < CASTLESIEGE_STATE_STARTSIEGE )
	{
		ptOrigin.y += 35;
		// 1545 "공성 예상 시기는"
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y,  GlobalText[1545], 190, 0, RT3_SORT_CENTER);

		ptOrigin.y += 14;
		// 1546 "%u-%u-%u %u : %u 입니다."
		sprintf( szTemp, GlobalText[1546], m_wSiegeStartYear, m_bySiegeStartMonth, m_bySiegeStartDay, m_bySiegeStartHour, m_bySiegeStartMinute );
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, szTemp, 190, 0, RT3_SORT_CENTER);

		ptOrigin.y += 35;
		// 1421 "다음 상태까지는 %u : %u : %u 남았습니다."
		sprintf( szTemp, GlobalText[1421], m_dwStateLeftSec/3600, (m_dwStateLeftSec%3600)/60, (m_dwStateLeftSec%3600)%60 );
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y,  szTemp, 190, 0, RT3_SORT_CENTER);
	}
}

void CNewUIGuardWindow::RenderRegisterTab()
{
 	POINT ptOrigin = { m_Pos.x, m_Pos.y+125 };
	g_pRenderText->SetFont(g_hFont);

	switch( m_eTimeType )
	{
	case CASTLESIEGE_STATE_NONE:		// 상태없음
	case CASTLESIEGE_STATE_IDLE_1:		// 신청대기 기간
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, GlobalText[1535], 190, 0, RT3_SORT_CENTER);	// 1535 "공성기간이 아닙니다."
		break;
	case CASTLESIEGE_STATE_REGSIEGE:	// 신청기간
 		if( Hero->GuildStatus == G_MASTER )
 		{
			if(!g_GuardsMan.HasRegistered())
			{
				// 수성측 연합에 속해있다면 선포불가
				if( !strcmp( GuildMark[Hero->GuildMarkIndex].UnionName, m_szOwnerGuild )
					|| !strcmp( GuildMark[Hero->GuildMarkIndex].GuildName, m_szOwnerGuild ) )
				{
					m_BtnProclaim.Lock();
					m_BtnProclaim.ChangeImgColor(BUTTON_STATE_UP, RGBA(100, 100, 100, 255));
					m_BtnProclaim.ChangeTextColor(RGBA(100, 100, 100, 255));
				}
				else
				{
					m_BtnProclaim.UnLock();
					m_BtnProclaim.ChangeImgColor(BUTTON_STATE_UP, RGBA(255, 255, 255, 255));
					m_BtnProclaim.ChangeTextColor(RGBA(255, 255, 255, 255));
				}
				m_BtnProclaim.Render();
			}
			else
			{
				g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, GlobalText[1547], 190, 0, RT3_SORT_CENTER);	// 1547 "선포되었습니다"
			}
		}
		else
		{
			g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, GlobalText[1320], 190, 0, RT3_SORT_CENTER);	// 1320 "길드마스터가 아닙니다."
		}
		break;
	case CASTLESIEGE_STATE_IDLE_2:		// 표식등록 대기기간
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, GlobalText[1548], 190, 0, RT3_SORT_CENTER);	// 1548 "표식등록 대기기간입니다."
		break;
	case CASTLESIEGE_STATE_REGMARK:		// 표식등록 기간
		{
			if(g_GuardsMan.HasRegistered())
			{
				// 1436 "획득한 표식을 등록하세요."
				g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, GlobalText[1436], 190, 0, RT3_SORT_CENTER);
				ptOrigin.y += 30;

				int nMarkCount = g_GuardsMan.GetMyMarkCount();
				unicode::t_char szBuffer[256];
				unicode::_sprintf( szBuffer, GlobalText[1437], nMarkCount );	// 1437 "습득한 표식수 : %u"
				g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, szBuffer, 190, 0, RT3_SORT_CENTER);
				
				ptOrigin.y += 14;
				unicode::_sprintf( szBuffer, GlobalText[1438], g_GuardsMan.GetRegMarkCount() );	// 1438 "등록한 표식수 : %u"
				g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, szBuffer, 190, 0, RT3_SORT_CENTER);

				if( nMarkCount > 0 )
				{
					m_BtnRegister.UnLock();
					m_BtnRegister.ChangeImgColor(BUTTON_STATE_UP, RGBA(255, 255, 255, 255));
					m_BtnRegister.ChangeTextColor(RGBA(255, 255, 255, 255));
				}
				else
				{
					m_BtnRegister.ChangeImgColor(BUTTON_STATE_UP, RGBA(100, 100, 100, 255));
					m_BtnRegister.ChangeTextColor(RGBA(100, 100, 100, 255));
					m_BtnRegister.Lock();
				}
				m_BtnRegister.Render();
			}
			else
			{
				// 1514 "공성전에 등록된 길드가 아닙니다."
				g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, GlobalText[1514], 190, 0, RT3_SORT_CENTER);	// 1514 "공성전에 등록된 길드가 아닙니다."
			}
		}
		break;
	case CASTLESIEGE_STATE_IDLE_3:		// 발표 대기기간
		g_pRenderText->SetFont(g_hFontBold);
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, GlobalText[1440], 190, 0, RT3_SORT_CENTER);
		ptOrigin.y += 14;
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, GlobalText[1441], 190, 0, RT3_SORT_CENTER);
		break;
	case CASTLESIEGE_STATE_NOTIFY:		// 발표 기간
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, GlobalText[1540], 190, 0, RT3_SORT_CENTER);
		break;
	case CASTLESIEGE_STATE_READYSIEGE:	// 공성준비 기간
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, GlobalText[1541], 190, 0, RT3_SORT_CENTER);
		break;
	case CASTLESIEGE_STATE_STARTSIEGE:	// 공성 기간
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, GlobalText[1542], 190, 0, RT3_SORT_CENTER);
		break;
	case CASTLESIEGE_STATE_ENDSIEGE:	// 휴전 기간
		g_pRenderText->SetFont(g_hFontBold);
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, GlobalText[1442], 190, 0, RT3_SORT_CENTER);
		break;
	case CASTLESIEGE_STATE_ENDCYCLE:	// 공성주기 종료
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, GlobalText[1544], 190, 0, RT3_SORT_CENTER);
		break;
	}
}

void CNewUIGuardWindow::RenderRegisterInfoTab()
{
	POINT ptOrigin = { m_Pos.x, m_Pos.y+125 };
	g_pRenderText->SetFont(g_hFontBold);
	
	// 신청기간, 문장 등록기간
	if( m_eTimeType == CASTLESIEGE_STATE_REGSIEGE || m_eTimeType == CASTLESIEGE_STATE_REGMARK )
	{
		EnableAlphaTest();
		// 테두리
		RenderImage(IMAGE_GUARDWINDOW_LEFT_PIXEL, ptOrigin.x+11, ptOrigin.y-14, 14, 255);
		RenderImage(IMAGE_GUARDWINDOW_RIGHT_PIXEL, ptOrigin.x+166, ptOrigin.y-14, 14, 255);
		RenderImage(IMAGE_GUARDWINDOW_TOP_PIXEL, ptOrigin.x+14, ptOrigin.y-14, 161, 14);
		RenderImage(IMAGE_GUARDWINDOW_BOTTOM_PIXEL, ptOrigin.x+14, ptOrigin.y+232, 161, 14);
		DisableAlphaBlend();

		m_DeclareGuildListBox.Render();
	}
	// 발표기간, 준비기간
	else if( m_eTimeType == CASTLESIEGE_STATE_NOTIFY || m_eTimeType == CASTLESIEGE_STATE_READYSIEGE )
	{
		EnableAlphaTest();
		// 테두리
		RenderImage(IMAGE_GUARDWINDOW_LEFT_PIXEL, ptOrigin.x+11, ptOrigin.y-14, 14, 215);
		RenderImage(IMAGE_GUARDWINDOW_RIGHT_PIXEL, ptOrigin.x+166, ptOrigin.y-14, 14, 215);
		RenderImage(IMAGE_GUARDWINDOW_TOP_PIXEL, ptOrigin.x+14, ptOrigin.y-14, 161, 14);
		RenderImage(IMAGE_GUARDWINDOW_BOTTOM_PIXEL, ptOrigin.x+14, ptOrigin.y+192, 161, 14);

		RenderImage(IMAGE_GUARDWINDOW_LEFT_PIXEL, ptOrigin.x+11, ptOrigin.y+220, 14, 25);
		RenderImage(IMAGE_GUARDWINDOW_RIGHT_PIXEL, ptOrigin.x+166, ptOrigin.y+220, 14, 25);
		RenderImage(IMAGE_GUARDWINDOW_TOP_PIXEL, ptOrigin.x+14, ptOrigin.y+220, 161, 14);
		RenderImage(IMAGE_GUARDWINDOW_BOTTOM_PIXEL, ptOrigin.x+14, ptOrigin.y+237, 161, 14);
		DisableAlphaBlend();

		m_GuildListBox.Render();
	}
	// 공성기간
	else if( m_eTimeType == CASTLESIEGE_STATE_NOTIFY )
	{
		unicode::t_char szBuffer[256];
		unicode::_sprintf( szBuffer, GlobalText[1443], 1, 1 );	// 1443 "공성전이 %d월 %d일"
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, szBuffer, 190, 0, RT3_SORT_CENTER);
		ptOrigin.y += 14;
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, GlobalText[1444], 190, 0, RT3_SORT_CENTER);
	}
	// 휴전기간
	else if( m_eTimeType == CASTLESIEGE_STATE_ENDSIEGE )
	{
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, GlobalText[1442], 190, 0, RT3_SORT_CENTER);
	}

	// 공성 등록상태일때 포기가능 기간에만 포기버튼 표시
	if( g_GuardsMan.HasRegistered() &&
		CASTLESIEGE_STATE_REGSIEGE <= m_eTimeType && m_eTimeType <= CASTLESIEGE_STATE_REGMARK 
		&& Hero->GuildStatus == G_MASTER)
	{
		m_BtnGiveUp.Render();
	}
}

void CNewUIGuardWindow::SetData( LPPMSG_ANS_CASTLESIEGESTATE Info )
{
	if( !Info )	return;

	memset(m_szOwnerGuild, 0, sizeof(char)*9);
	memset(m_szOwnerGuildMaster, 0, sizeof(char)*11);

	m_eTimeType = (CASTLESIEGE_STATE)Info->cCastleSiegeState;
	strncpy( m_szOwnerGuild, Info->cOwnerGuild, sizeof(char)*8 );
	strncpy( m_szOwnerGuildMaster, Info->cOwnerGuildMaster, sizeof(char)*10 );

	m_wStartYear = MAKEWORD( Info->btStartYearL, Info->btStartYearH );
	m_byStartMonth = Info->btStartMonth;
	m_byStartDay = Info->btStartDay;
	m_byStartHour = Info->btStartHour;
	m_byStartMinute = Info->btStartMinute;
	m_wEndYear = MAKEWORD( Info->btEndYearL, Info->btEndYearH );
	m_byEndMonth = Info->btEndMonth;
	m_byEndDay = Info->btEndDay;
	m_byEndHour = Info->btEndHour;
	m_byEndMinute = Info->btEndMinute;
	m_wSiegeStartYear = MAKEWORD( Info->btSiegeStartYearL, Info->btSiegeStartYearH );
	m_bySiegeStartMonth = Info->btSiegeStartMonth;
	m_bySiegeStartDay = Info->btSiegeStartDay;
	m_bySiegeStartHour = Info->btSiegeStartHour;
	m_bySiegeStartMinute = Info->btSiegeStartMinute;
	m_dwStateLeftSec = MAKELONG( MAKEWORD(Info->btStateLeftSec4,Info->btStateLeftSec3), MAKEWORD(Info->btStateLeftSec2,Info->btStateLeftSec1) );
	//m_dwStateLeftSec = Info->btStateLeftSec1<<24 | Info->btStateLeftSec2<<16 | Info->btStateLeftSec3<<8 | Info->btStateLeftSec4;
}

void CNewUIGuardWindow::AddDeclareGuildList( char* szGuildName, int nMarkCount, BYTE byIsGiveUP, BYTE bySeqNum )
{
	m_DeclareGuildListBox.AddText( szGuildName, nMarkCount, byIsGiveUP, bySeqNum );
}

void CNewUIGuardWindow::ClearDeclareGuildList()
{
	m_DeclareGuildListBox.Clear();
}

void CNewUIGuardWindow::SortDeclareGuildList()
{
	m_DeclareGuildListBox.Sort();
}

void CNewUIGuardWindow::AddGuildList( char* szGuildName, BYTE byCsJoinSide, BYTE byGuildInvolved,int iGuildScore)
{
	m_GuildListBox.AddText( szGuildName, byCsJoinSide, byGuildInvolved, iGuildScore);
}

void CNewUIGuardWindow::ClearGuildList()
{
	m_GuildListBox.Clear();
}

void CNewUIGuardWindow::RenderScrollBarFrame(int iPos_x, int iPos_y, int iHeight)
{
	RenderImage(IMAGE_GUARDWINDOW_SCROLL_TOP, iPos_x, iPos_y, 7, 3);
#ifdef PBG_ADD_INGAMESHOP_UI_ITEMSHOP
	// 스크롤 프레임중 중간 부분 시작과 끝의 픽셀의 흐려짐의 변화로
	// 이미지를 늘리지 않고 랜더한다
	BITMAP_t *pImage = &Bitmaps[IMAGE_GUARDWINDOW_SCROLL_MIDDLE];
	float _Temp = pImage->Height-1;
	float _fMiddle_Cnt = (iHeight-6)/_Temp;
	int _iMiddle_Cnt = (int)_fMiddle_Cnt;
	float _Middle_rest = _fMiddle_Cnt - _iMiddle_Cnt;

	// 중간부분 반복해서 그린다
	for(int i=0; i<_iMiddle_Cnt; i++)
		RenderImage(IMAGE_GUARDWINDOW_SCROLL_MIDDLE, iPos_x, iPos_y+(float)(i*_Temp+3), 7, _Temp);
	// 한개가 안되는 마지막 부분 그린다
	RenderImage(IMAGE_GUARDWINDOW_SCROLL_MIDDLE, iPos_x, iPos_y+(float)(_iMiddle_Cnt*_Temp+3), 7, _Temp*_Middle_rest);
#else //PBG_ADD_INGAMESHOP_UI_ITEMSHOP
	RenderBitmap(IMAGE_GUARDWINDOW_SCROLL_MIDDLE, iPos_x, iPos_y+3, 7.f, iHeight - 6, 0, 0, 7.f/8.f, 15.f/16.f);
#endif //PBG_ADD_INGAMESHOP_UI_ITEMSHOP
	RenderImage(IMAGE_GUARDWINDOW_SCROLL_BOTTOM, iPos_x, iPos_y + iHeight - 3, 7, 3);
}

void CNewUIGuardWindow::RenderScrollBar(int iPos_x, int iPos_y, BOOL bIsClicked)
{
	if (bIsClicked)
	{
		glColor3ub(200, 200, 200);
		RenderImage(IMAGE_GUARDWINDOW_SCROLLBAR_ON, iPos_x, iPos_y, 15, 30);
	}
	else
	{
		glColor3ub(255, 255, 255);
		RenderImage(IMAGE_GUARDWINDOW_SCROLLBAR_ON, iPos_x, iPos_y, 15, 30);
	}
	glColor3ub(255, 255, 255);
}
