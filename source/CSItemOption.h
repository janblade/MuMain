//////////////////////////////////////////////////////////////////////////
//  - 酒捞袍 可记 包访 -
//  
//  
//////////////////////////////////////////////////////////////////////////
#ifndef __CSITEM_OPTION_H__
#define __CSITEM_OPTION_H__

/*+++++++++++++++++++++++++++++++++++++
    INCLUDE.
+++++++++++++++++++++++++++++++++++++*/
#include "Singleton.h"
#include "zzzinfomation.h"

#ifdef LDS_FIX_OUTPUT_EQUIPMENTSETITEMOPTIONVALUE
#include <map>
#endif // LDS_FIX_OUTPUT_EQUIPMENTSETITEMOPTIONVALUE


const BYTE MAX_SET_OPTION = 64;
const BYTE MASTERY_OPTION = 24;

const BYTE EXT_A_SET_OPTION  = 1;
const BYTE EXT_B_SET_OPTION  = 2;

/*+++++++++++++++++++++++++++++++++++++
    CLASS.
+++++++++++++++++++++++++++++++++++++*/
//////////////////////////////////////////////////////////////////////////
//  
//////////////////////////////////////////////////////////////////////////
class CSItemOption : public Singleton<CSItemOption>
{
private :
	ITEM_SET_TYPE	m_ItemSetType[MAX_ITEM];
	ITEM_SET_OPTION	m_ItemSetOption[MAX_SET_OPTION];

	bool	m_bViewOptionList;
    BYTE    m_byRenderOptionList;
    BYTE    m_bySelectedItemOption;
    BYTE    m_bySameSetItem;
    char    m_strSetName[2][32];

#ifdef LDS_FIX_OUTPUT_EQUIPMENTSETITEMOPTIONVALUE
	typedef std::map<int, std::string>	MAP_EQUIPPEDSETITEMNAME;
	typedef std::map<BYTE, int>		MAP_EQUIPPEDSETITEM_SEQUENCE;

	MAP_EQUIPPEDSETITEMNAME			m_mapEquippedSetItemName;
	MAP_EQUIPPEDSETITEMNAME::iterator
									m_iterESIN;

	MAP_EQUIPPEDSETITEM_SEQUENCE	m_mapEquippedSetItemSequence;
	MAP_EQUIPPEDSETITEM_SEQUENCE::iterator
									m_iterESIS;
private:
	int		Search_From_EquippedSetItemNameMapTable( char *szSetItemname )
	{
		int		iSizeFindName = strlen( szSetItemname );

		for( m_iterESIN = m_mapEquippedSetItemName.begin(); m_iterESIN != m_mapEquippedSetItemName.end(); ++m_iterESIN )
		{
			std::string	strCur;

			strCur = m_iterESIN->second;
			int iSizeCurName = strCur.size();
			
			if( !strncmp( szSetItemname, strCur.c_str(), iSizeFindName ) 
				&& !strncmp( szSetItemname, strCur.c_str(), iSizeCurName ) )
			{
				return m_iterESIN->first;
			}
		}
		return -1;
	}

public:
	bool	Find_From_EquippedSetItemNameMapTable( char	*szSetItemname )
	{
		int iResult = Search_From_EquippedSetItemNameMapTable( szSetItemname );

		if( -1 == iResult )
		{
			return false;
		}
		else
		{
			return true;
		}
	}

#define	BYTE_MAX		255

	BYTE	Search_From_EquippedSetItemNameSequence( char *szSetItemname )
	{
		BYTE	byCur = 0;
		int		iResult = Search_From_EquippedSetItemNameMapTable( szSetItemname );
		
		if( -1 != iResult )
		{
			for( m_iterESIS = m_mapEquippedSetItemSequence.begin(); m_iterESIS != m_mapEquippedSetItemSequence.end(); ++m_iterESIS )
			{
				if( (int)(m_iterESIS->second) == iResult )
				{
					return (BYTE)m_iterESIS->first;
				}
			}
		}
		
		return (BYTE)BYTE_MAX;
	}
	
#endif // LDS_FIX_OUTPUT_EQUIPMENTSETITEMOPTIONVALUE	

