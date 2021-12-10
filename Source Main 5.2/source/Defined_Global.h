


#ifdef _DEBUG
	#define KWAK_FIX_ALT_KEYDOWN_MENU_BLOCK
#endif // _DEBUG

#define NEW_PROTOCOL_SYSTEM

#define PJH_NEW_SERVER_SELECT_MAP

#define ASG_ADD_GENS_SYSTEM
#ifdef ASG_ADD_GENS_SYSTEM
	#define ASG_ADD_INFLUENCE_GROUND_EFFECT
	#define ASG_ADD_GENS_MARK
	#define PBG_MOD_STRIFE_GENSMARKRENDER
	#define PBG_ADD_GENSRANKING
#endif	// ASG_ADD_GENS_SYSTEM

//----------------------------------------------------------------------------------------------
// << Season 5 - Part 1 

#define UPDATE_100527
#ifdef UPDATE_100527

	#define SEASON5_PART2
	#ifdef SEASON5_PART2
		#define KJH_PBG_ADD_INGAMESHOP_SYSTEM
		#ifdef KJH_PBG_ADD_INGAMESHOP_SYSTEM
			#define PBG_ADD_INGAMESHOP_UI_MAINFRAME
			#define PBG_ADD_INGAMESHOP_UI_ITEMSHOP
			#define PBG_ADD_NAMETOPMSGBOX
			#define KJH_ADD_INGAMESHOP_UI_SYSTEM
			#define KJH_ADD_PERIOD_ITEM_SYSTEM
			#define PBG_ADD_INGAMESHOPMSGBOX
			#define PBG_ADD_MSGBACKOPACITY
			#define PBG_ADD_ITEMRESIZE
			#define PBG_FIX_ITEMANGLE
			#define PBG_ADD_MU_LOGO
			#define KJH_MOD_SHOP_SCRIPT_DOWNLOAD
			//^#define PBG_ADD_CHARACTERSLOT
			#define PBG_ADD_CHARACTERCARD
			//^#define LDK_ADD_INGAMESHOP_LIMIT_MOVE_WINDOW
		#endif //KJH_PBG_ADD_INGAMESHOP_SYSTEM

	#endif // SEASON5_PART2

	#define ADD_TOTAL_CHARGE_8TH
	#ifdef  ADD_TOTAL_CHARGE_8TH
		#define YDG_ADD_HEALING_SCROLL						// 치유의 스크롤 (2009.12.03)

		#define LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12		// 희귀아이템 티켓 7-12 추가 (2010.02.12)
		#define LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH	//도플갱어, 뭏Ｄ�, 뭏Ｄ� 제 7맵 자유입장권 추가(2010.02.17)

		#define ADD_SKELETON_PET							// 스켈레톤 펫 (2009.12.03)
		#ifdef  ADD_SKELETON_PET
			#define YDG_ADD_SKELETON_PET					// 스켈레톤 펫 
			#ifndef KJH_ADD_PERIOD_ITEM_SYSTEM					// #ifndef
				#define LJH_FIX_IGNORING_EXPIRATION_PERIOD		// 일본에는 아직 기간제가 적용되지 않으므로 bExpiredPeriod를 사용하지 않도록 수정(2010.02.11) - 기간제 시스템 도입 후 삭제
			#endif // KJH_ADD_PERIOD_ITEM_SYSTEM
			#define LDK_FIX_PC4_GUARDIAN_DEMON_INFO			// 데몬 캐릭터정보창에 공격력,마력,저주력 추가 데미지 적용(09.10.15) - 캐릭터정보창에 펫 종렛� 의한 저주력 추가 데미지를 적용 시키기 위해 추가
			#define LJH_FIX_NOT_POP_UP_HIGHVALUE_MSGBOX_FOR_BANNED_TO_TRADE	//NPC에게 판매 금지된 아이템을 판매하려고 할때 고가의 아이템이라고 나오는 메세지 창을 안나오게 수정(10.02.19)
		#endif  //ADD_SKELETON_PET

		#define YDG_MOD_CHANGE_RING_EQUIPMENT_LIMIT			// 변신반지 한종렇� 장비하도록 수정 (2009.12.28)
	#endif  //ADD_TOTAL_CHARGE_8TH


	//-----------------------------------------------------------------------------
	// [ Season 5 - Part 1] (09.09.11)
	#define SEASON5										
	#ifdef SEASON5
		#define YDG_ADD_DOPPELGANGER_EVENT
		#ifdef YDG_ADD_DOPPELGANGER_EVENT
			#define YDG_ADD_MAP_DOPPELGANGER1					// 도플갱어 맵1 (라클리온베이스) (2009.03.22)
			#define YDG_ADD_MAP_DOPPELGANGER2					// 도플갱어 맵2 (불카누스베이스) (2009.03.22)
			#define YDG_ADD_MAP_DOPPELGANGER3					// 도플갱어 맵3 (아틀란스베이스) (2009.03.22)
			#define YDG_ADD_MAP_DOPPELGANGER4					// 도플갱어 맵4 (칸투르1차베이스) (2009.03.22)
			#define YDG_ADD_DOPPELGANGER_MONSTER				// 도플갱어 몬스터 추가 (2009.05.20)
			#define YDG_ADD_DOPPELGANGER_NPC					// 도플갱어 NPC 루가드 추가 (2009.05.20)
			#define YDG_ADD_DOPPELGANGER_ITEM					// 도플갱어 아이템 추가 (2009.05.20)
			#define YDG_ADD_DOPPELGANGER_UI						// 도플갱어 UI 추가 (2009.05.20)
			#define YDG_ADD_DOPPELGANGER_PROTOCOLS				// 도플갱어 프로토콜 추가 (2009.06.23)
			#define YDG_ADD_DOPPELGANGER_PORTAL					// 도플갱어 맵 포탈 추가 (2009.07.30)
			#define YDG_ADD_DOPPELGANGER_SOUND					// 도플갱어 사운드 추가 (2009.08.04)
		#endif	// YDG_ADD_DOPPELGANGER_EVENT

		#define LDS_ADD_EMPIRE_GUARDIAN
		#ifdef LDS_ADD_EMPIRE_GUARDIAN
			#define LDS_ADD_MAP_EMPIREGUARDIAN2					// 제국 수호군 맵 2   (화,  금)
			#define LDS_ADD_MAP_EMPIREGUARDIAN4					// 제국 수호군 맵 2   (일	  )
			#define LDS_ADD_EG_4_MONSTER_WORLDBOSS_GAIONKALEIN	// 제국 수호군 맵 4   (일	  )몬스터 영� 보스 가이온 카레인	(504/164)
			#define LDS_ADD_EG_4_MONSTER_JELINT					// 제국 수호군 맵 4   (일	  )몬스터 가이온 보좌관 제린트		(505/165)
			#define LDS_ADD_EG_3_4_MONSTER_RAYMOND				// 제국 수호군 맵 3,4 (수토,일)몬스터 부사령관 레이몬드			(506/166)
			#define LDS_ADD_EG_2_4_MONSTER_ERCANNE				// 제국 수호군 맵 2,4 (화금,일)몬스터 지휘관 에르칸느			(507/167)
			#define LDS_ADD_EG_2_MONSTER_2NDCORP_VERMONT		// 제국 수호군 맵 2   (화,  금)몬스터 2군단장 버몬트			(509/169)
			#define LDS_ADD_EG_2_MONSTER_ARTICLECAPTAIN			// 제국 수호군 맵 2   (화,  금)몬스터 기사단장					(514/174)
			#define LDS_ADD_EG_2_MONSTER_GRANDWIZARD			// 제국 수호군 맵 2   (화,  금)몬스터 대마법사					(515/176)

			#define LDK_ADD_EG_MONSTER_DEASULER					// 제국 수호군 1군단장 데슬러									(508/168)
			#define LDK_ADD_EG_MONSTER_DRILLMASTER				// 제국 수호군 제국수호군전투교관
			#define LDK_ADD_EG_MONSTER_QUARTERMASTER			// 제국 수호군 병참장교
			#define LDK_ADD_EG_MONSTER_CATO						// 제국 수호군 2군단장 카토
			#define LDK_ADD_EG_MONSTER_ASSASSINMASTER			// 제국 수호군 암살장교
			#define LDK_ADD_EG_MONSTER_RIDERMASTER				// 제국 수호군 기마단장
			#define LDK_ADD_EG_MONSTER_GALLIA					// 제국 수호군 4군단장 갈리아

			#define LDK_FIX_EG_DOOR_ROTATION_FIXED				// 제국 수호군 성문 악령에 의한 회전수정(2009.07.21)
			#define LDK_ADD_EG_DOOR_EFFECT						// 제국 수호군 맵 성문 파괴 이펙트
			#define LDK_ADD_EG_STATUE_EFFECT					// 제국 수호군 맵 석상 파괴 이펙트

			#define	LDK_ADD_EG_MONSTER_RAYMOND					// 제국 수호군 부사령관 레이몬드 (수, 일)
			#define LDK_ADD_EG_MONSTER_KNIGHTS					// 제국 수호군 기사단	Imperial Guardian Knights	520 - 181	
			#define LDK_ADD_EG_MONSTER_GUARD					// 제국 수호군 호위병	Imperial Guardian guard		521 - 182
			#define ASG_ADD_EG_MONSTER_GUARD_EFFECT				// 제국 수호군 호위병 (검기 이펙트)
			#define LDS_ADD_EG_MONSTER_GUARDIANDEFENDER			// 제국 수호군 맵 1234(모든요일)몬스터 수호군 방패병			(518/178)
			#define LDS_ADD_EG_MONSTER_GUARDIANPRIEST			// 제국 수호군 맵 1234(모든요일)몬스터 수호군 치유병			(519/179)

			#define LDK_ADD_MAPPROCESS_RENDERBASESMOKE_FUNC		// MapProcess에 RenderBaseSmoke 처리 함수 추가(09.07.31)
			#define	LDK_ADD_MAP_EMPIREGUARDIAN1					// 제국 수호군 맵 1 (�, 목)
			#define	LDK_ADD_MAP_EMPIREGUARDIAN3					// 제국 수호군 맵 3 (수, 토)

			#define LDK_ADD_EMPIRE_GUARDIAN_DOOR_ATTACK			// 제국 수호군 성문은 맵속성무기하고 공격가능하도록함 (09.08.06)

			#define LDK_ADD_EMPIREGUARDIAN_UI					// 제국 수호군 ui
			#define LDK_ADD_EMPIREGUARDIAN_PROTOCOLS			// 제국 수호군 프로토콜
			#define LDK_ADD_EMPIREGUARDIAN_ITEM					// 제국 수호군 아이템(4종:명령서, 종이쪽지, 세크로미콘, 조각)

			#define LDS_ADD_RESOURCE_FLARERED					// FLARE_RED.jpg 효과 추가

			#define LDS_ADD_MODEL_ATTACH_SPECIFIC_NODE_			// 특정 모델의 특정 노드에 뉨� 특정 모델을 ATTACH 하는 함수를 추가합니�. (09.06.12)
			#define LDS_ADD_INTERPOLATION_VECTOR3				// vec3_t의 보간 함수를 zzzmathlib.h에 추가. (09.06.24)
			#define LDS_ADD_EFFECT_FIRESCREAM_FOR_MONSTER		// 늚㈆琯揚� 파이어스크림 스킬에 특정 몬스터(에르칸느)의 파이어스크림을 추가합니�. (09.07.07)
			#define LDS_MOD_EFFECTBLURSPARK_FORCEOFSWORD		// EffectBlurSpark 의 검기들의 갯수 제한에 문제로 검기가 간혹 깨지는 현상으로 부분 수정. (09.07.28)
			#define LDS_ADD_MAP_EMPIREGUARDIAN4_MAPEFFECT		// 주말맵의 맵 Effect에 추가되는 파티클, EFFECT들.. 
			#define LDS_FIX_MEMORYLEAK_DESTRUCTORFORBMD			// BMD의 소멸자로 인한 기존 BMD에서 발생한 memoryleak FIXED.. (2009.08.13)

			#define PBG_ADD_RAYMOND_GUARDIANPRIEST_MONSTER_EFFECT	// (레이몬드)(치유병)몬스터 이펙트 작업(09.07.02)

			#define KJH_ADD_EG_MONSTER_KATO_EFFECT					// 3군단장 카토 이팩트 (09.07.20)
			#define KJH_ADD_EG_MONSTER_GUARDIANDEFENDER_EFFECT		// 수호군 방패병 이팩트 (09.07.31)
		#endif //LDS_ADD_EMPIRE_GUARDIAN

		#define ASG_ADD_NEW_QUEST_SYSTEM						// 뉴 캭뵈� 시스템(2009.05.20)
		#ifdef ASG_ADD_NEW_QUEST_SYSTEM
			#define ASG_ADD_UI_QUEST_PROGRESS					// 캭뵈� 진행 창(NPC용)(2009.05.27)
			#define ASG_ADD_UI_QUEST_PROGRESS_ETC				// 캭뵈� 진행 창(기타용)(2009.06.24)
			#define ASG_MOD_UI_QUEST_INFO						// 캭뵈� 정보 창(2009.07.06)
			#define ASG_MOD_3D_CHAR_EXCLUSION_UI				// 3D 캐릭터 표현이 없는 UI로 묾�.(2009.08.03)
		#endif	// ASG_ADD_NEW_QUEST_SYSTEM

		#define LJH_MOD_POSITION_OF_REGISTERED_LUCKY_COIN		// 행운의 동전 등록 제한 수가 2^31이 됨에 따라 동전이미지와 겹치는 현상 막기위해 수정(2010.02.16)							
		#define YDG_MOD_SEPARATE_EFFECT_SKILLS					// 스킬 검사하는 이펙트 분리 (블러드 어택 등) (2009.08.10)
		#define ASG_ADD_NEW_DIVIDE_STRING						// 새로운 문장 나누기 기능.(2009.06.08)
		#define PBG_ADD_DISABLERENDER_BUFF						// 랜더안할 버프 이미지 처리(09.08.10)

	#endif	// SEASON5


	#define ADD_TOTAL_CHARGE_7TH
	#ifdef ADD_TOTAL_CHARGE_7TH
		// - 양대�
		#define YDG_ADD_CS7_CRITICAL_MAGIC_RING		// 치명마법반지
		#define YDG_ADD_CS7_MAX_AG_AURA				// AG증가 오라
		#define YDG_ADD_CS7_MAX_SD_AURA				// SD증가 오라
		#define YDG_ADD_CS7_PARTY_EXP_BONUS_ITEM	// 파티 경험치 증가 아이템
		#define YDG_ADD_CS7_ELITE_SD_POTION			// 엘리트 SD회복 물약
		#define YDG_MOD_AURA_ITEM_EXCLUSIVELY_BUY	// 오라 중복 구입 막기 (09.11.02)

		// - 이동�
		#define LDK_MOD_PETPROCESS_SYSTEM			// 펫프로세스 업데이트 순서 변경(애니메이션 속도 임의 변경 가능)(2009.09.11)
		#define LDK_ADD_CS7_UNICORN_PET				// 유니콘 펫 
		#define LDK_FIX_CS7_UNICORN_PET_INFO		// 유니콘 펫 캐릭터 정보창 방어력 추가

		// - 박보�
		#define PBG_ADD_AURA_EFFECT					// AG SD 증가 오라 이펙트
	#endif //ADD_TOTAL_CHARGE_7TH

	#define KJH_FIX_GET_ZEN_SYSTEM_TEXT						// 겜블상점에서 아이템구입시 젠증가 메세지가 나오는 문제. (09.03.18) [09.03.19 테섭]
	#define KJH_FIX_WOPS_K33695_EQUIPABLE_DARKLOAD_PET_ITEM	// 늚㈆琯弱� 인벤에 펫을 소유하고 있을때, 툴팁에 착용불가로 나오는 버그수정 (09.04.27)
	#define KJH_FIX_WOPS_K33479_SELECT_CHARACTER_TO_HEAL	// 캐릭터에게 둘러쌓였을때, 요정의 치료스킬강화이후 캐릭터 선택이 잘 안되어지는 버그수정 (09.04.27)
	#define KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET			// 펫을타고 늚㈆琯� 카오틱디세이어 스킬시 애니메이션수정 (08.12.18)

	#define CSK_FIX_UI_FUNCTIONNAME							// UI관련 함수명 변경(2009.01.22) [2009.03.26 테섭]
	#define CSK_FIX_ANIMATION_BLENDING						// 애니메이션 블렌돠� 블렌드 안되게 옵션 주게 수정(2009.01.29) [2009.03.26 테섭]
	#define CSK_FIX_ADD_EXEPTION							// dmp파일 분석해보니 getTargetCharacterKey 함수에서 튕기는걸로 예측되서 예외처리 추가(2009.01.29) [2009.03.26 테섭]

	#define PBG_FIX_PKFIELD_ATTACK							// PKFIELD에서 길드원끼리 공격되는 현상(09.04.02) [2009.04.06 테섭]
	#define PBG_FIX_PKFIELD_CAOTIC							// 카오틱 디세이어 탈 것에서 버그 수정(09.04.07) [2009.04.13 테섭]
	#define PBG_FIX_GUILDWAR_PK								// PKFIELD에서 길드워 중에 일반인 공격안받는 버그 수정(09.04.07) [2009.04.13 테섭]
	#define PBG_FIX_CHAOTIC_ANIMATION						// 카오틱 디세이어 애니메이션 수정(09.06.11)
	#define PBG_FIX_DARK_FIRESCREAM_HACKCHECK				// 늚� 파이어스크림 (서버)플셔ŉ晥� 버그 수정(09.06.22)
	#define PBG_MOD_INVENTORY_REPAIR_COST					// 자동수리금액 하향조정(09.06.08)
	#define PBG_MOD_LUCKYCOINEVENT							// 행운의동전 255개 이상 등록되지 않도록 이벤트 수정(09.07.15)(뉨쩤I와의버그,열고이동버그)

	#define LDK_FIX_INVENTORY_SPEAR_SCALE					// 인벤토리 무기-spear 크기 처리 if문 수정 [09.03.19 테섭]

	#define YDG_FIX_INVALID_TERRAIN_LIGHT					// 메모리 침범 버그 수정(맵툴 관련) (2009.03.30) [2009.04.13 테섭]
	#define YDG_FIX_MEMORY_LEAK_0905						// 메모리 누수 제거 (2009.05.11)
	#define YDG_FIX_INVALID_SET_DEFENCE_RATE_BONUS			// 방어구세트 추가 방어력표시 방어력의 10%가 아니라 방어율의 10%임 (2009.04.15) [패치안됨] wops_32937
	#define YDG_FIX_STAFF_FLAMESTRIKE_IN_CHAOSCASLE			// 카오스캐슬에서 마검사 지팡이 착용시 플레임스트라이크와 블러드어택 아이콘색 문제 (2009.04.15) [패치안됨] wops_34747
	#define YDG_FIX_LEFTHAND_MAGICDAMAGE					// 마검사가 지팡이나 룬뭣뵀링躍� 왼손에 찼을때 마력이 올라가는 문제 (2009.04.15) [패치안됨] wops_32641
	#define YDG_FIX_BLOCK_STAFF_WHEEL						// 마검사 지팡이, 맨손 회오리베기 막기 (2009.05.18)
	#define YDG_FIX_MEMORY_LEAK_0905_2ND					// 메모리 누수 제거 2차 (2009.05.19)
	#define YDG_FIX_CLIENT_SKILL_EFFECT_SIZE				// 이펙트 많을때 블러드어택등 클라스킬 안먹는 버그 (2009.07.13)

	#define ASG_FIX_PICK_ITEM_FROM_INVEN					// 인벤창 특정 칸에서 아이템을 집어들었을 때 캐릭정보창에서 능력치가 변동되는 버그(2009.04.15) wops_33567
	#define ASG_FIX_MOVE_WIN_MURDERER1_BUG					// 무법자(카오) 레벨1일 때 맵 이동창 표시 버그.(2009.04.20) wops_34498

	#define PJH_FIX_4_BUGFIX_33								// wops_34066

	#define LDS_FIX_MASTERSKILLKEY_DISABLE_OVER_LIMIT_MAGICIAN		// 마스터 스킬 강화 된 스킬들에 대해 요구치 미달시에 이용 불가. (09.04.22) no_wops
	#define LDS_FIX_SETITEM_WRONG_CALCULATION_IMPROVEATTACKVALUE	// 세트아이템착용 이후 사랑의 묘약을 먹으면, 케릭터 정보창에 힘증가 스탯수치가 뉨Η恥�. (09.04.23) wops_35131
	#define LDS_FIX_MEMORYLEAK_PHYSICSMANAGER_RELEASE				// 메모리 누수 제거, Physicsmanager 힙영역 메모리 반환 처리. (늚㈆琯� 케릭 로돛京� 종료 시 릭 발생)(09.05.25)
