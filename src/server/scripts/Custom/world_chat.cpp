#include "ScriptMgr.h"
#include "Player.h"
#include "Chat.h"



class cs_world_chat : public CommandScript
{
        public:
                cs_world_chat() : CommandScript("cs_world_chat"){}
 

				std::vector<ChatCommand> GetCommands() const
				{
					static std::vector<ChatCommand> WorldChatCommandTable =
					{
						{ "w", rbac::RBAC_PERM_COMMAND_WORLD_CHAT, true, &HandleWorldChatCommand, "" },
						{ "chat", rbac::RBAC_PERM_COMMAND_WORLD_CHAT, true, &HandleWorldChatCommand, "" },
					};

					return WorldChatCommandTable;
				}



        static bool HandleWorldChatCommand(ChatHandler * handler, const char * args)
        {
                if (!args)
                        return false;
 
                std::string msg = "";
                Player * player = handler->GetSession()->GetPlayer();
 
                switch(player->GetSession()->GetSecurity())
                {
                        // Player
                        case SEC_PLAYER:
                                if (player->GetTeam() == ALLIANCE)
                                {
                                        msg += "|cff0000ff[Alliance] |cffffffff[";
                                        msg += player->GetName();
                                        msg += "] |cfffaeb00";
                                }
 
                                if (player->GetTeam() == HORDE)
                                {
                                        msg += "|cffff0000[Horde] |cffffffff[";
                                        msg += player->GetName();
                                        msg += "] |cfffaeb00";
                                }
                                break;
                        // Moderator/trial
                        case SEC_MODERATOR:
                                msg += "|cffff8a00[Mod] |cffffffff[";
                                msg += player->GetName();
                                msg += "] |cfffaeb00";
                                break;
                        // GM
                        case SEC_GAMEMASTER:
                                msg += "|cff00ffff[GM] |cffffffff[";
                                msg += player->GetName();
                                msg += "] |cfffaeb00";
                                break;
                        // Admin
                        case SEC_ADMINISTRATOR:
                                msg += "|cfffa9900[Admin] |cffffffff[";
                                msg += player->GetName();
                                msg += "] |cfffaeb00";
                                break;
 
                }
                       
                msg += args;
                sWorld->SendServerMessage(SERVER_MSG_STRING, msg.c_str(), 0);  
 
                return true;
        }
};
 
void AddSC_cs_world_chat()
{
        new cs_world_chat();
}