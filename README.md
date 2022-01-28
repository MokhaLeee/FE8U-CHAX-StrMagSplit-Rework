# FE8U Str/Mag-Split Rework

a decomp-based, Skill-Lite style C-HAX builfile

Compare to existing Str/Mag patch on FE7U or SkillSystem-integrated version, this patch alse use `Unit+0x3A` byte as unit magic status, and `BattleUnit+0x7F` byte as level-up magic status change. the main progress of this rework are:

- `Fix on expand-levelup-screen`:	
It can not be applied on existing str/mag patch to use expanded-screen. Although we can make a window on the screen, it still lies bugs when level up. Here we made it. **BTW**, it's now able to expand to even more unit status up, such as Three House style unit's charm or others. If you want to do so, read the source code inside `Wizardry/CoreHacks/LevelUpRework/LevelUpScreen/src`

- `Decomp-based and fit to Skill-Lite construction`:	
Fit to core-support system of Skill-Lite, includeing Battle-to-Unit-Hook, Load-Unit-Hook and Modular-Level-Up, etc. BTW, all of these base supports are all re-writed in c based on decomp project.
Expanded-modular-save has also been included.
- `Fix on Other bugs`	
Including auto-level, check-cap, etc. I did not work on BattleSystem anymore, since both unit attack calc and weapon attack range will all be re-write on construction of Skill-System, so it's pointless to spend too much time on these issues.


## How to build this file

For Windows users( I use win10, no idea how it works on mac...), you can simply assemble `Main.event` through EventAssembler, just refer to [Ultimate Tutorial 2.0](https://tutorial.feuniverse.us/buildbasics). Or, put FE8U clean rom named `FE8U` in current folder, opne WSL or Msys2(which are inside DevKitPro) at this dolder, and types `sh MakeHack.sh quick`, then you will get a `FE8-CHAX.gba`, which are our hacked rom.

For compiling `Wizardry`, you are recommended to refer to [setup-tips on Skill-Lite](https://github.com/StanHash/SkillsLite/blob/master/SETUP.md):

1. Type `git submodule update --init --recursive` to clone [FE-CLib](https://github.com/StanHash/FE-CLib.git) and [FE-CLib-Decompatible](https://github.com/boviex/FE-CLib-Decompatible) repos in `Tools/`;

2. Create a folder under `Tools/` named `EventAssembler` (no space!) and put [EA file](https://feuniverse.us/t/event-assembler/1749?u=stanh) and [ColorzCore](https://feuniverse.us/t/colorzcore/3970?u=stanh) in this `Tools/EventAssembler`;

3. Put [lyn.exe](https://github.com/StanHash/lyn) at `Tools/EventAssembler/Tools`.

4. Put a FE8U clean rom and open Msys2, type `sh MakeHack.sh all`

## Main ideas on expand levelup screen

1. For vanilla, `gLevelUpStatsBase`(start from 0x2020110, free up to +0x2020132) are used to store both unit base and unit status change on case of Anim-on. Here we just store status-up there, and unit base status are directly loaded from BattleUnit struct.

2. TextHandle struct are not enough for expansion, so I use `gStatScreen.texts[]` for displaying level-up texts.

3. Further reaserach can refer to [my thread](https://feuniverse.us/t/reserach-on-levelup-screen/13098) and [my c-style study](https://feuniverse.us/t/reserach-on-levelup-screen/13098) on level up screen.

## System Structure
- CoreSupport
	- Battle Unit Hook
	- Load Unit Hook
	- Expanded Modular Save
- CoreHacks
	- Modular Status Getter
	- Status Screen
		- Draw Pages (Page Unit)
		- Help Box (Page Unit)	
	-Level Up Rework
		- ModLU: CheckBattleUnitLevelUp
		- Level up Screen
		- Promotion: ApplyUnitPromotion/ promo-diff
		- Auto Level (add unit mag auto-level)
		- Check Cap (add check cap for unit mag level up)
		- Growth Getter	
	- Str/Mag Split core
		- combat (not change this file)
		- Misc Getter (get class mag cap, get unit mag growth, etc)
		- SRAM functions for Mod-Exp-Save
		- Other HookList functions

## Issues

1. There are problems on class name change process when promoting, currently no idea to fix.

## To do

1. Magic Booster
2. Magic Sword rework
3. Weapon bonus of unit mag-status

## Credits
- [Tequila](https://feuniverse.us/u/tequila/summary), the contributer of the 1st version of [FE7 Str/Mag Split](https://feuniverse.us/t/teqs-minor-assembly-shenanigans/1655/20).

- [StanH](https://github.com/StanHash), and [Skill-Lite](https://github.com/StanHash/SkillsLite), [FE-CHAX](https://github.com/StanHash/FE-CHAX) and [C compiling toturials](https://feuniverse.us/t/guide-doc-asm-hacking-in-c-with-ea/3351), etc.

- [Laquieer](https://github.com/laqieer), and [FE8U Decomp](https://github.com/laqieer/fireemblem8u) contribution, [Function-Lib](https://github.com/laqieer/FE_GBA_Function_Library), etc.