#endif // UPDATE_100527

#define KJH_ADD_SERVER_LIST_SYSTEM						// 서버리스트 시스템 변경 (09.10.19) - 국내의 내용을 미리 당겨 사용.
#define ASG_ADD_SERVER_LIST_SCRIPTS						// ServerList.txt 스크립트 추가.(2009.10.29) - 국내의 내용을 미리 당겨 사용.
#ifdef ASG_ADD_SERVER_LIST_SCRIPTS
	#define ASG_ADD_SERVER_LIST_SCRIPTS_GLOBAL_TEMP		// 미리 ASG_ADD_SERVER_LIST_SCRIPTS 추가로 인한 버그 수정.(10.03.02) 
															//Season5 이후 삭제해도 됨.(BuxConvert() 함수 위치 문제) // Season5 업데이트시에 삭제해도 되는것인지 확인 늄� 할것.
	#define ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL		// 서버리스트에 유료 채널 추가.(10.02.26) - 현재 글로벌만 적용.
#endif	//ASG_ADD_SERVER_LIST_SCRIPTS


//-----------------------------------------------------------------------------
// [ Season 4.5 ] 
#define SEASON4_5										
#ifdef SEASON4_5

	#define KJH_ADD_09SUMMER_EVENT					// 09년 여름이벤트		(09.06.23)

	#define YDG_ADD_NEW_DUEL_SYSTEM					// 새로운 결투 시스템 (2009.01.05) [09.03.19 테섭]
	#ifdef YDG_ADD_NEW_DUEL_SYSTEM
		#define YDG_ADD_NEW_DUEL_UI					// 새로운 결투 관련 UI 추가 (2009.01.05) [09.03.19 테섭]
		#define YDG_ADD_NEW_DUEL_PROTOCOL			// 새로운 결투 관련 프로토콜 추가 (2009.01.08) [09.03.19 테섭]
		#define YDG_ADD_NEW_DUEL_NPC				// 새로운 결투 관련 NPC 타이투스 추가 (2009.01.19) [09.03.19 테섭]
		#define YDG_ADD_NEW_DUEL_WATCH_BUFF			// 새로운 결투 관전 버프 추가 (2009.01.20) [09.03.19 테섭]
		#define YDG_ADD_MAP_DUEL_ARENA				// 새로운 결투장 맵 추가 (2009.02.04) [09.03.19 테섭]
	#endif	// YDG_ADD_PVP_SYSTEM

	#define PBG_ADD_PKFIELD							// PK필드 추가(2008.12.29) [09.03.19 테섭]
	#define PBG_ADD_HONOROFGLADIATORBUFFTIME		// 검투사의 명예 버프 시간 툴팁 추가(2009.03.19) [09.03.19 테섭]

	#define LDK_ADD_GAMBLE_SYSTEM					// 젠소모 무기 뽑기 상점 (09.01.05) [09.03.19 테섭]
	#ifdef LDK_ADD_GAMBLE_SYSTEM
		#define LDK_ADD_GAMBLE_NPC_MOSS				// 겜블 상인 모스 [09.03.19 테섭]
		#define LDK_ADD_GAMBLE_RANDOM_ICON			// 겜블용 랜덤무기 아이콘 [09.03.19 테섭]
		#define LDK_ADD_GAMBLERS_WEAPONS			// 겜블전용 레어 무기들 [09.03.19 테섭]
	#endif //LDK_ADD_GAMBLE_SYSTEM

	#define PJH_ADD_PANDA_PET
	#define PJH_ADD_PANDA_CHANGERING