    BYTE	m_bySetOptionANum;
	BYTE	m_bySetOptionBNum;
    BYTE    m_bySetOptionIndex[2];
	BYTE	m_bySetOptionList[16][3];       //  可记 府胶飘.
	BYTE	m_bySetOptionListOnOff[16];     //  荤侩等 可记.
    int     m_iSetOptionListValue[16][2];   //  可记 蔼.

	bool	OpenItemSetType ( const char* filename );
	bool	OpenItemSetOption ( const char* filename );

	void	checkItemType ( BYTE* optioList, const int iType, const int setType );

	void	calcSetOptionList ( BYTE* optioList );

	void	getExplainText ( char* text, const BYTE option, const BYTE value, const BYTE SetA );

#ifdef LDS_ADD_CHARISMAVALUE_TOITEMOPTION 
	void    getAllAddState ( WORD* Strength, WORD* Dexterity, WORD* Energy, WORD* Vitality, WORD* Charisma );
#else // LDS_ADD_CHARISMAVALUE_TOITEMOPTION
    void    getAllAddState ( WORD* Strength, WORD* Dexterity, WORD* Energy, WORD* Vitality );
#endif // LDS_ADD_CHARISMAVALUE_TOITEMOPTION
	
	int     GetSetItmeCount( const ITEM* pselecteditem );
	bool	isFullseteffect( const ITEM* ip );

#ifdef LDS_FIX_WRONG_CALCULATEEQUIPEDITEMOPTIONVALUE
public:	

#ifdef LDS_ADD_CHARISMAVALUE_TOITEMOPTION
	void	getAllAddOptionStatesbyCompare ( WORD* Strength, WORD* Dexterity, WORD* Energy, WORD* Vitality, WORD* Charisma, 
								WORD iCompareStrength, WORD iCompareDexterity, WORD iCompareEnergy, WORD iCompareVitality, WORD iC );
#else // LDS_ADD_CHARISMAVALUE_TOITEMOPTION
	void	getAllAddOptionStatesbyCompare ( WORD* Strength, WORD* Dexterity, WORD* Energy, WORD* Vitality,
								WORD iCompareStrength, WORD iCompareDexterity, WORD iCompareEnergy, WORD iCompareVitality );
#endif // LDS_ADD_CHARISMAVALUE_TOITEMOPTION
	
#ifdef LDS_ADD_CHARISMAVALUE_TOITEMOPTION
	void	getAllAddStateOnlyAddValue ( WORD* AddStrength, 
										WORD* AddDexterity, 
										WORD* AddEnergy, 
										WORD* AddVitality, 
										WORD* AddCharisma );
#else // LDS_ADD_CHARISMAVALUE_TOITEMOPTION
	void	getAllAddStateOnlyAddValue ( WORD* AddStrength, WORD* AddDexterity, WORD* AddEnergy, WORD* AddVitality );
#endif // LDS_ADD_CHARISMAVALUE_TOITEMOPTION

#endif // LDS_FIX_WRONG_CALCULATEEQUIPEDITEMOPTIONVALUE
	
public :
    CSItemOption ( void )  { init(); };
    ~CSItemOption ( void ) {};

	void init( void )
	{
        memset ( m_strSetName, 0, sizeof( char )*32*2 );

		m_bViewOptionList = false;
        m_byRenderOptionList= 0;
        m_bySelectedItemOption = 0;
        m_bySameSetItem = 0;
	}
    void    ClearListOnOff ( void )
    {
        memset ( m_bySetOptionListOnOff, 0, sizeof( BYTE )* 16 );
    }
    bool    OpenItemSetScript ( bool bTestServer );

	bool    IsDisableSkill ( int Type, int Energy, int Charisma = 0 );
    BYTE    IsChangeSetItem ( const int Type, const int SubType );
    WORD    GetMixItemLevel ( const int Type );
	bool	GetSetItemName ( char* strName, const int iType, const int setType );

