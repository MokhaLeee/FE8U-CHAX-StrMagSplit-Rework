#include "gbafe.h"
#include "level-up.h"
#include "str-mag.h"
#include "status-getter.h"

typedef struct Unit Unit;
extern struct StatScreenSt gStatScreen;	// 0x2003BFC in FE8U

extern void DrawStatScreenBar(u16 BarId, u8 x, u8 y, s8 ValueBase, s8 ValueReal, s8 MaxValue); // 0x80870BC
extern void DrawUiSmallNumber(u16* a, int b, int c);
extern u16 gBmFrameTmap0[0x280];
static void (*DisplayBwl)(void) = (const void*)0x8086FAD;

static void DrawPage1_Texts();
static void DrawPage1_NumBar(Unit*);

// ORG 0x8087184
void StatScreen_DrawPage1(void){
	Unit* unit = gStatScreen.unit;
	
	DrawPage1_Texts();
	DrawPage1_NumBar(unit);
	
	DisplayBwl();
}



// ==========================================
// =============== Internal =================
// ==========================================

static void DrawPage1_Texts(){
	
	// Draw Text
	DrawTextInline(		// Str
		&gStatScreen.text[STATSCREEN_TEXT_POWLABEL],
		gBmFrameTmap0 + TILEMAP_INDEX(1, 1),
		TEXT_COLOR_GOLD, 0, 0,
		GetStringFromIndex(0x4FE));
		
	DrawTextInline(		// Mag
		&gStatScreen.text[STATSCREEN_TEXT_AFFINLABEL],
		gBmFrameTmap0 + TILEMAP_INDEX(1, 3),
		TEXT_COLOR_GOLD, 0, 0,
		GetStringFromIndex(0x4FF));
	
	DrawTextInline(		// Skl
		&gStatScreen.text[STATSCREEN_TEXT_SKLLABEL],
		gBmFrameTmap0 + TILEMAP_INDEX(1, 5),
		TEXT_COLOR_GOLD, 0, 0,
		GetStringFromIndex(0x4EC));

	DrawTextInline(		// Spd
		&gStatScreen.text[STATSCREEN_TEXT_SPDLABEL],
		gBmFrameTmap0 + TILEMAP_INDEX(1, 7),
		TEXT_COLOR_GOLD, 0, 0,
		GetStringFromIndex(0x4ED));
		
	DrawTextInline(		// Def
		&gStatScreen.text[STATSCREEN_TEXT_DEFLABEL],
		gBmFrameTmap0 + TILEMAP_INDEX(1, 9),
		TEXT_COLOR_GOLD, 0, 0,
		GetStringFromIndex(0x4EF));
		
	DrawTextInline(		// Res
		&gStatScreen.text[STATSCREEN_TEXT_RESLABEL],
		gBmFrameTmap0 + TILEMAP_INDEX(1, 11),
		TEXT_COLOR_GOLD, 0, 0,
		GetStringFromIndex(0x4F0));
		
		
	
	DrawTextInline(		// Lck
		&gStatScreen.text[STATSCREEN_TEXT_LCKLABEL],
		gBmFrameTmap0 + TILEMAP_INDEX(9, 1),
		TEXT_COLOR_GOLD, 0, 0,
		GetStringFromIndex(0x4EE));
		
		
	DrawTextInline(		// Mov
		&gStatScreen.text[STATSCREEN_TEXT_MOVLABEL],
		gBmFrameTmap0 + TILEMAP_INDEX(9, 3),
		TEXT_COLOR_GOLD, 0, 0,
		GetStringFromIndex(0x4F6));
		
	DrawTextInline(		// Con
		&gStatScreen.text[STATSCREEN_TEXT_CONLABEL],
		gBmFrameTmap0 + TILEMAP_INDEX(9, 5),
		TEXT_COLOR_GOLD, 0, 0,
		GetStringFromIndex(0x4F7));
	
	DrawTextInline(		// Aid
		&gStatScreen.text[STATSCREEN_TEXT_AIDLABEL],
		gBmFrameTmap0 + TILEMAP_INDEX(9, 7),
		TEXT_COLOR_GOLD, 0, 0,
		GetStringFromIndex(0x4F8));

	
	DrawTextInline(		// Trv
		&gStatScreen.text[STATSCREEN_TEXT_RESCUENAME],
		gBmFrameTmap0 + TILEMAP_INDEX(9, 9),
		TEXT_COLOR_GOLD, 0, 0,
		GetStringFromIndex(0x4F9));
	
	// displaying unit rescue name
	Text_InsertString(
		&gStatScreen.text[STATSCREEN_TEXT_RESCUENAME],
		24, TEXT_COLOR_BLUE,
		GetUnitRescueName(gStatScreen.unit));
	
	
	DrawTextInline(		// Status
		&gStatScreen.text[STATSCREEN_TEXT_STATUS],
		gBmFrameTmap0 + TILEMAP_INDEX(9, 11),
		TEXT_COLOR_GOLD, 0, 0,
		GetStringFromIndex(0x4FA));
	
	// displaying unit status name and turns

	if (gStatScreen.unit->statusIndex != UNIT_STATUS_RECOVER)
	{
		// display name

		if (gStatScreen.unit->statusIndex == UNIT_STATUS_NONE)
		{
			Text_InsertString(
				&gStatScreen.text[STATSCREEN_TEXT_STATUS],
				24, TEXT_COLOR_BLUE,
				GetUnitStatusName(gStatScreen.unit));
		}
		else
		{
			Text_InsertString(
				&gStatScreen.text[STATSCREEN_TEXT_STATUS],
                22, TEXT_COLOR_BLUE,
				GetUnitStatusName(gStatScreen.unit));
		}

		// display turns

		if (gStatScreen.unit->statusIndex != UNIT_STATUS_NONE)
		{
			DrawUiSmallNumber(
				gBmFrameTmap0 + TILEMAP_INDEX(16, 11),
				0, gStatScreen.unit->statusDuration);
		}
	}
	else
	{
		// I do not understand what this is for

		struct Unit tmp = *gStatScreen.unit;

		tmp.statusIndex = 0;

		if (gStatScreen.unit->statusIndex == UNIT_STATUS_NONE)
		{
			Text_InsertString(
				&gStatScreen.text[STATSCREEN_TEXT_STATUS],
				24, TEXT_COLOR_BLUE,
				GetUnitStatusName(&tmp));
		}
		else
		{
			Text_InsertString(
				&gStatScreen.text[STATSCREEN_TEXT_STATUS],
				22, TEXT_COLOR_BLUE,
				GetUnitStatusName(&tmp));
		}
	}
}




