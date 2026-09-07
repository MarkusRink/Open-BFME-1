// ?bfme_appendGameOverDetails@GameLogic@@QAEXXZ
// partial score=0.9908 date=2026-09-07
// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <vector>
// Near-exact real C++ for GameLogic::bfme_appendGameOverDetails, not the
// falsely named EstablishConnectionsMenu ledger thunk at this address.
// Boundary 0x00387A50/657 from Ghidra and retail return; peer CRC handler
// 0x0038B597 and gameplay dispatcher 0x00397789 call through ILT0x0004A10B.
// Remaining six concrete byte differences only rotate the three temporary
// receiver address registers after switch-arm StringBase constructors.
// String literals decoded from retail; all REL32 callees resolve with no pins.
// Player+0x348 address check has an unresolved original member name.
#include <stddef.h>
extern "C" __declspec(dllimport) __declspec(nothrow) int __cdecl sprintf(char*,const char*,...);
template<class T>class StringBase {
 friend class AsciiString;
 StringBase():data(0){} StringBase(const T*);StringBase(const StringBase&);~StringBase();
 public: void concat(const char*);
 private: void concat(const char*,int);
 struct Header{int refs;unsigned short length,capacity;T text[1];};Header*data;
};
class AsciiString:private StringBase<char>{
public:
 AsciiString():StringBase<char>(){} AsciiString(const char*p):StringBase<char>(p){}
 AsciiString(const AsciiString&x):StringBase<char>(x){} ~AsciiString(){}
 const char*str()const{return data?data->text:"";}int getLength()const{return data?data->length:0;}
 using StringBase<char>::concat;
 void __cdecl format(AsciiString fmt,...);
};
class PlayerTemplate {public:AsciiString getName()const;};
struct PlayerData{int unused;};
class Player{public:char pad0[4];PlayerTemplate*playerTemplate;char pad8[0x340];PlayerData data;char pad34c[0x138];int quitFrame;};
class PlayerList{public:Player*getNthPlayer(int);};
extern PlayerList*ThePlayerList;
extern char g_rva012F0958PlayerTemplateName[];
struct PlayerLeaveStatus{int status,quitFrame,defeatFrame,victoryFrame;bool notPresent;char pad[3];int isHuman;void*name;};
class GameLogic{
public:
 void bfme_appendGameOverDetails();
 PlayerLeaveStatus*getPlayerLeaveStatus(int i){if(i<0||i>=8)return 0;return &status[i];}
 char pad0[0x54];_STL::vector<AsciiString> lines;char pad60[8];bool appended;char pad69[0x147];PlayerLeaveStatus status[8];
};
void GameLogic::bfme_appendGameOverDetails(){
 if(appended || lines.size()==0)return;
 AsciiString*last=&lines[lines.size()-1];if(!last)return;
 appended=true;
 AsciiString line;
 last->concat("    Game Over Details:\n");
 for(int i=0;i<8;++i){
  PlayerLeaveStatus*info=getPlayerLeaveStatus(i);
  if(info){
   Player*player=ThePlayerList->getNthPlayer(i);
   if(player && &player->data && player->playerTemplate){
    sprintf(g_rva012F0958PlayerTemplateName,"%s",player->playerTemplate->getName().str());
    player->quitFrame=info->quitFrame;
   }
   AsciiString reason;
   switch(info->status){
    case 0:reason.format("n/a");break;
    case 1:reason.format("graceful");break;
    case 2:reason.format("voted out");break;
    default:reason.format("unknown");break;
   }
   if(info->victoryFrame)line.format("      Slot %d: Victory frame: %d, Quit frame: %d(%s)\n",i,info->victoryFrame,info->quitFrame,reason.str());
   else if(info->defeatFrame)line.format("      Slot %d: Defeat frame: %d, Quit frame: %d(%s)\n",i,info->defeatFrame,info->quitFrame,reason.str());
   else if(info->notPresent)line.format("      Slot %d: n/a\n",i);
   else line.format("      Slot %d: Present at final frame\n",i);
  }else line.format("      Slot %d: PlayerLeaveStatus does not exist.\n",i);
  last->concat(line.str(),line.getLength());
 }
}