#endif // SEASON4_5


#define ASG_FIX_LENA_REGISTRATION

#define ASG_ADD_CHARGED_CHANNEL_TICKET					// 유료 채널 입장권.(2010.02.05) - 글로벌전용

#define ADD_TOTAL_CHARGE_6TH
#ifdef ADD_TOTAL_CHARGE_6TH

	#define ADD_CASH_SHOP_6TH
		#ifdef ADD_CASH_SHOP_6TH
		#define ASG_ADD_CS6_GUARD_CHARM				// 수호의부적(2009.02.09)
		#define ASG_ADD_CS6_ITEM_GUARD_CHARM		// 아이템보호부적(2009.02.09)
		#define ASG_ADD_CS6_ASCENSION_SEAL_MASTER 	// 상승의인장마스터(2009.02.24)
		#define ASG_ADD_CS6_WEALTH_SEAL_MASTER 		// 풍요의인장마스터(2009.02.24)
		#define LDS_ADD_CS6_CHARM_MIX_ITEM_WING
	#endif	// ADD_CASH_SHOP_6TH

	#define CSK_ADD_GOLDCORPS_EVENT					// 황금군단이벤트(2009.03.13)
	#define LDS_ADD_GOLDCORPS_EVENT_MOD_GREATDRAGON // 황금 그레이트 드레곤 비주얼 재작업. 비주얼 이펙트 추가. 기존 동일한 몹 존재. (2009.04.06) (BITMAP_FIRE_HIK3_MONO 효과 참조.)
