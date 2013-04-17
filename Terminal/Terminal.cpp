#include "Terminal.h"

#include <opendnp3/APL/Exception.h>
#include <opendnp3/APL/Thread.h>
#include <opendnp3/APL/Types.h>
#include <opendnp3/APL/IPhysicalLayerAsync.h>
#include <opendnp3/APL/Util.h>
#include <opendnp3/APL/Logger.h>

#include <sstream>
#include <vector>
#include <set>
#include <boost/bind.hpp>
#include <boost/tokenizer.hpp>

#ifdef GetMessage
#undef GetMessage
#endif

using namespace std;
using namespace boost;

namespace apl
{

Terminal::Terminal(Logger* apLogger, IPhysicalLayerAsync* apPhysical, ITimerSource* apTimerSrc, const std::string& arBanner, bool aIOMode) :
	Loggable(apLogger),
	LineReader(apLogger, apPhysical, apTimerSrc, 100),
	mSendBuffer(1024),
	mpPhysical(apPhysical),
	mpTimerSrc(apTimerSrc),
	mpInfiniteTimer(apTimerSrc->StartInfinite()),
	mBanner(arBanner),
	mIOMode(aIOMode)
{
	this->InitCmdHandlers();
	this->Start();
}

void Terminal::InitCmdHandlers()
{
	CommandNode cmd;
	cmd.mHandler = boost::bind(&Terminal::HandleDefault, this, _1);
	this->mCmdRoot.SetValue(cmd);

	////////////////////////
	// help
	////////////////////////

	cmd.mName = "help";
	cmd.mHandler = boost::bind(&Terminal::HandleHelp, this, _1);
	cmd.mUsage = "help [topic] [subtopic 1] ... [subtopic N]";
	cmd.mDesc = "Displays information on a topic.";

	this->BindCommand(cmd, cmd.mName);

	////////////////////////
	// echo
	////////////////////////

	cmd.mName = "echo";
	cmd.mHandler = boost::bind(&Terminal::HandleEcho, this, _1);
	cmd.mUsage = "echo <text to echo>";
	cmd.mDesc = "Echos the argument(s). Useful for producing annotated log files.";

	this->BindCommand(cmd, cmd.mName);

	if (mIOMode) {

		////////////////////////
		// quit
		////////////////////////
		CommandNode quit;
		quit.mName = "quit";
		quit.mHandler = boost::bind(&Terminal::HandleQuit, this, _1);
		quit.mUsage = "quit";
		quit.mDesc = "Terminates the program";

		this->BindCommand(quit, "quit");
	}
	else {

		////////////////////////
		// bye - closes the physical layer
		////////////////////////
		cmd.mName = "bye";
		cmd.mHandler = boost::bind(&Terminal::HandleBye, this, _1);
		cmd.mUsage = "bye";
		cmd.mDesc = "Closes the physical layer";

		this->BindCommand(cmd, "bye");
	}

}

void Terminal::Post(const FunctionVoidZero& arHandler)
{
	mpTimerSrc->Post(arHandler);
}

retcode Terminal::HandleHelp(std::vector<std::string>& arTokens)
{

	if(arTokens.size() > 0) { //help topics were provided
		//figure out what help the user has requested
		TokenNode<CommandNode>* pNode = mCmdRoot.FindNode(arTokens);
		CommandNode* pCmd = pNode->GetValue();

		if(arTokens.size() > 0) { //didn't consume all the tokens, didn't find the topic
			ostringstream oss;
			oss << "No topic found for: " << arTokens[0] << ITerminal::EOL;
			this->QueueSend(oss.str());
		}
		else {
			if(pCmd->mHandler) { // the node is not a command, so print it's subcommands
				this->QueueSend("usage: " + pCmd->mUsage + "\r\n");
				this->QueueSend(pCmd->mDesc + "\r\n");
			}
			else { //the node is a function
				vector<string> subcmds;
				pNode->GetSubNodeNames(subcmds);
				this->PrintSubCommands(pCmd->mName, subcmds);
			}
		}

	}
	else { //dump out all the commands at the root
		vector<string> names;
		deque<string> path;
		mCmdRoot.GetSubNodesWithOptions(names);
		this->QueueSend("usage: help [topic] [subtopic 1] ... [subtopic N]\r\n\r\n");
		for(size_t i = 0; i < names.size(); i++) this->QueueSend(names[i] + "\r\n");
	}

	return SUCCESS;
}

// does recursive lookup on the FullCommand name and popluates the command
// hierarchy
void Terminal::BindCommand(const CommandNode& arNode, const std::string& arFullCommand)
{
	//tokenize the full command name
	typedef boost::tokenizer<boost::char_separator<char> > Tok;
	boost::char_separator<char> sep; // default constructed
	Tok tok(arFullCommand, sep);
	std::vector<std::string> tokens;
	for(Tok::iterator iter = tok.begin(); iter != tok.end(); ++iter) {
		tokens.push_back(*iter);
	}

	// find the deepest tree node
	TokenNode<CommandNode>* pNode = this->mCmdRoot.FindNode(tokens);

	// create interior nodes
	while(tokens.size() > 0) {
		CommandNode node;
		node.mName = tokens[0];
		node.mUsage = node.mDesc = "";
		pNode = pNode->AddToken(tokens[0], node);
		tokens.erase(tokens.begin());
	}

	//when all the nodes are consume
	CommandNode* pCmdNode = pNode->GetValue();

	if(pCmdNode->mHandler) { // if a handler is already set
		throw Exception(LOCATION, "Command already has a bound handler: " + arFullCommand);
	}

	pNode->SetValue(arNode);
}

void Terminal::SendPrompt()
{
	this->QueueSend("\r\n>", false);
}

void Terminal::CheckForSend()
{
	if(mpPhys->CanWrite() && mSendQueue.size() > 0) {
		size_t len = mSendQueue.front().size();
		memcpy(mSendBuffer, mSendQueue.front().c_str(), len);
		mSendQueue.pop_front();
		mpPhys->AsyncWrite(mSendBuffer, len);
	}
}

void Terminal::_Up()
{
	this->QueueSend(mBanner, false);
	this->SendPrompt();
}

void Terminal::_Down()
{
	this->mSendQueue.clear();
}

void Terminal::QueueSend(const std::string& arData, bool aLog)
{
	if(aLog) {
		ERROR_BLOCK(LEV_INFO, "Sent: " << arData, TERMINAL_CODE);
	}
	this->QueueSendRecursive(arData);
}

// break the data into manageable chunks recursively
void Terminal::QueueSendRecursive(const std::string& arData)
{
	if(arData.size() <= mSendBuffer.Size()) {
		this->mSendQueue.push_back(arData);
		this->CheckForSend();
	}
	else {
		this->mSendQueue.push_back(arData.substr(0, mSendBuffer.Size()));
		this->QueueSendRecursive(arData.substr(mSendBuffer.Size())); //tail recursion
	}
}

void Terminal::_OnSendSuccess()
{
	this->CheckForSend();
}

void Terminal::_OnSendFailure()
{
	this->CheckForSend();
}

void Terminal::SetRedirect(const RedirectFunc& arFunc)
{
	mRedirectFunc = arFunc;
}

void Terminal::ClearRedirect()
{
	mRedirectFunc.clear();
}

void Terminal::AcceptLine(const std::string& arLine)
{
	if(mRedirectFunc) mRedirectFunc(arLine);
	else {
		if(this->mSendQueue.size() < 10) this->ProcessLine(arLine);
		else {
			LOG_BLOCK(LEV_WARNING, "Remote side flood");
		}
	}
	if(!mRedirectFunc) this->SendPrompt();
}

retcode Terminal::ProcessLine(const string& arLine)
{
	stringstream ss(arLine); // Insert the string into a stream
	vector<string> tokens; // Create vector to hold our words
	string buf;
	while (ss >> buf) tokens.push_back(buf);

	retcode result = SUCCESS;

	if(tokens.size() > 0) {
		ERROR_BLOCK(LEV_INFO, "Executing: " << arLine, TERMINAL_CODE);
		TokenNode<CommandNode>* pNode = mCmdRoot.FindNode(tokens);
		CommandNode* pCmd = pNode->GetValue();

		if(pCmd->mHandler) {
			result = pCmd->mHandler(tokens);

			if(result == BAD_ARGUMENTS) { //print the usage for this command
				this->QueueSend("usage: " + pCmd->mUsage + "\r\n", false);
			}
		}
		else { //the end node isn't a command, so print it it's subcommands
			vector<string> subcommands;
			pNode->GetSubNodeNames(subcommands);
			this->PrintSubCommands(pCmd->mName, subcommands);
		}
	}
	return result;
}

void Terminal::PrintSubCommands(const string& arCmdName, const vector<string>& arSubCmds)
{
	ostringstream oss;
	oss << arCmdName << " [";
	for(size_t i = 0; i < arSubCmds.size(); i++) {
		oss << arSubCmds[i];
		if( i != (arSubCmds.size() - 1)) oss << "|";
	}
	oss << "]\r\n";
	this->QueueSend(oss.str());
}

void Terminal::PrintClearScreen()
{
	this->QueueSend("\f"); //form feed
}

retcode Terminal::HandleBye(std::vector<std::string>&)
{
	this->Close();
	return SUCCESS;
}

retcode Terminal::HandleDefault(std::vector<std::string>&)
{
	this->QueueSend("Unrecognized command. Type \"help\" for a list of commands.\r\n");
	return BAD_ARGUMENTS;
}

retcode Terminal::HandleQuit(std::vector<std::string>&)
{
	this->mpInfiniteTimer->Cancel();
	this->Shutdown();
	return SUCCESS;
}

retcode Terminal::HandleEcho(std::vector<std::string>& arTokens)
{
	if(arTokens.size() == 0) return BAD_ARGUMENTS;
	std::ostringstream oss;
	for (size_t i = 0; i < arTokens.size(); i++) {
		oss << arTokens[i] << " ";
	}
	this->QueueSend(oss.str());
	return SUCCESS;
}

}

