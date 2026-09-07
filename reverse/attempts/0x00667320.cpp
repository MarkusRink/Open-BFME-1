// ?beginPlayerLeave@BFMEConnectionManager@@QAEHE@Z
// partial score=0.9924 date=2026-09-07
// cl: /DNDEBUG /MD /GX
class NetCommandMsg {
public:
 void *vptr; unsigned timestamp,frame,player;unsigned short id;int type,refs;
 void detach();
 unsigned getPlayerID(){return player;} int getNetCommandType(){return type;}
 void setExecutionFrame(unsigned f){frame=f;}void setPlayerID(unsigned p){player=p;}void setID(unsigned short i){id=i;}
};
class BFMENetInformPlayerLeaveFrameCommandMsg:public NetCommandMsg {
public:BFMENetInformPlayerLeaveFrameCommandMsg();void setLeaveFrame(unsigned);void setLeavingPlayerID(int);
 unsigned leaveFrame;int leavingPlayer;
};
class Connection {public:void clearCommandsExceptFrom(int);void setQuitting(unsigned);int quitFrame;};
class FrameDataManager {public:bool getIsQuitting();void setQuitFrame(unsigned);};
class GlobalData {public:char pad[0xcb4];unsigned networkRunAheadSlack;};
extern GlobalData *TheGlobalData;
class GameLogic {public:unsigned getFrame()const{return frame;}char pad[0x3c];unsigned frame;};
extern GameLogic *TheGameLogic;
enum PlayerLeaveCode {PLAYERLEAVE_CLIENT=0,PLAYERLEAVE_LOCAL=1,PLAYERLEAVE_PACKETROUTER=2,PLAYERLEAVE_UNKNOWN=3};
class ConnectionManager {public:PlayerLeaveCode disconnectPlayer(int);void sendLocalCommandDirect(NetCommandMsg*,unsigned char);};
enum NetCommandType {NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME=8};
bool DoesCommandRequireACommandID(NetCommandType);unsigned short GenerateNextCommandID();
void PopulateInGameDiplomacyPopup();
class BFMEConnectionManager {
public:int beginPlayerLeave(unsigned char);
 int isPlayerConnected(int p){if(p==localSlot)goto yes;if(connections[p]==0||connections[p]->quitFrame!=-1)goto no;yes:return 1;no:return 0;}
 char pad0[4];Connection *connections[8];char pad24[0x12004];unsigned localSlot;char pad1202c[0xb8];FrameDataManager*frameData[8];
};
int BFMEConnectionManager::beginPlayerLeave(unsigned char player){
 if(player==localSlot){
  for(int i=0;i<8;++i){if(connections[i]){connections[i]->clearCommandsExceptFrom(localSlot);connections[i]->setQuitting(TheGameLogic->getFrame()+1);}}
 }else{
  unsigned quitFrame=TheGameLogic->getFrame()+1;
  if(connections[player])connections[player]->setQuitting(quitFrame);
  if(frameData[player]&&!frameData[player]->getIsQuitting())frameData[player]->setQuitFrame(quitFrame+TheGlobalData->networkRunAheadSlack);
 }
 PlayerLeaveCode result=((ConnectionManager*)this)->disconnectPlayer(player);
 if(result==PLAYERLEAVE_PACKETROUTER){
  unsigned char mask=0;
  for(int p=0;p<8;++p)if(p!=localSlot&&isPlayerConnected(p))mask|=(unsigned char)(1<<p);
  if(mask){
   BFMENetInformPlayerLeaveFrameCommandMsg*msg=new BFMENetInformPlayerLeaveFrameCommandMsg;
   msg->setExecutionFrame(-1);msg->setPlayerID(localSlot);
   if(DoesCommandRequireACommandID((NetCommandType)msg->getNetCommandType()))msg->setID(GenerateNextCommandID());
   msg->setLeaveFrame(TheGameLogic->getFrame());msg->setLeavingPlayerID(player);
   ((ConnectionManager*)this)->sendLocalCommandDirect(msg,mask);msg->detach();
  }
 }
 PopulateInGameDiplomacyPopup();return result;
}