#endif // ADD_TOTAL_CHARGE_6TH


#define PBG_MOD_NONPVPSERVER
#define LDS_FIX_PETDESTRUCTOR_TERMINATE_EFFECTOWNER_ADD_TYPE
#define LDS_FIX_AFTER_PETDESTRUCTOR_ATTHESAMETIME_TERMINATE_EFFECTOWNER

// (2009.04.23)
#define PJH_CHARACTER_RENAME
#define LDK_MOD_GLOBAL_PORTAL_LOGO

//#define LDK_MOD_GLOBAL_PORTAL_CASHSHOP_BUTTON_DENY	// (09.04.07)
#define LDK_FIX_MOVEWINDOW_SCROLL_BUG				// (2009.04.22)
#define LDK_MOD_PASSWORD_LENGTH_20					// (2009.04.24)
#define LDK_MOD_GLOBAL_STORAGELOCK_CHANGE			// (2009.04.27)

#define ADD_CASH_SHOP_5TH

#ifdef ADD_CASH_SHOP_5TH
	#define LDK_FIX_CS5_HIDE_SEEDLEVEL
	#define YDG_ADD_CS5_REVIVAL_CHARM
	#define YDG_ADD_CS5_PORTAL_CHARM
#endif	// YDG_ADD_CASH_SHOP_5TH