static void DrawPage1_NumBar(Unit* unit){
	
	DrawStatScreenBar(0,5,1,	// Pow
		unit->pow,
		PowGetter(unit),
		unit->pClassData->maxPow );
	
	DrawStatScreenBar(1,5,3,	// Mag
		*GetMagAt(unit),
		MagGetter(unit),
		GetClassMagCap(unit->pClassData->number) );
	
	// displaying skl stat value
    DrawStatScreenBar(2, 5, 5,
        gStatScreen.unit->state & US_RESCUING
            ? gStatScreen.unit->skl/2
            : gStatScreen.unit->skl,
        SklGetter(gStatScreen.unit),
		gStatScreen.unit->state & US_RESCUING
			? UNIT_SKL_MAX(gStatScreen.unit)/2
			: UNIT_SKL_MAX(gStatScreen.unit));

    // displaying spd stat value
	DrawStatScreenBar(3, 5, 7,
		gStatScreen.unit->state & US_RESCUING
			? gStatScreen.unit->spd/2
			:gStatScreen.unit->spd,
		SpdGetter(gStatScreen.unit),
		gStatScreen.unit->state & US_RESCUING
			? UNIT_SPD_MAX(gStatScreen.unit)/2
			: UNIT_SPD_MAX(gStatScreen.unit));
	
	
	DrawStatScreenBar(4,5,9,	// Def
		unit->def,
		DefGetter(unit),
		unit->pClassData->maxDef );
	
	DrawStatScreenBar(5,5,11,	// Res
		unit->res,
		ResGetter(unit),
		unit->pClassData->maxRes );
	
	DrawStatScreenBar(6,13,1,	// Lck
		unit->lck,
		LckGetter(unit),
		30 );
	
	DrawStatScreenBar(7,13,3,	// Mov
		unit->pClassData->baseMov,
		MovGetter(unit),
		0xF );
	
	DrawStatScreenBar(9,13,5,	// Con
		unit->pClassData->baseCon + unit->pCharacterData->baseCon,
		ConGetter(unit),
		unit->pClassData->maxCon );
	
	// displaying unit aid
	DrawDecNumber(gBmFrameTmap0 + TILEMAP_INDEX(13, 7), TEXT_COLOR_BLUE,
		GetUnitAid(gStatScreen.unit));

    // displaying unit aid icon
    DrawIcon(gBmFrameTmap0 + TILEMAP_INDEX(14, 7),
        GetUnitAidIconId(UNIT_CATTRIBUTES(gStatScreen.unit)),
        TILEREF(0, STATSCREEN_BGPAL_EXTICONS));
}