	void	PlusSpecial ( WORD* Value, const int Special );
	void	PlusSpecialPercent ( WORD* Value, const int Special );
	void	PlusSpecialLevel ( WORD* Value, const WORD SrcValue, const int Special );
    void    PlusMastery ( int* Value, const BYTE MasteryType );

    void    MinusSpecialPercent ( int* Value, const int Special );

	void	GetSpecial ( WORD* Value, int Special );

	void	GetSpecialPercent ( WORD* Value, int Special );
	void	GetSpecialLevel ( WORD* Value, const WORD SrcValue, int Special );
    int     GetDefaultOptionValue ( ITEM* ip, WORD* Value );
    bool    GetDefaultOptionText ( const ITEM* ip, char* Text );
    int     RenderDefaultOptionText ( const ITEM* ip, int TextNum );

	bool    Special_Option_Check(int Kind = 0);
	void	CheckItemSetOptions ( void );
	void	MoveSetOptionList ( const int StartX, const int StartY );
	void	RenderSetOptionButton ( const int StartX, const int StartY );
	void	RenderSetOptionList ( const int StartX, const int StartY );
 
#ifdef LDS_FIX_OUTPUT_WRONG_COUNT_EQUIPPEDSETITEMOPTIONVALUE

	int		m_arLimitSetItemOptionCount[MAX_EQUIPMENT];		

	void	UpdateCount_SetOptionPerEquippedSetItem( const BYTE* byOptionList,int* arLimitSetItemOptionCount,ITEM* ItemsEquipment)
	{
		for( int iE = 0; iE < MAX_EQUIPMENT_INDEX; ++iE )
		{
			int &iCurCount = arLimitSetItemOptionCount[iE];
			ITEM &CurItem = ItemsEquipment[iE];
			
			iCurCount = GetCurrentTypeSetitemCount( CurItem, byOptionList );
		}
	}

	int		GetCurrentTypeSetitemCount( const ITEM &CurItem_, const BYTE* byOptionList )
	{
		BYTE bySetType = CurItem_.ExtOption;

		int setItemType = (bySetType%0x04);

		ITEM_SET_TYPE& itemSType = m_ItemSetType[CurItem_.Type];


		for (int i = 0; i < 30; i += 3)
		{
			ITEM_SET_OPTION& itemOption = m_ItemSetOption[byOptionList[i]];
			
			if( byOptionList[i] == itemSType.byOption[setItemType-1] )
			{
				int iEquippedCount = byOptionList[i+1];
				
				if ( iEquippedCount>=itemOption.byOptionCount-1 )
				{
					return BYTE_MAX;
				}
				
				return iEquippedCount;
			}
		}

		return 0;
	}

#endif // LDS_FIX_OUTPUT_WRONG_COUNT_EQUIPPEDSETITEMOPTIONVALUE

#ifdef LDS_FIX_SETITEM_OUTPUTOPTION_WHICH_LOCATED_INVENTORY
	int     RenderSetOptionListInItem ( const ITEM* ip, int TextNum, bool bIsEquippedItem = false );
#else // LDS_FIX_SETITEM_OUTPUTOPTION_WHICH_LOCATED_INVENTORY
	int     RenderSetOptionListInItem ( const ITEM* ip, int TextNum );
#endif // LDS_FIX_SETITEM_OUTPUTOPTION_WHICH_LOCATED_INVENTORY


    void    ClearOptionHelper ( void ) { m_byRenderOptionList = 0; }
    void    CheckRenderOptionHelper ( const char* FilterName );
    void    RenderOptionHelper ( void );
	
	BYTE GetSetOptionANum();
	BYTE GetSetOptionBNum();

	void SetViewOptionList(bool bView);
	bool IsViewOptionList();
};

#define g_csItemOption CSItemOption::GetSingleton ()


extern std::string g_strSelectedML;

#endif