#define PBG_WOPS_CURSEDTEMPLEBASKET_MOVING			//(2008.12.18)

#define PSW_PARTCHARGE_ITEM4

#ifdef PSW_PARTCHARGE_ITEM4
	#define PSW_ADD_PC4_SEALITEM
	#define PSW_ADD_PC4_SCROLLITEM
	#define PSW_ADD_PC4_CHAOSCHARMITEM
	#define LDK_ADD_PC4_GUARDIAN
	#define	LDK_FIX_GUARDIAN_CHANGE_LIFEWORD			//(2009.01.14)
	#define LDK_ADD_PC4_GUARDIAN_EFFECT_IMAGE
#endif //PSW_PARTCHARGE_ITEM4


#define PSW_ADD_FOREIGN_HELPWINDOW

#define PSW_PARTCHARGE_ITEM3

#ifdef PSW_PARTCHARGE_ITEM3
	#define PSW_NEW_CHAOS_CARD
	#define PSW_NEW_ELITE_ITEM
#endif //PSW_PARTCHARGE_ITEM3


#define PSW_PARTCHARGE_ITEM2

#ifdef PSW_PARTCHARGE_ITEM2
	#define PSW_ELITE_ITEM
	#define PSW_SCROLL_ITEM
	#define PSW_SEAL_ITEM
	#define PSW_FRUIT_ITEM
	#define PSW_SECRET_ITEM
	#define PSW_INDULGENCE_ITEM
	#define PSW_RARE_ITEM
	#define PSW_CURSEDTEMPLE_FREE_TICKET
#endif //PSW_PARTCHARGE_ITEM2


#define PSW_PARTCHARGE_ITEM1
				
#ifdef PSW_PARTCHARGE_ITEM1
	#define CSK_FREE_TICKET						// (2007.02.06)
	#define CSK_CHAOS_CARD						// (2007.02.07)
	#define CSK_RARE_ITEM						// (2006.02.15)
	#define CSK_LUCKY_CHARM						// ( 2007.02.22 )
	#define CSK_LUCKY_SEAL						// ( 2007.02.22 )	
#endif //PSW_PARTCHARGE_ITEM1

#define LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX


